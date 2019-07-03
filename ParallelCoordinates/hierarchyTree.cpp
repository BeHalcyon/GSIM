#include "hierarchyTree.h"
#include <queue>

const float PI = 3.14159265358;
HierarchyTree::HierarchyTree(QList<QColor> cs)
{
	setAutoFillBackground(true);
	QPalette p;
	p.setBrush(backgroundRole(), QBrush(QColor(255, 255, 255)));
	setPalette(p);
	colors = cs;
	combox = new QComboBox(this);
	treeRoot = NULL;
	connect(combox, SIGNAL(currentIndexChanged(int)), this, SLOT(getSelectVariate(int)));
}

HierarchyTree::~HierarchyTree()
{
}

QSize HierarchyTree::minimumSizeHint() const
{
	return QSize(512, 512);
}

QSize HierarchyTree::sizeHint() const
{
	return QSize(512, 512);
}

void HierarchyTree::paintEvent(QPaintEvent* event)
{
	if (!treeRoot) return;
	cout << "hierarchyTree" << endl;
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing);
	p.setRenderHint(QPainter::HighQualityAntialiasing);
	QPen pen;
	//pen.setColor(Qt::gray);
	//p.setPen(pen);
	float radius = width() / 2.0 / (maxlevel + 1);
	qreal sr = 254, sg = 204, sb = 92;
	qreal er = 189, eg = 0, eb = 38;
	for (int k = 0; k < tNodes.size(); k++)
	{
		TreeNode* parent = tNodes[k];
		for (int i = 0; i < parent->children.size(); i++)
		{
			float radio = parent->children[i]->correlate;
			QColor c = QColor(sr * (1 - radio) + er * radio,
				sg * (1 - radio) + eg * radio,
				sb * (1 - radio) + eb * radio);
			p.setPen(c);
			p.setBrush(c);
			p.drawLine(parent->pos, parent->children[i]->pos);
			//qreal angle = parent->children[i]->start_angle;
			////p.translate(parent->children[i]->pos);
			//p.translate(parent->pos);
			//if(angle > 90 && angle < 270)
			//{
			//	p.rotate(angle - 180);
			//	p.translate(-radius * 0.6, 0);
			//}
			//else
			//{
			//	p.rotate(angle);
			//	p.translate(5, 0);
			//}
			////p.drawText(0, 0,variateNames[parent->children[i]->attributeNo]);
			//QString str = QString::number(parent->children[i]->correlate);
			//p.drawText(0, 0,str);
			//p.resetMatrix();
		}
	}

	pen.setColor(QColor(81, 137, 184));
	pen.setWidth(1);
	p.setPen(pen);
	for (int i = 0; i < tNodes.size(); i++)
	{
		p.setBrush(colors[tNodes[i]->attributeNo]);
		p.drawEllipse(tNodes[i]->pos, 5, 5);
	}
}

void HierarchyTree::destroyTree(TreeNode* node)
{
	if (node == NULL) return;
	for (int i = 0; i < node->children.size(); i++)
	{
		destroyTree(node->children[i]);
	}
	node->children.clear();
	if (node->children.size() == 0)
	{
		delete node;
		return;
	}
}

void HierarchyTree::getSelectedClusters(vector<vector<int>> attributesets)
{
	destroyTree(treeRoot);
	tNodes.clear();
	treeRoot = new TreeNode(selectAttributeNo, NULL);
	tNodes.push_back(treeRoot);
	treeRoot->level = 0;
	maxlevel = 0;
	vector<int> t_attributeset;
	float maxcorr = FLT_MIN;
	float mincorr = FLT_MAX;
	for (int i = 0; i < attributesets.size(); i++)
	{
		vector<int> attributeset = attributesets[i];
		TreeNode* parent = treeRoot;
		t_attributeset.clear();
		t_attributeset.push_back(selectAttributeNo);
		for (int j = 0; j < attributeset.size(); j++)
		{
			TreeNode* node;
			t_attributeset.push_back(attributeset[j]);
			int k = 0;
			for (; k < parent->children.size(); k++)
			{
				if (parent->children[k]->attributeNo == attributeset[j])
				{
					node = parent->children[k];
					break;
				}
			}
			if (k == parent->children.size())
			{
				node = new TreeNode(attributeset[j], parent);
				node->level = parent->level + 1;
				float corr;
				emit getCorrelation(t_attributeset, corr);
				if (corr > maxcorr) maxcorr = corr;
				if (corr < mincorr) mincorr = corr;
				node->correlate = corr;
				if (node->level > maxlevel) maxlevel = node->level;
				tNodes.push_back(node);
				parent->children.push_back(node);
			}

			parent = node;
		}
	}
	for (int i = 0; i < tNodes.size(); i++)
	{
		tNodes[i]->correlate = pow((tNodes[i]->correlate - mincorr) / (maxcorr - mincorr), 0.5);
	}
	int* nexts = new int[maxlevel + 1];
	int* offset = new int[maxlevel + 1];
	for (int i = 0; i < maxlevel + 1; i++)
	{
		nexts[i] = 0;
		offset[i] = 0;
	}
	setup(treeRoot, 0, nexts, offset);
	delete[]nexts;
	delete[]offset;
	addmods(treeRoot);
	toPolarCoord();
	update();
}

