#include "mainslice.h"

QT_CHARTS_USE_NAMESPACE

MainSlice::MainSlice(QPieSeries *breakdownSeries, QObject *parent)
: QPieSlice(parent),
m_breakdownSeries(breakdownSeries)
{
	attributeno = 0;
	parent = NULL;
}

MainSlice::MainSlice(QString l, int attr, qreal v, qreal c)
{
	parent = NULL;
	m_breakdownSeries = new QPieSeries();
	setLabel(l);
	setValue(v);
	attributeno = attr;
	corr = c;
}

QPieSeries *MainSlice::breakdownSeries() const
{
	return m_breakdownSeries;
}

#include "moc_mainslice.cpp"
