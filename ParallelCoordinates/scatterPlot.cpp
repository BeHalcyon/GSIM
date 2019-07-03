#include "scatterPlot.h"
#include "classifier.h"
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QMenu>
#include <QPointF>
#include <fstream>

typedef vector<QPointF> PTARRAY;
const float PI = 3.14159265358;

float vectormodule(QPointF p)
{
	return sqrt((float)(p.x() * p.x() + p.y() * p.y()));
}

bool CompareVector(const QPointF &pt1, const QPointF &pt2) {
	//求向量的模
	float m1 = sqrt((float)(pt1.x() * pt1.x() + pt1.y() * pt1.y()));
	float m2 = sqrt((float)(pt2.x() * pt2.x() + pt2.y() * pt2.y()));
	//两个向量分别与(1, 0)求内积
	float v1 = pt1.x() / m1, v2 = pt2.x() / m2;
	return (v1 > v2 || (v1 == v2 && m1 < m2));
}

QPointF compute2DPolygonCentroid(vector<QPointF>& p)
{
	QPointF centroid(0, 0);
	double signedArea = 0.0;
	double x0 = 0.0; // Current vertex X
	double y0 = 0.0; // Current vertex Y
	double x1 = 0.0; // Next vertex X
	double y1 = 0.0; // Next vertex Y
	double a = 0.0;  // Partial signed area

	// For all vertices except last
	int i = 0;
	for (i = 0; i < p.size() - 1; ++i)
	{
		x0 = p[i].x();
		y0 = p[i].y();
		x1 = p[i + 1].x();
		y1 = p[i + 1].y();
		a = x0*y1 - x1*y0;
		signedArea += a;
		centroid.setX(centroid.x() + (x0 + x1)*a);
		centroid.setY(centroid.y() + (y0 + y1)*a);
	}

	// Do last vertex separately to avoid performing an expensive
	// modulus operation in each iteration.
	x0 = p[i].x();
	y0 = p[i].y();
	x1 = p[0].x();
	y1 = p[0].y();
	a = x0*y1 - x1*y0;
	signedArea += a;
	centroid.setX(centroid.x() + (x0 + x1)*a);
	centroid.setY(centroid.y() + (y0 + y1)*a);

	signedArea *= 0.5;
	centroid.setX(centroid.x() / (6.0*signedArea));
	centroid.setY(centroid.y() / (6.0*signedArea));

	return centroid;
}

//计算凸包
void CalcConvexHull(PTARRAY &vecSrc) {
	//点集中至少应有3个点，才能构成多边形
	if (vecSrc.size() < 3) {
		return;
	}
	//查找基点
	QPointF ptBase = vecSrc.front(); //将第1个点预设为最小点
	for (PTARRAY::iterator i = vecSrc.begin() + 1; i != vecSrc.end(); ++i) {
		//如果当前点的y值小于最小点，或y值相等，x值较小
		if (i->y() < ptBase.y() || (i->y() == ptBase.y() && i->x() > ptBase.x())) {
			//将当前点作为最小点
			ptBase = *i;
		}
	}
	//计算出各点与基点构成的向量
	for (PTARRAY::iterator i = vecSrc.begin(); i != vecSrc.end();) {
		//排除与基点相同的点，避免后面的排序计算中出现除0错误
		if (*i == ptBase) {
			i = vecSrc.erase(i);
		}
		else {
			//方向由基点到目标点
			i->setX(i->x() - ptBase.x()), i->setY(i->y() - ptBase.y());
			++i;
		}
	}
	//按各向量与横坐标之间的夹角排序
	sort(vecSrc.begin(), vecSrc.end(), &CompareVector);
	//删除相同的向量
	vecSrc.erase(unique(vecSrc.begin(), vecSrc.end()), vecSrc.end());
	//计算得到首尾依次相联的向量
	for (PTARRAY::reverse_iterator ri = vecSrc.rbegin();
		ri != vecSrc.rend() - 1; ++ri) {
		PTARRAY::reverse_iterator riNext = ri + 1;
		//向量三角形计算公式
		ri->setX(ri->x() - riNext->x()), ri->setY(ri->y() - riNext->y());
	}
	//依次删除不在凸包上的向量
	for (PTARRAY::iterator i = vecSrc.begin() + 1; i != vecSrc.end(); ++i) {
		//回溯删除旋转方向相反的向量，使用外积判断旋转方向
		for (PTARRAY::iterator iLast = i - 1; iLast != vecSrc.begin();) {
			int v1 = i->x() * iLast->y(), v2 = i->y() * iLast->x();
			//如果叉积小于0，则无没有逆向旋转
			//如果叉积等于0，还需判断方向是否相逆
			if (v1 < v2 || (v1 == v2 && i->x() * iLast->x() > 0 &&
				i->y() * iLast->y() > 0)) {
				break;
			}
			//删除前一个向量后，需更新当前向量，与前面的向量首尾相连
			//向量三角形计算公式
			i->setX(i->x() + iLast->x()), i->setY(i->y() + iLast->y());
			iLast = (i = vecSrc.erase(iLast)) - 1;
		}
	}
	//将所有首尾相连的向量依次累加，换算成坐标
	vecSrc.front().setX(vecSrc.front().x() + ptBase.x()), vecSrc.front().setY(vecSrc.front().y() + ptBase.y());
	for (PTARRAY::iterator i = vecSrc.begin() + 1; i != vecSrc.end(); ++i) {
		i->setX(i->x() + (i - 1)->x()), i->setY(i->y() + (i - 1)->y());
	}
	//添加基点，全部的凸包计算完成
	vecSrc.push_back(ptBase);
}

