#ifndef RENDERPROPERTY_H
#define RENDERPROPERTY_H
#include <QWidget>
#include <QButtonGroup>
#include <QColorDialog>
#include "ui_renderproperties.h"
#include <renderWidget.h>
#include <define.h>

class RenderPropertyWidget : public QWidget, public Ui::RenderProperties
{
	Q_OBJECT
public:
	RenderPropertyWidget(RenderWidget* renderwidget)
	{
		setupUi(this);
		buttonGroup = new QButtonGroup;
		buttonGroup->addButton(pushButton, 0);
		buttonGroup->addButton(pushButton_2, 1);
		buttonGroup->addButton(pushButton_3, 2);
		buttonGroup->addButton(pushButton_4, 3);
		connect(buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(buttonJudge(int)));
		connect(horizontalSlider, SIGNAL(valueChanged(int)), doubleSpinBox, SLOT(setIntValue(int)));
		connect(horizontalSlider_2, SIGNAL(valueChanged(int)), doubleSpinBox_2, SLOT(setIntValue(int)));
		connect(horizontalSlider_3, SIGNAL(valueChanged(int)), doubleSpinBox_3, SLOT(setIntValue(int)));
		connect(horizontalSlider_4, SIGNAL(valueChanged(int)), doubleSpinBox_4, SLOT(setIntValue(int)));
		connect(horizontalSlider_5, SIGNAL(valueChanged(int)), this, SLOT(alpha1Changed(int)));
		connect(horizontalSlider_6, SIGNAL(valueChanged(int)), this, SLOT(alpha2Changed(int)));
		connect(horizontalSlider_7, SIGNAL(valueChanged(int)), this, SLOT(alpha3Changed(int)));
		connect(horizontalSlider_8, SIGNAL(valueChanged(int)), this, SLOT(alpha4Changed(int)));
		connect(doubleSpinBox, SIGNAL(sendIntValue(int)), horizontalSlider, SLOT(setValue(int)));
		connect(doubleSpinBox_2, SIGNAL(sendIntValue(int)), horizontalSlider_2, SLOT(setValue(int)));
		connect(doubleSpinBox_3, SIGNAL(sendIntValue(int)), horizontalSlider_3, SLOT(setValue(int)));
		connect(doubleSpinBox_4, SIGNAL(sendIntValue(int)), horizontalSlider_4, SLOT(setValue(int)));
		connect(doubleSpinBox, SIGNAL(valueChanged(double)), renderwidget, SLOT(setKa(double)));
		connect(doubleSpinBox_2, SIGNAL(valueChanged(double)), renderwidget, SLOT(setKd(double)));
		connect(doubleSpinBox_3, SIGNAL(valueChanged(double)), renderwidget, SLOT(setKs(double)));
		connect(doubleSpinBox_4, SIGNAL(valueChanged(double)), renderwidget, SLOT(setOpacity(double)));
		connect(this, SIGNAL(alphaChanged(int, double)), renderwidget, SLOT(setOpacities(int, double)));
		connect(this, SIGNAL(colorChanged()), renderwidget, SLOT(colorUpdate()));
	}

	~RenderPropertyWidget()
	{

	}
signals:
	void colorChanged();
	void alphaChanged(int id, double val);
	public slots:
	void buttonJudge(int buttonId)
	{
		QColor newColor = QColorDialog::getColor(featurecolors[buttonId], 0);
		featurecolors[buttonId] = newColor;
		emit colorChanged();
	}
	void alpha1Changed(int val)
	{
		emit alphaChanged(1, val / 100.0);
	}
	void alpha2Changed(int val)
	{
		emit alphaChanged(2, val / 100.0);
	}
	void alpha3Changed(int val)
	{
		emit alphaChanged(3, val / 100.0);
	}
	void alpha4Changed(int val)
	{
		emit alphaChanged(4, val / 100.0);
	}
private:
	QButtonGroup *buttonGroup;
protected:
	QSize minimumSizeHint() const
	{
		return QSize(360, 300);
	}
	QSize sizeHint() const
	{
		return QSize(360, 300);
	}
};

#endif