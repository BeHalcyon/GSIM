#include "disDistribution.h"
#include <QPainter>
#include <QLineF>

const float Pi = 3.141592653589793;
DisDistribution::DisDistribution()
{
	setAutoFillBackground(true);
	QPalette p;
	p.setBrush(backgroundRole(), QBrush(QColor(255, 255, 255)));
	setPalette(p);
	currentV = 0.98;
	resize(360, 320);
}

//void DisDistribution::paintEvent(QPaintEvent *event)
//{
//	if (distribution.size() == 0) return;
//	QPainter p(this);
//	p.setRenderHint(QPainter::HighQualityAntialiasing);
//
//	//////draw axis
//	QPointF sourcePoint(15, Height - 10);
//	QPointF destPoint(Width - 10, Height - 10);
//	QLineF line(sourcePoint, destPoint);
//	qreal arrowSize = 10;
//	double angle = ::acos(line.dx() / line.length());
//	if (line.dy() >= 0)
//		angle = 2 * Pi - angle;
//	p.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
//	p.drawLine(line);
//
//	p.setBrush(Qt::black);
//	QPointF destArrowP1 = destPoint + QPointF(sin(angle - Pi / 3) * arrowSize,
//		cos(angle - Pi / 3) * arrowSize);
//	QPointF destArrowP2 = destPoint + QPointF(sin(angle - Pi + Pi / 3) * arrowSize,
//		cos(angle - Pi + Pi / 3) * arrowSize);
//	p.drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
//	p.drawText(sourcePoint, "0");
//	p.drawText(destPoint, "1.0");
//
//	//////draw distribution
//	p.setPen(Qt::NoPen);
//	p.setBrush(Qt::blue);
//	bool* mask = new bool[Width * Height];
//	std::memset(mask, 0, Width * Height * sizeof(bool));
//	for (int i = 0; i < distribution.size(); i++)
//	{
//		float xx = distribution[i] * (Width - 30) + 15;
//		float yy = Height - 12;
//		float vscale = 6;
//		QRect region;
//		for ( ; yy > 10; yy -= 6)
//		{
//			QRect rect(xx - vscale / 2.0, yy - vscale / 2.0, vscale, vscale);
//			bool isOccupied = false;
//			for (int r = 0; r < rect.width(); r++)
//			{
//				for (int c = 0; c < rect.height(); c++)
//				{
//					if (mask[(rect.top() + c) * Width + (rect.left() + r)])
//					{
//						isOccupied = true;
//						break;
//					}
//				}
//				if (isOccupied)
//					break;
//			}
//			if (!isOccupied)
//			{
//				region = rect;
//				break;
//			}
//		}
//		if (yy >= Height - 10)
//		{
//			cout << "out rang!" << endl;
//		}
//		for (int r = 0; r < region.width(); r++)
//		for (int c = 0; c < region.height(); c++)
//			mask[(region.top() + c) * Width + (region.left() + r)] = true;
//		p.drawEllipse(QPointF(xx, yy), 0.5 * vscale, 0.5 * vscale);
//	}
//
//	///////draw current value
//	p.setBrush(Qt::NoBrush);
//	p.setPen(Qt::darkBlue);
//	p.drawLine(15 + currentV * (Width - 30), 10, 15 + currentV * (Width - 30), Height - 10);
//}

void DisDistribution::paintEvent(QPaintEvent *event)
{
	if (distribution.size() == 0) return;
	QPainter p(this);
	p.setRenderHint(QPainter::HighQualityAntialiasing);
	
	//////draw axis
	QPointF sourcePoint(20, Height - 20);
	QPointF destPoint(Width - 20, Height - 20);
	QLineF line(sourcePoint, destPoint);
	qreal arrowSize = 10;
	double angle = ::acos(line.dx() / line.length());
	if (line.dy() >= 0)
		angle = 2 * Pi - angle;
	p.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	p.drawLine(line);
	QString text("iteration step");
	QFontMetricsF fm = p.fontMetrics();
	qreal pixelsWide = fm.width(text);
	qreal pixelsHigh = fm.height();
	p.drawText(destPoint - QPointF(pixelsWide, -pixelsHigh), text);

	QPointF sourcePoint2(20, Height - 20);
	QPointF destPoint2(20, 20);
	QLineF line2(sourcePoint2, destPoint2);
	double angle2 = ::acos(line.dx() / line.length());
	if (line.dy() >= 0)
		angle2 = 2 * Pi - angle2;
	p.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	p.drawLine(line2);
	text = "1.0";
	pixelsWide = fm.width(text);
	pixelsHigh = fm.height();
	p.drawText(sourcePoint2 - QPointF(pixelsWide, -pixelsHigh), "0");
	p.drawText(destPoint2 - -QPointF(pixelsWide, -pixelsHigh), "1.0");

	qreal deltax = (Width - 40) * 1.0 / distribution.size();
	qreal deltay = (Height - 40) * 1.0 / (distribution.size() + 1);

	int deltait;
	if (distribution.size() > 20)
		deltait = ceil(distribution.size() / 20.0);
	else
		deltait = 1;
	for (int iter = 0; iter < distribution.size(); iter += deltait)
	{
		qreal x1, y1, x2, y2;
		p.setPen(QColor(70, 130, 180));
		p.setBrush(QColor(70, 130, 180));
		int it = iter - deltait;

		/////distance
		if (iter > 0)
		{
			x1 = 20 + deltax * it;
			y1 = Height - 20 - distribution[it] * (Height - 40);
			x2 = 20 + deltax * (iter + 1);
			y2 = Height - 20 - distribution[iter] * (Height - 40);
			p.drawLine(x1, y1, x2, y2);
			p.drawEllipse(x1 - 2.5, y1 - 2.5, 5, 5);
			p.drawEllipse(x2 - 2.5, y2 - 2.5, 5, 5);
		}

		/////iteration
		it = iter + deltait;
		p.setPen(QColor(0, 128, 0));
		p.setBrush(QColor(0, 128, 0));
		x1 = 20 + iter * deltax;
		y1 = Height - 20 - (distribution.size() + 1 - iter) * deltay;
		x2 = 20 + it * deltax;
		y2 = Height - 20 - (distribution.size() + 1 - it) * deltay;
		p.drawLine(x1, y1, x2, y2);
		p.drawEllipse(x1 - 2.5, y1 - 2.5, 5, 5);
		p.drawEllipse(x2 - 2.5, y2 - 2.5, 5, 5);
	}

	///////draw current value
	p.setPen(Qt::black);
	p.drawLine(20, Height - 20 - currentV * (Height - 40), Width - 20, Height - 20 - currentV * (Height - 40));
}

void DisDistribution::resize(int w, int h)
{
	Width = w;
	Height = h;
}

void DisDistribution::getDistribution(vector<float> d)
{
	distribution = d;
	update();
}

void DisDistribution::mousePressEvent(QMouseEvent *event)
{
	if (event->y() >= 20 && event->y() <= Height - 20)
	{
		currentV = 1.0 - (event->y() - 20) * 1.0 / (Height - 40);
    		emit sendCurrentValue(currentV);
		update();
	}	
}

QSize DisDistribution::minimumSizeHint() const
{
	return QSize(360, 320);
}

QSize DisDistribution::sizeHint() const
{
	return QSize(360, 320);
}