#include "setView.h"
#include <queue>

SetView::SetView()
{
	//this->setMinimumSize(QSize(360, 700));
	//this->setMaximumSize(QSize(360, 3000));

	isHiden = true;
	currenty = 0;
	scale = 1.0;
	currentItem = NULL;
	isSubsetsContained = false;
	isJaccardUsed = false;

	setAutoFillBackground(true);
	setMouseTracking(true);
	QPalette p;
	p.setBrush(backgroundRole(), QBrush(QColor(255, 255, 255)));
	setPalette(p);

	firstSortType = 0;
	secondSortType = 0;
	sortTypeColors.push_back(QColor(60, 60, 60));
	sortTypeColors.push_back(QColor(189, 189, 189));
	sortTypeColors.push_back(QColor(136, 136, 136));
	sortTypeColors.push_back(QColor(95, 95, 95));
	//Debug 20180202 增加颜色
	sortTypeColors.push_back(QColor(30, 30, 30));
}

SetView::~SetView()
{

}

// p0---p2
//  \   /
//    p1
QPainterPath trianglePath(float scale)
{
	QPainterPath path;
	QPointF p0(0, 0);
	QPointF p1(5, 5);
	QPointF p2(10, 0);
	path.moveTo(p0 * scale);
	path.lineTo(p1 * scale);
	path.lineTo(p2 * scale);
	path.lineTo(p0 * scale);
	return path;
}


void SetView::updateLayout()
{
	for (int i = 0; i < items.size(); i++)
	{
		items[i]->xoffset = 0;
		items[i]->ypos = -100;
	}
	int xpos = 0;
	int ypos = 10;
	int count = 0;
	for (int i = 0; i < topLevelItems.size(); i++)
	{
		if (topLevelItems[sortorder[i]]->variateset->amount == 0)
			count++;
		computeItemPos(topLevelItems[sortorder[i]], xpos, ypos);	
	}
	//resize(400, ypos);
	update();
}

void SetView::computeItemPos(TreeItem* item, int xoffset, int& ypos)
{
	if (item->variateset->subset.size() < mindegree)
		return;
	if (item->variateset->subset.size() > maxdegree)
		return;
	if (isHiden && item->variateset->amount == 0)
		return;
	item->xoffset = xoffset;
	item->ypos = ypos;
	ypos += 30;
	if (item->isExpanded)
	{
		vector<int> secondorder;
		for (int i = 0; i < item->children.size(); i++)
		{
			secondorder.push_back(i);
		}
		if (secondSortType == 0)
			sort(secondorder.begin(), secondorder.end(), DegreeOrder(item->children));
		else if (secondSortType == 1)
			sort(secondorder.begin(), secondorder.end(), AmountOrder(item->children));
		else if (secondSortType == 2)
			sort(secondorder.begin(), secondorder.end(), CorreleteOrder(item->children));
		else if (secondSortType == 3)
			sort(secondorder.begin(), secondorder.end(), CoherentOrder(item->children));
		for (int i = 0; i < item->children.size(); i++)
		{
			computeItemPos(item->children[secondorder[i]], xoffset + 15, ypos);
		}
	}

}


