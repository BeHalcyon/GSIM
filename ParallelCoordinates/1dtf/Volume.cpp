#include "Volume.h"
#include <string.h>
#include <iostream>

using namespace std;
Volume::Volume()
{
	m_alignedDim.set(0, 0, 0);
	m_normalizedDim.set(0.0, 0.0, 0.0);
	m_pFileName = NULL;

	meta.data = NULL;
	meta.dim.set(0, 0, 0);
	meta.spacing.set(1.0, 1.0, 1.0);
	meta.component_count = 1;
}

Volume::~Volume()
{
	clear();
}

void Volume::clear()
{
	free(meta.data);
	meta.data = NULL;
	meta.dim.set(0, 0, 0);
	meta.spacing.set(1.0, 1.0, 1.0);
	m_alignedDim.set(0, 0, 0);
	m_normalizedDim.set(0.0, 0.0, 0.0);
	m_pFileName = NULL;
}

bool Volume::loadVolume(QString filenamestring)
{
	QByteArray ba = filenamestring.toLocal8Bit();
	const char* filename = ba.data();
	if (filename == NULL)
		return false;

	FILE *fp = fopen(filename, "r");
	if(fp == NULL) {
		printf("Can't open file %s\n", filename);
		return false;
	}
	printf("---------------------------------\n");
	printf("Load:%s\n", filename);

	if(meta.data != NULL)
 		clear();
	m_pFileName = filename;

	//////////////////////////////////////////////////////////////////////////
	// read volume information
	char dataFile[1024];
	char dataType;
	int dataWide;
	char volumeDataFileName[200];
	fscanf(fp, "%d %d %d\n", &(meta.dim.x), &(meta.dim.y), &(meta.dim.z));
	fscanf(fp, "%f %f %f\n", &(meta.spacing.x), &(meta.spacing.y), &(meta.spacing.z));
	fscanf(fp, "%s", volumeDataFileName);
	int dtRet = fscanf(fp, "%d%c%d", &dataWide, &dataType, &(meta.component_count));

	switch(dtRet)
	{
	case -1:
	case 0:
		meta.component_count = 1;
		dataType = 'u';
		dataWide = 1;
		break;
	case 1:
		meta.component_count = 1;
		dataType = 'u';
		break;
	case 2:
		meta.component_count = 1;
		break;
	}
	meta.type = getDataType(dataWide, dataType);
	fclose(fp);
	//printf("data file Name:[%s]\n", volumeDataFileName);

	m_alignedDim.x = getPow2(meta.dim.x);
	m_alignedDim.y = getPow2(meta.dim.y);
	m_alignedDim.z = getPow2(meta.dim.z);

	// the range in [0..1] in each dimension
	m_normalizedDim.set(meta.dim.x * meta.spacing.x, meta.dim.y * meta.spacing.y, meta.dim.z * meta.spacing.z);
	double maxSize = Max(m_normalizedDim.x, Max(m_normalizedDim.y, m_normalizedDim.z));
	m_normalizedDim /= maxSize;

	const char* pSlash = strrchr(filename, '/');
	memset(dataFile, 0, 1024);
	strncpy(dataFile, filename, pSlash - filename + 1);
	//printf("data file dir :[%s]\n", dataFile);
	strcat(dataFile, volumeDataFileName);
	printf("data file     :[%s]\n", dataFile);

	//////////////////////////////////////////////////////////////////////////
	// read volume data from file
	fp = fopen(dataFile, "rb");
	if(fp == NULL) {
		printf("Can't open data file %s\n", dataFile);
		return false;
	}


	// 根据数据尺寸、每个体素元素个数和数据类型计算总共体数据大小
	int volumeSize = meta.dim.x * meta.dim.y * meta.dim.z * meta.component_count * bytePerComponent(meta.type);
	meta.data = (void*)malloc(volumeSize);
	if (meta.data != NULL)
	{
		fread(meta.data, 1, volumeSize, fp);
	}
	else
	{
		printf("Bad allocate memory!\n");
	}
	fclose(fp);

	//计算数据分布直方图
	calHist();
	return true;
}

double Volume::getValue(unsigned char* pData, double x, double y, double z)
{
	x = Max(Min(x + 0.5, meta.dim.x - 1.0), 0.0);
	y = Max(Min(y + 0.5, meta.dim.y - 1.0), 0.0);
	z = Max(Min(z + 0.5, meta.dim.z - 1.0), 0.0);
	int index = (int)z * meta.dim.x * meta.dim.y + (int)y * meta.dim.z + (int)x;
	return pData[index];
}

//////////////////////////////////////////////////////////////////////////
/*
 *	get the power of 2 greater than or equal to size
 */
int Volume::getPow2(int size)
{
	double tmp = size / 2.0;
	int i = 2;
	while(tmp > 1.0){
		i *= 2;
		tmp /= 2.0;
	}
	return i;
}



/*
 *	 Trilinear interpolation, assume 0<=xIndex<xiSize 0<=yIndex<yiSize 0<=zIndex<ziSize 
 */
