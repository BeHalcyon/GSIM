#include "setViewHeader.h"
#include "define.h"


//  p0-------p1
//  /        /
//p3--------p2
QPainterPath parallelogram(QPointF p0, QPointF p1, QPointF p2, QPointF p3)
{
	QPainterPath path;
	path.moveTo(p0);
	path.lineTo(p1);
	path.lineTo(p2);
	path.lineTo(p3);
	path.lineTo(p0);
	return path;
}

SetViewHeader::SetViewHeader(CalEntropy* calentropy)
{
	setAutoFillBackground(true);
	QPalette p;
	p.setBrush(backgroundRole(), QBrush(QColor(255, 255, 255)));
	setPalette(p);
	setContentsMargins(0, 0, 0, 0);
	entropyCalor = calentropy;
	maxTextWidth = 0;
}

QSize SetViewHeader::sizeHint() const
{
	return QSize(400, 160);
}

QSize SetViewHeader::minimumSizeHint() const
{
	return QSize(400, 160);
}


void SetViewHeader::paintEvent(QPaintEvent* event)
{
	if (variatenames.size() == 0)
		return;
	nodewidth = 25 * (1 - 0.04 * (variatenames.size() - 5));
	QPainter p(this);
	p.setRenderHint(QPainter::HighQualityAntialiasing);

	if (maxTextWidth < 1.0)
	{
		for (int i = 0; i < variatenames.size(); i++)
		{
			int textpos = variatenames[i].indexOf(".");
			QString text = variatenames[i].left(textpos);
			QFontMetricsF fm = p.fontMetrics();
			qreal pixelsWide = fm.width(text);
			if (pixelsWide > maxTextWidth)
				maxTextWidth = pixelsWide;
		}
		maxTextWidth += 20;
		maxTextWidth /= pow(2, 0.5);
	}

	vector<float> infamount;
	if (selectedNo < 0 || selectedNo >= variatenames.size())
		infamount = entropyCalor->getEntropy();
	else
		infamount = entropyCalor->getMutual(selectedNo);

	p.setPen(Qt::NoPen);

	//////header background
	p.setBrush(QColor(240, 240, 240));
	p.drawRect(70 + maxTextWidth, height() - 130 - maxTextWidth, variatenames.size() * nodewidth, 130);

	QPointF p0(70 + maxTextWidth, height() - maxTextWidth);
	QPointF p1(70 + maxTextWidth + variatenames.size() * nodewidth, height() - maxTextWidth);
	QPointF p2(70 + variatenames.size() * nodewidth + 5, height());
	QPointF p3(70, height());
	QPainterPath path = parallelogram(p0, p1, p2, p3);
	p.drawPath(path);

	//////highlight current set
	p.setBrush(QColor(254, 208, 145));
	for (set<int>::iterator it = currentset.begin(); it != currentset.end(); it++)
	{
		p.drawRect(70 + maxTextWidth + (*it) * nodewidth, height() - 100 - maxTextWidth, nodewidth, 100);
		QPointF p0(70 + maxTextWidth + (*it) * nodewidth, height() - maxTextWidth);
		QPointF p1(70 + maxTextWidth + ((*it) + 1) * nodewidth, height() - maxTextWidth);
		QPointF p2(70 + ((*it) + 1) * nodewidth, height());
		QPointF p3(70 + (*it) * nodewidth, height());
		QPainterPath path = parallelogram(p0, p1, p2, p3);
		p.drawPath(path);
	}

	//////mutual information bar
	for (int i = 0; i < variatenames.size(); i++)
	{
		p.setBrush(colors[i]);
		float barheight = infamount[i] * 100;
		//barheight /= pow(2, 0.5);
		QPointF drawpos = QPointF(70 + maxTextWidth + i * nodewidth, height() - maxTextWidth - barheight);
		p.drawRect(QRectF(drawpos, QPointF(70 + maxTextWidth + 18 + i * nodewidth, height() - maxTextWidth)));
		//QPointF p0(70 + i * 25 + barheight * 0.5, 180 - barheight * pow(3, 0.5));
		//QPointF p1(70 + (i + 1) * 25 + barheight * 0.5, 180 - barheight * pow(3,0.5));
		//QPointF p2(70 + (i + 1) * 25, 180);
		//QPointF p3(70 + i * 25, 180);
		//QPainterPath path = parallelogram(p0, p1, p2, p3);
		//p.drawPath(path);
	}

	//////variate names
	p.setPen(Qt::black);
	for (int i = 0; i < variatenames.size(); i++)
	{
		int textpos = variatenames[i].indexOf(".");
		QString text = variatenames[i].left(textpos);
		QFontMetricsF fm = p.fontMetrics();
		qreal pixelsWide = fm.width(text);
		qreal pixelsHigh = fm.height();
		QPointF drawpos = QPointF(100 + i * nodewidth, height());
		p.translate(drawpos);
		p.rotate(-40);
		p.drawText(0, -pixelsHigh, text);
		p.resetMatrix();
	}
}

void SetViewHeader::mousePressEvent(QMouseEvent * event)
{
	selectedNo = (event->x() - 70 - maxTextWidth) / nodewidth;
	update();
}

void SetViewHeader::getCurrentSet(set<int> cset)
{
	currentset = cset;
	update();
}