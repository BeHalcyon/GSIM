#ifndef RENDERWIDGET_H
#define RENDERWIDGET_H
#include "stdafx.h"
#include "define.h"
#include <QtOpenGL/QGLWidget>
#include <QWheelEvent>
#include <string>
#include <sstream>
#include <cmath>
#include <ctime>
#include <vector>
#include "1dtf/Volume.h"
#include "util/Camera.h"

using namespace std;
// window size
static int winWidth = 800, winHeight = 800;

class RenderWidget : public QGLWidget
{
	Q_OBJECT
public:
	RenderWidget(QWidget* parent = 0);
	float * getBoundingBox() { return boundingbox; }

signals:
	void sendViewMatrix(float * viewmatrix);
	void dataLoaded(const Volume*);
	public slots:
	void getVolumeTF(unsigned char* tf);
	void updateRender(illumParam illumparam);
	void setData(Volume*);
	void regionsUpdate();
	void setBoundingBoxShow();
	void setKa(double ka_);
	void setKd(double kd_);
	void setKs(double ks_);
	void setOpacity(double opacity_);
	void colorUpdate();
	void setOpacities(int id, double opacity_);
protected:
	void cgErrorCallback();
	void glErrorCheck();
	void InitOpenGL();
	void loadPositionShader();
	void loadRayCastingShader();
	void InitCg();
	void InitTexture();
	void InitFBO();

	void setupVolumeTexture();
	void setupTransferFunction();
	void drawVolumeBoundingBox(Volume * vol);
	//void drawRayPosition();
	void GPURayCasting();
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();
	void wheelEvent(QWheelEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent * event);
	void keyPressEvent(QKeyEvent *event);
	void contextMenuEvent(QContextMenuEvent * event);
	void modelMatrix();

	void updateTFTexture();
	void drawCoord();
	void setupRegionTexture();
	void smooth(uchar* region);
private:
	// CG Parameters
	CGcontext cg_context;
	CGprofile cg_vprofile, cg_gprofile, cg_fprofile;
	CGprogram cgPostionFragProgram, cgRayCastingProgram;
	CGparameter cgVolume;
	CGparameter cgTransferFunction;
	CGparameter cgStep;
	CGparameter cgViewMatrix;
	CGparameter cgImageParam;
	CGparameter cgIllumParam;
	CGparameter cgDimension;
	CGparameter cgSpacing;
	CGparameter cgRegion1;
	CGparameter cgRegion2;
	CGparameter cgRegion3;
	CGparameter cgRegion4;
	CGparameter cgFeatureColor1;
	CGparameter cgFeatureColor2;
	CGparameter cgFeatureColor3;
	CGparameter cgFeatureColor4;
	CGparameter cgOpacities;
	CGparameter cgOpacity;

	// Texture
	unsigned int volumeTextureIdx;
	unsigned int transferTextureIdx;
	unsigned int region1TextureIdx;
	unsigned int region2TextureIdx;
	unsigned int region3TextureIdx;
	unsigned int region4TextureIdx;

	// start position and end position texture
	//unsigned int startPosTextureIdx;
	//unsigned int endPosTextureIdx;
	//unsigned int depthTextureIdx;
	unsigned int resTextureIdx;

	// Frame buffer object
	FramebufferObject* pFBO;

	// Volume size
	int   xiSize, yiSize, ziSize;		// assume the power of 2
	float xfSize, yfSize, zfSize;		// normalized size in range [0..1]
	float xSpace, ySpace, zSpace;		// the spacings of each dimension
	float zoom;
	float xAngle, yAngle, zAngle;
	int volumeSize;

	//rendering parameter;
	float Ka, Kd, Ks, Opacity;
	float viewMatrix[16];
	float mvmatrix[16];
	float * boundingbox;

	QPoint lastPoint;
	QPoint TFPoint;

	float xtran, ytran;

	// ray casting step
	float step;

	// Volume data
	//unsigned short *pData;

	unsigned char *pData;
	unsigned char* pDataTexture;

	unsigned char *lenData;
	unsigned char *lenDataTexture;
	// 1D Transfer Function
	unsigned char TF1DTable[256][4];
	float Xstart, Yend, Slope, RY;

	bool isVolumeTFChanged;
	bool showBoundingBox;
	unsigned char *tf1dVolume;

	Volume * volume1;
	Camera m_camera;

	float opacity1;
	float opacity2;
	float opacity3;
	float opacity4;
};

#endif