#include <QWidget>
#include <QPainter>
#include <QList>
#include <QColor>
#include <QMouseEvent>

#include <set>
#include "calEntropy.h"
#include "define.h"

class SetViewHeader : public QWidget
{
	Q_OBJECT
public:
	SetViewHeader(CalEntropy* calentropy);
	public slots :
	void getCurrentSet(set<int> cset);
protected:
	void mousePressEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent* event);
	QSize minimumSizeHint() const;
	QSize sizeHint() const;
private:
	CalEntropy* entropyCalor;
	QStringList variateNames;
	set<int> currentset;
	int selectedNo;
	int nodewidth;
	float maxTextWidth;
};