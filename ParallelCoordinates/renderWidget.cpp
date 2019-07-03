#include "renderWidget.h"
#include "ext/imdebug/imdebuggl.h"
#include "util/Vector4.h"
#include "util/Functions.h"
#include "util/util.h"

#include <QMenu>

RenderWidget::RenderWidget(QWidget* parent) :QGLWidget(parent)
{
	xAngle = yAngle = zAngle = 0.0;
	zoom = 1.0;
	xtran = ytran = 0.0;
	//pData = NULL;
	isVolumeTFChanged = false;
	showBoundingBox = true;
	winWidth = this->width();
	winHeight = this->height();
	boundingbox = new float[3];
	Ka = 0.73;
	Kd = 0.5;
	Ks = 0.1;
	//Debug 20180305
	Opacity = 0.07;
	//Opacity = 1.0f;
	setFocusPolicy(Qt::ClickFocus);
	volume1 = NULL;
	opacity1 = 1.0;
	opacity2 = 1.0;
	opacity3 = 1.0;
	opacity4 = 1.0;
}

void RenderWidget::initializeGL()
{
	InitOpenGL();

	InitCg();

	InitTexture();

	InitFBO();

	setupTransferFunction();
}

void RenderWidget::resizeGL(int w, int h)
{
	winWidth = w, winHeight = h;

	// Update 2D start and end position texture
	glEnable(GL_TEXTURE_RECTANGLE_ARB);
	//glBindTexture(GL_TEXTURE_RECTANGLE_ARB, startPosTextureIdx);
	//glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGB32F_ARB, winWidth, winHeight, 0, GL_RGB, GL_FLOAT, 0);
	//glBindTexture(GL_TEXTURE_RECTANGLE_ARB, endPosTextureIdx);
	//glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGB32F_ARB, winWidth, winHeight, 0, GL_RGB, GL_FLOAT, 0);
	glBindTexture(GL_TEXTURE_RECTANGLE_ARB, resTextureIdx);
	glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGB32F_ARB, winWidth, winHeight, 0, GL_RGB, GL_FLOAT, 0);
	//glBindTexture(GL_TEXTURE_RECTANGLE_ARB, depthTextureIdx);
	//glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_DEPTH_COMPONENT, winWidth, winHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glDisable(GL_TEXTURE_RECTANGLE_ARB);

	glViewport(0, 0, w, h);
	m_camera.setWindowSize(w, h);
	m_camera.setOrthoProjection();
}

void RenderWidget::paintGL()
{
	if (volume1 == NULL || volume1->getVolume() == NULL)
		return;
	//glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//tf1dVolume « ≤√¥
	updateTFTexture();
	setupVolumeTexture();
	setupRegionTexture();
	// GPU Ray Casting in screen framebuffer
	glEnable(GL_BLEND);
	glBlendFunc(GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (showBoundingBox)
		drawVolumeBoundingBox(volume1);
	modelMatrix();
	GPURayCasting();
	glDisable(GL_BLEND);
}

void RenderWidget::modelMatrix()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glScalef(m_camera.getZoom(), m_camera.getZoom(), m_camera.getZoom());
	glMultMatrixd(m_camera.getRotateMatrix());
	glGetFloatv(GL_MODELVIEW_MATRIX, viewMatrix);
	glPopMatrix();

}

void RenderWidget::cgErrorCallback()
{
	CGerror lastError = cgGetError();
	if (lastError)
	{
		printf("%s\n", cgGetErrorString(lastError));
		printf("%s\n", cgGetLastListing(cg_context));
		exit(0);
	}
}

void RenderWidget::glErrorCheck()
{
	GLenum errCode;
	const GLubyte *errString;
	if ((errCode = glGetError()) != GL_NO_ERROR) {
		errString = gluErrorString(errCode);
		fprintf(stderr, "OpenGL Error: %s\n", errString);
		exit(0);
	}
}

