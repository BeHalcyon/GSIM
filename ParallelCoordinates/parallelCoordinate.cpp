#include "parallelCoordinate.h"
#include "define.h"
#include <QScreen>
#include <QApplication>
#include <QAction>
#include <set>
#include <algorithm>
#include <QMenu>

ParallelCoordinate::ParallelCoordinate(QList<QColor> colors)
{
	attributeColors = colors;
	setAutoFillBackground(true);
	QPalette p;
	p.setBrush(backgroundRole(), QBrush(QColor(255, 255, 255)));
	setPalette(p);
	axisNum = 0;
	displayManner = 0;
	//setAttribute(Qt::WA_PaintOnScreen);
	frashNum = 0;
	currentID = 0;
	isGlobal = false;
}

ParallelCoordinate::~ParallelCoordinate()
{
}

void ParallelCoordinate::paintEvent(QPaintEvent* event)
{
	if ((Gvoxels.size() == 0 && voxelIdx.size() < 1) || axisNum <= 1) return;

	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing, true);

	int axes = axisNum;
	if (displayManner == 1) axes = attributeIdx.size();
	else if (displayManner == 2) axes = dimensionalOrder.size();

	float deltax = width() / (axisNum + 1);
	//float deltax = 100.0;
	float deltay = height() - 60;
	vector<int> vIdx;
	QColor c;
	p.setBrush(Qt::NoBrush);

	for (int k = 0; k < gobal_pc_maps.size(); k++)
	{
		vector<map<pair<float, float>, int>>& pc_maps = gobal_pc_maps[k];
		vector<pair<int,int>>& maxd = maxds[k];
		c = Gvoxels.size() == 1 ? QColor(77, 181, 255) : featurecolors[k];
		for (int i = 0; i < pc_maps.size(); i++)
		{
			map<pair<float, float>, int>& pc_map = pc_maps[i];
			float max_d1 = maxd[i].first, max_d2 = maxd[i].second;
			for (map<pair<float, float>, int>::iterator iter = pc_map.begin(); iter != pc_map.end(); iter++)
			{
				//c.setAlphaF(0.01);
				//p.setPen(c);
				QPointF st((i + 1) * deltax, height() - 30.0 - iter->first.first / 255.0 * deltay);
				QPointF ed((i + 2) * deltax, height() - 30.0 - iter->first.second / 255.0 * deltay);
				float st_alpha = iter->second / max_d1;
				float ed_alpha = iter->second / max_d2;
				QLinearGradient linearGradient(st, ed);
				for (int j = 0; j <= 100; j++)
				{
					linearGradient.setColorAt(j / 100.0, QColor(c.red(), c.green(), c.blue(), (st_alpha + (ed_alpha - st_alpha) * j / 100.0) * 255));
				}
				p.setPen(QPen(QBrush(linearGradient), 1));
				p.drawLine(st, ed);
			}
		}
	}

	for (int i = 0; i < axes; i++)
	{
		int idx = i;
		if (displayManner == 1) idx = attributeIdx[i];
		else if (displayManner == 2) idx = dimensionalOrder[i];

		//draw axes
		p.setPen(QColor(0, 0, 0, 255));
		p.drawLine((i + 1) * deltax, height() - 30.0, (i + 1) * deltax, height() - 30.0 - deltay);
		//draw scale 0~10
		for (int k = 0; k <= 10; k++)
		{
			p.drawLine((i + 1) * deltax - 5, height() - 30.0 - deltay / 10.0 * k, (i + 1) * deltax, height() - 30.0 - deltay / 10.0 * k);
		}

		//draw text
		p.setPen(QColor(0, 0, 0, 255));
		QFont font;
		font.setPixelSize(15);
		font.setBold(false);
		p.setFont(font);

		if (displayManner == 0)
		{
			vector<int>::iterator iter = std::find(attributeIdx.begin(), attributeIdx.end(), i);
			if (iter != attributeIdx.end())
			{
				p.setPen(QColor(255, 0, 0, 255));
				font.setBold(true);
				p.setFont(font);
			}
		}
		int textpos = variatenames[i].indexOf(".");
		QString text = variatenames[idx].left(textpos);
		QFontMetricsF fm = p.fontMetrics();
		qreal pixelsWide = fm.width(text);
		qreal pixelsHigh = fm.height();
		QPointF drawpos = QPointF((i + 1) * deltax, 25.0) + QPointF(-pixelsWide / 2.0, -pixelsHigh / 2.0);
		//current TF ID
		/*if (idx == currentID)
		p.drawRect(drawpos.x(), drawpos.y() - pixelsHigh + 3, pixelsWide, pixelsHigh);*/
		p.drawText(drawpos, text);

		QPainterPath left_path;
		QPainterPath right_path;
		left_path.moveTo((i + 1) * deltax, height() - 30.0);
		right_path.moveTo((i + 1) * deltax, height() - 30.0);

		if (Gvoxels.size() > 1) continue;

		vector<int>& count = counts[i];
		float max_density = maxc[i];
		for (int j = 1; j < 256; j++)
		{
			float delta = count[j] / max_density * deltax / 5.0;
			left_path.lineTo((i + 1) * deltax - delta, height() - 30.0 - j / 255.0 * deltay);
			right_path.lineTo((i + 1) * deltax + delta, height() - 30.0 - j / 255.0 * deltay);

		}
		left_path.lineTo((i + 1) * deltax, height() - 30.0 - deltay);
		right_path.lineTo((i + 1) * deltax, height() - 30.0 - deltay);
		QColor c = QColor(70, 129, 179);
		QPainterPath path(left_path + right_path.toReversed());

		c.setAlphaF(0.6);
		p.setBrush(c);
		p.setPen(Qt::black);
		p.drawPath(path);
	}

	for (int i = 0; i < sRegin.size(); i++)
	{
		QRectF rect((sRegin[i].selectNo + 1) * deltax - 10, sRegin[i].startY, 20, sRegin[i].endY - sRegin[i].startY);
		p.setBrush(QColor(179, 179, 179, 125));
		p.setPen(Qt::white);
		p.drawRect(rect);
	}

	p.setPen(QColor(0, 0, 0, 255));
	QFont font;
	font.setPixelSize(15);
	font.setBold(false);
	p.setFont(font);
	p.drawText(20, 20, "high");
	p.drawText(20, height() - 20, "low");
}