ScatterPlot::ScatterPlot(QList<QColor> cs)
{
	setAutoFillBackground(true);
	QPalette p;
	p.setBrush(backgroundRole(), QBrush(QColor(255, 255, 255)));
	setPalette(p);
	setMouseTracking(true);

	border = 0.2;
	d_matrix = NULL;
	pos = NULL;
	data = NULL;
	classifier = NULL;
	colors = cs;

	//////// open engine  
	if (!(ep = engOpen("\0")))
	{
		fprintf(stderr, "\nCan't start MATLAB engine\n");
		return;
	}
	// 是否显示MATLAB窗口：true-显示；false-隐藏。
	int nStatus = engSetVisible(ep, false);           // 设为ture运行时也只是一闪而过
	if (nStatus != 0)
	{
		cout << "设置MATLAB显示属性失败。" << endl;
		exit(EXIT_FAILURE);
	}
}

ScatterPlot::~ScatterPlot()
{
	engClose(ep);
}

void ScatterPlot::paintEvent(QPaintEvent* event)
{
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing);
	p.setRenderHint(QPainter::HighQualityAntialiasing);

	if (selectedPoints.size() == 0) return;

	QImage pix(Width, Height, QImage::Format_RGB32);
	pix.fill(QColor(255, 255, 255));
	QPainter pp(&pix);
	pp.setPen(Qt::NoPen);

	//draw group backgroud
	for (int i = 0; i < clusterNum; i++)
	{
		p.setPen(Qt::NoPen);
		//QColor c(clusterColors[i]);
		QColor c(166, 206, 227);
		c.setAlphaF(0.3);

		p.setPen(c.lighter(50));
		if (highlight < 0 || highlight == i)
			p.setBrush(c);	
		else
			p.setBrush(c.lighter(70));	

		vector<int>::iterator it = std::find(selectedClusterID.begin(), selectedClusterID.end(), i);
		if (it != selectedClusterID.end())
		{
			QPen pen(QColor(0, 0, 0));
			pen.setWidth(2);
			p.setPen(pen);
		}

		p.drawPath(paths[i]);

		pp.setBrush(QColor(i, i, i));
		pp.drawPath(paths[i]);
	}

	background = pix;
	for (int i = 0; i < selectedPoints.size(); i++)
	{
		int idx = selectedPoints[i].second;
		if (onlyRepNodeShow && representation[clusters[idx]] != idx)
			continue;
		MaximalDimentionalSet* t_mds = selectMDS[idx];
		if (!t_mds->isSelected)
			continue;
		float xx = selectedPoints[idx].first.x();
		float yy = selectedPoints[idx].first.y();
		float vscale = sqrt(t_mds->getObjectSet()->getVoxelsNum() / maxsize) + 0.15;

		QRectF piesize = QRectF(xx - 15.0 * vscale, yy - 15.0 * vscale, 30.0 * vscale, 30.0 * vscale);
		vector<int> group;
		for (int j = 0; j < t_mds->getAttributeSet()->size(); j++)
		{
			bitset<defaultAttributeNum>* attributes = t_mds->getAttributeSet();
			if ((*attributes)[j]) group.push_back(j);
		}
		p.setPen(Qt::NoPen);
		if (isPieChartShow)
		{
			if (group.size() > 0)
			{
				int startAngle = 90 * 16;
				int spanAngle = 360 / group.size() * 16;
				for (int j = 0; j < group.size(); j++)
				{
					if (highlight < 0 || highlight == clusters[selectedPoints[idx].second])
						p.setBrush(colors[group[j]]);
					else
						p.setBrush(colors[group[j]].light(70));
					startAngle = j * spanAngle;
					p.drawPie(piesize, startAngle, spanAngle);
				}
			}
		}
		else
		{
			QColor c(31, 119, 180);
			if (highlight < 0 || highlight == clusters[selectedPoints[idx].second])
				p.setBrush(c);
			else
				p.setBrush(c.light(70));
			p.drawEllipse(piesize);
		}
		if (representation[clusters[idx]] == idx)
		{
			QPen pen(QColor(235, 193, 1));
			pen.setWidth(3);
			p.setPen(pen);
			p.setBrush(Qt::NoBrush);
			p.drawEllipse(QPointF(xx, yy), 15.0 * vscale, 15.0 * vscale);
		}

		///////draw the selected mark
		vector<int>::iterator it = std::find(selectedIdx.begin(), selectedIdx.end(), idx);
		if (it != selectedIdx.end())
		{
			QPen pen(QColor(218, 1, 54));
			pen.setWidth(3);
			p.setPen(pen);
			p.setBrush(Qt::NoBrush);
			p.drawEllipse(QPointF(xx, yy), 15.0 * vscale, 15.0 * vscale);
		}
	}

	QPen pen(QColor(235, 193, 1));
	pen.setWidth(3);
	p.setPen(pen);
	p.setBrush(QColor(31, 119, 180));
	p.drawEllipse(45, height() - 30, 25, 25);
	p.setPen(Qt::black);
	p.setFont(QFont("Helvetica", 10));
	p.drawText(QRectF(80, height() - 30, 120, 50), "A representative feature subspace");

	pen.setColor(QColor(218, 1, 54));
	p.setPen(pen);
	p.drawEllipse(220, height() - 30, 25, 25);
	p.setPen(Qt::black);
	p.drawText(QRectF(250, height() - 30, 120, 50), "A selected feature subspace");

	QColor c(166, 206, 227);
	pen.setColor(c.lighter(70));
	p.setPen(pen);
	p.setBrush(c);
	p.drawRoundRect(QRectF(390, height() - 30, 25, 25), 25, 25);
	p.setPen(Qt::black);
	p.drawText(QRectF(420, height() - 25, 100, 50), "A cluster");

	pen.setColor(Qt::black);
	p.setPen(pen);
	p.setBrush(c);
	p.drawRoundRect(QRectF(530, height() - 30, 25, 25), 25, 25);
	p.setPen(Qt::black);
	p.drawText(QRectF(560, height() - 30, 120, 50), "A selected cluster");

}

