#ifndef VOLUME_H
#define VOLUME_H

#include "1dtf/VolumeMeta.h"
#include "util/Vector3.h"
#include <string>
#include <QString>

using namespace std;

class Volume 
{

public:
	Volume();
	~Volume();
	// clear volume data
	void clear();

	bool loadVolume(QString filenamestring);
	bool loaded();

	const char* getFileName() const {return m_pFileName;}

	inline Vector3i getAlignedDim() const { return m_alignedDim; }
	inline Vector3f getNormalizedDim() const { return m_normalizedDim; }
	// Slices number
	inline Vector3i getDimension() const { return meta.dim; }
	inline Vector3f getSpacing() const { return meta.spacing; }
	inline int getTotalSize() const { return meta.dim.x * meta.dim.y * meta.dim.z; }
	inline int getMaxDensity() const { return max_density; }
	const int* getDensityDistribution() const { return hist; }

	/**
	 * @brief Deprecated. Use data<DataType>() instead.
	 * @date 2013/06/14
	 */
	unsigned char* getVolume() const {
		return data<unsigned char>();
	}

	template<typename T>
	T* data() const
	{
		return static_cast<T*>(meta.data);
	};

	inline void setDimension(Vector3i dim)
	{
		meta.dim = dim;
	}

	inline void setData(void* d)
	{
		meta.data = d;
	};

	inline void setSpacing(Vector3f spc)
	{
		meta.spacing = spc;
	}
protected:
	// get the power of 2 greater than or equal to size
	int getPow2(int size);

	// trilinear interpolation
	double intpTrilinear(unsigned char* pData, double x, double y, double z);

	// trilinear cubic bspline scalar interpolation
	double cubicIntpValue(double v0, double v1, double v2, double v3, double mu);
	double triCubicIntpValue(unsigned char* pData, double x, double y, double z);

	// nearest neighbor scalar value
	double getValue(unsigned char* pData, double x, double y, double z);
	void calHist();

private:
	const char* m_pFileName;
	int* hist;
	int max_density;
	VolumeMeta meta;
	Vector3i m_alignedDim; // xSize
	Vector3f m_normalizedDim; // xfSize the spacings of each dimension
};

#endif // VOLUME_H