void RenderWidget::InitOpenGL()
{
	if (glewInit() != GLEW_OK || !GLEW_VERSION_2_0)
	{
		printf("failed to initialize GLEW, OpenGL 4.0 required.\n");
		exit(-1);
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glViewport(0, 0, width(), height());
	m_camera.setWindowSize(width(), height());
	m_camera.setOrthoProjection();
}

void RenderWidget::loadPositionShader()
{
	cgPostionFragProgram = cgCreateProgramFromFile(
		cg_context,
		CG_SOURCE,
		"fp_PositionShader.cg",
		cg_fprofile,
		"fp_PositionShader", 0);

	cgGLLoadProgram(cgPostionFragProgram);
}

void RenderWidget::loadRayCastingShader()
{
	cgRayCastingProgram = cgCreateProgramFromFile(
		cg_context,
		CG_SOURCE,
		"fp_RayCastingShader.cg",
		cg_fprofile,
		"fp_RayCastingShader", 0);

	if (!cgRayCastingProgram) {
		cout << "SimpleShader: Unable to load shaders/fp_RayCastingShader.cg" << endl;
		return;
	}

	cgVolume = cgGetNamedParameter(cgRayCastingProgram, "volume");
	cgTransferFunction = cgGetNamedParameter(cgRayCastingProgram, "transferFunction");
	cgStep = cgGetNamedParameter(cgRayCastingProgram, "step");
	cgOpacity = cgGetNamedParameter(cgRayCastingProgram, "opacity");
	cgViewMatrix = cgGetNamedParameter(cgRayCastingProgram, "viewMatrix");
	cgImageParam = cgGetNamedParameter(cgRayCastingProgram, "imageParam");
	cgIllumParam = cgGetNamedParameter(cgRayCastingProgram, "illumParam");
	cgDimension = cgGetNamedParameter(cgRayCastingProgram, "dimension");
	cgSpacing = cgGetNamedParameter(cgRayCastingProgram, "spacing");
	cgRegion1 = cgGetNamedParameter(cgRayCastingProgram, "region1");
	cgRegion2 = cgGetNamedParameter(cgRayCastingProgram, "region2");
	cgRegion3 = cgGetNamedParameter(cgRayCastingProgram, "region3");
	cgRegion4 = cgGetNamedParameter(cgRayCastingProgram, "region4");
	cgFeatureColor1 = cgGetNamedParameter(cgRayCastingProgram, "featurecolor1");
	cgFeatureColor2 = cgGetNamedParameter(cgRayCastingProgram, "featurecolor2");
	cgFeatureColor3 = cgGetNamedParameter(cgRayCastingProgram, "featurecolor3");
	cgFeatureColor4 = cgGetNamedParameter(cgRayCastingProgram, "featurecolor4");
	cgOpacities = cgGetNamedParameter(cgRayCastingProgram, "opacities");
	cgGLLoadProgram(cgRayCastingProgram);
}

void RenderWidget::InitCg()
{
	// Create Cg Context
	cg_context = cgCreateContext();
	//cgSetErrorCallback(cgErrorCallback);

	// Load Cg programs
	cg_vprofile = cgGLGetLatestProfile(CG_GL_VERTEX);
	cg_gprofile = cgGLGetLatestProfile(CG_GL_GEOMETRY);
	cg_fprofile = cgGLGetLatestProfile(CG_GL_FRAGMENT);

	// Load programs
	loadPositionShader();
	loadRayCastingShader();
}

void RenderWidget::InitTexture()
{
	// volume data texture
	glEnable(GL_TEXTURE_3D);
	glGenTextures(1, &volumeTextureIdx);
	glBindTexture(GL_TEXTURE_3D, volumeTextureIdx);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glDisable(GL_TEXTURE_3D);

	// region data texture
	glEnable(GL_TEXTURE_3D);
	glGenTextures(1, &region1TextureIdx);
	glBindTexture(GL_TEXTURE_3D, region1TextureIdx);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glDisable(GL_TEXTURE_3D);

	glEnable(GL_TEXTURE_3D);
	glGenTextures(1, &region2TextureIdx);
	glBindTexture(GL_TEXTURE_3D, region2TextureIdx);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glDisable(GL_TEXTURE_3D);

	glEnable(GL_TEXTURE_3D);
	glGenTextures(1, &region3TextureIdx);
	glBindTexture(GL_TEXTURE_3D, region3TextureIdx);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glDisable(GL_TEXTURE_3D);

	glEnable(GL_TEXTURE_3D);
	glGenTextures(1, &region4TextureIdx);
	glBindTexture(GL_TEXTURE_3D, region4TextureIdx);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glDisable(GL_TEXTURE_3D);

	// transfer function texture
	glEnable(GL_TEXTURE_1D);
	glGenTextures(1, &transferTextureIdx);
	glBindTexture(GL_TEXTURE_1D, transferTextureIdx);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glDisable(GL_TEXTURE_1D);

	// create 2D start and end position texture
	//glEnable(GL_TEXTURE_RECTANGLE_ARB);
	//glGenTextures(1, &startPosTextureIdx);
	//glBindTexture(GL_TEXTURE_RECTANGLE_ARB, startPosTextureIdx);
	//glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGB32F_ARB, winWidth, winHeight, 0, GL_RGB, GL_FLOAT, 0);
	//glGenTextures(1, &endPosTextureIdx);
	//glBindTexture(GL_TEXTURE_RECTANGLE_ARB, endPosTextureIdx);
	//glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGB32F_ARB, winWidth, winHeight, 0, GL_RGB, GL_FLOAT, 0);
	//glGenTextures(1, &depthTextureIdx);
	//glBindTexture(GL_TEXTURE_RECTANGLE_ARB, depthTextureIdx);
	//glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_DEPTH_COMPONENT, winWidth, winHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

	glGenTextures(1, &resTextureIdx);
	glBindTexture(GL_TEXTURE_RECTANGLE_ARB, resTextureIdx);
	glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGB32F_ARB, winWidth, winHeight, 0, GL_RGB, GL_FLOAT, 0);
	glDisable(GL_TEXTURE_RECTANGLE_ARB);
}