QSize ParallelCoordinate::minimumSizeHint() const
{
	return QSize(1024, 300);
}

void ParallelCoordinate::setVolDatas(vector<Volume *>& vols)
{
	axisNum = vols.size();
	volDatas = vols;
}

void ParallelCoordinate::setClusterVoxels(vector<int> voxels, vector<int> attributes)
{
	isGlobal = false;
	Gvoxels.clear();
	Gvoxels.push_back(voxels);
	attributeIdx = attributes;
	dimensionalOrder = attributeIdx;
	for (int i = 0; i < axisNum; i++)
	{
		vector<int>::iterator iter = std::find(attributes.begin(), attributes.end(), i);
		if (iter == attributes.end())
			dimensionalOrder.push_back(i);
	}
	sRegin.clear();
	calDistribution();
	update();
}

void ParallelCoordinate::setGlobalClusters(vector<vector<int>> gvoxels, vector<vector<int>> gattributes)
{
	isGlobal = true;
	Gvoxels = gvoxels;
	Gattributes = gattributes;
	set<int> attributes;
	for (int i = 0; i < gattributes.size(); i++)
	{
		for (int j = 0; j < gattributes[i].size(); j++)
		{
			attributes.insert(gattributes[i][j]);
		}
	}
	dimensionalOrder.resize(attributes.size());
	copy(attributes.begin(), attributes.end(), dimensionalOrder.begin());
	for (int i = 0; i < axisNum; i++)
	{
		vector<int>::iterator iter = std::find(dimensionalOrder.begin(), dimensionalOrder.end(), i);
		if (iter == dimensionalOrder.end())
			dimensionalOrder.push_back(i);
	}
	calDistribution();
	update();
}