void HierarchyTree::setup(TreeNode* node, int depth, int* nexts, int* offset)
{
	for (int i = 0; i < node->children.size(); i++)
		setup(node->children[i], depth + 1, nexts, offset);
	node->y = depth;
	int place;
	if (node->children.size() == 0)
	{
		place = nexts[depth];
		node->x = place;
	}
	else if (node->children.size() == 1)
	{
		place = node->children[0]->x;
	}
	else
	{
		int s = (node->children[0]->x + (*(node->children.end() - 1))->x) / 2;
		place = s;
	}
	offset[depth] = max(offset[depth], nexts[depth] - place);
	if (node->children.size() > 0)
		node->x = place + offset[depth];
	nexts[depth] = (node->x + 2);
	node->mod = offset[depth];
}

void HierarchyTree::addmods(TreeNode* node, int modsum /* = 0*/)
{
	node->x += modsum;
	modsum += node->mod;

	for (int i = 0; i < node->children.size(); i++)
	{
		addmods(node->children[i], modsum);
	}
}

void HierarchyTree::toPolarCoord()
{
	vector<TreeNode*>::iterator iter = treeRoot->children.end() - 1;
	float delta_theta = 360.0 / ((*iter)->x + 1);
	float delta_rho = width() / 2.0 / (maxlevel + 1);
	float centerx = width() / 2.0;
	float centery = height() / 2.0;
	queue<TreeNode*> stack;
	stack.push(treeRoot);
	while (!stack.empty())
	{
		TreeNode* parent = stack.front();
		stack.pop();
		float xx = parent->x;
		float yy = parent->y;
		float theta = delta_theta * xx;
		float rho = delta_rho * yy;
		parent->start_angle = delta_theta * xx;
		parent->pos.setX(centerx + delta_rho * yy * cos(delta_theta * xx / 180 * PI));
		parent->pos.setY(centery + delta_rho * yy * sin(delta_theta * xx / 180 * PI));
		//parent->x = centerx + delta_rho * 1.3 * yy * cos(delta_theta * xx / 180 * PI);
		//parent->y = centery + delta_rho * 1.3 * yy * sin(delta_theta * xx / 180 * PI);
		for (int i = 0; i < parent->children.size(); i++)
		{
			stack.push(parent->children[i]);
		}
	}
}

void HierarchyTree::getVarianteNames(QStringList variatenames)
{
	variateNames = variatenames;
	combox->insertItems(0, variatenames);
}

void HierarchyTree::getSelectVariate(int No)
{
	selectAttributeNo = No;
	emit sendSelectedVariate(No);
}

void HierarchyTree::mouseDoubleClickEvent(QMouseEvent * event)
{
	QPointF spot(event->x(), event->y());
	for (int i = 0; i < tNodes.size(); i++)
	{
		TreeNode* node = tNodes[i];
		if (spot.x() >= node->pos.x() - 5 && spot.x() <= node->pos.x() + 5
			&& spot.y() >= node->pos.y() - 5 && spot.y() <= node->pos.y() + 5)
		{
			vector<int> attributenos;
			TreeNode* p = node;
			while (true)
			{
				attributenos.push_back(p->attributeNo);
				p = p->parent;
				if (p == NULL) break;
			}
			emit sendSelectedVariates(attributenos);
			break;
		}
	}
}