void RenderWidget::InitFBO()
{
	pFBO = new FramebufferObject();
	pFBO->Bind();
	//pFBO->AttachTexture(GL_TEXTURE_RECTANGLE_ARB, startPosTextureIdx, GL_COLOR_ATTACHMENT0_EXT);
	//pFBO->AttachTexture(GL_TEXTURE_RECTANGLE_ARB, endPosTextureIdx, GL_COLOR_ATTACHMENT1_EXT);
	pFBO->AttachTexture(GL_TEXTURE_RECTANGLE_ARB, resTextureIdx, GL_COLOR_ATTACHMENT2_EXT);
	//pFBO->AttachTexture(GL_TEXTURE_RECTANGLE_ARB, depthTextureIdx, GL_DEPTH_ATTACHMENT_EXT);
	pFBO->IsValid();
	FramebufferObject::Disable();
}

void RenderWidget::setupVolumeTexture()
{
	glEnable(GL_TEXTURE_3D);
	glBindTexture(GL_TEXTURE_3D, volumeTextureIdx);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage3DEXT(GL_TEXTURE_3D, 0, GL_LUMINANCE8, volume1->getDimension().x, volume1->getDimension().y, volume1->getDimension().z, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, volume1->getVolume());

	glDisable(GL_TEXTURE_3D);
	glErrorCheck();
}

