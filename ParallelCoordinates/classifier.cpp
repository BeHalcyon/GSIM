#include "classifier.h"
#include <algorithm>
#include <queue>

Classifier::Classifier(vector<MaximalDimentionalSet*> mds, float* dis, int criteria, int function)
{
	selectedMDS = mds;
	clusterid = 0;
	cluster_root = NULL;
	objNum = mds.size();
	linkage_criteria = criteria;
	distance_function = function;
	init_classifer(dis, objNum);
	classification();
}

Classifier::~Classifier()
{

	for (int i = objNum; i < clusters.size(); i++)
	{
		delete clusters[i]->obj;
	}

	for (int i = 0; i < clusters.size(); i++)
	{
		delete clusters[i];
	}
}

void Classifier::init_classifer(float* dis, int num)
{
	for (int i = 0; i < num; i++)
	{
		ClusterNode *node = new ClusterNode();
		node->idx = clusterid++;
		node->obj = selectedMDS[i]->getObjectSet()->objset;
		clusters.push_back(node);
	}

	for (int i = 0; i < num; i++)
	{
		ClusterNode *current = clusters[i];
		for (int j = 0; j < num; j++)
		{
			if (i == j) continue;
			current->neighbors.push_back(new Neighbor(clusters[j], dis[i * num + j]));
		}
	}
}

bool Classifier::find_best_distance_neighbour(ClusterNode*& first, ClusterNode*& second, float& dis)
{
	float best_dis = FLT_MAX;
	for (int i = 0; i < clusters.size(); i++)
	{
		if (clusters[i]->is_active)
		{
			for (int j = 0; j < clusters[i]->neighbors.size(); j++)
			{
				if (clusters[i]->neighbors[j]->cluster->is_active && clusters[i]->neighbors[j]->distance < best_dis)
				{
					best_dis = clusters[i]->neighbors[j]->distance;
					second = clusters[i]->neighbors[j]->cluster;
					first = clusters[i];
				}
			}
		}
	}

	dis = best_dis;
	if (first && second)
		return true;
	else
		return false;
}

float Classifier::get_distance(ClusterNode* newc, ClusterNode* oldc)
{
	float best_dis;
	if (linkage_criteria == SINGLE_LINKAGE)
	{
		best_dis = FLT_MAX;
		ClusterNode *l_child = newc->l_child;
		for (int i = 0; i < l_child->neighbors.size(); i++)
		{
			if (l_child->neighbors[i]->cluster == oldc)
				best_dis = std::min(best_dis, l_child->neighbors[i]->distance);
		}

		ClusterNode *r_child = newc->r_child;
		for (int i = 0; i < r_child->neighbors.size(); i++)
		{
			if (r_child->neighbors[i]->cluster == oldc)
				best_dis = std::min(best_dis, r_child->neighbors[i]->distance);
		}
	}
	else if (linkage_criteria == COMPLETE_LINKAGE)
	{
		best_dis = FLT_MIN;
		ClusterNode *l_child = newc->l_child;
		for (int i = 0; i < l_child->neighbors.size(); i++)
		{
			if (l_child->neighbors[i]->cluster == oldc)
				best_dis = std::max(best_dis, l_child->neighbors[i]->distance);
		}

		ClusterNode *r_child = newc->r_child;
		for (int i = 0; i < r_child->neighbors.size(); i++)
		{
			if (r_child->neighbors[i]->cluster == oldc)
				best_dis = std::max(best_dis, r_child->neighbors[i]->distance);
		}
	}
	else if (linkage_criteria == WEIGHTED_LINKAGE)
	{
		ClusterNode *l_child = newc->l_child;
		for (int i = 0; i < l_child->neighbors.size(); i++)
		{
			if (l_child->neighbors[i]->cluster == oldc)
			{
				best_dis = l_child->neighbors[i]->distance;
				break;
			}
		}

		ClusterNode *r_child = newc->r_child;
		for (int i = 0; i < r_child->neighbors.size(); i++)
		{
			if (r_child->neighbors[i]->cluster == oldc)
			{
				best_dis = (best_dis + r_child->neighbors[i]->distance) / 2.0;
				break;
			}
		}
	}
	else if (linkage_criteria == ACCURATE_LINKAGE)
	{
		bitset<defaultObjectNum>* obj1 = newc->obj;
		bitset<defaultObjectNum>* obj2 = oldc->obj;
		float overlap = ((*obj1)&(*obj2)).count()/ std::min(obj1->count(), obj2->count());
		best_dis =  sqrt(1 - overlap);
	}
	return best_dis;
}