QSize ScatterPlot::minimumSizeHint() const
{
	return QSize(512, 512);
}

QSize ScatterPlot::sizeHint() const
{
	return QSize(512, 512);
}

void ScatterPlot::getDistanceMatrix(float* m, int dim, vector<MaximalDimentionalSet*> mds)
{
	cout << "selected subspace nums: " << mds.size() << endl;
	isPieChartShow = false;
	onlyRepNodeShow = false;
	selectedIdx.clear();
	selectedClusterID.clear();
	pointsnum = dim;
	selectMDS = mds;
	for (int i = 0; i < selectMDS.size(); i++)
	{
		selectMDS[i]->isSelected = true;
	}
	matrix = m;
	if (classifier)
	{
		delete classifier;
		classifier = NULL;
	}
	classifier = new Classifier(selectMDS, matrix, WEIGHTED_LINKAGE, DOT_PRODUCT);
	//clusters = classifier->getCluter(clusterNum);
	//Maybe Need Modification. 
	clusters = classifier->checkcut("distance", 0.992);
	vector<float> dis = classifier->getDistance("distance");
	emit sendDistence(dis);
	//clusters = classifier->checkcut("inconsistent", 0.95);
	clusterNum = 0;
	for (int i = 0; i < clusters.size(); i++)
	{
		if (clusters[i] > clusterNum) clusterNum = clusters[i];
	}
	clusterNum++;

	//if(d_matrix) delete d_matrix;
	//d_matrix = new Matrix<float>(dim, matrix);
	//if(pos) delete pos;
	//if(dim <= 2)
	//	pos = d_matrix;
	//else
	//	pos = MDS_UCF(d_matrix, NULL, 2, 30); 

	double* pos = new double[2 * dim];

	if (dim > 1)
	{
		mxArray *T = NULL, *D = NULL;
		int nStatus = 0;
		char buffer[BUFSIZE + 1];
		T = mxCreateDoubleMatrix(dim, dim, mxREAL);
		D = mxCreateDoubleMatrix(dim, 2, mxREAL);
		double* t = new double[dim * dim];
		for (int i = 0; i < dim; i++)
		{
			for (int j = 0; j < dim; j++)
			{
				t[i * dim + j] = matrix[i * dim + j];
			}
		}
		memcpy((void *)mxGetPr(T), (void *)t, dim * dim * sizeof(double));
		nStatus = engPutVariable(ep, "T", T);
		if (nStatus != 0)
		{
			cout << "矩阵变量写入MATLAB引擎空间失败。" << endl;
		}
		nStatus = engEvalString(ep, "D = mdscale(T,2);");
		if (nStatus != 0)
		{
			cout << "执行MATLAB引擎命令失败。" << endl;
		}

		D = engGetVariable(ep, "D");
		if (D == NULL) {
			cout << "matlab: get array failed!" << endl;
		}
		else
		{
			memcpy((void*)pos, (void*)mxGetPr(D), dim * 2 * sizeof(double));
			//for (int i = 0; i < dim; i++)
			//{
			//	cout << setw(2) << pos[i] << " " << pos[dim + i] << endl;
			//}
		}
		mxDestroyArray(D);
		mxDestroyArray(T);
	}
	else
	{
		pos[0] = Width / 2.0;
		pos[1] = Height / 2.0;
	}

	//vector<IndexType> indices(dim);
	//for (int i = 0; i < dim; i++) indices[i] = i;

	//MyDistanceCallback d(matrix, dim);
	//TapkeeOutput output = tapkee::initialize()
	//	.withParameters((method = MultidimensionalScaling, target_dimension = 2))
	//	.withDistance(d)
	//	.embedUsing(indices);

	//data = pos->getData();
	if (data) delete data;
	data = new float*[dim];
	selectedPoints.clear();
	for (int i = 0; i < dim; i++)
	{
		//data[i] = new float[2];
		//data[i][0] = output.embedding(i, 0);
		//data[i][1] = output.embedding(i, 1);
		//selectedPoints.push_back(make_pair(QPointF(data[i][0], data[i][1]), i));
		//selectedPoints.push_back(make_pair(QPointF(pos->get(i, 0), pos->get(i, 1)), i));
		selectedPoints.push_back(make_pair(QPointF(pos[i], pos[dim + i]), i));
	}
	layout();
}