void RenderWidget::setupTransferFunction()
{
	for (size_t i = 0; i < 256; ++i)
	{
		TF1DTable[i][0] = TF1DTable[i][1] = TF1DTable[i][2] = TF1DTable[i][3] = i;
	}

	glEnable(GL_TEXTURE_1D);
	glBindTexture(GL_TEXTURE_1D, transferTextureIdx);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA8, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, TF1DTable);
	glDisable(GL_TEXTURE_1D);
}

void RenderWidget::drawVolumeBoundingBox(Volume * vol)
{
	double delta = 0.1;
	float v[8][3] = { { 0, 0, 0},
	{ vol->getNormalizedDim().x * (1 + delta), 0, 0 },
	{ 0, vol->getNormalizedDim().y * (1 + delta), 0 },
	{ vol->getNormalizedDim().x * (1 + delta), vol->getNormalizedDim().y * (1 + delta), 0 },
	{ 0, 0, vol->getNormalizedDim().z * (1 + delta) },
	{ vol->getNormalizedDim().x * (1 + delta), 0, vol->getNormalizedDim().z * (1 + delta) },
	{ 0, vol->getNormalizedDim().y * (1 + delta), vol->getNormalizedDim().z * (1 + delta) },
	{ vol->getNormalizedDim().x * (1 + delta), vol->getNormalizedDim().y * (1 + delta), vol->getNormalizedDim().z * (1 + delta) } };
	int f[] = { 1, 3, 7, 5, 0, 4, 6, 2, 2, 6, 7, 3, 0, 1, 5, 4, 4, 5, 7, 6, 0, 2, 3, 1 };

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMultMatrixd(m_camera.getRotateMatrix());
	glScalef(1.0 / m_camera.getZoom(), 1.0 / m_camera.getZoom(), 1.0 / m_camera.getZoom());
	glTranslatef(-vol->getNormalizedDim().x * (1 + delta) / 2.0, -vol->getNormalizedDim().y * (1 + delta) / 2.0, -vol->getNormalizedDim().z * (1 + delta) / 2.0);
	glColor4f(1.0, 1.0, 1.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	for (int i = 0; i < 24; i += 4) {
		glVertex3f(v[f[i]][0], v[f[i]][1], v[f[i]][2]);
		glVertex3f(v[f[i + 1]][0], v[f[i + 1]][1], v[f[i + 1]][2]);
		glVertex3f(v[f[i + 2]][0], v[f[i + 2]][1], v[f[i + 2]][2]);
		glVertex3f(v[f[i + 3]][0], v[f[i + 3]][1], v[f[i + 3]][2]);
	}
	glEnd();
	glPopMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

//void RenderWidget::drawVolumeBoundingBox(Volume * vol)
//{
//
//	float v[8][3] = { { 0, 0, 0 },
//	{ vol->getDimension().x, 0, 0 },
//	{ 0, vol->getDimension().y, 0 },
//	{ vol->getDimension().x, vol->getDimension().y, 0 },
//	{ 0, 0, vol->getDimension().z },
//	{ vol->getDimension().x, 0, vol->getDimension().z },
//	{ 0, vol->getDimension().y, vol->getDimension().z },
//	{ vol->getDimension().x, vol->getDimension().y, vol->getDimension().z } };
//	float t[8][3] = { { 0, 0, 0 },
//	{ 1, 0, 0 },
//	{ 0, 1, 0 },
//	{ 1, 1, 0 },
//	{ 0, 0, 1 },
//	{ 1, 0, 1 },
//	{ 0, 1, 1 },
//	{ 1, 1, 1 } };
//	int f[] = { 1, 3, 7, 5, 0, 4, 6, 2, 2, 6, 7, 3, 0, 1, 5, 4, 4, 5, 7, 6, 0, 2, 3, 1 };
//
//	glBegin(GL_QUADS);
//	for (int i = 0; i < 24; i += 4) {
//		glTexCoord3f(t[f[i]][0], t[f[i]][1], t[f[i]][2]);
//		glVertex3f(v[f[i]][0], v[f[i]][1], v[f[i]][2]);
//
//		glTexCoord3f(t[f[i + 1]][0], t[f[i + 1]][1], t[f[i + 1]][2]);
//		glVertex3f(v[f[i + 1]][0], v[f[i + 1]][1], v[f[i + 1]][2]);
//
//		glTexCoord3f(t[f[i + 2]][0], t[f[i + 2]][1], t[f[i + 2]][2]);
//		glVertex3f(v[f[i + 2]][0], v[f[i + 2]][1], v[f[i + 2]][2]);
//
//		glTexCoord3f(t[f[i + 3]][0], t[f[i + 3]][1], t[f[i + 3]][2]);
//		glVertex3f(v[f[i + 3]][0], v[f[i + 3]][1], v[f[i + 3]][2]);
//	}
//	glEnd();
//}

//void RenderWidget::drawRayPosition()
//{
//	pFBO->Bind();
//	modelMatrix();
//	// position fragment program
//	cgGLEnableProfile(cg_fprofile);
//	cgGLBindProgram(cgPostionFragProgram);
//	// front faces
//	glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	drawVolumeBoundingBox(volume1);
//	// back faces
//	glDrawBuffer(GL_COLOR_ATTACHMENT1_EXT);
//	glClear(GL_COLOR_BUFFER_BIT);
//	glDepthFunc(GL_GREATER);
//	drawVolumeBoundingBox(volume1);
//	glDepthFunc(GL_LESS);
//	// disable position fragment program and FBO
//	cgGLDisableProfile(cg_fprofile);
//	pFBO->IsValid();
//	FramebufferObject::Disable();
//}

void RenderWidget::GPURayCasting()
{
	//pFBO->Bind();
	//pFBO->AttachTexture(GL_TEXTURE_RECTANGLE_ARB, resTextureIdx, GL_COLOR_ATTACHMENT2_EXT);
	//glDrawBuffer(GL_COLOR_ATTACHMENT2_EXT);

	//glEnable(GL_BLEND);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, winWidth, 0, winHeight);

	glEnable(GL_TEXTURE_1D);
	glEnable(GL_TEXTURE_RECTANGLE_ARB);
	glEnable(GL_TEXTURE_3D);
	cgGLEnableProfile(cg_fprofile);

	cgGLBindProgram(cgRayCastingProgram);
	cgGLSetTextureParameter(cgVolume, volumeTextureIdx);
	cgGLSetTextureParameter(cgRegion1, region1TextureIdx);
	cgGLSetTextureParameter(cgRegion2, region2TextureIdx);
	cgGLSetTextureParameter(cgRegion3, region3TextureIdx);
	cgGLSetTextureParameter(cgRegion4, region4TextureIdx);
	cgGLEnableTextureParameter(cgRegion1);
	cgGLEnableTextureParameter(cgRegion2);
	cgGLEnableTextureParameter(cgRegion3);
	cgGLEnableTextureParameter(cgRegion4);
	cgGLEnableTextureParameter(cgVolume);

	cgGLSetTextureParameter(cgTransferFunction, transferTextureIdx);
	cgGLEnableTextureParameter(cgTransferFunction);
	cgGLSetParameter1f(cgStep, step);
	cgGLSetParameter1f(cgOpacity, Opacity);
	cgGLSetParameter2f(cgImageParam, (float)winWidth, (float)winHeight);
	cgGLSetMatrixParameterfr(cgViewMatrix, viewMatrix);
	cgGLSetParameter4f(cgIllumParam, Ka, Kd, 32, Ks);
	cgGLSetParameter3f(cgDimension, volume1->getDimension().x, volume1->getDimension().y, volume1->getDimension().z);
	cgGLSetParameter3f(cgSpacing, volume1->getSpacing().x, volume1->getSpacing().y, volume1->getSpacing().z);
	cgGLSetParameter4f(cgOpacities, opacity1, opacity2, opacity3, opacity4);
	int r, g, b, a;
	featurecolors[0].getRgb(&r, &g, &b);
	cgGLSetParameter4f(cgFeatureColor1, (float)r, (float)g, (float)b, 0.0);
	featurecolors[1].getRgb(&r, &g, &b);
	cgGLSetParameter4f(cgFeatureColor2, (float)r, (float)g, (float)b, 0.0);
	featurecolors[2].getRgb(&r, &g, &b);
	cgGLSetParameter4f(cgFeatureColor3, (float)r, (float)g, (float)b, 0.0);
	featurecolors[3].getRgb(&r, &g, &b);
	cgGLSetParameter4f(cgFeatureColor4, (float)r, (float)g, (float)b, 0.0);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(0, 0);
	glTexCoord2f(0.0, winHeight);
	glVertex2f(0, winHeight);
	glTexCoord2f(winWidth, winHeight);
	glVertex2f(winWidth, winHeight);
	glTexCoord2f(winWidth, 0.0);
	glVertex2f(winWidth, 0);
	glEnd();

	cgGLDisableTextureParameter(cgVolume);
	cgGLDisableTextureParameter(cgTransferFunction);
	cgGLDisableProfile(cg_fprofile);
	glDisable(GL_TEXTURE_1D);
	glDisable(GL_TEXTURE_RECTANGLE_NV);
	glDisable(GL_TEXTURE_3D);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	//pFBO->IsValid();

	////float results[3];
	//imdebugTexImagef(GL_TEXTURE_RECTANGLE_ARB, resTextureIdx, GL_RGB);
	////glReadBuffer(GL_COLOR_ATTACHMENT3_EXT);
	////glReadPixels(256, 256, 1, 1,GL_RGB,GL_FLOAT,results);
	////cout<<results[0]<<" "<<results[1]<<" "<<results[2]<<endl;

	//FramebufferObject::Disable();
}

void RenderWidget::wheelEvent(QWheelEvent *event)
{
	//int numDegrees = event->delta() / 20;
	//zoom+=numDegrees*1.0/100;
	//if(zoom<0)
	//	zoom=0.01;
	int numDegrees = event->delta() / 8;
	int numSteps = numDegrees / 15;

	if (numSteps > 0)
	{
		m_camera.zoom(1.1 * numSteps);
		zoom = m_camera.getZoom();
	}
	else if (numSteps < 0)
	{
		m_camera.zoom(1.0 / (-1.1 * numSteps));
		zoom = m_camera.getZoom();
	}
	updateGL();
}

void RenderWidget::mousePressEvent(QMouseEvent *event)
{
	m_camera.beginDrag(event->x(), event->y());
	lastPoint = event->pos();
}

void RenderWidget::mouseReleaseEvent(QMouseEvent *event)
{
	//if(event->buttons() & Qt::RightButton)
	m_camera.endDrag(event->x(), event->y());
	updateGL();
}

void RenderWidget::mouseMoveEvent(QMouseEvent *event)
{
	int dx = event->x() - lastPoint.x();
	int dy = event->y() - lastPoint.y();

	if (event->buttons() & Qt::LeftButton)
	{
		xAngle += dy;
		yAngle += dx;
		m_camera.mouseMove(event->x(), event->y());
	}
	else if (event->buttons() & Qt::RightButton) {
		/*xAngle += dy;
		zAngle += dx;*/
		/*	xtran+=1.0*dx/width();
		ytran-=1.0*dy/height();	*/
	}
	lastPoint = event->pos();
	updateGL();

}

void RenderWidget::mouseDoubleClickEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton)
	{
		TFPoint = event->pos();
		float x = event->pos().x();
		float y = event->pos().y();
	}

}

