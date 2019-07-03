#include "calEntropy.h"
#include "define.h"
#include <cmath>
#include <QImage>
#include <QColor>

QImage drawBar(int width, int height, float ratio, QColor color)
{
	int l = width * ratio;
	QImage img(width, height, QImage::Format_ARGB32);
	img.fill(color);
	for (int i = 0; i < height; i++)
	{
		for (int j = l; j < width; j++)
		{
			img.setPixel(j, i, Qt::white);
		}
	}
	return img;
}
CalEntropy::CalEntropy()
{
	setupUi(this);
	connect(pushButton_2, SIGNAL(clicked()), this, SLOT(updateSelect()));
	tableWidget->horizontalHeader()->hide();
	tableWidget->verticalHeader()->hide();
	tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	connect(tableWidget, SIGNAL(cellClicked(int, int)), this, SLOT(getClickCol(int, int)));
	selectedno = -1;
}

CalEntropy::~CalEntropy()
{
}

QSize CalEntropy::minimumSizeHint()const
{
	return QSize(500, 200);
}
void CalEntropy::setDatas(vector<Volume *>& vds)
{
	vdatas = vds;
	//variatenames = vns;
	entropies.resize(vdatas.size());

	tableWidget->setColumnCount(3);
	tableWidget->setRowCount(vdatas.size());
	QTableWidgetItem* checkBox = new QTableWidgetItem[vdatas.size()];
	for (int i = 0; i < vdatas.size(); i++)
	{
		QTableWidgetItem *item = new QTableWidgetItem;
		item->setText("");
		item->setTextAlignment (Qt::AlignCenter);
		tableWidget->setItem(i, 0, item);
		tableWidget->item(i , 0)->setCheckState ( Qt::Unchecked);
	}
	//for (int i = 0; i < vdatas.size(); i++)
	//	tableWidget->setItem(i, 1, new QTableWidgetItem(variatenames.at(i)));

	labels = new QLabel[vdatas.size()];
	for (int i = 0; i < vdatas.size(); i++)
	{
		tableWidget->setCellWidget(i, 2, &labels[i]);
	}

	TableUpdate();
}

float* hist2D(Volume* d1, Volume* d2)
{
	int totalVoxels = d1->getTotalSize();
	float* hist = new float[256 * 256];
	for (int i = 0; i < 256 * 256; i++)
		hist[i] =  0;
	for (int i =0; i < totalVoxels; i++)
		hist[d1->getVolume()[i] * 256 + d2->getVolume()[i]] += 1;
	for (int i = 0; i < 256 * 256; i++)
		hist[i] /= totalVoxels;
	return hist;
}


float* hist1D(Volume* d)
{
	int totalVoxels = d->getTotalSize();
	float* hist = new float[256];
	for (int i = 0; i < 256; i++)
		hist[i] = 0;
	for (int i = 0; i < totalVoxels; i++)
		hist[d->getVolume()[i]] += 1;
	for (int i = 0; i < 256; i++)
		hist[i] /= totalVoxels;
	return hist;
}

float CalEntropy::calculateEntropy(Volume* d)
{
	float* h = hist1D(d);
	float entropy = 0;
	for (int i = 0; i < 256; i++)
	{
		float probability = h[i];
		if(probability > FLT_EPSILON)
			entropy += -probability * log(probability);
	}
	return entropy;
}

float CalEntropy::calculateMutual(Volume* d1, Volume* d2)
{
	float* h1 = hist1D(d1);
	float* h2 = hist1D(d2);
	float* h12 = hist2D(d1, d2);
	float* p12 = new float[256*256];
	for (int i = 0; i < 256; i++)
		for(int j = 0; j < 256; j++)
			p12[i * 256 + j] = h1[i] * h2[j];
	float mutual = 0;
	for(int i = 0; i < 256 * 256; i++)
	{
		if(p12[i] > FLT_EPSILON && h12[i] > FLT_EPSILON)
			mutual += h12[i] * log(h12[i] / p12[i]);
	}
	return mutual;
}

void CalEntropy::TableUpdate()
{
	int w = tableWidget->width() - tableWidget->columnWidth(0)- tableWidget->columnWidth(1) - 10;
	if(selectedno < 0)
	{
		float maxe = FLT_MIN;
		for (int i = 0; i < vdatas.size(); i++)
		{
			entropies[i] = calculateEntropy(vdatas[i]);
			if(entropies[i] > maxe) maxe = entropies[i];
		}

		for (int i = 0; i < vdatas.size(); i++)
			entropies[i] /= maxe;
		for (int i = 0; i < vdatas.size(); i++)
		{
			labels[i].setPixmap(QPixmap::fromImage(drawBar(w, 25, entropies[i], colors[i])));
		}
	}
	else
	{
		for (int i = 0; i < vdatas.size(); i++)
		{
			entropies[i] = calculateMutual(vdatas[selectedno], vdatas[i]);
		}
		for (int i = 0; i < vdatas.size(); i++)
			entropies[i] /= entropies[selectedno];
		for (int i = 0; i < vdatas.size(); i++)
		{
			labels[i].setPixmap(QPixmap::fromImage(drawBar(w, 25, entropies[i], colors[selectedno])));
		}
	}

	update();
}

void CalEntropy::getClickCol(int row, int col)
{
	if(col == 0)
		return ;
	if(selectedno == row)
		selectedno = -1;
	else
		selectedno = row;
	TableUpdate();
	sendSelectedVariateNo(row);
}

void CalEntropy::updateSelect()
{
	vector<int> selectedVariates;
	for (int i = 0; i < vdatas.size(); i++)
	{
		if(tableWidget->item(i, 0)->checkState() == Qt::Checked)
			selectedVariates.push_back(i);
	}
	emit sendSelectedVariatesNo(selectedVariates);
}

vector<float> CalEntropy::getEntropy()
{
	float maxe = FLT_MIN;
	for (int i = 0; i < vdatas.size(); i++)
	{
		entropies[i] = calculateEntropy(vdatas[i]);
		if (entropies[i] > maxe) maxe = entropies[i];
	}

	for (int i = 0; i < vdatas.size(); i++)
		entropies[i] /= maxe;
	return entropies;
}

vector<float> CalEntropy::getMutual(int sno)
{
	for (int i = 0; i < vdatas.size(); i++)
	{
		entropies[i] = calculateMutual(vdatas[sno], vdatas[i]);
	}
	for (int i = 0; i < vdatas.size(); i++)
		entropies[i] /= entropies[sno];
	return entropies;
}