void ScatterPlot::resizeEvent(QResizeEvent *event)
{
	Width = width();
	Height = height() - 40;
}

void enlarge(PTARRAY& ptarray, vector<float> pSize, QPointF center, float scale)
{
	for (int j = 0; j < ptarray.size(); j++)
	{
		QPointF A = ptarray[j];
		QPointF AC(A - center);
		QPointF ACm = AC / vectormodule(AC);
		//A = A + (scale + pSize[j]) * AC;
		A = A + 0.12 * AC + pSize[j] * ACm;
		ptarray[j] = A;
	}
}

PTARRAY smooth(PTARRAY ptarray)
{
	PTARRAY current;
	for (int j = 0; j < ptarray.size(); j++)
	{
		QPointF p = ptarray[j];
		QPointF q = ptarray[(j + 1) % ptarray.size()];
		float dis = vectormodule(p - q);
		QPointF direction = (q - p) / dis;
		for (int k = 0; k < 20; k++)
		{
			QPointF pt = p + k / 20.0 * dis * direction;
			current.push_back(pt);
		}
	}

	int iter = 10;
	PTARRAY next;
	while (iter)
	{
		for (int j = 0; j < current.size(); j++)
		{
			QPointF p0 = current[(j + current.size() - 1) % current.size()];
			QPointF p2 = current[(j + 1) % current.size()];
			QPointF p1 = (p0 + p2) / 2;
			next.push_back(p1);
		}

		current = next;
		next.clear();
		iter--;
	}

	return current;
}