void ParallelCoordinate::calDistribution()
{
	gobal_pc_maps.clear();
	maxds.clear();
	counts.clear();
	maxc.clear();

	int axes = axisNum;
	if (displayManner == 1) axes = attributeIdx.size();
	else if (displayManner == 2) axes = dimensionalOrder.size();
	for (int k = 0; k < Gvoxels.size(); k++)
	{
		vector<map<pair<float, float>, int>> pc_maps;
		vector<int>& vIdx = Gvoxels[k];
		vector<pair<int, int>> maxd;
		for (int i = 0; i < axes - 1; i++)
		{
			map<pair<float, float>, int> pc_map;
			map<pair<float, float>, int>::iterator iter;
			uchar* v1 = volDatas[i]->getVolume();
			uchar* v2 = volDatas[i + 1]->getVolume();
			if (displayManner == 1)
			{
				v1 = volDatas[attributeIdx[i]]->getVolume();
				v2 = volDatas[attributeIdx[i + 1]]->getVolume();
			}
			else if (displayManner == 2)
			{
				v1 = volDatas[dimensionalOrder[i]]->getVolume();
				v2 = volDatas[dimensionalOrder[i + 1]]->getVolume();
			}
			else
			{
				v1 = volDatas[i]->getVolume();
				v2 = volDatas[i + 1]->getVolume();
			}

			vector<int> dim1(256, 0), dim2(256, 0);
			for (int j = 0; j < vIdx.size(); j++)
			{
				int idx = vIdx[j];
				int s1 = v1[idx];
				int s2 = v2[idx];
				dim1[s1]++;
				dim2[s2]++;
				iter = pc_map.find(make_pair(s1, s2));
				if (iter != pc_map.end())
					pc_map[make_pair(s1, s2)]++;
				else
					pc_map[make_pair(s1, s2)] = 1;
			}
			pc_maps.push_back(pc_map);
			float max_d1 = 0, max_d2 = 0;
			for (int j = 0; j < dim1.size(); j++)
			{
				if (dim1[j] > max_d1) max_d1 = dim1[j];
				if (dim2[j] > max_d2) max_d2 = dim2[j];
			}
			maxd.push_back(make_pair(max_d1, max_d2));
		}
		gobal_pc_maps.push_back(pc_maps);
		maxds.push_back(maxd);
	}

	if (Gvoxels.size() > 1)
		return;
	for (int i = 0; i < axes; i++)
	{
		int idx = i;
		if (displayManner == 1) idx = attributeIdx[i];
		else if (displayManner == 2) idx = dimensionalOrder[i];

		uchar* v1 = volDatas[idx]->getVolume();
		vector<int> count(256, 0);
		int iter = Gvoxels.empty() ? 1 : Gvoxels.size();

		for (int k = 0; k < Gvoxels.size(); k++)
		{
			vector<int>& vIdx = Gvoxels[k];
			for (int j = 0; j < vIdx.size(); j++)
			{
				count[v1[vIdx[j]]]++;
			}
			iter--;
		}

		float max_density = 0;
		for (int j = 0; j < 256; j++)
		{
			if (count[j] > max_density)
				max_density = count[j];
		}
		counts.push_back(count);
		maxc.push_back(max_density);
	}
}

void ParallelCoordinate::setAllDisplay()
{
	displayManner = 0;
	calDistribution();
	update();
}

void ParallelCoordinate::setPartDisplay()
{
	displayManner = 1;
	calDistribution();
	update();
}

void ParallelCoordinate::setArrangedDisplay()
{
	displayManner = 2;
	calDistribution();
	update();
}

void ParallelCoordinate::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::RightButton)
		return;
	QPointF startPos = event->pos();
	float deltax = width() / (axisNum + 1);
	//float deltax = 100.0;
	int i = 0;
	selectRegion sg;
	sg.startY = startPos.y();

	int axes;
	if (displayManner == 0 || displayManner == 2) axes = axisNum;
	else axes = attributeIdx.size();
	for (; i < axes; i++)
	{
		if (startPos.x() >= (i + 1) * deltax - 10 && startPos.x() <= (i + 1) * deltax + 10)
		{
			int idx;
			if (displayManner == 1) idx = attributeIdx[i];
			else if (displayManner == 2) idx = dimensionalOrder[i];
			else idx = i;
			sg.selectNo = idx;
			if (event->pos().y() <= 30)
			{
				if (currentID != idx)
					emit TFIDChanged(idx);
				currentID = idx;
			}
			break;
		}
	}
	if (i == axes)
		return;
	sRegin.push_back(sg);
}