void RenderWidget::keyPressEvent(QKeyEvent * event)
{
	if (event->key() == Qt::Key_Z)
	{
		if (event->modifiers() == Qt::ShiftModifier)
			zAngle -= 2;
		else
			zAngle += 2;
	}
	updateGL();

}

void RenderWidget::getVolumeTF(unsigned char* tf)
{
	tf1dVolume = tf;
	isVolumeTFChanged = true;
	update();
}

void RenderWidget::updateTFTexture()
{
	if (tf1dVolume != NULL && isVolumeTFChanged)
	{
		glEnable(GL_TEXTURE_1D);
		glBindTexture(GL_TEXTURE_1D, transferTextureIdx);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA8, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, tf1dVolume);
		glDisable(GL_TEXTURE_1D);
		isVolumeTFChanged = false;
	}
}

void RenderWidget::updateRender(illumParam illumparam)
{
	Ka = illumparam.Ka;
	Kd = illumparam.Kd;
	Ks = illumparam.Ks;
	updateGL();
}

void RenderWidget::setData(Volume* v)
{
	volume1 = v;
	step = 0.5 / Min(volume1->getDimension().x, Min(volume1->getDimension().y, volume1->getDimension().z));
	volumeSize = v->getDimension().x * v->getDimension().y * v->getDimension().z;
	emit dataLoaded(volume1);
}

