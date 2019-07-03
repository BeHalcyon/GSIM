
#include <QWidget>
#include <QImage>
#include <QMouseEvent>

#include <vector>
#include <iostream>
using namespace std;

class DisDistribution : public QWidget
{
	Q_OBJECT
public:
	DisDistribution();
signals:
	void sendCurrentValue(float v);
	public slots:
	void getDistribution(vector<float> d);
protected:
	void paintEvent(QPaintEvent *event);
	void resize(int w, int h);
	void mousePressEvent(QMouseEvent *event);
	QSize minimumSizeHint() const;
	QSize sizeHint() const;
private:
	vector<float> distribution;
	int Width;
	int Height;
	float currentV;
};