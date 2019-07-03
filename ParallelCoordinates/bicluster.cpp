#include "biclusters.h"
#include "SimpleMatrix.h"
#include <string>
#include <fstream>
#include<io.h>
//#include <AtlBase.h>
#include <set>
#include <ctime>
#include <sstream>


void getFiles(string path, vector<string>& files){

	long long hFile = 0;
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1){
		do{

			if ((fileinfo.attrib &  _A_SUBDIR)){
				continue;
			}
			else{

				if (strlen(fileinfo.name) == 1 && fileinfo.name[0] == '.'
					|| strlen(fileinfo.name) == 2 && fileinfo.name[0] == '.' && fileinfo.name[1] == '.')
					continue;

				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
				//ownname.push_back(fileinfo.name);
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

//void getJustCurrentFile(LPCTSTR path, vector<LPCTSTR> & files)
//{
//	//find the first file
//	_tfinddata64_t c_file;
//	intptr_t hFile;
//	TCHAR root[MAX_PATH];
//	_tcscpy(root, path);
//	_tcscat(root, _T("\\*.*"));
//	hFile = _tfindfirst64(root, &c_file);
//	if (hFile == -1)
//		return;
//	do
//	{
//		if (_tcslen(c_file.name) == 1 && c_file.name[0] == _T('.')
//			|| _tcslen(c_file.name) == 2 && c_file.name[0] == _T('.') && c_file.name[1] == _T('.'))
//			continue;
//		TCHAR *fullPath = new TCHAR[MAX_PATH];
//		_tcscpy(fullPath, path);
//		_tcscat(fullPath, _T("\\"));
//		_tcscat(fullPath, c_file.name);
//		if (c_file.attrib&_A_SUBDIR)
//		{
//			;
//		}
//		else
//		{
//			files.push_back(fullPath);
//			//files.push_back(p.assign(path).append("\\").append(fileinfo.name) );  
//		}
//	} while (_tfindnext64(hFile, &c_file) == 0);
//	_findclose(hFile);
//}

Bicluster::Bicluster()
{
	min_a = 2;
	//Debug 20180203 setValue
	max_a = 3;
	min_o_f = 1000;
	max_o_f = 5000;
	//maxo_ratio = 0.1;
	//mino_ratio = 0.002;	
	maxo_ratio = 1;
	mino_ratio = 0;
	
	filter_scale = 0.;
	//Debug 20180203 setValue
	delta = 20;
	isSaved = false;
	isSelected = false;
	isSubsetContained = false;
	isJaccardUsed = false;

	selectClusters = new PCluster;
	H = NULL;


	GSIM = 0.90;
	if (!discreteMDS.empty()) {
		discreteMDS.clear();
	}
}

Bicluster::~Bicluster()
{
}

void Bicluster::setVolDatas(vector<Volume *>& vols)
{
	attributeNum = vols.size();
	assert(vols.size() <= 1);
	volDatas = vols;
	sampleNum = volDatas[0]->getTotalSize();

	pClusters = new PCluster;

	//biningandAggregation();
	calculateDiscreteField();
	if(isSaved)
	{
		//LPCTSTR = wchar_t
		//vector<LPCTSTR> files;
		vector<string> files;
		vector<VSubset> variateSubsets;
		getFiles("res", files);
		//getJustCurrentFile(_T("res"), files);
		int idx = 0;
		max_a = 0;
		for (int i = 0; i < files.size(); i++)
		{
			ifstream fin(files[i]);
			vector<int> variatesubset;
			if(!fin.is_open())
			{
				std::cout<<"open error!"<<endl;
				return;
			}
			bitset<defaultAttributeNum> t_attributeset;
			int c = 0;
			while (files[i][c] != '\0')
			{
				if (files[i][c] == '_')
				{
					t_attributeset[(int)(files[i][c - 1] - 48)] = true;
					variatesubset.push_back((int)(files[i][c - 1] - 48));
				}	
				c++;
			}

			while (!fin.eof())
			{
				string strobjectset;
				fin>>strobjectset;
				if(strobjectset.empty()) continue;
				ObjectSet* objectset = new ObjectSet(this, new bitset<defaultObjectNum>(strobjectset));
				bitset<defaultAttributeNum>* attributeset = new bitset<defaultAttributeNum>(t_attributeset);
				MaximalDimentionalSet* tmds = new MaximalDimentionalSet(attributeset, objectset);
				tmds->setIdx(idx++);
				vector<MaximalDimentionalSet*> mdss;
				mdss.push_back(tmds);
				tmds->coherent = ccScore(mdss, *attributeset);
				pClusters->addMDS(tmds);
			}
			filenames.push_back(t_attributeset);
			fin.close();

			if (t_attributeset.count() > max_a)
				max_a = t_attributeset.count();
		}
	}
	else
	{
		float run_time = 0;
		clock_t start, finish;
		start = clock();
		Discrete();
		finish = clock();
		run_time = (finish - start) / CLOCKS_PER_SEC;
		cout<<"Discrete time: "<<run_time<<endl;
		clusterNum = pClusters->getMDS().size();
	}
	//ifstream fin("coherence.txt");
	//if (fin.is_open())
	//{
	//	while (!fin.eof())
	//	{
	//		string idx;
	//		float coh;
	//		fin >> idx;
	//		fin >> coh;
	//		coherence[idx] = coh;
	//	}
	//	isCoherenceSaved = true;
	//}
	//else
	//	isCoherenceSaved = false;
	//fin.close();

	//ifstream fin2("correlation.txt");
	//if (fin2.is_open())
	//{
	//	while (!fin2.eof())
	//	{
	//		string idx;
	//		float corr;
	//		fin2 >> idx;
	//		fin2 >> corr;
	//		correlation[idx] = corr;
	//	}
	//	isCorrelationSaved = true;
	//}
	//else
	//	isCorrelationSaved = false;
	//fin2.close();
	emit sendMaxDegree(max_a);
	cout << "subspace num: " << pClusters->getMDS().size() << endl;
	getVariateSubsets();
	cout << "get variate sets." << endl;
	std::cout << "cluster finish" << endl;
}
void Bicluster::getGSIMValue(float value) {

	GSIM = value;
	setVolDatas();
}
void Bicluster::setVolDatas()
{
	if (volDatas.empty()) return;
	sampleNum = volDatas[0]->getTotalSize();
	if(!discreteMDS.empty())
		discreteMDS.clear();

		float run_time = 0;
		clock_t start, finish;
		start = clock();
		Discrete();
		finish = clock();
		run_time = (finish - start) / CLOCKS_PER_SEC;
		cout << "Discrete time: " << run_time << endl;

	emit sendMaxDegree(max_a);
	getVariateSubsets();
	cout << "get variate sets." << endl;
	//std::cout << "cluster finish" << endl;
}
double Bicluster::calculateGSIM(int& pointIndex, int& attribute_idx1, int& attribute_idx2) {

	Vector3d gi = discreteData[attribute_idx1][pointIndex];
	Vector3d gj = discreteData[attribute_idx2][pointIndex];

	double giNorm = (gi).norm();
	double gjNorm = (gj).norm();

	if (giNorm == 0 && gjNorm == 0) {
		return 0;
	}
	if (abs(gi.x - gj.x) < 1e-9&&abs(gi.y - gj.y) < 1e-9&&abs(gi.z - gj.z) < 1e-9) {
		return 1;
	}
	//Debug 20180306
	if (giNorm == 0 || gjNorm == 0) {
		return 0;
	}

	double pointMulti = (gi).x*(gj).x + (gi).y*(gj).y + (gi).z*(gj).z;
	//��ֵ��Զ����0
	double result = 4 * pointMulti*pointMulti / (giNorm*gjNorm*(giNorm + gjNorm)*(giNorm + gjNorm));
	//if (pointIndex > 10000 && pointIndex < 15000)
	//cout << pow(result, 4)<<"\t"<< result << endl;
	return pow(result,4);
}
//ȥ���ظ����أ������ڴ�
void Bicluster::biningandAggregation()
{
	binnum = 256;
	binwidth = 256.0 / binnum;
	dMatrix = new uchar*[attributeNum];
	for (int i = 0; i < attributeNum; i++)
	{
		dMatrix[i] = volDatas[i]->getVolume();
	}
	vector<int> order;
	for (int i = 0; i < sampleNum; i++)
		order.push_back(i);
	//�������Ե�˳�򣬰�������ֵ��С����ĽǱ��������յ�order˳���voxel��Ӧ����ֵ�������ӣ�
	sort(order.begin(), order.end(), RowOrder(dMatrix, attributeNum));
	//markIdx��ʾ��Ӧ���ظ����صĵ�n��Ԫ�أ������ǰԪ����ǰһԪ����ͬ����markIdx[i]ָ��markIdx[i-1]�������ǰԪ����ǰһԪ�ز�ͬ����markIdx[i]=markIdx[i-1]+1
	//���markIdx[i]!=markIdx[i-1]��˵��Ԫ�ز��ظ��ˣ����corIdx[markIdx[order[i]]]��¼�˵�ǰ���ظ�Ԫ�صĽǱ꣬Ҳ����corIdx[markIdx[order[i]]]=order[i]
	//markIdxʵ���˴��������ص����ظ�����index��ӳ�䣬corIdxʵ���˴Ӳ��ظ����ص��������ص�ӳ�䣬Ҳ����corIdx[markIdx[i]]=i
	markIdx = new int[sampleNum];
		markIdx[order[0]] = 0;
		int c = 0;
		//corIdx��ʾͳ����Ӧ����ֵ��Ӧ�ĽǱ�
		corIdx = new int[sampleNum];
		corIdx[c] = order[0];
		//����������Ҫ���˵���ͬ������ֵ������¼������ֵ���ֵĴ���
		for (int i = 1; i < sampleNum; i++)
		{
			int diff = 0;
			for (int j = 0; j < attributeNum; j++)
				diff += abs(dMatrix[j][order[i]] - dMatrix[j][order[i - 1]]);

			if (diff == 0)
			{
				markIdx[order[i]] = c;
			}
			else
			{
				markIdx[order[i]] = ++c;
				corIdx[c] = order[i];
			}
		}
	//filterColNum��ʾ���ղ��ظ�������Ԫ�ظ���
		filterColNum = ++c;
		
		mergeNum = new int[filterColNum];
		memset(mergeNum, 0, filterColNum * sizeof(int));
		for (int i = 0; i < sampleNum; i++)
			mergeNum[markIdx[i]]++;
	
		//һ��Ԫ�ع��˽��������ͷ��źţ�sendFilterDatas
		emit sendFilterDatas(markIdx, corIdx, filterColNum);
}

void Bicluster::MaPle()
{
	add_count = 0;
	add_time = 0;
	coldiff = new int[filterColNum];
	orderdiff = new int[filterColNum];
	attributePair.resize(attributeNum);
	for (int i = 0; i < attributeNum; i++)
		attributePair[i].resize(attributeNum);

	min_o = sampleNum * mino_ratio;
	max_o = sampleNum * maxo_ratio;
	//min_o = filterColNum * mino_ratio;
	//max_o = filterColNum * maxo_ratio;
	//������������Ѱ�ҷ���pScore ������Maximal dimension set��ά�ȼ��ϣ������Ƕ�άͶӰ
	for (int i = 0; i < attributeNum; i++)
	{
		for (int j = i + 1; j < attributeNum; j++)
		{
			PCluster* ap = findAttributePair(i, j);
			attributePair[i][j] = ap;
		}
	}

	//Ȼ�󣬶���ÿ�������Զ�Ӧ��Maximal dimension set��������ȱ�����
	for (int i = 0; i < attributeNum - min_a + 1; i++)
	{
		for (int j = i + 1; j < attributeNum - min_a + 2; j++)
		{
	//int i = 1, j = 2;
			PCluster* ap = attributePair[i][j];
			vector<MaximalDimentionalSet *> mds = ap->getMDS();
			for (int k = 0; k < mds.size(); k++)
			{
				search(mds[k], 1);
			}
		}
	}
}
//Calculate discrete field
void Bicluster::calculateDiscreteField() {

	if (volDatas.size()<1) {
		cout << "The volume Data is Empty. Please load data firstly." << endl;
		return;
	}
	if (!discreteData.empty()) {

		discreteData.clear();
		cout << "The discrete field vectors have already existed." << endl;
		//return;
	}
	discreteData.resize(attributeNum);
	for (int i = 0;i < attributeNum;i++) {
		discreteData[i].resize(volDatas[0]->getTotalSize());
	}
	uchar** volumeData = new uchar*[attributeNum];
	for (int i = 0; i < attributeNum; i++)
	{
		volumeData[i] = volDatas[i]->getVolume();
		Vector3i volumeDim = volDatas[i]->getDimension();
		cout << volumeDim << endl;
		//int a;
		//cin >> a;
		//vector<Vector3d> currentDistanceValue;
		//���߽���ݶ�ֵ��ֵΪ0
		int totalSize = volDatas[i]->getTotalSize();

		for (int j = 0;j < totalSize;j++) {
			Vector3d tempValue;
			int z = j / (volumeDim.y*volumeDim.x);
			int y = (j % (volumeDim.y*volumeDim.x))/ (volumeDim.x);
			int x = j % (volumeDim.x);
			if (x==0/*||x==volumeDim.x-1*/) {
				tempValue.x = 0;
			}
			else {
				//tempValue.x = (volumeData[i][j + 1] - volumeData[i][j - 1])*1.0f / 255.0f;
				//tempValue.x = (volumeData[i][j] - volumeData[i][j - 1])*100.0f / 255.0f;
				//tempValue.x = ((int)(volumeData[i][j]) - (int)(volumeData[i][j - 1]) +255.0f)/ 510.0f;
				tempValue.x = ((int)(volumeData[i][j]) - (int)(volumeData[i][j - 1])) / 255.0f;

			}
			if (y==0/*||y==volumeDim.y-1*/) {
				tempValue.y = 0;
			}
			else {
				//tempValue.y = (volumeData[i][j + volumeDim.x] - volumeData[i][j - volumeDim.x])*1.0f/ 255.0f;
				//tempValue.y = (volumeData[i][j] - volumeData[i][j - volumeDim.x])*100.0f / 255.0f;
				//tempValue.y = ((int)(volumeData[i][j]) - (int)(volumeData[i][j - volumeDim.x]) + 255.0f) / 510.0f;
				tempValue.y = ((int)(volumeData[i][j]) - (int)(volumeData[i][j - volumeDim.x])) / 255.0f;

			}
			if (z==0/*||z==volumeDim.z-1*/) {
				tempValue.z = 0;
			}
			else {
				//tempValue.z = (volumeData[i][j + volumeDim.x*volumeDim.y] - volumeData[i][j - volumeDim.x*volumeDim.y])*1.0f/ 255.0f;
				//tempValue.z = (volumeData[i][j] - volumeData[i][j - volumeDim.x*volumeDim.y])*100.0f / 255.0f;
				//tempValue.z = ((int)(volumeData[i][j]) - (int)(volumeData[i][j - volumeDim.x*volumeDim.y]) + 255.0f) / 510.0f;
				tempValue.z = ((int)(volumeData[i][j]) - (int)(volumeData[i][j - volumeDim.x*volumeDim.y])) / 255.0f;

			}
			//discreteData.x = sqrt(3)*sin(z) + cos(y);
			//discreteData.y = sqrt(2)*sin(x) + sqrt(3)*cos(y);
			//discreteData.z = sin(z) + sqrt(2)*cos(y);
			discreteData[i][j] = tempValue;
			
			//currentDistanceValue.push_back(discreteData);
		}
		
	}
	for (int i = 10000;i < 15000;i++) {
		cout << discreteData[0][i] << discreteData[1][i] << discreteData[2][i] << endl;
	}
	cout << "The discrete value has been calculated." << endl;
}
void Bicluster::findDiscreteAttributePair(int a1, int a2){
	bitset<defaultAttributeNum>* attribute = new bitset<defaultAttributeNum>;
	bitset<defaultObjectNum>* object = new bitset<defaultObjectNum>;
	(*attribute)[a1] = true;
	(*attribute)[a2] = true;
	for (int k = 0; k < sampleNum; k++)
	{
		//?
		double gsim = calculateGSIM(k, a1, a2);
		if (k % 100000 == 0) {
			cout << "gsim is : "<<gsim << endl;
		}

		if (gsim >= GSIM) {
			(*object)[k] = true;
		}
		else {
			(*object)[k] = false;
		}
		//Need Modification
	}
	
	MaximalDimentionalSet* mds = new MaximalDimentionalSet(attribute, new ObjectSet(this, object));

	discreteMDS.push_back(mds);
	//pClusters->addMDS(mds);
}
void Bicluster::searchDiscrete(MaximalDimentionalSet* mds, int cycle)
{
	//��ǰmds�����е����Լ���
	bitset<defaultAttributeNum>* attributeset = mds->getAttributeSet();
	//max_a��ʾ�û��趨���������ֵ�������ǰ���Լ��ϵ�����������ֵ�����˳�search
	if (attributeset->count() >= max_a)
	{
		return;
	}
	//��ǰmds�����еĶ��󼯺�
	bitset<defaultObjectNum>* objectset = mds->getObjectSet()->objset;
	//maxa��ʾ��ǰ��������ֵ��index
	int maxa = -1;
	//Find the maximum variate in list dk
	for (int i = 0; i < attributeset->size(); i++)
	{
		if ((*attributeset)[i] == true)
			maxa = i;
	}
	//��ǰmds�����еĶ��󼯺�
	bitset<defaultObjectNum>* reside = mds->getObjectSet()->objset;
	//����mds������ð������ķ�ʽ�����ģ���˿��Բ�����maxa֮ǰ�����ݼ��ϣ���maxa���������趨����ֵ
	for (int i = maxa + 1; i < attributeNum; i++)
	{
		ObjectSet* intermediateRes = new ObjectSet(this, new bitset<defaultObjectNum>(*objectset));
		bool isEmpty = false;
		for (int j = 0; j < attributeset->size(); j++)
		{
			if ((*attributeset)[j] == false)
				continue;
			
			//����jһ���ǵ�ǰmds����������֮һ����˲ſ��Դ�(a,b,..c)��չ��(a,b,...c,d)
			//�¼��϶�Ӧ��mds
			MaximalDimentionalSet* ap = attributeDiscretePair[j][i];

			MaximalDimentionalSet* pmds = ap;
			bitset<defaultObjectNum>* po = pmds->getObjectSet()->objset;
			bitset<defaultObjectNum>* intersect = new bitset<defaultObjectNum>;

			bitset<defaultObjectNum>* obj = intermediateRes->objset;
			(*intersect) = (*obj)&(*po);
			int voxelNum = (*intersect).count();
			//if (voxelNum > min_o /*&& voxelNum < max_o && voxelNum < max_o_f*/) {
				delete intermediateRes;
				intermediateRes = new ObjectSet(this, intersect);
			//}
			//delete intersect;
			//else {
			//	isEmpty = true;
			//	delete intersect;
			//	break;
			//}
		}

		bitset<defaultObjectNum>* obj = intermediateRes->objset;
		
		//ԭʼ���ݼ�ʣ�µ�
		(*reside) = ((*reside) & (~(*obj)));
		bitset<defaultAttributeNum>* t_attributeset = new bitset<defaultAttributeNum>(*attributeset);
		(*t_attributeset)[i] = true;
		MaximalDimentionalSet* tmds = new MaximalDimentionalSet(t_attributeset, new ObjectSet(this, obj));
		//Discover Bug 20180205
		if (tmds->getAttributeSet()->count() == max_a)
		{
			saveDiscreteMDS(tmds);
			cout << "Save......" << endl;
			continue;
		}
		searchDiscrete(tmds, cycle + 1);
		if (tmds->getAttributeSet()->count() > 2)
			delete tmds;

	}
	cout << "Search key value ......\n";

	//if (reside->count() == objectset->count())
	//	saveMDS(mds);
	//else
	//{
	float voxelNum = (*reside).count();
	//float voxelNum = reside->count();
	if (voxelNum > min_o && voxelNum < max_o /*&& voxelNum < max_o_f*/)
		saveDiscreteMDS(mds);
	cout << "Save......finished" << endl;
	//}
}

//�����������mds���뵽discreteMDS��
void Bicluster::saveDiscreteMDS(MaximalDimentionalSet* t_mds)
{
	vector<MaximalDimentionalSet*>::iterator itr;
	bitset<defaultAttributeNum>* attributeset = t_mds->getAttributeSet();
	bitset<defaultObjectNum>* object = t_mds->getObjectSet()->objset;
	bitset<defaultObjectNum>* tmp = new bitset<defaultObjectNum>;
	int object_num = (*object).count();

	for (itr = discreteMDS.begin(); itr != discreteMDS.end(); ++itr) {
		if ((*attributeset) != (*(*itr)->getAttributeSet()))
			continue;
		if ((*object) != (*((*itr)->getObjectSet()->objset)))
			continue;
		else return;
		bitset<defaultObjectNum>* element = (*itr)->getObjectSet()->objset;
		*tmp = (*object)&(*element);
		float voxelNum = min(object_num, (int)(*(*itr)->getObjectSet()->objset).count());
		if ((*tmp).count() / voxelNum > filter_scale) {
			break;
		}
	}
	
	delete tmp;
	if (itr == discreteMDS.end()) {
		cout<<"Save object number is : "<< object_num <<endl;
		discreteMDS.push_back(new MaximalDimentionalSet(t_mds, this));
	}
}


void Bicluster::Discrete()
{
	add_count = 0;
	add_time = 0;
	//coldiff = new int[filterColNum];
	//orderdiff = new int[filterColNum];
	attributeDiscretePair.resize(attributeNum);
	for (int i = 0; i < attributeNum; i++)
		attributeDiscretePair[i].resize(attributeNum);
	discreteMDS.clear();
	min_o = sampleNum * mino_ratio;
	max_o = sampleNum * maxo_ratio;

	for (int i = 0; i < attributeNum; i++)
	{
		for (int j = i + 1; j < attributeNum; j++)
		{
			findDiscreteAttributePair(i, j);
			//attributeDiscretePair[i][j] = discreteMDS[discreteMDS.size()-1];
			attributeDiscretePair[i][j] = discreteMDS.back();
			
		}
	}
	cout << "Get attribute discrete pair finished.\n";
	//Ȼ�󣬶���ÿ�������Զ�Ӧ��Maximal dimension set��������ȱ�����
	for (int i = 0; i < attributeNum - min_a + 1; i++)
	{
		for (int j = i + 1; j < attributeNum - min_a + 2; j++)
		{
			//int i = 1, j = 2;
			MaximalDimentionalSet* mds = attributeDiscretePair[i][j];
			//Debug 20180305
			searchDiscrete(mds, 1);
		}
	}
}

//Parameter a1 and a2: attribute
//�ҵ�������������Ӧ����������mdsͼ
PCluster* Bicluster::findAttributePair(int a1, int a2)
{
	bitset<defaultObjectNum>* intersect = new bitset<defaultObjectNum>;
	PCluster* pc = new PCluster();
	for (int k = 0; k < filterColNum; k++)
	{
		//what it means?
		//coldiff[k]��ʾ����֮���ͬһ�����ص���������֮��Ĳ�ֵ
		coldiff[k] = (dMatrix[a1][corIdx[k]] + 1 - dMatrix[a2][corIdx[k]]) * binwidth - 1;
		orderdiff[k] = k;
	}
	//���չ��˺��Ԫ�أ���������֮��Ĳ�ֵ����Ӧ�ĽǱ�ֵ��С��������
	sort(orderdiff, orderdiff + filterColNum, AscendOrder(coldiff));

	//��������orderdiff�����Ӧ��colddiff[orderdiff[i]]ֵ��С��������

	int s_start = 0, s_end = 1, pre_end;
	//total��ʾmerge��Ԫ��ֵ
    int total = mergeNum[orderdiff[s_start]];
	while (s_start < filterColNum)
	{
		int pscore = 0;
		pre_end = s_end;

		while (s_end < filterColNum)
		{
			//pscore��ʾ������ͬ���صģ���ͬ������������ͬ�����Ĳ�ֵ���Ĳ�ֵ����Ӧ�����е�pscore
			pscore = coldiff[orderdiff[s_end]] - coldiff[orderdiff[s_start]];
			//������ֵ�����ݣ������ݼ��������ǡ���Ϊһ���������ݳ�����ֵ�����������������ݶ�����������Ϊcoldiff[orderdiff[s_end]]�ǵ����ġ����break
			if (pscore > delta || pscore < 0) break;
			total += mergeNum[orderdiff[s_end]];
			s_end++;
		}
		
		//���ص�����ֵ�����趨����С�������������������ԶԵ������������Ӧ��mds�����뵽pcluster��
		if (s_end > pre_end /*&& s_end - s_start >= min_o*/&&total >= min_o)
		{
			MaximalDimentionalSet* mds = new MaximalDimentionalSet(new bitset<defaultAttributeNum>, new ObjectSet(this, new bitset<defaultObjectNum>));
			bitset<defaultAttributeNum>* attribute = mds->getAttributeSet();
			(*attribute)[a1] = true;
			(*attribute)[a2] = true;
			bitset<defaultObjectNum>* object = mds->getObjectSet()->objset;
			//ѡ�����������Ķ�Ӧ����
			for (int k = s_start; k < s_end; k++)
				(*object)[orderdiff[k]] = true;
			vector<MaximalDimentionalSet *>& t_mds = pc->getMDS();
			if (t_mds.size() > 0)
			{
				//��ȡ��ǰpcluster�����һ��mds���жϵ�ǰmds��֮�ཻ��Ԫ�ظ���
				bitset<defaultObjectNum>* t_obj = t_mds.back()->getObjectSet()->objset;
				//�ж��������ݼ��е��ཻԪ�ظ���������������ܹ���ȡ����Ԫ�ص�index����getVoxelNum���Ի�ȡ�ص�Ԫ�ص�����
				(*intersect) = (*object)&(*t_obj);
				//float min_num = min(object->count(), t_obj->count());
				//if (intersect->count() / min_num > filter_scale)
				float num0 = getVoxelsNum(intersect);
				float num1 = mds->getObjectSet()->getVoxelsNum();
				float num2 = t_mds.back()->getObjectSet()->getVoxelsNum();
				//��ǰ���õ������Զ���Ϊ����֮�����Сֵ����Ҫ��Ϊ����
				//Need modification
				//��������ֵ����һ����ֵ��˵������֮������Ժܸߣ���Ӧ�÷�Ϊ������ͬ��mds
				if (num0 / min(num1, num2) > 0.6)
				//if (num0 * 1.0 / num1 > filter_scale)
				{
					continue;
				}
				//if (num0 * 1.0 / num2 > filter_scale)
				//{
				//	delete t_mds.back();
				//	t_mds.pop_back();
				//}
			}
			//���������󣬽���mds���뵽pc�У���Ϊ����������һ����mds��
			pc->addMDS(mds);
			//pClusters->addMDS(mds);
		}
		//���ò�ѭ����������Ҫɾ���ײ���Ӧ��merge number�Ը�����һ������
		total -= mergeNum[orderdiff[s_start]];
		s_start++;
	}
	delete intersect;
	return pc;
}

void Bicluster::search(MaximalDimentionalSet* mds, int cycle)
{
	//��ǰmds�����е����Լ���
	bitset<defaultAttributeNum>* attributeset = mds->getAttributeSet();
	//max_a��ʾ�û��趨���������ֵ�������ǰ���Լ��ϵ�����������ֵ�����˳�search
	if (attributeset->count() >= max_a)
	{
		return;
	}
	//��ǰmds�����еĶ��󼯺�
	bitset<defaultObjectNum>* objectset = mds->getObjectSet()->objset;
	//maxa��ʾ��ǰ��������ֵ��index
	int maxa = -1;
	//Find the maximum variate in list dk
	for (int i = 0; i < attributeset->size(); i++)
	{
		if ((*attributeset)[i] == true)
			maxa = i;
	}
	//��ǰmds�����еĶ��󼯺�
	bitset<defaultObjectNum>* reside = mds->getObjectSet()->objset;
	//����mds������ð������ķ�ʽ�����ģ���˿��Բ�����maxa֮ǰ�����ݼ��ϣ���maxa���������趨����ֵ
	for (int i = maxa + 1; i < attributeNum; i++)
	{
		list<ObjectSet*> intermediateRes;
		intermediateRes.push_back(new ObjectSet(this, new bitset<defaultObjectNum>(*objectset)));
		bitset<defaultObjectNum>* tmp = new bitset<defaultObjectNum>;
		for (int j = 0; j < attributeset->size(); j++)
		{
			if ((*attributeset)[j] == false)
				continue;
			int count = intermediateRes.size();
			//����jһ���ǵ�ǰmds����������֮һ����˲ſ��Դ�(a,b,..c)��չ��(a,b,...c,d)
			//���α����Ѵ��ڵ����ԣ�
			PCluster* ap = attributePair[j][i];

			while (count > 0)
			{
				bitset<defaultObjectNum>* obj = intermediateRes.front()->objset;
				intermediateRes.pop_front();
				count--;
				int c = 0;
				//������չ���ԶԵ�maximal dimension set
				for (int k = 0; k < ap->getMDS().size(); k++)
				{
					MaximalDimentionalSet* pmds = ap->getMDS()[k];
					bitset<defaultObjectNum>* po = pmds->getObjectSet()->objset;
					bitset<defaultObjectNum>* intersect = new bitset<defaultObjectNum>;
					//�ҵ���ǰmds����������չ�����Զ�Ӧ��mds���ݼ�֮�������ԡ������ⲿѭ���趨�˵�ǰ���ԶԵ�������mds���ݼ���������ж��β�����չ���ԶԵ�����mds��ض�
					(*intersect) = (*obj)&(*po);
					float voxelNum = getVoxelsNum(intersect);
					//float voxelNum = intersect->count();

					//һ���������չ���Զ��뵱ǰmds���ཻ���ظ��������ε�������
					if (voxelNum > min_o /*&& voxelNum < max_o && voxelNum < max_o_f*/)
					{
						list<ObjectSet*>::iterator iter;
						for (iter = intermediateRes.begin(); iter != intermediateRes.end(); ++iter)
						{
							bitset<defaultObjectNum>* element = (*iter)->objset;
							//���㵱ǰmds����չ�����ཻ���صĸ�����������ཻ������ԭ���ݼ��ཻ�����ݽ��
							(*tmp) = (*intersect)&(*element);
							//�����������ཻ������ԭʼ���ݼ��Ĵ�С��ͬ��������ѭ����
							if (tmp->count() == intersect->count() || tmp->count() == element->count())
								break;
							//float min_num = min(intersect->count(), element->count());
							//if (tmp->count() / min_num > filter_scale)
							//Need Modification
							//����������ظ����뵱ǰ���ؼ�
							if (getVoxelsNum(tmp) / min(voxelNum, (*iter)->getVoxelsNum()*1.0f) > filter_scale)
							{
								//(*element) = (*intersect) | (*element);
								//(*tmp) = (*intersect) | (*element);
								//(*element) = (*tmp);
								break;
							}
						}
						if (iter == intermediateRes.end())
							intermediateRes.push_back(new ObjectSet(this, intersect));
					}
					else
						delete intersect;
				}
				delete obj;
			}
		}
		delete tmp;
		while (intermediateRes.size())
		{
			bitset<defaultObjectNum>* obj = intermediateRes.front()->objset;
			//����
			(*reside) = ((*reside) & (~(*obj)));
			intermediateRes.pop_front();
			bitset<defaultAttributeNum>* t_attributeset = new bitset<defaultAttributeNum>(*attributeset);
			(*t_attributeset)[i] = true;
			MaximalDimentionalSet* tmds = new MaximalDimentionalSet(t_attributeset, new ObjectSet(this, obj));
			if (tmds->getAttributeSet()->count() == max_a)
			{
				saveMDS(tmds);
				continue;
			}
			search(tmds, cycle + 1);
			if (tmds->getAttributeSet()->count() > 2)
				delete tmds;
		}
		intermediateRes.clear();
	}

	//if (reside->count() == objectset->count())
	//	saveMDS(mds);
	//else
	//{
		float voxelNum = getVoxelsNum(reside);
		//float voxelNum = reside->count();
		if (voxelNum > min_o && voxelNum < max_o /*&& voxelNum < max_o_f*/)
			saveMDS(mds);
	//}
}

//�����������mds���뵽pcluster��
void Bicluster::saveMDS(MaximalDimentionalSet* t_mds)
{
	vector<MaximalDimentionalSet*>::iterator itr;
	bitset<defaultAttributeNum>* attributeset = t_mds->getAttributeSet();
	bitset<defaultObjectNum>* object = t_mds->getObjectSet()->objset;
	bitset<defaultObjectNum>* tmp = new bitset<defaultObjectNum>;
	int object_num = t_mds->getObjectSet()->getVoxelsNum();
	for (itr = pClusters->getMDS().begin(); itr != pClusters->getMDS().end(); ++itr)
	{
		if ((*attributeset) != (*(*itr)->getAttributeSet()))
			continue;
		bitset<defaultObjectNum>* element = (*itr)->getObjectSet()->objset;
		*tmp = (*object)&(*element);
		//if (tmp->count() == object->count() || tmp->count() == element->count())
		//	break;
		/*float min_num = min(object->count(), element->count());
		if (tmp->count() / min_num > filter_scale)*/

		//Need Modification
		float voxelNum = min(object_num, (*itr)->getObjectSet()->getVoxelsNum());
			if(getVoxelsNum(tmp) / voxelNum > filter_scale)
		{
			//(*tmp) = (*object) | (*element);
			//(*element) = (*tmp);
			break;
		}
	}
	delete tmp;
	if (itr == pClusters->getMDS().end())
	{
		//cout<<t_mds->getObjectSet()->count()<<endl;
		pClusters->addMDS(new MaximalDimentionalSet(t_mds, this));
		//string filename = "res/";
		//for (int i = 0; i < attributeset->size(); i++)
		//{
		//	if ((*attributeset)[i])
		//		filename += to_string(i) + "_";
		//}
		//ofstream fout(filename, std::ofstream::out | std::ofstream::app);
		//if (!fout.is_open())
		//{
		//	std::cout << "open error!" << endl;
		//	return;
		//}
		//fout << *(t_mds->getObjectSet()) << endl;
		//fout.close();
		//vector<MaximalDimentionalSet*> mdss;
		//mdss.push_back(t_mds);
		//t_mds->coherent = ccScore(mdss, *attributeset);
	}
}

int Bicluster::getVoxelsNum(bitset<defaultObjectNum>* objs)
{
	add_count++;
	//clock_t start, finish;
	//start = clock();
	int total = 0;
	for (int i = 0; i < objs->size()&& i< filterColNum; i++)
	{
		
		total += mergeNum[i] * (*objs)[i];
	}
	//finish = clock();
	//add_time += (finish - start);
	return total;
	//return objs->count();
}



float Bicluster::ccScore(vector<MaximalDimentionalSet *> mds, bitset<defaultAttributeNum> a_union)
{
	if (mds.size() > 1)
	{
		float min_coh = FLT_MAX;
		for (int i = 0; i < mds.size(); i++)
		{
			if (mds[i]->coherent < min_coh)
				min_coh = mds[i]->coherent;
		}
		return min_coh;
	}

	clusterNum = mds.size();
	bitset<defaultObjectNum> o_union;
	for (int i = 0; i < clusterNum; i++)
	{
		bitset<defaultObjectNum>* o1 = mds[i]->getObjectSet()->objset;
		o_union = o_union | (*o1);
	}

	float* mat = new float[a_union.count() * o_union.count()];
	float* row_mean = new float[o_union.count()];   //row -- object
	float* col_mean = new float[a_union.count()];   //col -- attribute
	float mean = 0;

	int row = 0, col;
	for (int r = 0; r < o_union.size(); r++)
	{
		if (o_union[r])
		{
			col = 0;
			for (int c = 0; c < a_union.size(); c++)
			{
				if (a_union[c])
				{
					mat[row * a_union.count() + col] = dMatrix[c][corIdx[r]];
					mean += dMatrix[c][corIdx[r]];
					col++;
				}
			}
			row++;
		}
	}
	mean /= row * col;

	for (int r = 0; r < row; r++)
	{
		row_mean[r] = 0;
		for (int c = 0; c < col; c++)
			row_mean[r] += dMatrix[c][corIdx[r]];
		row_mean[r] /= col;
	}

	for (int c = 0; c < col; c++)
	{
		col_mean[c] = 0;
		for (int r = 0; r < row; r++)
			col_mean[c] += dMatrix[c][corIdx[r]];
		col_mean[c] /= row;
	}

	float h = 0;
	for (int r = 0; r < row; r++)
	for (int c = 0; c < col; c++)
	{
		h += pow(mat[r * col + c] - row_mean[r] - col_mean[c] + mean, 2);
	}
	h /= row * col;
	delete[]mat;
	delete[]row_mean;
	delete[]col_mean;
	return h;
}

float Bicluster::spatialDistance(int idx1, int idx2)
{
	Vector3i dim = volDatas[0]->getDimension();
	int x1 = idx1 % dim.x;
	int y1 = (idx1 - x1) % dim.x % dim.y;
	int z1 = idx1 / dim.x / dim.y;

	int x2 = idx2 % dim.x;
	int y2 = (idx2 - x2) % dim.x % dim.y;
	int z2 = idx1 / dim.x / dim.y;

	float dis = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2);

	return sqrt(dis);
}

float* Bicluster::calSpatialSimilarity(PCluster* selectedSubspaces)
{
	clusterNum = selectedSubspaces->getMDS().size();
	SSM = new float[clusterNum * clusterNum];
	//ifstream fin("spatialsim.txt");
	//if (fin.is_open())
	//{
	//	for (int i = 0; i < clusterNum; i++)
	//	for (int j = 0; j < clusterNum; j++)
	//	{
	//		if (fin.eof())
	//		{
	//			cout << "out of range!" << endl;
	//			return;
	//		}
	//		fin >> SSM[i * clusterNum + j];
	//	}
	//	return;
	//}

	//bool* clusterRegion1 = new bool[sampleNum];
	//memset(clusterRegion1, 0, sampleNum * sizeof(bool));
	//bool* clusterRegion2 = new bool[sampleNum];
	//memset(clusterRegion2, 0, sampleNum * sizeof(bool));

	//float* dis1 = new float[sampleNum];
	//float* dis2 = new float[sampleNum];

	vector<MaximalDimentionalSet *> mds = selectedSubspaces->getMDS();
	clusterNum = mds.size();
	clock_t start, finish;
	//int* vol = new int[clusterNum];
	//std::memset(vol, 0, clusterNum * sizeof(int));
	start = clock();
	//for (int i = 0; i < clusterNum; i++)
	//{
	//	bitset<defaultObjectNum>* objs = mds[i]->getObjectSet();
	//	for (int k = 0; k < sampleNum; k++)
	//	{
	//		vol[i] += (*objs)[markIdx[k]];
	//	}
	//}
	for (int i = 0; i < clusterNum; i++)
	for (int j = i; j < clusterNum; j++)
		{
			bitset<defaultObjectNum>* o1 = mds[i]->getObjectSet()->objset;
			bitset<defaultObjectNum>* o2 = mds[j]->getObjectSet()->objset;

			//float vOverlap = 0;
			//for (int k = 0; k < sampleNum; k++)
			//{
			//	vOverlap += ((*o1)[markIdx[k]] & (*o2)[markIdx[k]]);
			//}
			//float sim = vOverlap / min(vol[i], vol[j]);

			//Need Modification
			//�ռ������ԣ���Ҫ�޸�ΪJaccard���룬����������Ƿ���Ҫ�޸ģ�
			//Debug 20180203
			if (isJaccardUsed) {
				float vOverlap = ((*o1)&(*o2)).count();
				float sim = vOverlap / min(o1->count(), o2->count());

				SSM[i * clusterNum + j] = sqrt(1 - sim);
				SSM[j * clusterNum + i] = SSM[i * clusterNum + j];
			}
			else {
				float vOverlap = ((*o1)&(*o2)).count();
				float sim = vOverlap / (o1->count() + o2->count() - vOverlap);
				
				SSM[i * clusterNum + j] = (1 - sim);
				SSM[j * clusterNum + i] = SSM[i * clusterNum + j];
			}
			
		}
	finish = clock();
	float run_time = (finish - start) / CLOCKS_PER_SEC;
	cout << "sim cal time: " << run_time << endl;
	return SSM;
	//ofstream out("spatialsim.txt");
	//if (!out.is_open())
	//	cout << "open error" << endl;
	//for (int i = 0; i < clusterNum; i++)
	//{
	//	for (int j = 0; j < clusterNum; j++)
	//		out << SSM[i * clusterNum + j] << " ";
	//	out << endl;
	//}
	//out.close();
}

//Add function: Pearson correlation coffiencet.
float Bicluster::calPearson(bitset<defaultObjectNum> obj, int idx1, int idx2) {
	uchar* vol1 = volDatas[idx1]->getVolume();
	uchar* vol2 = volDatas[idx2]->getVolume();
	float hist1D1[256];
	float hist1D2[256];
	float hist2D[256 * 256];
	//Init histogram
	for (int i = 0; i < 256; i++) {
		hist1D1[i] = 0;
		hist1D2[i] = 0;
	}
	for (int i = 0; i < 256 * 256; i++) {
		hist2D[i] = 0;
	}
	//Calculate value distribution
	for (int i = 0; i < volDatas[idx1]->getTotalSize(); i++) {
		//Only work for feature subspace
		//Debug 20180202 �޸�index
		if (!obj[i]) continue;
		//if (!obj[markIdx[i]]) continue;
		hist1D1[vol1[i]] += 1;
		hist1D2[vol2[i]] += 1;
		hist2D[vol1[i] * 256 + vol2[i]] += 1;
	}

	float totalvoxelnum = obj.count();
	
	double EX = 0.0f, EY = 0.0f, EXY = 0.0f;
	double DX = 0.0f, Ex2 = 0.0f;
	double DY = 0.0f, Ey2 = 0.0f;

	//Calculate EX, EY, Ex2, Ey2
	for (int i = 0; i < 256; i++) {
		hist1D1[i] /= totalvoxelnum;
		Ex2 += i*i*hist1D1[i];
		EX += i*hist1D1[i];

		hist1D2[i] /= totalvoxelnum;
		Ey2 += i*i*hist1D2[i];
		EY += i*hist1D2[i];

	}
	DX = Ex2 - EX*EX;
	DY = Ey2 - EY*EY;
	
	if (abs(EXY - EX*EY) < FLT_EPSILON)
		return 0;

	//���߷����Ϊ0
	if (DX < FLT_EPSILON&&DY < FLT_EPSILON)
		return 1;

	if (DX < FLT_EPSILON) DX = 1;
	if (DY < FLT_EPSILON) DY = 1;

	//Calculate EXY
	for (int i = 0;i < 256;i++) {
		for (int j = 0;j < 256;j++) {
			int idx = i * 256 + j;
			hist2D[idx] /= totalvoxelnum;
			EXY += i*j*hist2D[idx];
		}
	}
	//Get person correlation coefficient and detect the error of out of range
	double pearson = (EXY - EX*EY) / (sqrt(DX)*sqrt(DY));
	if (pearson > 1-FLT_EPSILON|| pearson < -1 + FLT_EPSILON) {
		cout << "Result Error: Pearson correlation coefficient!" << endl;
	}
	//Need return absolute value?
	return abs(pearson);
}

float Bicluster::calMutual(float* random1, float* random2, int size, int binnum)
{
	float maxv = FLT_MIN;
	float minv = FLT_MAX;
	for (int i = 0; i < size; i++)
	{
		if (random1[i] < FLT_MAX)
		{
			if (random1[i] > maxv) maxv = random1[i];
			if (random1[i] < minv) minv = random1[i];
		}

		if (random2[i] < FLT_MAX)
		{
			if (random2[i] > maxv) maxv = random2[i];
			if (random2[i] < minv) minv = random2[i];
		}
	}

	float binsize = (maxv - minv) / binnum;
	float* hist1D1 = new float[binnum];
	float* hist1D2 = new float[binnum];
	float* hist2D = new float[binnum * binnum];
	memset(hist1D1, 0, binnum * sizeof(float));
	memset(hist1D2, 0, binnum * sizeof(float));
	memset(hist2D, 0, binnum * binnum * sizeof(float));

	for (int i = 0; i < size; i++)
	{
		hist1D1[(int)(random1[i] / binsize)]++;
	}

	for (int i = 0; i < size; i++)
	{
		hist1D2[(int)(random2[i] / binsize)]++;
	}

	for (int i = 0; i < size; i++)
	{
		hist2D[(int)(random1[i] / binsize) * binnum + (int)(random2[i] / binsize)]++;
	}

	for (int i = 0; i < binnum; i++)
	{
		hist1D1[i] /= size;
		hist1D2[i] /= size;
	}

	for (int i = 0; i < binnum * binnum; i++)
	{
		hist2D[i] /= size;
	}
	float mumual = 0;
	for (int i = 0; i < binnum * binnum; i++)
	{
		int firstidx = i % binnum;
		int secondidx = i / binnum;
		if (hist1D1[firstidx] > FLT_EPSILON && hist1D2[secondidx] > FLT_EPSILON && hist2D[i] > FLT_EPSILON)
			mumual += hist2D[i] * log(hist2D[i] / hist1D1[firstidx] / hist1D2[secondidx]);
	}

	return mumual / log(2.0);
}


float Bicluster::calMutual(bitset<defaultObjectNum> obj, int idx1, int idx2)
{
	uchar* vol1 = volDatas[idx1]->getVolume();
	uchar* vol2 = volDatas[idx2]->getVolume();
	float hist1D1[256];
	float hist1D2[256];
	float hist2D[256 * 256];
	for (int i = 0; i < 256; i++)
	{
		//hist1D1[vol1[obj[i]]];
		hist1D1[i] = 0;
		hist1D2[i] = 0;
	}
	for (int i = 0; i < 256 * 256; i++)
	{
		hist2D[i] = 0;
	}

	for (int i = 0; i < volDatas[idx1]->getTotalSize(); i++)
	{
		//Debug 20180202 �޸�index
		if (!obj[i]) continue;
		//if (!obj[markIdx[i]]) continue;
		hist1D1[vol1[i]] += 1;
		hist1D2[vol2[i]] += 1;
		hist2D[vol1[i] * 256 + vol2[i]] += 1;
	}

	float totalvoxelnum = obj.count();
	//cout<<"voxel num: "<<obj.count()<<endl;
	for (int i = 0; i < 256; i++)
	{
		hist1D1[i] /= totalvoxelnum;
	}
	for (int i = 0; i < 256; i++)
	{
		hist1D2[i] /= totalvoxelnum;
	}
	for (int i = 0; i < 256; i++)
	for (int j = 0; j < 256; j++)
	{
		int idx = i * 256 + j;
		if (hist1D1[i] < FLT_EPSILON && hist1D2[j] <  FLT_EPSILON && hist2D[idx] > FLT_EPSILON)
			cout << "error!" << endl;
		hist2D[idx] /= totalvoxelnum;
	}
	float mumual = 0;
	for (int i = 0 ; i < 256; i++)
	for (int j = 0; j < 256; j++)
	{
		int idx = i * 256 + j;
		if (hist1D1[i] > FLT_EPSILON && hist1D2[j] > FLT_EPSILON && hist2D[idx] > FLT_EPSILON)
			mumual += hist2D[idx] * log2(hist2D[idx] / hist1D1[i] / hist1D2[j]);
	}

	if (mumual < FLT_EPSILON)
	{
		cout << "error!" << endl;
	}
	return mumual;
}

//���ֵ������Ϣ
float Bicluster::correlationValue(vector<int> selectedNo)
{
	static int number = 0;
	if (selectedNo.size() <= 1) return -1;
	std::stringstream result;
	std::copy(selectedNo.begin(), selectedNo.end(), std::ostream_iterator<int>(result, "_"));
	string idx = result.str();

	//if (isCorrelationSaved)
	//{
	//	return correlation[idx];
	//}

	bitset<defaultObjectNum> obj;
	bitset<defaultAttributeNum> attributeset;
	//������Ӧ���Ե�index
	for (int i = 0; i < selectedNo.size(); i++)
	{
		attributeset[selectedNo[i]] = true;
	}

	for (int i = 0; i < pClusters->getMDS().size(); i++)
	{
		if (!pClusters->getMDS()[i]->isSelected) continue;
		bitset<defaultAttributeNum>* t_attributeset = pClusters->getMDS()[i]->getAttributeSet();
		bitset<defaultAttributeNum> intersect = (*t_attributeset) & attributeset;

		//˵��attributeset��t_attributeset���Ӽ���t_attributeset�ϴ�
		if (intersect.count() == attributeset.count())
		{
			if (isSubsetContained ||
				//˵��t_attributeset��sttributeset�����ı�����ȫһ��
				(!isSubsetContained && (t_attributeset->count() == attributeset.count())))
			{
				//����
				bitset<defaultObjectNum>* t_obj = pClusters->getMDS()[i]->getObjectSet()->objset;
				obj = obj | (*t_obj);
			}
		}
	}

	float min_mutual = FLT_MAX;
	float min_pearson = FLT_MAX;
	if (obj.count() == 0) {
		min_mutual = -1;
		min_pearson = -1;
	}
		
	else
	{
		for (int i = 0; i < selectedNo.size(); i++)
		for (int j = i + 1; j < selectedNo.size(); j++)
		{
			//Need Modification
			min_mutual = min(min_mutual, calMutual(obj, selectedNo[i], selectedNo[j]));
			//min_pearson = min(min_pearson, calPearson(obj, selectedNo[i], selectedNo[j]));
		}
	}
	
	cout << "group size is : "<<selectedNo.size() << ", min_mutual is : " << min_mutual << endl;
	//ofstream fout("correlation.txt", std::ofstream::app);
	//fout << idx << endl;
	//fout << min_mutual << endl;
	return min_mutual;
}


//����Ϣ
void Bicluster::calCorrelation(vector<int> variates, float& corr)
{
	selectNo.clear();
	selectNo = variates;
	corr = correlationValue(variates);
}

float Bicluster::correlationValuePearson(vector<int> selectedNo)
{
	static int number = 0;
	if (selectedNo.size() <= 1) return -1;
	std::stringstream result;
	std::copy(selectedNo.begin(), selectedNo.end(), std::ostream_iterator<int>(result, "_"));
	string idx = result.str();

	//if (isCorrelationSaved)
	//{
	//	return correlation[idx];
	//}

	bitset<defaultObjectNum> obj;
	bitset<defaultAttributeNum> attributeset;
	//������Ӧ���Ե�index
	for (int i = 0; i < selectedNo.size(); i++)
	{
		attributeset[selectedNo[i]] = true;
	}

	for (int i = 0; i < pClusters->getMDS().size(); i++)
	{
		if (!pClusters->getMDS()[i]->isSelected) continue;
		bitset<defaultAttributeNum>* t_attributeset = pClusters->getMDS()[i]->getAttributeSet();
		bitset<defaultAttributeNum> intersect = (*t_attributeset) & attributeset;

		//˵��attributeset��t_attributeset���Ӽ���t_attributeset�ϴ�
		if (intersect.count() == attributeset.count())
		{
			if (isSubsetContained ||
				//˵��t_attributeset��sttributeset�����ı�����ȫһ��
				(!isSubsetContained && (t_attributeset->count() == attributeset.count())))
			{
				//����
				bitset<defaultObjectNum>* t_obj = pClusters->getMDS()[i]->getObjectSet()->objset;
				obj = obj | (*t_obj);
			}
		}
	}

	//float min_mutual = FLT_MAX;
	float min_pearson = FLT_MAX;
	if (obj.count() == 0) {
		//min_mutual = -1;
		min_pearson = -1;
	}

	else
	{
		for (int i = 0; i < selectedNo.size(); i++)
			for (int j = i + 1; j < selectedNo.size(); j++)
			{
				//Need Modification
				//min_mutual = min(min_mutual, calMutual(obj, selectedNo[i], selectedNo[j]));
				min_pearson = min(min_pearson, calPearson(obj, selectedNo[i], selectedNo[j]));
			}
	}
	cout << "group size is : " << selectedNo.size() << ", min_pearson is : " << min_pearson << endl;
	//cout << "Group number is : " << number++ << " , group size is : " << selectedNo.size() << ", min_mutual is : " << min_mutual << " , " << "min_pearson is : " << min_pearson << endl;
	//ofstream fout("correlation.txt", std::ofstream::app);
	//fout << idx << endl;
	//fout << min_mutual << endl;
	return min_pearson;
}
//�趨Pearson���ϵ����ֵ
void Bicluster::calCorrelationPearson(vector<int> variates, float& corr)
{
	selectNo.clear();
	selectNo = variates;
	corr = correlationValuePearson(variates);
}

void Bicluster::calCoherence(vector<int> variates, float& coh)
{
	coh = SelectedVariatesCorr(variates);
}

void Bicluster::getClusterNo(int idx)
{
	globalselected.clear();
	for (int i = 0; i < volRegions.size(); i++)
	{
		memset(volRegions[i], 0, sampleNum * sizeof(uchar));
	}
	
	MaximalDimentionalSet* tmds;
	if (isSelected)
		tmds = selectClusters->getMDS()[idx];
	else
		tmds = pClusters->getMDS()[idx];
	bitset<defaultAttributeNum>* attributeset = tmds->getAttributeSet();
	bitset<defaultObjectNum>* objectset = tmds->getObjectSet()->objset;
	clusterVoxels.clear();
	clusterAttributes.clear();
	for (int i = 0; i < attributeset->size(); i++)
	{
		if ((*attributeset)[i]) clusterAttributes.push_back(i);
	}
	selectNo.clear();
	selectNo = clusterAttributes;
	//filtered
	//for (int i = 0; i < objectset->size(); i++)
	//{
	//	if((*objectset)[i]) clusterVoxels.push_back(corIdx[i]);
	//}
	set<int> voxels;
	for (int i = 0; i < objectset->size(); i++)
	{
		//if ((*objectset)[i]) voxels.insert(corIdx[markIdx[i]]);
		//Debug ����ʱ���ִ���,�޸�����
		if ((*objectset)[i]) voxels.insert(corIdx[i]);
		//voxels.insert(corIdx[i] * (*objectset)[i]);
	}
	if (!(*objectset)[markIdx[0]])
		voxels.erase(0);
	clusterVoxels.resize(voxels.size());
	copy(voxels.begin(), voxels.end(), clusterVoxels.begin());
	//for (int i = 0; i < sampleNum; i++)
	//{
	//	if((*objectset)[markIdx[i]]) clusterRegion[i] = 255;
	//}
	int voxelnum = 0;
	for (int i = 0; i < sampleNum; i++)
	{
		volRegions[0][i] = 255 * (*objectset)[markIdx[i]];
		voxelnum += (*objectset)[markIdx[i]];
	}
	cout << "voxel size:" << voxelnum * 1.0 / sampleNum << endl;
	std::cout << "subspace size:" << objectset->count() * 1.0 / filterColNum << endl;
	//cout << "coherence: " << tmds->coherent << endl;
	emit clusterRegionChange();
	emit sendClusterVoxels(clusterVoxels, clusterAttributes);
}

float Bicluster::SelectedVariatesCorr(vector<int> selectedNo)
{
	selectNo.clear();
	selectNo = selectedNo;
	std::stringstream result;
	std::copy(selectedNo.begin(), selectedNo.end(), std::ostream_iterator<int>(result, "_"));
	string idx = result.str();

	//if (isCoherenceSaved)
	//{
	//	return coherence[idx];
	//}

	vector<MaximalDimentionalSet *> t_mds;
	bitset<defaultAttributeNum> attributeset;
	for (int i = 0; i < selectedNo.size(); i++)
	{
		attributeset[selectedNo[i]] = true;
	}

	for (int i = 0; i < pClusters->getMDS().size(); i++)
	{
		if (!pClusters->getMDS()[i]->isSelected) continue;
		bitset<defaultAttributeNum>* t_attributeset = pClusters->getMDS()[i]->getAttributeSet();
		bitset<defaultAttributeNum> intersect = (*t_attributeset) & attributeset;
		if (intersect.count() == attributeset.count())
		{
			if (isSubsetContained ||
				(!isSubsetContained && (t_attributeset->count() == attributeset.count())))
			{
				t_mds.push_back(pClusters->getMDS()[i]);
			}
		}
	}
	//ofstream fout("coherence.txt", std::ofstream::app);
	float score;
	if (t_mds.size() == 0)
		score = -1;
	else
		score = ccScore(t_mds, attributeset);
	//fout << idx << endl;
	//fout << score << endl;
	return score;

}

void Bicluster::SelectedVariatesNo(vector<int> selectedNo) {

	selectNo.clear();
	selectNo = selectedNo;

	if (selectNo.size() <= 0) {
		isSelected = false;
		return;
	}
	isSelected = true;
	selectClusters->getMDS().clear();
	int selectedClusterNum = -1;
	bitset<defaultAttributeNum> attributeset;
	for (int i = 0; i < selectedNo.size(); i++)
	{
		attributeset[selectedNo[i]] = true;
	}
	for (int i = 0;i < discreteMDS.size();i++) {
		bitset<defaultAttributeNum>* t_attributeset = discreteMDS[i]->getAttributeSet();
		bitset<defaultAttributeNum> intersect = (*t_attributeset) & attributeset;
		//˵��������ͬ
		if (intersect.count() == attributeset.count() && t_attributeset->count() == attributeset.count()) {
			selectedClusterNum = i;
			break;
		}
	}
	if (selectedClusterNum == -1) {
		cout << "System error in calculating discrete mds." << endl;
		return;
	}
	Volume* volume;
	MaximalDimentionalSet* currentMDS = discreteMDS[selectedClusterNum];
	bitset<defaultObjectNum>* currentObject = currentMDS->getObjectSet()->objset;

	//Need Modification

	for (int i = 0; i < volRegions.size(); i++)
	{
		memset(volRegions[i], 0, sampleNum * sizeof(uchar));
	}
	int voxelnum = 0;
	for (int i = 0; i < sampleNum; i++)
	{
		volRegions[0][i] = 255 * (*currentObject)[i];
		voxelnum += (*currentObject)[i];
	}
	cout << "voxel size:" << voxelnum * 1.0 / sampleNum << endl;
	//std::cout << "subspace size:" << currentObject->count() * 1.0 / filterColNum << endl;

	emit clusterRegionChange();

}

//void Bicluster::SelectedVariatesNo(vector<int> selectedNo)
//{
//	selectNo.clear();
//	selectNo = selectedNo;
//	if (selectedNo.size())
//	{
//		isSelected = true;
//		selectClusters->getMDS().clear();
//		vector<int> selectedClusterNum;
//		bitset<defaultAttributeNum> attributeset;
//		for (int i = 0; i < selectedNo.size(); i++)
//		{
//			attributeset[selectedNo[i]] = true;
//		}
//
//		for (int i = 0; i < pClusters->getMDS().size(); i++)
//		{
//			if (!pClusters->getMDS()[i]->isSelected) continue;
//			bitset<defaultAttributeNum>* t_attributeset = pClusters->getMDS()[i]->getAttributeSet();
//			bitset<defaultAttributeNum> intersect = (*t_attributeset) & attributeset;
//			if (intersect.count() == attributeset.count() && 
//				(isSubsetContained || (!isSubsetContained && (t_attributeset->count() == attributeset.count())))
//				)
//			{
//				selectClusters->addMDS(pClusters->getMDS()[i]);
//				selectedClusterNum.push_back(i);
//			}
//		}
//		if (selectedClusterNum.size() == 0)
//			return;
//		clusterNum = selectedClusterNum.size();
//		if (H) delete[]H;
//		H = calSpatialSimilarity(selectClusters);
//		//H = new float[clusterNum * clusterNum];
//		//for (int i = 0; i < clusterNum; i++)
//		//for (int j = 0; j < clusterNum; j++)
//		//{
//		//	H[i * clusterNum + j] = SSM[selectedClusterNum[i] * pClusters->getMDS().size() + selectedClusterNum[j]];
//		//}
//		//ofstream out("test.txt");
//		//for (int i = 0; i < clusterNum; i++)
//		//{
//		//	for (int j = i + 1; j < clusterNum; j++)
//		//	{
//		//		out << H[i * clusterNum + j] << " ";
//		//	}
//		//}
//		//out.close();
//		emit sendDistanceMatrix(H, clusterNum, selectClusters->getMDS());
//	}
//	else
//	{
//		isSelected = false;
//	}
//}

void Bicluster::getVariateSubsets()
{
	variateSubsets.clear();
	vector<MaximalDimentionalSet*> mdss = pClusters->getMDS();
	for (int i = 0; i < mdss.size(); i++)
	{
		if (!mdss[i]->isSelected) continue;
		bitset<defaultAttributeNum> t_attributeset = *(mdss[i]->getAttributeSet());
		string a_set;
		for (int i = 0; i < t_attributeset.size(); i++)
		{
			if (t_attributeset[i])
				a_set += std::to_string(i) + "_";
		}

		vector<VSubset>::iterator iter;
		bool existed = false;
		for (iter = variateSubsets.begin(); iter != variateSubsets.end(); ++iter)
		{
			if (a_set == iter->first)
				break;
		}
		if (iter == variateSubsets.end())
			variateSubsets.push_back(make_pair(a_set, 1));
		else
			iter->second++;
	}

	emit sendVariateSubsets(variateSubsets);
}

void Bicluster::getGlobalSelect(int idx)
{
	MaximalDimentionalSet* tmds;
	if (isSelected)
		tmds = selectClusters->getMDS()[idx];
	else
		tmds = pClusters->getMDS()[idx];
	globalselected.push_back(tmds);

	bitset<defaultAttributeNum>* attributeset = tmds->getAttributeSet();
	bitset<defaultObjectNum>* objectset = tmds->getObjectSet()->objset;
	vector<int> cVoxels;
	vector<int> cAttributes;
	for (int i = 0; i < attributeset->size(); i++)
	{
		if ((*attributeset)[i]) cAttributes.push_back(i);
	}
	gclustera.push_back(cAttributes);
	set<int> voxels;
	for (int i = 0; i < objectset->size(); i++)
	{
		if ((*objectset)[i]) voxels.insert(corIdx[i]);
	}
	cVoxels.resize(voxels.size());
	copy(voxels.begin(), voxels.end(), cVoxels.begin());
	gclusterv.push_back(cVoxels);
	int voxelnum = 0;
	for (int i = 0; i < volRegions.size(); i++)
	{
		memset(volRegions[i], 0, sampleNum * sizeof(uchar));
	}
	for (int k = 0; k < globalselected.size() && k < 4; k++)
	{
		objectset = globalselected[k]->getObjectSet()->objset;
		for (int i = 0; i < sampleNum; i++)
		{
			if ((*objectset)[markIdx[i]])
			{
				volRegions[k][i] = 255;
				voxelnum++;
			}
		}
	}
	emit clusterRegionChange();
	emit sendGlobalCluster(gclusterv, gclustera);
}

void Bicluster::getAGroup(vector<int> agroup)
{
	globalselected.clear();
	vector<MaximalDimentionalSet*> mdss = pClusters->getMDS();
	for (int i = 0; i < volRegions.size(); i++)
	{
		memset(volRegions[i], 0, sampleNum * sizeof(uchar));
	}
	clusterVoxels.clear();
	set<int> voxels;
	bitset<defaultAttributeNum> totalattr;
	for (int i = 0; i < agroup.size(); i++)
	{
		int idx = agroup[i];
		MaximalDimentionalSet* tmds = selectClusters->getMDS()[idx];
		bitset<defaultObjectNum>* objectset = tmds->getObjectSet()->objset;
		bitset<defaultAttributeNum>* attribute = tmds->getAttributeSet();

		for (int j = 0; j < objectset->size(); j++)
		{
			if ((*objectset)[j]) voxels.insert(corIdx[j]);
		}

		for (int j = 0; j < sampleNum; j++)
		{
			if ((*objectset)[markIdx[j]])
			{
				volRegions[0][j]++;
			}
		}
		totalattr = totalattr | (*attribute);
	}
	clusterVoxels.resize(voxels.size());
	copy(voxels.begin(), voxels.end(), clusterVoxels.begin());

	vector<int> selectedNo;
	for (int i = 0; i < totalattr.size(); i++)
	{
		if (totalattr[i])
			selectedNo.push_back(i);
	}
	emit sendClusterVoxels(clusterVoxels, selectedNo);

	float maxnum = 0;
	for (int i = 0; i < sampleNum; i++)
	{
		if (volRegions[0][i] > maxnum)
			maxnum = volRegions[0][i];
	}

	for (int i = 0; i < sampleNum; i++)
	{
		volRegions[0][i] = volRegions[0][i] / maxnum * 255;
	}
	emit clusterRegionChange();
}

void Bicluster::getGlobalGroups(vector<vector<int>> groups)
{
	globalselected.clear();
	vector<MaximalDimentionalSet*> mdss = pClusters->getMDS();
	for (int i = 0; i < volRegions.size(); i++)
	{
		memset(volRegions[i], 0, sampleNum * sizeof(uchar));
	}

	for (int k = 0; k < groups.size() && k < 4; k++)
	{
		vector<int> agroup = groups[k];
		vector<int> cVoxels;
		vector<int> cAttributes;
		set<int> voxels;
		for (int i = 0; i < agroup.size(); i++)
		{
			voxels.clear();
			cAttributes.clear();
			int idx = agroup[i];
			MaximalDimentionalSet* tmds = selectClusters->getMDS()[idx];
			bitset<defaultObjectNum>* objectset = tmds->getObjectSet()->objset;
			bitset<defaultAttributeNum>* attribute = tmds->getAttributeSet();
			for (int j = 0; j < attribute->size(); j++)
			{
				if ((*attribute)[j]) cAttributes.push_back(j);
			}
			gclustera.push_back(cAttributes);
			for (int j = 0; j < objectset->size(); j++)
			{
				if ((*objectset)[j]) voxels.insert(corIdx[j]);
			}
			for (int j = 0; j < sampleNum; j++)
			{
				if ((*objectset)[markIdx[j]])
				{
					volRegions[k][j]++;
				}
			}
		}
		cVoxels.resize(voxels.size());
		copy(voxels.begin(), voxels.end(), cVoxels.begin());
		gclusterv.push_back(cVoxels);
		float maxnum = 0;
		for (int i = 0; i < sampleNum; i++)
		{
			if (volRegions[k][i] > maxnum)
				maxnum = volRegions[k][i];
		}

		for (int i = 0; i < sampleNum; i++)
		{
			volRegions[k][i] = volRegions[k][i] / maxnum * 255;
		}
	}

	emit clusterRegionChange();
	emit sendGlobalCluster(gclusterv, gclustera);
}

void Bicluster::updateMDSSelected()
{
	max_o = maxo_ratio * sampleNum;
	min_o = mino_ratio * sampleNum;
	for (int i = 0; i < pClusters->getMDS().size(); i++)
	{
		MaximalDimentionalSet* mds = pClusters->getMDS()[i];
		bitset<defaultAttributeNum>* t_attributeset = mds->getAttributeSet();
		bitset<defaultObjectNum>* t_object = mds->getObjectSet()->objset;
		if (t_object->count() >= min_o && t_object->count() <= max_o)
			mds->isSelected = true;
		else
			mds->isSelected = false;
	}
	getVariateSubsets();
}

void Bicluster::getMaxORatio(double ratio)
{
	maxo_ratio = ratio / 100.0;
	updateMDSSelected();
}

void Bicluster::getMinORatio(double ratio)
{
	mino_ratio = ratio / 100.0;
	updateMDSSelected();
}

void Bicluster::calCCScore(vector<int>& voxels, vector<int>& variables, float& score)
{
	score = 0;
	for (int i = 0; i < variables.size(); i++)
	for (int j = i + 1; j < variables.size(); j++)
		{
		int idxi = variables[i];
		int idxj = variables[j];
		int maxdiff = dMatrix[voxels[0]][idxi] - dMatrix[voxels[0]][idxj];
		int mindiff = dMatrix[voxels[0]][idxi] - dMatrix[voxels[0]][idxj];
		for (int k = 1; k < voxels.size(); k++)
			{
			int diff = dMatrix[voxels[k]][idxi] - dMatrix[voxels[k]][idxj];
			if (diff > maxdiff)
			{
				maxdiff = diff;
				cout << (int)dMatrix[voxels[k]][idxi] << " " << (int)dMatrix[voxels[k]][idxj] << endl;
			}
			if (diff < mindiff)
			{
				mindiff = diff;
				cout << (int)dMatrix[voxels[k]][idxi] << " " << (int)dMatrix[voxels[k]][idxj] << endl;
			}
			}
		if (maxdiff - mindiff > score) score = maxdiff - mindiff;
		}
}

void Bicluster::getMDSValueRange(vector<MaximalDimentionalSet *> subspaces)
{
	for (int k = 0; k < subspaces.size(); k++)
	{
		MaximalDimentionalSet* mds = subspaces[k];
		bitset<defaultAttributeNum>* t_attributeset = mds->getAttributeSet();
		bitset<defaultObjectNum>* t_object = mds->getObjectSet()->objset;
		mds->vRange.resize(t_attributeset->size());
		for (int i = /*0*/1; i < /*t_attributeset->size()*/2; i++)
		{
			mds->vRange[i].first = INT_MAX;
			mds->vRange[i].second = INT_MIN;
			if (!(*t_attributeset)[i])
				continue;

			for (int j = 0; j < t_object->size(); j++)
			{
				if (!(*t_object)[j])
					continue;
				if (dMatrix[i][corIdx[j]] < mds->vRange[i].first)
					mds->vRange[i].first = dMatrix[i][corIdx[j]];
				if (dMatrix[i][corIdx[j]] > mds->vRange[i].second)
					mds->vRange[i].second = dMatrix[i][corIdx[j]];
			}
			//if (i == 1)
			//cout << "[" << mds->vRange[i].first << " " << mds->vRange[i].second << "] ";
		}
	}
	//cout << endl;
}

void Bicluster::setSubsetsContained(int iscontained_)
{
	isSubsetContained = iscontained_;
	getVariateSubsets();
}

void Bicluster::setJaccardDistanceUsed(int isJaccarsUsed_) {
	isJaccardUsed = isJaccarsUsed_;
	cout << isJaccardUsed << endl;
	SelectedVariatesNo(selectNo);
}