void ParallelCoordinate::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->pos().y() <= 30)
	{
		sRegin.clear();
		update();
		return;
	}	
	if (event->button() == Qt::RightButton || sRegin.empty())
		return;
	float deltax = width() / (axisNum + 1);
	//float deltax = 100.0;

	voxelIdx.clear();
	QPointF endPos = event->pos();
	selectRegion sg = sRegin.back();

	int axes, idx;
	if (displayManner == 0 || displayManner == 2) axes = axisNum;
	else axes = attributeIdx.size();

	int i = 0;
	for (; i < axes; i++)
	{
		if (endPos.x() >= (i + 1) * deltax - 10 && endPos.x() <= (i + 1) * deltax + 10)
			break;
	}

	idx = i;
	if (displayManner == 1) idx = attributeIdx[i];
	else if (displayManner == 2) idx = dimensionalOrder[i];
	if (i == axes || idx != sg.selectNo)
	{
		sRegin.pop_back();
		return;
	}

	if (endPos.y() - sg.startY < 2)
	{
		sRegin.clear();
		return;
	}
	sRegin[sRegin.size() - 1].endY = endPos.y();

	float startV, endV;
	vector<int> variables;
	for (int i = 0; i < volRegions.size(); i++)
	{
		memset(volRegions[i], 0, volDatas[0]->getTotalSize() * sizeof(uchar));
	}
	for (vector<selectRegion>::iterator iter = sRegin.begin(); iter != sRegin.end(); iter++)
	{
		variables.push_back(sg.selectNo);
		sg = *iter;
		startV = (height() - 30 - sg.endY) / (height() - 60) * 255;
		endV = (height() - 30 - sg.startY) / (height() - 60) * 255;
		Volume* vol = volDatas[sg.selectNo];
		uchar* v = vol->getVolume();
		if (iter == sRegin.begin())
		{
			for (int i = 0; i < vol->getTotalSize(); i++)
			{
				if (v[i] >= startV && v[i] <= endV)
				{
					volRegions[0][i] = 255;
				}
			}
		}
		else
		{
			for (int i = 0; i < vol->getTotalSize(); i++)
			{
				if (v[i] < startV || v[i] > endV)
				{
					volRegions[0][i] = 0;
				}
			}
		}

	}

	int voxelnum = 0;
	set<int> voxels;
	for (int i = 0; i < volDatas[0]->getTotalSize(); i++)
	{
		if (volRegions[0][i] == 255)
		{
			voxelnum++;
			voxels.insert(corIdx[markIdx[i]]);
		}
	}

	voxelIdx.resize(voxels.size());
	std::copy(voxels.begin(), voxels.end(), voxelIdx.begin());
	float score;
	emit getCCScore(voxelIdx, variables, score);
	//std::cout << "voxel num: " << voxelnum << endl;
	std::cout << "voxel num: " << voxels.size() << endl;
	std::cout << "ccscore: " << score << endl;
	std::cout << "===================================" << endl;
	update();

	emit volRegionChange();
	//emit sendRange(variables[0], startV, endV);
}

void ParallelCoordinate::setFilterDatas(int* mIdx, int* cIdx, int fColNum)
{
	markIdx = mIdx;
	corIdx = cIdx;
	filterColNum = fColNum;
}

void ParallelCoordinate::contextMenuEvent(QContextMenuEvent * event)
{
	QMenu* menu = new QMenu(this);
	QAction* all = new QAction("Show All Dim", this);
	all->setCheckable(true);
	connect(all, SIGNAL(changed()), this, SLOT(setAllDisplay()));
	menu->addAction(all);

	QAction* part = new QAction("Show Selected Dim", this);
	part->setCheckable(true);
	connect(part, SIGNAL(changed()), this, SLOT(setPartDisplay()));
	menu->addAction(part);

	QAction* arranged = new QAction("Show Arranged Dim", this);
	arranged->setCheckable(true);
	connect(arranged, SIGNAL(changed()), this, SLOT(setArrangedDisplay()));
	menu->addAction(arranged);

	QPoint pos = cursor().pos();
	menu->move(pos);
	menu->show();
}