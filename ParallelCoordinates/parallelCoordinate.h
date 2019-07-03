#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QContextMenuEvent>
#include "1dtf\Volume.h"
#include "define.h"

struct selectRegion
{
	float startY;
	float endY;
	int selectNo;
};
class ParallelCoordinate : public QWidget
{
	Q_OBJECT
public:
	ParallelCoordinate(QList<QColor> colors);
	~ParallelCoordinate();

protected:
	void paintEvent(QPaintEvent* event);
	QSize minimumSizeHint() const;
	void mousePressEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);
	void contextMenuEvent(QContextMenuEvent * event);

signals:
	void volRegionChange();
	void TFIDChanged(int idx);
	void getCCScore(vector<int>& voxels, vector<int>& variables, float& score);
	void sendRange(int v, int r, int l);

	public slots:
	void setVolDatas(vector<Volume *>& vols);
	void setFilterDatas(int* mIdx, int* cIdx, int fColNum);
	void setClusterVoxels(vector<int> voxels, vector<int> attributes);
	void setGlobalClusters(vector<vector<int>> gvoxels, vector<vector<int>> gattributes);
	void setAllDisplay();
	void setPartDisplay();
	void setArrangedDisplay();

private:
	void calDistribution();
	int axisNum;
	vector<Volume *> volDatas;
	vector<int> voxelIdx;
	vector<int> attributeIdx;
	int displayManner;  //0--all dim 1-only selected dim  2-arranged
	bool isGlobal;   //select multiple clusters
	QPixmap screenPixmap;
	vector<selectRegion> sRegin;
	int frashNum;
	int* markIdx;
	int* corIdx;
	int filterColNum;
	int currentID;
	vector<int> dimensionalOrder;
	vector<vector<int>> Gvoxels;
	vector<vector<int>> Gattributes;
	QList<QColor> attributeColors;

	vector<vector<map<pair<float, float>, int>>> gobal_pc_maps;
	vector<vector<pair<int, int>>> maxds;
	vector<vector<int>> counts;
	vector<int> maxc;
};
