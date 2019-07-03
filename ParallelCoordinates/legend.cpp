#include "legend.h"
#include <QPainter>

Legend::Legend(QList<QColor> cs)
{
	colors = cs;
}

void Legend::getVarianteNames(QStringList variatenames)
{
	variateNames = variatenames;
}

void Legend::selectedVariates(vector<int> s)
{
	subset = s;
	update();
}

QSize Legend::minimumSizeHint() const
{
	return QSize(512, 50);
}

QSize Legend::sizeHint() const
{
	return QSize(512, 50);
}

void Legend::paintEvent(QPaintEvent* event)
{
	QPainter p(this);
	QPointF startpoint(0, 0);
	for (int i = 0; i < subset.size(); i++)
	{
		QPainterPath path;
		path.moveTo(startpoint);
		path.lineTo(QPointF(60, 0) + startpoint);
		QPointF t_point = path.currentPosition();
		path.lineTo(QPointF(75, 15) + startpoint);
		path.lineTo(QPointF(60, 30) + startpoint);
		path.lineTo(QPointF(0, 30) + startpoint);
		if (i!=0)
			path.lineTo(QPointF(15, 15) + startpoint);
		path.lineTo(startpoint);
		p.setBrush(colors[subset[subset.size() - i - 1]]);
		p.drawPath(path);
		QString text = variateNames[subset[subset.size() - i - 1]];
		QFontMetricsF fm = p.fontMetrics();
		qreal pixelsWide = fm.width(text);
		qreal pixelsHigh = fm.height();
		QPointF pos = startpoint + QPointF(35, 15) + QPointF( -pixelsWide / 2.0, pixelsHigh / 2.0);
		p.drawText(pos, text);
		startpoint = t_point + QPointF(4, 0);
	}
}