void ScatterPlot::layout()
{
	float minx = FLT_MAX, maxx = FLT_MIN;
	float miny = FLT_MAX, maxy = FLT_MIN;
	maxsize = 0;
	for (int i = 0; i < selectedPoints.size(); i++)
	{
		if (selectedPoints[i].first.x() > maxx) maxx = selectedPoints[i].first.x();
		if (selectedPoints[i].first.x() < minx) minx = selectedPoints[i].first.x();
		if (selectedPoints[i].first.y() > maxy) maxy = selectedPoints[i].first.y();
		if (selectedPoints[i].first.y() < miny) miny = selectedPoints[i].first.y();
		if (selectMDS[selectedPoints[i].second]->getObjectSet()->getVoxelsNum() > maxsize)
			maxsize = selectMDS[selectedPoints[i].second]->getObjectSet()->getVoxelsNum();
	}

	//float delta = std::max((maxx - minx), (maxy - miny));
	//float scale = std::min(Width, Height) * (1 - border);
	//float w = (Width - scale) / 2;
	//float h = (Height - scale) / 2;

	float scalex = Width * (1 - border);
	float scaley = Height * (1 - border);
	float w = (Width - scalex) / 2;
	float h = (Height - scaley) / 2;
	for (int i = 0; i < selectedPoints.size(); i++)
	{
		//QPointF p((selectedPoints[i].first.x() - minx) / delta,
		//	(selectedPoints[i].first.y() - miny) / delta);
		//float xx = p.x() * scale + w;
		//float yy = p.y() * scale + h;

		QPointF p((selectedPoints[i].first.x() - minx) / (maxx - minx),
			(selectedPoints[i].first.y() - miny) / (maxy - miny));
		float xx = p.x() * scalex + w;
		float yy = p.y() * scaley + h;

		selectedPoints[i].first.setX(xx);
		selectedPoints[i].first.setY(yy);
	}

	////////refinement 
	bool* mask = new bool[Width * Height];
	std::memset(mask, 0, Width * Height * sizeof(bool));
	for (int i = 0; i < selectedPoints.size(); i++)
	{
		int idx = selectedPoints[i].second;
		MaximalDimentionalSet* t_mds = selectMDS[idx];
		float xx = selectedPoints[idx].first.x();
		float yy = selectedPoints[idx].first.y();
		float vscale = sqrt(t_mds->getObjectSet()->getVoxelsNum() / maxsize) + 0.2;
		float x = xx, y = yy;
		int iter = 20;
		float radius = 0;
		float radius_step = 2;
		int angle_step = 10;
		QRect region;
		while (iter--)
		{
			bool isOccupied = false;
			radius += radius_step;
			for (int angle = 0; angle < 360; angle += angle_step)
			{
				QRect rect(x - 15.0 * vscale, y - 15.0 * vscale, 30.0 * vscale, 30.0 * vscale);
				isOccupied = false;
				for (int r = 0; r < rect.width(); r++)
				{
					for (int c = 0; c < rect.height(); c++)
					{
						if (mask[(rect.top() + c) * Width + (rect.left() + r)])
						{
							isOccupied = true;
							break;
						}
					}
					if (isOccupied)
						break;
				}
				region = rect;
				if (!isOccupied)
					break;
				x = xx + radius * cos(angle);
				y = yy + radius * sin(angle);
				if (x < 0 || x >= Width || y < 0 || y >= Height)
					iter = 0;
			}
			if (!isOccupied)
			{
				xx = x;
				yy = y;
				break;
			}
		}
		selectedPoints[idx].first.setX(xx);
		selectedPoints[idx].first.setY(yy);

		for (int r = 0; r < region.width(); r++)
		for (int c = 0; c < region.height(); c++)
			mask[(region.top() + c) * Width + (region.left() + r)] = true;
	}

	updateBackground();
	update();
}

