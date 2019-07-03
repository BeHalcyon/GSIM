#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H
#include <QWidget>
#include <QIntValidator>
#include "ui_controlPanel.h"
#include <setView.h>

class ControlPanel : public QWidget, public Ui::ControlPanel
{
	Q_OBJECT
public:
	ControlPanel(SetView* setview)
	{
		setupUi(this);
		setAutoFillBackground(true);
		QPalette p;
		p.setBrush(backgroundRole(), QBrush(QColor(255, 255, 255)));

		
		setPalette(p);
		label_3->setStyleSheet("font-weight: bold; font-size: 10px");
		label_6->setStyleSheet("font-weight: bold; font-size: 10px");
		connect(lineEdit, SIGNAL(textEdited(const QString &)), setview, SLOT(setMinDegree(const QString &)));
		connect(lineEdit_2, SIGNAL(textEdited(const QString &)), setview, SLOT(setMaxDegree(const QString &)));
		connect(comboBox, SIGNAL(currentIndexChanged(int)), setview, SLOT(updateSortType(int)));
		connect(comboBox_2, SIGNAL(currentIndexChanged(int)), setview, SLOT(updateSecondSortType(int)));
		connect(checkBox, SIGNAL(stateChanged(int)), setview, SLOT(setHideEmpty(int)));
		connect(checkBox_2, SIGNAL(stateChanged(int)), setview, SLOT(subsetsContainChanged(int)));
		
		//Debug 20180203 增加是否使用Jaccard Distance
		//connect(isJaccardUsed, SIGNAL(stateChanged(int)), setview, SLOT(setJaccardDistance(int)));
		
	}
signals:
void sendGSIMValue(float);
	public slots:
	void sendTextLineValue() {

		float GSIMValue = lineEdit_3->text().toFloat();

		emit sendGSIMValue(GSIMValue);
	}
	void getMaxDegree(int maxd)
	{
		QIntValidator* aIntValidator = new QIntValidator;
		aIntValidator->setRange(1, maxd);
		lineEdit->setValidator(aIntValidator);
		lineEdit_2->setValidator(aIntValidator);
		lineEdit->setText("1");
		lineEdit_2->setText(QString::number(maxd));
	}

protected:
	QSize minimumSizeHint() const
	{
		return QSize(115, 800);
	}
	QSize sizeHint() const
	{
		return QSize(115, 800);
	}
private:
};

#endif