void RenderWidget::smooth(uchar *region)
{
	int kernelr = 3;
	int kernelw = kernelr * 2 + 1;
	float kernel[7] = { 0.00443, 0.05399, 0.24197, 0.39894, 0.24197, 0.05399, 0.00443 }; //sigma = 1
	//float kernel[7] = { 0.008863696823876, 0.107981933026376, 0.483941449038287, 0.797884560802865, 0.483941449038287, 0.107981933026376, 0.008863696823876 }; //sigma = 0.5
	Vector3i vsize = volume1->getDimension();

	uchar* temp = new uchar[volume1->getTotalSize()];
	uchar* temp2 = new uchar[volume1->getTotalSize()];
	memcpy(temp2, region, volume1->getTotalSize() * sizeof(uchar));
	//along x - direction
	for (int z = 0; z < vsize.z; z++)
	{
		for (int y = 0; y < vsize.y; y++)
		{
			for (int x = 0; x < vsize.x; x++)
			{
				float sum = 0;
				for (int i = -kernelr; i <= kernelr; i++)
				{
					int xx = x - i;
					if (xx >= vsize.x || xx < 0)
						continue;
					int idx = z * vsize.y * vsize.x + y * vsize.x + xx;
					sum += kernel[i + 2] * temp2[idx];
				}
				int idx = z * vsize.y * vsize.x + y * vsize.x + x;
				temp[idx] = sum;
			}
		}
	}
	memcpy(temp2, temp, volume1->getTotalSize() * sizeof(uchar));

	//along y - direction
	for (int z = 0; z < vsize.z; z++)
	{
		for (int x = 0; x < vsize.x; x++)
		{
			for (int y = 0; y < vsize.y; y++)
			{
				float sum = 0;
				for (int i = -kernelr; i <= kernelr; i++)
				{
					int yy = y - i;
					if (yy >= vsize.y || yy < 0)
						continue;
					int idx = z * vsize.y * vsize.x + yy * vsize.x + x;
					sum += kernel[i + 2] * temp2[idx];
				}
				int idx = z * vsize.y * vsize.x + y * vsize.x + x;
				temp[idx] = sum;
			}
		}
	}
	memcpy(temp2, temp, volume1->getTotalSize() * sizeof(uchar));

	//along z - direction
	for (int y = 0; y < vsize.y; y++)
	{
		for (int x = 0; x < vsize.x; x++)
		{
			for (int z = 0; z < vsize.z; z++)
			{
				float sum = 0;
				for (int i = -kernelr; i <= kernelr; i++)
				{
					int zz = z - i;
					if (zz >= vsize.z || zz < 0)
						continue;
					int idx = zz * vsize.y * vsize.x + y * vsize.x + x;
					sum += kernel[i + 2] * temp2[idx];
				}
				int idx = z * vsize.y * vsize.x + y * vsize.x + x;
				temp[idx] = sum;
			}
		}
	}
	//memcpy(selectRegion, temp2, volume1->getTotalSize() * sizeof(uchar));
	for (int z = 0; z < vsize.z; z++)
	{
		for (int y = 0; y < vsize.y; y++)
		{
			for (int x = 0; x < vsize.x; x++)
			{
				int idx = z * vsize.y * vsize.x + y * vsize.x + x;
				region[idx] = max(region[idx], temp2[idx]);
			}
		}
	}
}

