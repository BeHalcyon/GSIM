#include "donutbreakdownchart.h"
#include <QtCharts/QPieSlice>
#include <QPainter>

QT_CHARTS_USE_NAMESPACE

QColor DonutBreakdownChart::calcolor(float radio)
{
	int left = (int)floor(radio * 10);
	int right = left + 1;
	float delta = radio * 10 - left;
	//return QColor(colors[left].red() * (1 - delta) + colors[right].red() * delta,
	//	colors[left].blue() * (1 - delta) + colors[right].blue() * delta,
	//	colors[left].green() * (1 - delta) + colors[right].green() * delta);
	//return colors[left];
	int sh, ss, sv;
	int eh, es, ev;
	colormap[left].getHsv(&sh, &ss, &sv);
	colormap[right].getHsv(&eh, &es, &ev);
	if (sh < 180) sh += 360;
	if (eh < 180) eh += 360;
	QColor c;
	int h = sh * (1 - delta) + eh * delta;
	int s = ss * (1 - delta) + es * delta;
	int v = sv * (1 - delta) + ev * delta;
	c.setHsv(h % 360,
		std::min(255, s),
		std::min(255, v));
	//cout << c.red() << " " << c.green() << " " << c.blue() << endl;
	return c;
}

DonutBreakdownChart::DonutBreakdownChart(QList<QColor> cs)
{
	m_chart = this->chart();
	m_chart->legend()->setVisible(false);
	m_chart->setContentsMargins(0, 0, 0, 0);
	m_chart->setBackgroundRoundness(0);
	this->setRenderHint(QPainter::Antialiasing);
	setBackgroundBrush(Qt::white);
	// create the series for main center pie
	root_Series = new QPieSeries();
	root_slice = new MainSlice(root_Series, 0);
	root_slice->parent = NULL;
	colors = cs;

	// yellow to green
	colormap.push_back(QColor(255, 255, 99));
	colormap.push_back(QColor(239, 247, 99));
	colormap.push_back(QColor(222, 239, 99));
	colormap.push_back(QColor(206, 231, 99));
	colormap.push_back(QColor(189, 222, 99));
	colormap.push_back(QColor(173, 214, 99));
	colormap.push_back(QColor(156, 206, 99));
	colormap.push_back(QColor(132, 198, 99));
	colormap.push_back(QColor(115, 189, 99));
	colormap.push_back(QColor(99, 181, 99));
	colormap.push_back(QColor(82, 173, 99));
	colormap.push_back(QColor(82, 173, 99));

	//red to pink
	//colormap.push_back(QColor(180, 4, 38));
	//colormap.push_back(QColor(192, 40, 47));
	//colormap.push_back(QColor(203, 62, 56));
	//colormap.push_back(QColor(213, 80, 66));
	//colormap.push_back(QColor(222, 96, 77));
	//colormap.push_back(QColor(229, 112, 88));
	//colormap.push_back(QColor(236, 127, 99));
	//colormap.push_back(QColor(241, 141, 111));
	//colormap.push_back(QColor(244, 154, 123));
	//colormap.push_back(QColor(247, 166, 135));
	//colormap.push_back(QColor(247, 177, 148));
	//colormap.push_back(QColor(247, 187, 160));

}

QSize DonutBreakdownChart::minimumSizeHint() const
{
	return QSize(512, 512);
}

QSize DonutBreakdownChart::sizeHint() const
{
	return QSize(512, 512);
}

MainSlice* foundPieSlice(QPieSeries* pieSeries, QString str)
{
	foreach(QPieSlice *slice, pieSeries->slices())
	{
		if (slice->label() == str)
			return qobject_cast<MainSlice *>(slice);
	}
	return NULL;
}

void recalculateAngles(qreal st, qreal ed, QPieSeries* pieSeries)
{
	qreal angle = st;
	foreach(QPieSlice *slice, pieSeries->slices()) {
		QPieSeries *breakdownSeries = qobject_cast<MainSlice *>(slice)->breakdownSeries();
		breakdownSeries->setPieStartAngle(angle);
		angle += slice->percentage() * (ed - st);
		breakdownSeries->setPieEndAngle(angle);
	}
}

