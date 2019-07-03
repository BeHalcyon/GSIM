#ifndef DEFINE_H
#define DEFINE_H
#include <utility>
#include <vector>
#include <string>
#include <QList>
#include <QColor>

using namespace std;
typedef unsigned char uchar;
typedef unsigned char VolumeType;
typedef pair<string, int> VSubset;

extern QList<QColor> colors;
extern QList<QColor> featurecolors;
extern QStringList variatenames;
extern vector<uchar*> volRegions;

struct illumParam
{
	float Ka;
	float Kd;
	float Ks;
};
#endif // DEFINE_H