void RenderWidget::regionsUpdate()
{
	//smooth(volRegions[0]);
	//smooth(volRegions[1]);
	//smooth(volRegions[2]);
	//smooth(volRegions[3]);
	update();
}

void RenderWidget::setupRegionTexture()
{
	glEnable(GL_TEXTURE_3D);
	glBindTexture(GL_TEXTURE_3D, region1TextureIdx);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage3DEXT(GL_TEXTURE_3D, 0, GL_LUMINANCE8, volume1->getDimension().x, volume1->getDimension().y, volume1->getDimension().z, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, volRegions[0]);
	glDisable(GL_TEXTURE_3D);
	glErrorCheck();

	glEnable(GL_TEXTURE_3D);
	glBindTexture(GL_TEXTURE_3D, region2TextureIdx);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage3DEXT(GL_TEXTURE_3D, 0, GL_LUMINANCE8, volume1->getDimension().x, volume1->getDimension().y, volume1->getDimension().z, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, volRegions[1]);
	glDisable(GL_TEXTURE_3D);
	glErrorCheck();

	glEnable(GL_TEXTURE_3D);
	glBindTexture(GL_TEXTURE_3D, region3TextureIdx);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage3DEXT(GL_TEXTURE_3D, 0, GL_LUMINANCE8, volume1->getDimension().x, volume1->getDimension().y, volume1->getDimension().z, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, volRegions[2]);
	glDisable(GL_TEXTURE_3D);
	glErrorCheck();

	glEnable(GL_TEXTURE_3D);
	glBindTexture(GL_TEXTURE_3D, region4TextureIdx);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage3DEXT(GL_TEXTURE_3D, 0, GL_LUMINANCE8, volume1->getDimension().x, volume1->getDimension().y, volume1->getDimension().z, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, volRegions[3]);
	glDisable(GL_TEXTURE_3D);
	glErrorCheck();
}