void ScatterPlot::updateBackground()
{

	//calculate cluster boundary
	paths.clear();
	for (int i = 0; i < clusterNum; i++)
	{
		PTARRAY ptarray;
		vector<float> pSize;
		for (int j = 0; j < selectedPoints.size(); j++)
		{
			if (clusters[selectedPoints[j].second] == i)
			{
				ptarray.push_back(selectedPoints[j].first);
				int idx = selectedPoints[i].second;
				MaximalDimentionalSet* t_mds = selectMDS[idx];
				float vscale = sqrt(t_mds->getObjectSet()->getVoxelsNum() / maxsize) + 0.15;
				pSize.push_back(vscale * 30.0);
			}

		}

		PTARRAY cluster_region;
		QPainterPath path;
		if (ptarray.size() == 1)
		{
			path.addEllipse(ptarray[0], 30, 30);
		}
		else if (ptarray.size() == 2)
		{
			QPointF c = (ptarray[0] + ptarray[1]) / 2.0;
			qreal x = ptarray[0].x() - c.x();
			qreal y = ptarray[0].y() - c.y();
			qreal w = 30;
			qreal h = vectormodule(ptarray[0] - ptarray[1]) + 30;
			if (y > -FLT_EPSILON && y < FLT_EPSILON)
				path.addEllipse(c, h, w);
			if (x > -FLT_EPSILON && x < FLT_EPSILON)
				path.addEllipse(c, w, h);
			else
			{
				float angle;
				angle = atan(y / x) * 180 / PI + 90;
				QMatrix mat;
				mat.translate(c.x(), c.y());
				mat.rotate(angle);
				QPainterPath t_path;
				t_path.addEllipse(0.0 - w / 2.0, 0.0 - h / 2.0, w, h);
				path = mat.map(t_path);
			}
		}
		else
		{
			CalcConvexHull(ptarray);

			QPointF center = compute2DPolygonCentroid(ptarray);
			enlarge(ptarray, pSize, center, 30);
			cluster_region = smooth(ptarray);

			path.moveTo(cluster_region[0]);
			for (int j = 1; j < cluster_region.size(); j++)
			{
				path.lineTo(cluster_region[j]);
			}
			path.lineTo(cluster_region[0]);
		}
		paths.push_back(path);
	}

	//calculate the representative node
	representation.clear();
	representation.resize(clusterNum);
	for (int i = 0; i < clusterNum; i++)
	{
		int maxsize = 0;
		for (int j = 0; j < selectedPoints.size(); j++)
		{
			int idx = selectedPoints[j].second;
			MaximalDimentionalSet* t_mds = selectMDS[idx];
			if (clusters[selectedPoints[j].second] == i && t_mds->getObjectSet()->getVoxelsNum() > maxsize)
			{
				maxsize = t_mds->getObjectSet()->getVoxelsNum();
				representation[i] = j;
			}
		}
	}
}

void ScatterPlot::mouseMoveEvent(QMouseEvent *event)
{
	if (!background.isNull() && event->x() < Width && event->y() < Height)
	{
		QRgb rgb = background.pixel(event->x(), event->y());
		int mark;
		if (qRed(rgb) == 255 && qBlue(rgb) == 255 && qGreen(rgb) == 255)
			mark = -1;
		else
			mark = qRed(rgb);
		if (mark != highlight)
		{
			highlight = mark;
			update();
		}
	}
}

