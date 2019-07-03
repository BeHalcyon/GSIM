#pragma once
#include <QtWidgets/QDoubleSpinBox>

//Debug 20180130 将构建函数和析构函数放置类内部

class MyDoubleSpinBox : public QDoubleSpinBox
{
	Q_OBJECT
public:
	MyDoubleSpinBox(QWidget* parent = 0) : QDoubleSpinBox(parent)
	{
		connect(this, SIGNAL(valueChanged(double)), this, SLOT(getIntValue(double)));
	}
	~MyDoubleSpinBox() {}
	public slots:
	void setIntValue(int value)
	{
		this->setValue(value / 100.0);
	}
	void getIntValue(double value)
	{
		emit sendIntValue(value * 100);
	}
signals:
	void sendIntValue(int value);
private:

};