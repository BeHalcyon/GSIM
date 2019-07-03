#include <QWidget>
#include <QPainter>
#include <QList>
#include <QColor>

class ColorBar : public QWidget
{
	Q_OBJECT
public:
	ColorBar();
	public slots :
		void getcolormap(QList<QColor> colors);
protected:
	void paintEvent(QPaintEvent* event);
	QSize minimumSizeHint() const;
	QSize sizeHint() const;
private:
	QList<QColor> colormap;

};