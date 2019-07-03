#ifndef DONUTBREAKDOWNCHART_H
#define DONUTBREAKDOWNCHART_H

#include <iostream>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QList>
#include "mainslice.h"
#include "define.h"

using namespace std;
QT_CHARTS_USE_NAMESPACE

class DonutBreakdownChart : public QChartView
{
	Q_OBJECT

public:
	DonutBreakdownChart(QList<QColor> cs);
signals:
	void sendSelectedVariates(vector<int>);
	void sendSelectedSubset(vector<int>);
	void getCorrelation(vector<int> variates, float& corr);
	void sendcolormap(QList<QColor> colormap);
public slots:
	void getVariateSubsets(vector<VSubset> attributesets);
	void highlightSlice(bool highlight);
	void selected();
	void getVarianteNames(QStringList variatenames);
protected:
	QSize minimumSizeHint() const;
	QSize sizeHint() const;
	void mousePressEvent(QMouseEvent *event);

private:
	QColor calcolor(float radio);
	QPieSeries *root_Series;
	MainSlice *root_slice;
	QStringList variateNames;
	QList<QColor> colors;
	QList<QColor> colormap;
	vector<int> subset;
	QChart* m_chart;
	float min_corr;
	float max_corr;
};

#endif // DONUTBREAKDOWNCHART_H
