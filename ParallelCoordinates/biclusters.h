#ifndef BICLUSTERS_H
#define BICLUSTERS_H

#include <QObject>
#include <vector>
#include <bitset>
#include <map>
#include <queue>
#include "1dtf\Volume.h"
#include "define.h"

using namespace std;
using std::bitset;

const int defaultObjectNum = 9249841;
const int defaultAttributeNum = 15;
struct ObjectSet;
struct MaximalDimentionalSet;
struct PCluster;




class RowOrder
{
public:
	RowOrder(uchar** d, int s) : data(d), size(s) {}
	bool operator()(const int & a, const int & b) const {
		//对每个属性均返回相应index的voxel值，如果前者小于后者返回true
		for (int i = 0; i < size; i++)
		{
			if (data[i][a] < data[i][b]) return true;
			else if (data[i][a] > data[i][b]) return false;
		}
		return false;
	}
private:
	uchar** data;
	int size;
};

class AscendOrder
{
public:
	AscendOrder(int *d) : data(d) {}
	~AscendOrder(){}
	bool operator()(const int & a, const int & b) const{
		return data[a] < data[b];
	}

private:
	int* data;
};

class Bicluster : public QObject
{
	Q_OBJECT
public:
	Bicluster();
	~Bicluster();
	friend class ObjectSet;
signals:
	void sendMaxDegree(int maxd);
	void clusterRegionChange();
	void sendClusterVoxels(vector<int> clusterVoxels, vector<int>clusterAttributes);
	void sendGlobalCluster(vector<vector<int>> clusterVoxels, vector<vector<int>> clusterAttributes);
	void sendVariateSubsets(vector<VSubset> variateSubsets);
	void sendDistanceMatrix(float* m, int dim);
	void sendFilterDatas(int* mIdx, int* cIdx, int fColNum);
	void sendDistanceMatrix(float* m, int dim, vector<MaximalDimentionalSet*> mds);
	public slots:
	void setVolDatas(vector<Volume *>& vols);
	void setVolDatas();
	void SelectedVariatesNo(vector<int> selectedNo);
	void getVariateSubsets();
	void getClusterNo(int No);
	//互信息
	void calCorrelation(vector<int> variates, float& corr);
	void calCoherence(vector<int> variates, float& coh);
	//Pearson Information
	void calCorrelationPearson(vector<int> variates, float& corr);

	void getGlobalSelect(int idx);   //the spatial selection results
	void getAGroup(vector<int> agroup);
	void getGlobalGroups(vector<vector<int>> groups);
	void getMaxORatio(double ratio);
	void getMinORatio(double ratio);
	void calCCScore(vector<int>& voxels, vector<int>& variables, float& score);
	void setSubsetsContained(int iscontained_);
	void setJaccardDistanceUsed(int isJaccardUsed_);

	void getGSIMValue(float);

private:
	void biningandAggregation();
	PCluster* findAttributePair(int a1, int a2);
	void MaPle();
	void updateMDSSelected();
	float* calSpatialSimilarity(PCluster* selectedSubspaces);
	void saveMDS(MaximalDimentionalSet* mds);
	void search(MaximalDimentionalSet* mds, int cycle);
	float ccScore(vector<MaximalDimentionalSet *> mds, bitset<defaultAttributeNum> attributes);  //calculate mean squared residue value
	//Mutual Information
	float correlationValue(vector<int> selectedNo);
	//Pearson
	float correlationValuePearson(vector<int> selectedNo);
	int getVoxelsNum(bitset<defaultObjectNum>* objs);
	float calMutual(bitset<defaultObjectNum> obj, int idx1, int idx2);
	float calMutual(float* random1,float* random2, int size, int binnum);
	float calPearson(bitset<defaultObjectNum> obj, int idx1, int idx2);
	float spatialDistance(int idx1, int idx2);
	float SelectedVariatesCorr(vector<int> selectedNo);
	void getMDSValueRange(vector<MaximalDimentionalSet *> subspaces);

	void Discrete();
	void findDiscreteAttributePair(int a1, int a2);
	void searchDiscrete(MaximalDimentionalSet* mds, int cycle);
	void saveDiscreteMDS(MaximalDimentionalSet* t_mds);
	//Calculate discrete field
	void calculateDiscreteField();
	//Calculate discrete Sd
	
	double calculateGSIM(int& pointIndex, int& attribute_idx1, int& attribute_idx2);

private:
	vector<Volume *> volDatas;
	vector<vector<PCluster*>> attributePair;
	vector<vector<MaximalDimentionalSet*>> attributeDiscretePair;
	PCluster* pClusters;
	uchar** dMatrix;               //original data matrix
	int filterColNum;
	int* markIdx;                  //volume idx to sample idx//markIdx表示相应不重复体素的第n个元素，如果当前元素与前一元素相同，则markIdx[i]指向markIdx[i-1]，如果当前元素与前一元素不同，则markIdx[i]=markIdx[i-1]+1
	int* corIdx;                   //sample idx to volume idx//如果markIdx[i]!=markIdx[i-1]，说明元素不重复了，因此corIdx[markIdx[order[i]]]记录了当前不重复元素的角标，也就是corIdx[markIdx[order[i]]]=order[i]//markIdx实现了从所有体素到不重复体素index的映射，corIdx实现了从不重复体素到所有体素的映射，也就是corIdx[markIdx[i]]=i
	
