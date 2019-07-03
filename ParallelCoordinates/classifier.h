#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <vector>
#include <utility>
#include "biclusters.h"

using namespace std;

const int DOT_PRODUCT = 0;
const int JACCARD = 1;

typedef
enum Linkage_Criterion
{
	SINGLE_LINKAGE,
	COMPLETE_LINKAGE,
	WEIGHTED_LINKAGE,
	ACCURATE_LINKAGE
}Linkage_Criterion;

struct Neighbor;

struct ClusterNode
{
	ClusterNode()
	{
		parent = NULL;
		l_child = NULL;
		r_child = NULL;
		is_active = true;
	}
	~ClusterNode()
	{
		for (int i = 0; i < neighbors.size(); i++)
		{
			delete neighbors[i];
		}
	}
	int idx;
	ClusterNode *parent;
	ClusterNode *l_child, *r_child;
	vector<Neighbor*> neighbors;
	bool is_active;
	bitset<defaultObjectNum>* obj;
};

struct Neighbor
{
	Neighbor(ClusterNode* c, float d)
	{
		cluster = c;
		distance = d;
	}
	~Neighbor()
	{
		delete cluster;
	}
	ClusterNode * cluster;
	float distance;
};

struct Linkage
{
	int left;
	int right;
	float dis;
	Linkage(int l, int r, float d) :left(l), right(r), dis(d){}
};

struct Inconsistent
{
	float meanHeight;
	float standardDeviation;
	int edgeNum;
	float value;
	Inconsistent()
	{
		meanHeight = 0;
		standardDeviation = 0;
		edgeNum = 0;
		value = 0.0;
	}
};

class Classifier
{
public:
	Classifier(vector<MaximalDimentionalSet*> mds, float* dis, int criteria, int function);
	~Classifier();
	vector<int> getCluter(int maxclust);
	vector<int> checkcut(QString criterion, float cutoff);
	vector<int> recluster(int clustId);
	vector<float> getDistance(QString criterion);
	vector<int> remergecluster(int clustId1, int clustID2);
private:
	void init_classifer(float* dis, int num);
	// classification with provided linkage_criteria and distance_function
	void classification();
	void calInconsistent();
	bool find_best_distance_neighbour(ClusterNode*& first, ClusterNode*& second, float& dis);
	ClusterNode* merge_cluster(ClusterNode* first, ClusterNode* second);
	float get_distance(ClusterNode* newc, ClusterNode* oldc);
	void signChild(ClusterNode* clust, int clsnum);
	void disconnect(ClusterNode* clust, bool* conn);
	void labeltree(ClusterNode* clust, bool* conn);
	vector<ClusterNode*> clusters;
	int clusterid;
	int objNum;
	int linkage_criteria;
	int distance_function;
	int clsnum;
	ClusterNode *cluster_root;
	vector<Linkage> order;   //merge in dis increase order
	vector<Inconsistent> Y;           //inconsistent value of each mergence
	vector<int> T;           //group id of each feature subspace
	vector<int> groupID;     //group id of each cluster
	vector<MaximalDimentionalSet*> selectedMDS;
	bool* conn;
};

#endif