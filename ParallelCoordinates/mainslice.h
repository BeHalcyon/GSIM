#ifndef MAINSLICE_H
#define MAINSLICE_H

#include <QtCharts/QPieSlice>
#include <QtCharts/QPieSeries>

QT_CHARTS_USE_NAMESPACE

class MainSlice : public QPieSlice
{
	Q_OBJECT
public:
	MainSlice(QPieSeries *breakdownSeries, QObject *parent = 0);
	MainSlice(QString l, int attr, qreal v, qreal c);

	QPieSeries *breakdownSeries() const;
	MainSlice *parent;
	int attributeno;
	float corr;
	QColor m_color;
signals:
	public Q_SLOTS:
private:
	QPieSeries *m_breakdownSeries;
};

#endif // MAINSLICE_H