void RenderWidget::contextMenuEvent(QContextMenuEvent * event)
{
	QMenu* menu = new QMenu(this);

	QAction* showbox = new QAction("Show Bounding Box", this);
	showbox->setCheckable(true);
	connect(showbox, SIGNAL(changed()), this, SLOT(setBoundingBoxShow()));
	menu->addAction(showbox);

	QPoint pos = cursor().pos();
	menu->move(pos);
	menu->show();
}

void RenderWidget::setBoundingBoxShow()
{
	showBoundingBox = !showBoundingBox;
	update();
}

void RenderWidget::setKa(double ka_)
{
	Ka = ka_;
	update();
}

void RenderWidget::setKd(double kd_)
{
	Kd = kd_;
	update();
}

void RenderWidget::setKs(double ks_)
{
	Ks = ks_;
	update();
}

void RenderWidget::setOpacity(double opacity_)
{
	Opacity = opacity_;
	update();
}

void RenderWidget::colorUpdate()
{
	update();
}

void RenderWidget::setOpacities(int id, double opacity_)
{
	uchar* region;
	switch (id)
	{
	case 1: opacity1 = opacity_;
		break;
	case 2: opacity2 = opacity_;
		break;
	case 3: opacity3 = opacity_;
		break;
	case 4: opacity4 = opacity_;
		break;
	default:
		break;
	}
	update();
}