#include <QWidget>
#include <QPainter>
#include <QList>
#include <QColor>
#include <iostream>

using namespace std;

class Legend : public QWidget
{
	Q_OBJECT
	public:
		Legend(QList<QColor> cs);
	public slots:
	void selectedVariates(vector<int> s);
	void getVarianteNames(QStringList variatenames);
protected:
	void paintEvent(QPaintEvent* event);
	QSize minimumSizeHint() const;
	QSize sizeHint() const;
private:
	vector<int> subset;
	QList<QColor> colors;
	QStringList variateNames;
};