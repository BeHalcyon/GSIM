#pragma once

#pragma comment(lib, "cg.lib")
#pragma comment(lib, "cggl.lib")

#if _DEBUG
//#pragma comment(lib, "glew32.lib")
//#pragma comment(lib, "nvWidgetsd.lib")
//#pragma comment(lib, "nvModeld.lib")
#else
//#pragma comment(lib, "glew32.lib")
//#pragma comment(lib, "nvWidgets.lib")
//#pragma comment(lib, "nvModel.lib")
#endif

#include <stdio.h>
#include <tchar.h>
#include <assert.h>

// TODO: reference additional headers your program requires here
#include <iostream>
#include <map>

using namespace std;



#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>

//#include <nvGlutManipulators.h>
//#include <nvModel.h>
//#include <nvGlutWidgets.h>
//#include <nvSDKPath.h>

#include <Cg/cg.h>
#include <Cg/cgGL.h>

#include "util/framebufferObject.h"