void SetView::paintEvent(QPaintEvent* event)
{
	QPainter p(this);
	p.setRenderHint(QPainter::HighQualityAntialiasing);

	////////highlight item
	if (currentItem && !currentItem->isExpanded)
	{
		set<int> vset = currentItem->variateset->subset;
		p.setPen(Qt::NoPen);
		p.setBrush(QColor(254, 208, 145));
		for (set<int>::iterator it = vset.begin(); it != vset.end(); it++)
		{
			p.drawRect(80 - nodewidth / 2.0 + (*it) * nodewidth, 0, nodewidth, 10000);
		}
		p.setPen(QColor(95, 95, 95));
		p.drawRect(80 - nodewidth / 2.0 - 3, currentItem->ypos - nodewidth / 2.0, 400, nodewidth);
	}


	//////set nodes for every items
	int ypos = 230;
	int count = 0;
	for (int i = 0; i < items.size(); i++)
	{
		p.setBrush(Qt::SolidPattern);
		TreeItem* treeitem = items[i];
		if (treeitem->ypos < 0)
			continue;
		count++;
		set<int> variateset = treeitem->variateset->subset;
		int xoffset = treeitem->xoffset;
		int ypos = treeitem->ypos;
		int nodesize;

		p.setBrush(QColor(240, 240, 240));
		p.setPen(QColor(235, 235, 235));
		if (treeitem->isExpanded)
		{
			p.drawRoundedRect(QRectF(0, ypos - nodewidth / 2.0, 400, nodewidth), 5, 5);
			p.setBrush(QColor(95, 95, 95));
			QPainterPath triangle = trianglePath(1.0);
			p.setPen(Qt::NoPen);
			p.translate(5 + xoffset, ypos - 5);
			p.drawPath(triangle);
			p.resetMatrix();
			nodesize = 0.32 * nodewidth;
		}
		else
		{
			nodesize = 0.8 * nodewidth;
			p.setPen(Qt::NoPen);
			p.setBrush(QColor(240, 240, 240));
		}

		//////not occupy
		for (int j = 0; j < variatenames.size(); j++)
		{
			int xpos = 80 + j * nodewidth;
			p.drawEllipse(xpos - nodesize / 2, ypos - nodesize / 2, nodesize, nodesize);
		}

		//////occupy
		p.setBrush(QColor(95, 95, 95));
		if (treeitem->isExpanded)
			nodesize = 0.64 * nodewidth;
		else
			nodesize = 0.8 * nodewidth;
		for (set<int>::iterator it = variateset.begin(); it != variateset.end(); it++)
		{
			int xpos = 80 + (*it) * nodewidth;
			p.drawEllipse(xpos - nodesize / 2, ypos - nodesize / 2, nodesize, nodesize);
		}

		//////draw sort type bar

		int sorttype;
		int barheight;
		int barwidth = 400 - (80 + variatenames.size() * nodewidth * 0.8) - 10;
		if (xoffset == 0)
		{
			sorttype = firstSortType;
			barheight = 0.8 * nodewidth;
		}
		else
		{
			sorttype = secondSortType;
			barheight = 0.4 * nodewidth;
		}
		float setsize = -1;
		if (sorttype == 1) setsize = treeitem->variateset->amount;
		if (sorttype == 2) setsize = treeitem->variateset->correlation;
		if (sorttype == 3) setsize = treeitem->variateset->coherent;
		if (sorttype == 4)setsize = treeitem->variateset->correlationPearson;
		QColor sortColor = sortTypeColors[sorttype];
		if (setsize < 0)
		{
			//p.setBrush(QBrush(sortColor, Qt::FDiagPattern));
			//p.drawRect(QRectF(80 + variateNames.size() * 25, ypos - barheight / 2, 150.0, barheight));
		}
		else
		{
			p.setBrush(QBrush(sortColor, Qt::SolidPattern));
			p.drawRect(QRectF(80 + variatenames.size() * nodewidth, ypos - barheight / 2, setsize * barwidth, barheight));
		}

		if (treeitem == selectedItem)
		{
			p.setBrush(Qt::NoBrush);
			p.setPen(Qt::black);
			p.drawRect(QRectF(80 - nodewidth / 2.0 - 3, ypos - nodewidth / 2.0, variatenames.size() * nodewidth + 200, nodewidth));
		}

		if (treeitem->variateset->visited)
		{
			p.setBrush(QColor(122, 185, 0));
			QPainterPath triangle = trianglePath(1.5);
			p.setPen(Qt::NoPen);
			p.translate(65, ypos + 2.5);
			p.rotate(180);
			p.drawPath(triangle);
			p.resetMatrix();
		}
	}
}

QSize SetView::minimumSizeHint() const
{
	return QSize(400, 9000);
}

QSize SetView::sizeHint() const
{
	return QSize(400, 9000);
}