ClusterNode* Classifier::merge_cluster(ClusterNode* first, ClusterNode* second)
{
	ClusterNode *new_cluster = new ClusterNode();
	new_cluster->idx = clusterid++;
	new_cluster->l_child = first;
	new_cluster->r_child = second;
	bitset<defaultObjectNum> *obj1 = first->obj;
	bitset<defaultObjectNum> *obj2 = second->obj;
	bitset<defaultObjectNum> *obj = new bitset<defaultObjectNum>;
	(*obj) = (*obj1)&(*obj2);
	new_cluster->obj = obj;
	first->is_active = false;
	second->is_active = false;
	first->parent = new_cluster;
	second->parent = new_cluster;
	for (int i = 0; i < clusters.size(); i++)
	{
		if (clusters[i]->is_active)
		{
			float dis = get_distance(new_cluster, clusters[i]);
			new_cluster->neighbors.push_back(new Neighbor(clusters[i], dis));
			clusters[i]->neighbors.push_back(new Neighbor(new_cluster, dis));
		}
	}
	clusters.push_back(new_cluster);
	return new_cluster;
}

void Classifier::classification()
{
	ClusterNode *first = NULL, *second = NULL;
	float distance;
	while (find_best_distance_neighbour(first, second, distance))
	{
		cluster_root = merge_cluster(first, second);
		order.push_back(Linkage(first->idx, second->idx, distance));
		first = NULL;
		second = NULL;
	}
	if (selectedMDS.size() == 1)
	{
		cluster_root = new ClusterNode();
		cluster_root->idx = 0;
	}
		
}

void Classifier::signChild(ClusterNode* clust, int cnum)
{
	if (clust->l_child == NULL && clust->r_child == NULL)
	{
		T[clust->idx] = cnum;
		return;
	}
	else
	{
		signChild(clust->l_child, cnum);
		signChild(clust->r_child, cnum);
	}
}

vector<int> Classifier::getCluter(int maxclust)
{
	T.clear();
	T.resize(objNum);
	clsnum = 0;
	for (int k = objNum - maxclust; k < objNum - 1; k++)
	{
		int i = order[k].left; // left tree
		if (i < objNum)         //original node, no leafs
		{
			T[i] = clsnum++;
		}
		else if (i < 2 * objNum - maxclust)
		{
			signChild(clusters[i], clsnum);
			clsnum++;
		}

		i = order[k].right;
		if (i < objNum)         //original node, no leafs
		{
			T[i] = clsnum++;
		}
		else if (i < 2 * objNum - maxclust)
		{
			signChild(clusters[i], clsnum);
			clsnum++;
		}
	}
	return T;
}

void Classifier::disconnect(ClusterNode* clust, bool* conn)
{
	if (clust == NULL)
		return;
	ClusterNode* parent = clust->parent;
	if (parent == NULL)
		return;
	int idx = parent->idx - objNum;
	conn[idx] = false;
	disconnect(clust->parent, conn);
}

