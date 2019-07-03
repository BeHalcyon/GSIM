#ifndef CALENTROPY_H
#define CALENTROPY_H


#include <QWidget>
#include <QLabel>
#include <vector>
#include "1dtf/Volume.h"
#include "ui_entropyHistogram.h"

using namespace std;

class CalEntropy : public QWidget, public Ui::EntropyForm
{
	Q_OBJECT
public:
	CalEntropy();
	~CalEntropy();
	public slots:
	void setDatas(vector<Volume *>& vds);
	void updateSelect();
	vector<float> getEntropy();
	vector<float> getMutual(int sno);
signals:
	void sendSelectedVariateNo(int selectedNo);
	void sendSelectedVariatesNo(vector<int> selectedVariates);
	public slots:
		void getClickCol(int row, int col);
protected:
	QSize minimumSizeHint() const;
private:
	float calculateEntropy(Volume* d);
	float calculateMutual(Volume* d1, Volume* d2);
	void TableUpdate();
private:
	vector<Volume *> vdatas;
	vector<float> entropies;
	//QStringList variatenames;
	QLabel* labels;
	int selectedno;
};

#endif // !CALENTROPY_H