void SetView::getVarianteNames()
{
	scale = 1 - 0.04 * (variatenames.size() - 5);
	nodewidth = 25 * scale;

	set<int> s;
	TreeItem* rootitem = new TreeItem(new VariateSet(s), 0);
	queue<TreeItem*> que;
	que.push(rootitem);

	//////top level items
	while (!que.empty())
	{
		TreeItem* treeitem = que.front();
		que.pop();
		if (treeitem->variateset->subset.size() == maxLevel)
			continue;
		set<int>::iterator it = treeitem->variateset->subset.end();
		int i;
		if (treeitem->variateset->subset.size() == 0)
			i = 0;
		else
		{
			it--;
			i = (*it) + 1;
		}
		for (; i < variatenames.size(); i++)
		{

			VariateSet* child_variateset;
			set<int> vset = treeitem->variateset->subset;
			vset.insert(i);
			if (vset.size() <= treeitem->variateset->subset.size())
				continue;
			std::stringstream result;
			std::copy(vset.begin(), vset.end(), std::ostream_iterator<int>(result, "_"));
			string str = result.str();

			child_variateset = new VariateSet(vset);
			hash[str] = child_variateset;

			TreeItem* child = new TreeItem(child_variateset, 1);
			que.push(child);
			topLevelItems.push_back(child);
		}
	}

	///////child items
	int iter = 2;
	vector<TreeItem*> temp_res = topLevelItems;
	items = topLevelItems;
	while (iter <= 3)
	{
		vector<TreeItem*> inter_res;
		for (int i = 0; i < temp_res.size(); i++)
		{
			TreeItem* item = temp_res[i];
			for (int j = 0; j < variatenames.size(); j++)
			{
				set<int> vset = item->variateset->subset;
				vset.insert(j);
				if (vset.size() <= item->variateset->subset.size() || vset.size() > maxLevel)
					continue;
				std::stringstream result;
				std::copy(vset.begin(), vset.end(), std::ostream_iterator<int>(result, "_"));
				string str = result.str();
				VariateSet* v = hash[str];
				TreeItem* child = new TreeItem(v, iter);
				item->children.push_back(child);
				inter_res.push_back(child);
			}
		}
		temp_res = inter_res;
		items.insert(items.end(), inter_res.begin(), inter_res.end());
		iter++;
	}
}

void SetView::getVariateSubsets(vector<VSubset> subsets_)
{
	subsets = subsets_;
	getSubsetsProperties();
}

void SetView::getSubsetsProperties()
{
	float maxcorr = 0;
	float maxcorrPearson = 0;
	float maxcoh = 0;
	float maxamout = 0;
	int totalElements = 0;

	for (int i = 0; i < subsets.size(); i++)
	{
		totalElements += subsets[i].second;
		string str = subsets[i].first;
		for (map<string, VariateSet*>::iterator it = hash.begin(); it != hash.end(); it++)
		{
			if ((!isSubsetsContained && str == it->first) ||
				(isSubsetsContained && it->first.find(str) != std::string::npos))
				it->second->amount += subsets[i].second;
		}
	}

	for (map<string, VariateSet*>::iterator it = hash.begin(); it != hash.end(); it++)
	{
		VariateSet* vset = (*it).second;
		vset->visited = false;
		float corr;
		vector<int> variateset(vset->subset.begin(), vset->subset.end());
		getCorrelation(variateset, corr);
		vset->correlation = corr;
		if (corr > maxcorr) maxcorr = corr;

		//Get Pearson
		float corrPearson;
		getCorrelationPearson(variateset, corrPearson);
		vset->correlationPearson = corrPearson;
		if (corrPearson > maxcorrPearson) maxcorrPearson = corrPearson;

		float coh;
		getCoherence(variateset, coh);
		vset->coherent = coh;
		if (coh > maxcoh) maxcoh = coh;
		if (vset->amount > maxamout) maxamout = vset->amount;
	}

	sortorder.clear();
	for (int i = 0; i < topLevelItems.size(); i++)
	{
		//////uniform three kinds of characteristic
		//topLevelItems[i]->variateset->amount /= totalElements;
		topLevelItems[i]->variateset->amount /= maxamout;
		
		if (topLevelItems[i]->variateset->coherent < 0)
			topLevelItems[i]->variateset->coherent = 1.0;
		else
			topLevelItems[i]->variateset->coherent /= maxcoh;
		//Question 为什么会小于0
		topLevelItems[i]->variateset->correlation /= maxcorr;

		topLevelItems[i]->variateset->correlationPearson /= maxcorrPearson;

		sortorder.push_back(i);
	}

	updateSortType(firstSortType);
}
void SetView::updateSortType(int type)
{
	firstSortType = type;
	sortorder.clear();
	for (int i = 0; i < topLevelItems.size(); i++)
	{
		sortorder.push_back(i);
	}

	if (type == 0) //degree
	{
		sort(sortorder.begin(), sortorder.end(), DegreeOrder(topLevelItems));
	}
	else if (type == 1) //amount
	{
		sort(sortorder.begin(), sortorder.end(), AmountOrder(topLevelItems));
	}
	else if (type == 2) //mutual information
	{
		sort(sortorder.begin(), sortorder.end(), CorreleteOrder(topLevelItems));
	}
	else if (type == 3) //residue
	{
		sort(sortorder.begin(), sortorder.end(), CoherentOrder(topLevelItems));
	}
	else if (type == 4)//pearson
	{
		sort(sortorder.begin(), sortorder.end(), CorreletePearsonOrder(topLevelItems));
	}
	updateLayout();
}

