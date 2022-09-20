//D'Elcortese 2014-04-20

#ifndef GLVIEW_HPP_INCLUDED
#define GLVIEW_HPP_INCLUDED

#define GLEW_STATIC
#define FL_GL_CORE_PROFILE = 1024

#define GLSL(src) "#version 300 es\n\nprecision mediump float;\n" #src
#define glslv(src) "0#version 300 es\n\nprecision highp float;\n" #src
#define glslf(src) "1#version 300 es\n\nprecision highp float;\n" #src
#define glslg(src) "2#version 300 es\n\nprecision mediump float;\n #extension GL_EXT_geometry_shader4 : enable \n #extension GL_EXT_gpu_shader4 : enable \n " #src
//#define glslv(src) "0#version 150  \n " #src
//#define glslf(src) "1#version 150    \n " #src
//#define glslg(src) "2#version 150  \n #extension GL_EXT_geometry_shader4 : enable \n #extension GL_EXT_gpu_shader4 : enable \n " #src

//GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP,GL_LINES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN,GL_TRIANGLES, GL_QUAD_STRIP, GL_QUADS, GL_POLYGON

//GL_COMPUTE_SHADER,  GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, GL_FRAGMENT_SHADER


using namespace std;
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include <FL/gl.h>

#include "math.hpp"

//	theProgram=InitializeProgram({strVertexShader,strFragmentShader});
GLuint InitializeProgram(vstring src);
GLuint loadDDS(const char * imagepath);
void textext(const char * text,vfloat &vertices,vfloat &UVs,int size);

struct glview3{
		glm::mat4 mvp, modelView, projection, accum;
    GLint orto0Frustum1Perspective2=0;
    GLint wW,wH;//window where viewport and ortho is
    GLdouble eyeX=0, eyeY=0, eyeZ=0, atX=0,atY=0,atZ=-100,upX=0,upY=1,upZ=0; //lookAt
    GLdouble xLeft=-1,  xRight=1,  yBottom=-1,  yTop=1,  zNear=-1,  zFar=1;//ortho or frustum
    GLint viewport[4];
    GLdouble matrixProjection[16];
    GLdouble matrixModel[16];
    GLuint selectBuf[1024];
    const int bufferSize = sizeof(selectBuf)/sizeof(GLuint);
    GLdouble xLeftRightStep, yBottomTopStep;
    GLdouble xScale=1,yScale=1,zScale=1; //scale
    GLfloat crossX=0,crossY=0; //mouse
    GLint mX=0,mY=0; //mouse
    GLdouble wX=0,wY=0,wZ=0; //world coords
    GLboolean mouseOverViewport;
    GLboolean selecting;
    //on mouseUP mousePan tem q passar a false ex if(glv.mousePan)glv.mousePan=false;
    GLboolean mousePan=false;
    GLdouble mousePanStartCords[2];
    void mousePanStart();
    void mousePanMotion(bool &redisplay);
    void view();
    void view(GLint xpos,GLint ypos,GLint ww,GLint wh) ;
    glview3( );
    void setnew(GLint xpos=0,GLint ypos=0,GLint ww=1280,GLint wh=528);
    void lookAt();
    void scale();
    void zoomCentered(GLdouble xFactor,GLdouble yFactor);
    void layout();
    void updCoords(GLint mx,GLint my,bool updateWorldCoords=true);
    int select(void *displayfunc);
//    void zoom
};



#endif // GLVIEW_HPP_INCLUDED