	int* mergeNum;//mergeNum表示每个不重复元素的个数，例如体素值为x的体素个数. mergeNum[i]表示第i个象征体素重复的元素个数，也就是merge number
	int sampleNum;                 //volume size
	int clusterNum;
	int attributeNum;
	int min_o;          //minimum object num //设置最低和最高的体素值，不在此体素值范围内的数据不再显示。过小的数据集无需显示，过大的数据集一般为背景等，不需显示
	int max_o;
	int min_o_f;        //minimum object num filtered
	int max_o_f;
	int min_a;          //minimum attribute num
	int max_a;
	int delta;          //User-specified clustering threshold
	int* coldiff;
	int* orderdiff;
	int binnum;
	int binwidth;
	vector<int> clusterVoxels;
	vector<int> clusterAttributes;
	bool isSaved;      //true -- read from files  false -- calculate
	bool isCoherenceSaved;
	bool isCorrelationSaved;
	bool isSubsetContained;
	bool isJaccardUsed;
	PCluster* selectClusters;
	bool isSelected;
	vector<bitset<defaultAttributeNum>> filenames;
	float* H;		//mean squared residue value
	float* SSM;    //spatial similarity matrix
	float filter_scale;
	float maxo_ratio;
	float mino_ratio;
	vector<MaximalDimentionalSet*> globalselected;
	vector<VSubset> variateSubsets;
	vector<vector<int>> gclusterv;
	vector<vector<int>> gclustera;
	map<string, float> coherence;
	map<string, float> correlation;
	int add_count;
	int add_time;
	vector<int> selectNo;

	//梯度值
	vector<vector<Vector3d>> discreteData;
	vector<double> discreteValue;
	float GSIM = 0;
	vector<MaximalDimentionalSet*> discreteMDS;
};

//存储双聚类每个集合中的体素数量？
struct ObjectSet
{
	bitset<defaultObjectNum>* objset;
	int voxelnum;
	Bicluster* parent;

	ObjectSet(Bicluster* parent_, bitset<defaultObjectNum>* objset_)
	{
		parent = parent_;
		objset = objset_;
		voxelnum = -1;
	}
	~ObjectSet()
	{
		if (objset)
		delete objset;
	}
	int getVoxelsNum()
	{
		if (voxelnum > 0)
			return voxelnum;
		int total = 0;
		//Debug 20180129
		for (int i = 0; i < objset->size()&&i<parent->filterColNum; i++)
			total += parent->mergeNum[i] * (*objset)[i];
		voxelnum = total;
		return voxelnum;
		//return objectSet->count();
	}
};

struct MaximalDimentionalSet
{
public:
	MaximalDimentionalSet()
	{
		attributeSet = NULL;
		objectSet = NULL;
		voxelnum = -1;
	}
	MaximalDimentionalSet(bitset<defaultAttributeNum>* a, ObjectSet* o)
	{
		attributeSet = a;
		objectSet = o;
		
		voxelnum = -1;
	}
	MaximalDimentionalSet(MaximalDimentionalSet* m, Bicluster* parent_)
	{
		attributeSet = new bitset<defaultAttributeNum>(*(m->getAttributeSet()));
		objectSet = new ObjectSet(parent_, new bitset<defaultObjectNum>(*(m->getObjectSet()->objset)));
		voxelnum = -1;
	}
	~MaximalDimentionalSet()
	{
		if (attributeSet)
			delete attributeSet;
		if (objectSet)
			delete objectSet;
	}
	bool operator ()(const MaximalDimentionalSet* a, const MaximalDimentionalSet* b){
		return a->objectSet->getVoxelsNum() > b->objectSet->getVoxelsNum();
	}
	bitset<defaultAttributeNum>* getAttributeSet() { return attributeSet; }
	ObjectSet* getObjectSet() { return objectSet; }
	void setIdx(int i) { idx = i; }
	int getIdx() { return idx; }
public:
	bool isSelected;
	float coherent;
	vector<pair<int, int>> vRange; //first -- min, second -- max
private:
	bitset<defaultAttributeNum>* attributeSet;
	ObjectSet* objectSet;
	int idx;
	vector<float> correlation;
	int voxelnum;
};

//存储多个mds图
class PCluster
{
public:
	PCluster() {}
	~PCluster()
	{
		for (int i = 0; i < MDS.size(); i++)
		{
			delete MDS[i];
		}
	}
	void addMDS(MaximalDimentionalSet* mds)
	{
		MDS.push_back(mds);
	}
	vector<MaximalDimentionalSet*>& getMDS() { return MDS; }
private:
	vector<MaximalDimentionalSet*> MDS;
};
#endif