void DonutBreakdownChart::getVariateSubsets(vector<VSubset> attributesets)
{
	QPieSeries* pSeries;
	qreal minSize = 0.2;
	qreal maxSize = 1.0;
	int donutCount = 0;
	max_corr = 0;
	min_corr = FLT_MAX;
	for (int i = 0; i < attributesets.size(); i++)
	{
		vector<int> attributeset;
		for (int j = 0; j < attributesets[j].first.length(); j++)
		{
			attributeset.push_back(attributesets[j].first.at(j) - 48);
		}
		int number = attributesets[i].second;
		if (attributeset.size() > donutCount) donutCount = attributeset.size();
		pSeries = root_Series;
		MainSlice* parent_slice = root_slice;
		vector<int> t_attribute;
		for (int j = 0; j < attributeset.size(); j++)
		{
			t_attribute.push_back(attributeset[j]);
			MainSlice* slice = foundPieSlice(pSeries, variateNames[attributeset[j]]);
			pSeries->setHoleSize(minSize + j * (maxSize - minSize) / donutCount);
			pSeries->setPieSize(minSize + (j + 1) * (maxSize - minSize) / donutCount);
			if (slice == NULL)
			{
				float corr;
				emit getCorrelation(t_attribute, corr);
				if (corr > max_corr) max_corr = corr;
				if (corr < min_corr && corr > 0) min_corr = corr;
				slice = new MainSlice(variateNames[attributeset[j]], attributeset[j], number, corr);
				//slice->setColor(colors[attributeset[j]]);
				slice->parent = parent_slice;
				connect(slice, SIGNAL(hovered(bool)), this, SLOT(highlightSlice(bool)));
				connect(slice, SIGNAL(clicked()), this, SLOT(selected()));
				pSeries->append(slice);
				pSeries = slice->breakdownSeries();
			}
			else
			{
				slice->setValue(slice->value() + number);
				pSeries = slice->breakdownSeries();
			}

			parent_slice = slice;
		}
	}

	vector<QPieSeries*> stack;
	root_Series->setPieStartAngle(0);
	root_Series->setPieEndAngle(360);
	stack.push_back(root_Series);
	QColor st(5, 113, 59);
	QColor ed(172, 7, 38);
	while (!stack.empty())
	{
		QPieSeries *pSeries = stack.front();
		stack.erase(stack.begin());
		m_chart->addSeries(pSeries);
		qreal start_angle = pSeries->pieStartAngle();
		qreal end_angle = pSeries->pieEndAngle();
		recalculateAngles(start_angle, end_angle, pSeries);
		//max_corr += 1;
		foreach(QPieSlice *slice, pSeries->slices())
		{
			float radio;
			if (qobject_cast<MainSlice *>(slice)->corr < 0)
			{
				qobject_cast<MainSlice *>(slice)->corr = max_corr;
				radio = 1;
			}
			else
				radio = pow((qobject_cast<MainSlice *>(slice)->corr - min_corr) / (max_corr - min_corr), 0.5);
			//cout << qobject_cast<MainSlice *>(slice)->corr << " " << radio << endl;
			QColor c = calcolor(radio);
			slice->setColor(c);
			qobject_cast<MainSlice *>(slice)->m_color = c;
			stack.push_back(qobject_cast<MainSlice *>(slice)->breakdownSeries());
		}
	}

	emit sendcolormap(colormap);
}

void DonutBreakdownChart::highlightSlice(bool highlight)
{
	subset.clear();
	MainSlice *slice = qobject_cast<MainSlice *>(sender());
	vector<MainSlice*> stack;
	stack.push_back(root_slice);
	while (!stack.empty())
	{
		MainSlice *pSlice = stack.front();
		stack.erase(stack.begin());
		for each (QPieSlice *t_slice in pSlice->breakdownSeries()->slices())
		{
			stack.push_back(qobject_cast<MainSlice *>(t_slice));
		}
		if (highlight)
			pSlice->setColor(pSlice->color().lighter(60));
		else
			//pSlice->setColor(colors[pSlice->attributeno]);
			pSlice->setColor(pSlice->m_color);
	}
	if (highlight)
	{
		while (slice->parent != NULL)
		{
			subset.push_back(slice->attributeno);
			//slice->setColor(colors[slice->attributeno]);
			slice->setColor(slice->m_color);
			slice = slice->parent;
		}
	}

	emit sendSelectedVariates(subset);
}

void DonutBreakdownChart::selected()
{
	subset.clear();
	MainSlice *slice = qobject_cast<MainSlice *>(sender());
	while (slice->parent != NULL)
	{
		subset.push_back(slice->attributeno);
		slice = slice->parent;
	}
	emit sendSelectedSubset(subset);
}

void DonutBreakdownChart::getVarianteNames(QStringList variatenames)
{
	variateNames = variatenames;
}


void DonutBreakdownChart::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		QMouseEvent ev(event->type(), event->localPos(), Qt::RightButton, Qt::RightButton, event->modifiers());

		QChartView::mousePressEvent(&ev);
	}
	else
		QChartView::mousePressEvent(event);
}