void Classifier::labeltree(ClusterNode* clust, bool* conn)
{
	groupID[clust->idx] = clsnum;
	if (clust->l_child == NULL && clust->r_child == NULL)
	{
		T[clust->idx] = clsnum;
		return;
	}
	int idx = clust->idx - objNum;
	if (conn[idx])
	{
		labeltree(clust->l_child, conn);
		labeltree(clust->r_child, conn);
	}
	else
	{
		labeltree(clust->l_child, conn);
		++clsnum;
		labeltree(clust->r_child, conn);
	}
}

vector<int> Classifier::checkcut(QString criterion, float cutoff)
{
	T.clear();
	if (selectedMDS.size() == 0)
		return T;
	float * crit = new float[objNum - 1];
	if (criterion == "inconsistent")
	{
		calInconsistent();
		for (int i = 0; i < Y.size(); i++)
		{
			crit[i] = Y[i].value;
		}
	}
	else if (criterion == "distance")
	{
		for (int i = 0; i < order.size(); i++)
		{
			crit[i] = order[i].dis;
		}
	}
	else
		return T;

	conn = new bool[objNum - 1];
	memset(conn, 1, (objNum - 1) * sizeof(bool));
	for (int i = 0; i < objNum - 1; i++)
	{
		if (crit[i] > cutoff && conn[i])
		{
			ClusterNode* node = clusters[order[i].left];
			disconnect(node, conn);
		}
	}

	//for (int i = 0; i < objNum - 1; i++)
	//{
	//	cout << order[i].left << " " << order[i].right << " " << order[i].dis << " " << conn[i] << endl;
	//}

	// assign cluster numbers
	T.resize(objNum);
	groupID.clear();
	groupID.resize(clusters.size() + 1);
	clsnum = 0;
	labeltree(cluster_root, conn);
	return T;
}

vector<int> Classifier::recluster(int clustId)
{
	queue<ClusterNode*> cqueue;
	cqueue.push(cluster_root);
	ClusterNode* cnode;
	while (!cqueue.empty())
	{
		cnode = cqueue.front();
		cqueue.pop();
		if (cnode->l_child == NULL || cnode->r_child == NULL)
			continue;
		if (groupID[cnode->l_child->idx] == clustId && groupID[cnode->r_child->idx] == clustId)
			break;
		cqueue.push(cnode->l_child);
		cqueue.push(cnode->r_child);
	}

	int idx = cnode->idx - objNum;
	conn[idx] = false;
	T.clear();
	T.resize(objNum);
	groupID.clear();
	groupID.resize(clusters.size() + 1);
	clsnum = 0;
	labeltree(cluster_root, conn);
	return T;
}

