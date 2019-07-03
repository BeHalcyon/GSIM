#include <QWidget>
#include <QPainterPath>
#include <QImage>
#include <iostream>
#include "SimpleMatrix.h"
#include "biclusters.h"
#include "classifier.h"
#include "ext/tapkee/tapkee.hpp"
#include "ext/tapkee/callbacks/dummy_callbacks.hpp"

#include "engine.h"     // add header file
#define BUFSIZE 256

// import necessary lib  
#pragma comment( lib, "libeng.lib")  
#pragma comment( lib, "libmx.lib")  
#pragma comment( lib, "libmat.lib")  

using namespace std;
using namespace smat;
using namespace tapkee;

QT_BEGIN_NAMESPACE
class QTimer;
QT_END_NAMESPACE

struct MyDistanceCallback
{
	float* dmatrix;
	int dim;
	MyDistanceCallback(float* m, int d) : dmatrix(m), dim(d) {}
	ScalarType distance(IndexType l, IndexType r) { return dmatrix[l * dim + r]; }
};

class ScatterPlot : public QWidget
{
	Q_OBJECT
public:
	ScatterPlot(QList<QColor> cs);
	~ScatterPlot();
signals:
	void sendIdx(int idx);
	void sendGlobalSelect(int idx);
	void sendAGroup(vector<int> group);
	void sendGroups(vector<vector<int>> groups);
	void sendDistence(vector<float> dis);
	public slots:
	void getDistanceMatrix(float* matrix, int dim, vector<MaximalDimentionalSet*> mds);
	void getRange(int vno, int l, int r);
	void getCutValue(float v);
	void clusterSplit();
	void clusterMerge();
	void setPieChartShow(int isPieChartShow_);
	void setRepNodeOnly();
	void simulShow();

protected:
	void paintEvent(QPaintEvent* event);
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);
	void resizeEvent(QResizeEvent *event);
	void contextMenuEvent(QContextMenuEvent * event);
	QSize minimumSizeHint() const;
	QSize sizeHint() const;
private:
	void layout();
	void updateBackground();
private:
	Matrix<float> * d_matrix;
	Matrix<float> * pos;
	float border;
	vector<int> selectedIdx;
	float** data;
	int pointsnum;
	vector<MaximalDimentionalSet*> selectMDS;
	QList<QColor> colors;
	float maxsize;
	float* matrix;
	QPointF upLeft;
	QPointF bottomRight;
	vector<pair<QPointF,int>> selectedPoints;  //position & original number
	QList<QColor> clusterColors;
	Classifier* classifier;
	vector<int> clusters;  //which cluster do this subspace belong to
	vector<int> representation;  // representative feature subspaces of each group
	//bool displayManner;
	int Width;
	int Height;
	int clusterNum;
	int splitID;
	vector<int> mergeIDs;
	vector<QPainterPath> paths;
	QImage background;
	int highlight;
	vector<int> selectedClusterID;
	QTimer *updateTimer;
	Engine *ep;
	bool isPieChartShow;   //0--not show the pie chart 1--show the pie chart
	bool onlyRepNodeShow;  //0--show all the subspaces in a cluster, 1--only show the representative subspaces in a cluster
};