void SetView::updateSecondSortType(int type)
{
	secondSortType = type;
	updateLayout();
}

void SetView::mouseMoveEvent(QMouseEvent *event)
{
	TreeItem* item = NULL;
	for (int i = 0; i < items.size(); i++)
	{
		if (event->y() >= items[i]->ypos - nodewidth / 2 && event->y() <= items[i]->ypos + nodewidth / 2)
		{
			item = items[i];
			break;
		}
	}
	currentItem = item;
	update();
	if (currentItem)
	{
		emit currentset(currentItem->variateset->subset);
	}
	else
	{
		set<int> tmp;
		emit currentset(tmp);
	}
	////cout << item->ypos << endl;
}

void SetView::mousePressEvent(QMouseEvent * event)
{
	TreeItem* item = NULL;
	for (int i = 0; i < items.size(); i++)
	{
		if (event->y() >= items[i]->ypos - nodewidth / 2 && event->y() <= items[i]->ypos + nodewidth / 2)
		{
			item = items[i];
			break;
		}
	}
	if (item == NULL)  return;
	item->isExpanded = !(item->isExpanded);
	updateLayout();
}

void SetView::mouseDoubleClickEvent(QMouseEvent *event)
{
	TreeItem* item = NULL;
	for (int i = 0; i < items.size(); i++)
	{
		if (event->y() >= items[i]->ypos - nodewidth / 2 && event->y() <= items[i]->ypos + nodewidth / 2)
		{
			item = items[i];
			break;
		}
	}
	if (item == NULL)  return;
	vector<int> subset(item->variateset->subset.begin(), item->variateset->subset.end());
	emit sendSelectedSubset(subset);
	item->variateset->visited = true;
	selectedItem = item;
	item->isExpanded = !(item->isExpanded);
	update();
}

void SetView::setMaxDegree(const QString & maxd)
{
	maxdegree = maxd.toInt();
	updateLayout();
}

void SetView::setMinDegree(const QString & mind)
{
	mindegree = mind.toInt();
	updateLayout();
}

void SetView::getMaxLevel(int maxl)
{
	maxLevel = maxl;
	maxdegree = maxl;
	mindegree = 1;
	getVarianteNames();
}

void SetView::setHideEmpty(int hiden)
{
	isHiden = hiden;
	updateLayout();
}

void SetView::subsetsContainChanged(int iscontained_)
{
	isSubsetsContained = iscontained_;
	vector<int> subset(selectedItem->variateset->subset.begin(), selectedItem->variateset->subset.end());
	getSubsetsProperties();
	emit sendSelectedSubset(subset);
}

//void SetView::setJaccardDistance(int isJaccardUsed_) {
//	isJaccardUsed = isJaccardUsed_;
//	emit sendJaccardDistanceUsed(isJaccardUsed_);
//}