void ScatterPlot::mousePressEvent(QMouseEvent * event)
{
	if (QApplication::keyboardModifiers() & Qt::ControlModifier)
	{
		if (!background.isNull())
		{
			QRgb rgb = background.pixel(event->x(), event->y());
			int mark;
			if (qRed(rgb) == 255 && qBlue(rgb) == 255 && qGreen(rgb) == 255)
				return;
			else
				mark = qRed(rgb);
			mergeIDs.push_back(mark);
			selectedClusterID.push_back(mark);
		}
		return;
	}
	mergeIDs.clear();
	selectedClusterID.clear();
	splitID = -1;
	if (event->button() == Qt::RightButton)
	{
		if (!background.isNull())
		{
			QRgb rgb = background.pixel(event->x(), event->y());
			if (qRed(rgb) == 255 && qBlue(rgb) == 255 && qGreen(rgb) == 255)
				return;
			else
				splitID = qRed(rgb);
		}
		return;
	}

	QPointF spot(event->x(), event->y());
	float scale = std::min(width(), height());
	float w = (width() - scale) / 2;
	float h = (height() - scale) / 2;

	for (int i = 0; i < selectedPoints.size(); i++)
	{
		float xx = selectedPoints[i].first.x();
		float yy = selectedPoints[i].first.y();
		MaximalDimentionalSet* t_mds = selectMDS[selectedPoints[i].second];
		float vscale = sqrt(t_mds->getObjectSet()->getVoxelsNum() / maxsize) + 0.2;
		int nsize = vscale * 15;

		if (spot.x() >= xx - nsize && spot.x() <= xx + nsize
			&& spot.y() >= yy - nsize && spot.y() <= yy + nsize)
		{
			int idx = selectedPoints[i].second;
			if (onlyRepNodeShow && representation[clusters[idx]] != idx)
				break;
			if (QApplication::keyboardModifiers() & Qt::ShiftModifier)
			{
				emit sendGlobalSelect(selectedPoints[i].second);
				selectedIdx.push_back(selectedPoints[i].second);
			}
			else
			{
				//cout << selectedPoints[i].second << " " << selectMDS[selectedPoints[i].second]->getObjectSet()->count() << endl;
				selectedIdx.clear();
				selectedIdx.push_back(selectedPoints[i].second);
				update();
				emit sendIdx(selectedPoints[i].second);
			}
			return;
		}
	}

	if (!background.isNull())
	{
		QRgb rgb = background.pixel(event->x(), event->y());
		int mark;
		if (qRed(rgb) == 255 && qBlue(rgb) == 255 && qGreen(rgb) == 255)
			mark = -1;
		else
			mark = qRed(rgb);
		//cout << mark << endl;
		if (mark >= 0)
		{
			selectedClusterID.push_back(mark);
			selectedIdx.clear();
			update();
		}
		if (selectedClusterID.size() > 0)
		{
			vector<int> agroup;
			for (int i = 0; i < selectedPoints.size(); i++)
			{
				if (clusters[selectedPoints[i].second] == selectedClusterID[0])
					agroup.push_back(selectedPoints[i].second);
			}
			emit sendAGroup(agroup);
		}
	}

}

void ScatterPlot::mouseReleaseEvent(QMouseEvent * event)
{
	/*	if (QApplication::keyboardModifiers() & Qt::ControlModifier)
	{
	bottomRight = QPointF(event->x(), event->y());
	if (bottomRight.x() - upLeft.x() < 2 || bottomRight.y() - upLeft.y() < 2)
	return;
	vector<pair<QPointF,int>> points;
	for (int i = 0; i < selectedPoints.size(); i++)
	{
	if (selectedPoints[i].first.x() > upLeft.x() && selectedPoints[i].first.x() < bottomRight.x()
	&& selectedPoints[i].first.y() > upLeft.y() && selectedPoints[i].first.y() < bottomRight.y())
	{
	points.push_back(selectedPoints[i]);
	}
	}
	selectedPoints.clear();
	copy(points.begin(), points.end(), selectedPoints.begin());
	bottomRight = upLeft;
	layout();
	update();
	}
	else */if (QApplication::keyboardModifiers() & Qt::ShiftModifier)
	{
		//float** d = d_matrix->getData();
		for (int i = 0; i < selectedIdx.size(); i++)
		{
			bitset<defaultObjectNum>* obj1 = selectMDS[selectedIdx[i]]->getObjectSet()->objset;
			for (int j = i + 1; j < selectedIdx.size(); j++)
			{
				bitset<defaultObjectNum>* obj2 = selectMDS[selectedIdx[j]]->getObjectSet()->objset;
				cout << "similarity: " << selectedIdx[i] << " " << selectedIdx[j] << " " << matrix[selectedIdx[i] * pointsnum + selectedIdx[j]] << endl;
				cout << "intersect: " << obj1->count() << " " << obj2->count() << " " << ((*obj1)&(*obj2)).count() << endl;
			}
		}
	}
	//else
	//{
	//	selectedIdx.clear();
	//}
}
void ScatterPlot::clusterSplit()
{
	if (splitID < 0) return;
	clusters = classifier->recluster(splitID);
	clusterNum++;
	updateBackground();
	update();
	splitID = -1;
}

