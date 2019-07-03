#ifndef SETVIEW_H
#define SETVIEW_H


#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QComboBox> 

#include <vector>
#include <set>
#include <map>
#include <sstream>
#include <string>

#include "define.h"


using namespace std;

struct VariateSet
{
	set<int> subset;
	float amount;
	float coherent;
	float correlation;
	float correlationPearson;
	bool visited;
	VariateSet(set<int> vset)
	{
		amount = 0;
		subset = vset;
		visited = false;
	}
};

struct TreeItem
{
	VariateSet* variateset;
	bool isExpanded;
	vector<TreeItem*> children;
	float xoffset;
	float ypos;
	int level;
	TreeItem(VariateSet* vset, int ll)
	{
		isExpanded = false;
		variateset = vset;
		level = ll;
		xoffset = 0;
		ypos = -1000;
	}
};

class DegreeOrder
{
	vector<TreeItem*> & data;
public:
	//SelectedVariatesNo
	DegreeOrder(vector<TreeItem*> & d) : data(d) {}
	bool operator()(const uint & a, const uint & b) const {
		return data[a]->variateset->subset.size() < data[b]->variateset->subset.size();
	}
};

class AmountOrder
{
	vector<TreeItem*> & data;
public:
	AmountOrder(vector<TreeItem*> & d) : data(d) {}
	bool operator()(const uint & a, const uint & b) const {
		return data[a]->variateset->amount > data[b]->variateset->amount;
	}
};

class CoherentOrder
{
	vector<TreeItem*> & data;
public:
	CoherentOrder(vector<TreeItem*> & d) : data(d) {}
	bool operator()(const uint & a, const uint & b) const {
		return data[a]->variateset->coherent < data[b]->variateset->coherent;
	}
};

class CorreleteOrder
{
	vector<TreeItem*> & data;
public:
	CorreleteOrder(vector<TreeItem*> & d) : data(d) {}
	bool operator()(const uint & a, const uint & b) const {
		return data[a]->variateset->correlation > data[b]->variateset->correlation;
	}
};

class CorreletePearsonOrder
{
	vector<TreeItem*> & data;
public:
	CorreletePearsonOrder(vector<TreeItem*> & d) : data(d) {}
	bool operator()(const uint & a, const uint & b) const {
		return data[a]->variateset->correlationPearson > data[b]->variateset->correlationPearson;
	}
};

class SetView : public QWidget
{
	Q_OBJECT
public:
	SetView();
	~SetView();
signals:
	void getCorrelation(vector<int> variates, float& corr);
	void getCorrelationPearson(vector<int> variates, float& corr);
	void getCoherence(vector<int> variates, float& corr);
	void sendSelectedSubset(vector<int> selectedset);
	void currentset(set<int> cset);
public slots:
	void getVariateSubsets(vector<VSubset> subsets);
	void getVarianteNames();
	void updateSortType(int type);
	void updateSecondSortType(int type);
	void getMaxLevel(int maxl);
	void setMaxDegree(const QString & maxd);
	void setMinDegree(const QString & mind);
	void setHideEmpty(int hiden);
	void subsetsContainChanged(int iscontained_);
	//void setJaccardDistance(int isJaccardUsed);
protected:
	QSize minimumSizeHint() const;
	QSize sizeHint() const;
	void paintEvent(QPaintEvent* event);
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
private:
	void computeItemPos(TreeItem* item, int xoffset, int& posy);
	void updateLayout();
	void getSubsetsProperties();
private:
	int maxLevel;
	int currenty;
	int maxdegree;
	int mindegree;
	int firstSortType;
	int secondSortType;
	bool isHiden;
	bool isSubsetsContained;   ////0---not contain  1---contain
	bool isJaccardUsed;
	float scale;
	TreeItem* currentItem;
	TreeItem* selectedItem;
	vector<int> sortorder;
	vector<TreeItem*> items;
	vector<TreeItem*> topLevelItems;
	QList<QColor> sortTypeColors;
	map<string, VariateSet*> hash;
	vector<VSubset> subsets;
	int nodewidth;
};

#endif // !SETVIEW_H