double Volume::intpTrilinear(unsigned char* pData, double x, double y, double z)
{
	int xIndex = (int)x, yIndex = (int)y, zIndex = (int)z;
	double xFraction = x - xIndex;
	double yFraction = y - yIndex;
	double zFraction = z - zIndex;
	if(xIndex < 0 || xIndex > meta.dim.x - 1 || yIndex < 0 || yIndex > meta.dim.y || zIndex < 0 || zIndex > meta.dim.z - 1) {
		printf("interpolation size out of range\n");
		return 0;
	}
	int index = zIndex * meta.dim.x * meta.dim.y + yIndex * meta.dim.x + xIndex;
	int xNext = (xIndex < meta.dim.x - 1) ? 1 : 0;
	int yNext = (yIndex < meta.dim.y - 1) ? meta.dim.x : 0;
	int zNext = (zIndex < meta.dim.z - 1) ? meta.dim.x * meta.dim.y : 0;
	int f000 = pData[index];
	int f100 = pData[index + xNext];
	int f010 = pData[index + yNext];
	int f001 = pData[index + zNext];
	int f101 = pData[index + xNext + zNext];
	int f011 = pData[index + yNext + zNext];
	int f110 = pData[index + xNext + yNext];
	int f111 = pData[index + xNext + yNext + zNext];
	double fResult = f000 * (1 - xFraction) * (1 - yFraction) * (1 - zFraction) +
					 f100 * xFraction * (1 - yFraction) * (1 - zFraction) +
					 f010 * (1 - xFraction) * yFraction * (1 - zFraction) +
					 f001 * (1 - xFraction) * (1 - yFraction) * zFraction +
					 f101 * xFraction * (1 - yFraction) * zFraction +
					 f011 * (1 - xFraction) * yFraction * zFraction +
					 f110 * xFraction * yFraction * (1 - zFraction) +
					 f111 * xFraction * yFraction * zFraction;
	return fResult;
}

/*
 *  trilinear cubic BSpline scalar interpolation
 */
double Volume::cubicIntpValue(double v0, double v1, double v2, double v3, double mu)
{
	const double mu2 = mu * mu;
	const double mu3 = mu2 * mu;

	const double a0 = -1.0 * v0 + 3.0 * v1 - 3.0 * v2 + 1.0 * v3;
	const double a1 =  3.0 * v0 - 6.0 * v1 + 3.0 * v2 + 0.0 * v3;
	const double a2 = -3.0 * v0 + 0.0 * v1 + 3.0 * v2 + 0.0 * v3;
	const double a3 =  1.0 * v0 + 4.0 * v1 + 1.0 * v2 + 0.0 * v3;
			
	return (a0 * mu3 + a1 * mu2 + a2 * mu + a3) / 6.0;
}

double Volume::triCubicIntpValue(unsigned char* pData, double x, double y, double z)
{
	// Extract the integer and decimal components of the x, y co-ordinates
	double ulo, vlo, wlo;
	const double ut = modf( x, &ulo );
	const double vt = modf( y, &vlo );
	const double wt = modf( z, &wlo );

	int		xlo = int( ulo );
	int		ylo = int( vlo );
	int		zlo = int( wlo );

	// We need all the voxels around the primary
	double voxels[4][4][4];
	{
		for( int z=0; z<4; z++ ) {
			for( int y=0; y<4; y++ ) {
				for( int x=0; x<4; x++ ) {
					int px = (xlo-1+x);
					int py = (ylo-1+y);
					int pz = (zlo-1+z);
					voxels[z][y][x] =  getValue(pData, px, py, pz);
				}
			}
		}
	}

	// Now that we have all our voxels, run the cubic interpolator in one dimension to collapse it (we choose to collapase x)
	double voxelcol[4][4];
	{
		for( int z=0; z<4; z++ ) {
			for( int y=0; y<4; y++ ) {
				voxelcol[z][y] = cubicIntpValue(voxels[z][y][0], voxels[z][y][1], voxels[z][y][2], voxels[z][y][3], ut);
			}
		}
	}

	// Then collapse the y dimension 
	double voxelcol2[4];
	{
		for( int z=0; z<4; z++ ) {
			voxelcol2[z] = cubicIntpValue(voxelcol[z][0], voxelcol[z][1], voxelcol[z][2], voxelcol[z][3], vt);
		}
	}

	// The collapse the z dimension to get our value
	return cubicIntpValue(voxelcol2[0], voxelcol2[1], voxelcol2[2], voxelcol2[3], wt);
}

bool Volume::loaded()
{
	//return m_pData != NULL;
	return meta.data != NULL;
}

void Volume::calHist()
{
	unsigned char* vol = data<unsigned char>();
	int voxelNum = getTotalSize();
	hist = new int[256];
	memset(hist, 0, 256 * sizeof(int));
	for (int i = 0; i < voxelNum; i++)
	{
		hist[vol[i]]++;
	}

	max_density = 0;
	for (int i = 1; i < 256; i++)
	{
		if (hist[i] > max_density) max_density = hist[i];
	}
}