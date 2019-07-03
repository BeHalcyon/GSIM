#include "1dtf\TF1DWidget.h"
#include "util\util.h"
#include "IntensityHistogram.h"

TF1DWidget::TF1DWidget(QWidget *parent)
	: QWidget(parent), m_pHistogram(NULL)
{
	ui.setupUi(this);
	this->setWindowTitle("Intensity Transfer Function");
}

TF1DWidget::~TF1DWidget()
{
	SAFE_DELETE(m_pHistogram);
}

void TF1DWidget::on_canvas_colorChanged( const QColor& c )
{
	emit colorChanged(c);
}

void TF1DWidget::on_canvas_resetTransferFunction()
{
	emit tfReset();
}

void TF1DWidget::on_canvas_changed()
{
	//emit tfChanged();
	//emit tmpsignal();
}

void TF1DWidget::on_canvas_sendTF( unsigned char* data )
{
	emit sendTF(data);
}

void TF1DWidget::setVolume( const Volume* volume )
{
	if (m_pHistogram != NULL)
	{
		delete m_pHistogram;
	}

	m_pHistogram = new IntensityHistogram(volume);
	ui.canvas->setHistogram(m_pHistogram);
}

void TF1DWidget::on_btnSave_clicked()
{
	if(ui.canvas->save())
		emit sematicAdd();

}

void TF1DWidget::on_btnLoad_clicked()
{
	ui.canvas->load();
}

void TF1DWidget::getTF(unsigned char * TF)
{
	ui.canvas->getKeys(TF);
}