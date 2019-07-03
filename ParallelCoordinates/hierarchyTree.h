#include <vector>
#include <biclusters.h>
#include <QStringList>
#include <QWidget>
#include <QComboBox>
#include <QPainter>
#include <QMouseEvent>

using namespace std;

struct TreeNode
{
	int attributeNo;
	bool has_Clusters;
	//float size;
	QPointF pos;
	float start_angle;
	//float angle_range;
	int x;
	int y;
	int mod;
	int level;
	float correlate;
	TreeNode* parent;
	TreeNode(int a, TreeNode* p) { attributeNo = a; has_Clusters = false;  parent = p; }
	vector<TreeNode*> children;
};

class HierarchyTree : public QWidget
{
	Q_OBJECT
public:
	HierarchyTree(QList<QColor> cs);
	~HierarchyTree();
protected:
	void paintEvent(QPaintEvent* event);
	QSize minimumSizeHint() const;
	QSize sizeHint() const;
	void mouseDoubleClickEvent(QMouseEvent * event);
	public slots:
	void getSelectedClusters(vector<vector<int>> attributesets);
	void getVarianteNames(QStringList variatenames);
	void getSelectVariate(int No);
signals:
	void sendSelectedVariate(int No);
	void sendSelectedVariates(vector<int> variates);
	void getCorrelation(vector<int> variates, float& corr);
private:
	void destroyTree(TreeNode* node);
	void setup(TreeNode* node, int depth, int* nexts, int* offset);
	void addmods(TreeNode* node, int modsum = 0);
	void toPolarCoord();
private:
	TreeNode* treeRoot;
	QComboBox* combox;
	int selectAttributeNo;
	int maxlevel;
	QStringList variateNames;
	vector<TreeNode*> tNodes;
	QList<QColor> colors;
};
