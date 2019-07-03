#include "colorbar.h"

ColorBar::ColorBar()
{

}

void ColorBar::getcolormap(QList<QColor> colors)
{
	colormap = colors;
	update();
}

void ColorBar::paintEvent(QPaintEvent* event)
{
	if (!colormap.size()) return;
	QPainter p(this);
	QPointF st(300, 25);
	QPointF ed(450, 25);

	QLinearGradient linearGradient(st, ed);
	for (int k = 0; k < colormap.size(); k++)
	{
		linearGradient.setColorAt(k * 1.0 / colormap.size(), colormap[k]);
	}
	p.setBrush(linearGradient);
	p.drawRect(220, 15, 250, 20);
	p.drawText(QPointF(190, 30), "high");
	p.drawText(QPointF(480, 30), "low");
}
QSize ColorBar::minimumSizeHint() const
{
	return QSize(512, 50);
}
QSize ColorBar::sizeHint() const
{
	return QSize(512, 50);
}