void ScatterPlot::clusterMerge()
{
	int newNo = clusterNum;
	set<int> currentNos;
	for (int i = 0; i < clusters.size(); i++)
	{
		vector<int>::iterator it = std::find(mergeIDs.begin(), mergeIDs.end(), clusters[i]);
		if (it != mergeIDs.end())
			clusters[i] = newNo;
		currentNos.insert(clusters[i]);
	}
	int count = 0;
	for (set<int>::iterator it = currentNos.begin(); it != currentNos.end(); ++it)
	{
		for (int i = 0; i < clusters.size(); i++)
		{
			if (clusters[i] == *it)
				clusters[i] = count;
		}
		count++;
	}
	//clusterNum -= (mergeIDs.size() - 1);
	clusterNum = currentNos.size();
	mergeIDs.clear();
	updateBackground();
	update();

	//////adjust the binary tree

	//if (mergeIDs.size() != 2)
	//	return;
	//set<int>::iterator it = mergeIDs.begin();
	//int first = *it;
	//int second = *(++it);
	//clusters = classifier->remergecluster(first, second);
	//clusterNum = 0;
	//for (int i = 0; i < clusters.size(); i++)
	//{
	//	if (clusters[i] > clusterNum)
	//		clusterNum = clusters[i];
	//}
	//clusterNum++;
	//updateBackground();
	//update();
	//mergeIDs.clear();
	//vector<float> dis = classifier->getDistance("distance");
	//emit sendDistence(dis);
}

void ScatterPlot::setPieChartShow(int isPieChartShow_)
{
	isPieChartShow = isPieChartShow_;
	update();
}

void ScatterPlot::setRepNodeOnly()
{
	onlyRepNodeShow = !onlyRepNodeShow;
	update();
}

void ScatterPlot::simulShow()
{
	vector<vector<int>> groups;
	for (vector<int>::iterator it = mergeIDs.begin(); it != mergeIDs.end(); ++it)
	{
		vector<int> agroup;
		for (int i = 0; i < selectedPoints.size(); i++)
		{
			if (clusters[selectedPoints[i].second] == *it)
				agroup.push_back(selectedPoints[i].second);
		}
		groups.push_back(agroup);
	}
	mergeIDs.clear();
	emit sendGroups(groups);
}

void ScatterPlot::contextMenuEvent(QContextMenuEvent * event)
{
	QMenu* menu = new QMenu(this);

	QAction* split = new QAction("Split", this);
	split->setCheckable(true);
	connect(split, SIGNAL(changed()), this, SLOT(clusterSplit()));
	menu->addAction(split);

	QAction* merge = new QAction("Merge", this);
	merge->setCheckable(true);
	connect(merge, SIGNAL(changed()), this, SLOT(clusterMerge()));
	menu->addAction(merge);

	//QAction* showpie = new QAction("Show Pie Chart", this);
	//showpie->setCheckable(true);
	//connect(showpie, SIGNAL(changed()), this, SLOT(setPieChartShow()));
	//menu->addAction(showpie);

	QAction* repnode = new QAction("Representative Node Only", this);
	repnode->setCheckable(true);
	connect(repnode, SIGNAL(changed()), this, SLOT(setRepNodeOnly()));
	menu->addAction(repnode);

	QAction* simul = new QAction("Simultaneously Show", this);
	simul->setCheckable(true);
	connect(simul, SIGNAL(changed()), this, SLOT(simulShow()));
	menu->addAction(simul);

	QPoint pos = cursor().pos();
	menu->move(pos);
	menu->show();
}

void ScatterPlot::getRange(int vno, int l, int r)
{
	for (int i = 0; i < selectedPoints.size(); i++)
	{
		int idx = selectedPoints[i].second;
		MaximalDimentionalSet* t_mds = selectMDS[idx];
		//cout << t_mds->vRange[vno].first << " " << t_mds->vRange[vno].second << endl;
		if ((t_mds->vRange[vno].first >= l && t_mds->vRange[vno].first <= r) || (t_mds->vRange[vno].second >= l && t_mds->vRange[vno].second <= r))
			t_mds->isSelected = true;
		else
			t_mds->isSelected = false;
	}
	update();
}

void ScatterPlot::getCutValue(float v)
{
	clusters = classifier->checkcut("distance", v);
	clusterNum = 0;
	for (int i = 0; i < clusters.size(); i++)
	{
		if (clusters[i] > clusterNum) clusterNum = clusters[i];
	}
	clusterNum++;
	updateBackground();
	update();
}