vector<int> Classifier::remergecluster(int clustId1, int clustId2)
{
	queue<ClusterNode*> cqueue;
	cqueue.push(cluster_root);
	ClusterNode* cnode;
	ClusterNode* cnode1 = NULL;
	ClusterNode* cnode2 = NULL;
	while (!cqueue.empty())
	{
		cnode = cqueue.front();
		cqueue.pop();
		if (cnode->l_child == NULL || cnode->r_child == NULL)
			continue;
		if (groupID[cnode->l_child->idx] == clustId1 && groupID[cnode->r_child->idx] == clustId1 && cnode1 == NULL)
		{
			cnode1 = cnode;
		}
		if (groupID[cnode->l_child->idx] == clustId2 && groupID[cnode->r_child->idx] == clustId2 && cnode2 == NULL)
		{
			cnode2 = cnode;
		}
		if (cnode1 && cnode2)
			break;
		cqueue.push(cnode->l_child);
		cqueue.push(cnode->r_child);
	}
	//////  p0(lk0)     p1(lk1) 
	//////	|           |
	//////  p2          p3(lk3)
	////// |-|        |----|
	////// 1 2       3/p5 4/p4 

	//////    p0           p1(lk1)
	//////	  |            |
	//////    p3(lk3)      |
	//////	|---|          |
	//////  p2  |          | 
	////// |-|  |          |
	////// 1 2  3/p5     4/p4 
	ClusterNode *p0, *p1, *p2, *p3, *p4, *p5;
	int lk0 = -1, lk1 = -1, lk2 = -1, lk3 = -1;
	p2 = cnode1;
	p0 = p2->parent;
	p5 = cnode2;
	p3 = p5->parent;
	p4 = (p3->l_child == p5) ? p3->r_child : p3->l_child;
	p1 = p3->parent;
	for (int i = 0; i < order.size(); i++)
	{
		if (order[i].left == p2->idx || order[i].right == p2->idx)
			lk0 = i;
		if (order[i].left == p5->idx || order[i].right == p5->idx)
			lk3 = i;
		if (order[i].left == p3->idx || order[i].right == p3->idx)
			lk1 = i;
	}
	if (p1)
	{
		if (p1->l_child == p3) p1->l_child = p4;
		else p1->r_child = p4;
		p4->parent = p1;
	}
	else
	{
		cluster_root = p4;
		p4->parent = NULL;
	}

	if (p3->l_child == p5) p3->r_child = p2;
	else p3->l_child = p2;
	p2->parent = p3;

	if (p0->l_child = p2) p0->l_child = p3;
	else p0->r_child = p3;
	p3->parent = p0;

	if (order[lk3].left == p5->idx) order[lk3].right = p2->idx;
	else order[lk3].left = p2->idx;
	order[lk3].dis = get_distance(clusters[order[lk3].left], clusters[order[lk3].right]);

	if (order[lk0].left == p2->idx) order[lk0].left = p3->idx;
	else order[lk0].right = p3->idx;
	order[lk0].dis = get_distance(clusters[order[lk0].left], clusters[order[lk0].right]);

	if (lk1 > 0)
	{
		if (order[lk1].left == p3->idx) order[lk1].left = p4->idx;
		else order[lk1].right = p4->idx;
		order[lk1].dis = get_distance(clusters[order[lk1].left], clusters[order[lk1].right]);
	}

	int idx = p3->idx - objNum;
	conn[idx] = true;
	T.clear();
	T.resize(objNum);
	groupID.clear();
	groupID.resize(clusters.size() + 1);
	clsnum = 0;
	labeltree(cluster_root, conn);
	return T;
}

void Classifier::calInconsistent()
{
	Y.clear();
	Y.resize(objNum - 1);
	for (int i = 0; i < order.size(); i++)
	{
		Inconsistent s;
		int depth = 2;
		queue<int> todo;
		todo.push(i);
		while (!todo.empty())
		{
			int idx = todo.front();
			todo.pop();
			s.meanHeight += order[idx].dis;
			s.standardDeviation += order[idx].dis * order[idx].dis;
			s.edgeNum++;
			if (depth > 1)
			{
				int l = order[idx].left - objNum;
				int r = order[idx].right - objNum;
				if (l >= 0) todo.push(l);
				if (r >= 0) todo.push(r);
				depth--;
			}
		}

		Y[i].meanHeight = s.meanHeight / s.edgeNum;
		float V = (s.standardDeviation - s.meanHeight * s.meanHeight / s.edgeNum) / (s.edgeNum - (s.edgeNum != 1));
		Y[i].standardDeviation = sqrt(std::max((float)0, V));
		Y[i].edgeNum = s.edgeNum;

		if (Y[i].standardDeviation > 0)
			Y[i].value = (order[i].dis - Y[i].meanHeight) / Y[i].standardDeviation;
		else
			Y[i].value = 0;
	}
	
}

vector<float> Classifier::getDistance(QString criterion)
{
	vector<float> crit;
	if (criterion == "inconsistent")
	{
		calInconsistent();
		for (int i = 0; i < Y.size(); i++)
		{
			crit.push_back(Y[i].value);
		}
	}
	else if (criterion == "distance")
	{
		for (int i = 0; i < order.size(); i++)
		{
			crit.push_back(order[i].dis);
		}
	}
	return crit;
}