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


#if 0
#include "stringf.hpp"
GLenum stype[]={GL_VERTEX_SHADER,GL_FRAGMENT_SHADER,GL_GEOMETRY_SHADER};

GLuint CreateShader(GLenum eShaderType, const std::string &strShaderFile){
	GLuint shader = glCreateShader(eShaderType);dbgv(9);
	const char *strFileData = strShaderFile.c_str();
	glShaderSource(shader, 1, &strFileData, NULL);
	glCompileShader(shader);
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE){
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

		const char *strShaderType = NULL;
		switch(eShaderType){
		case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
		case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
		case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
		}

		fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
		delete[] strInfoLog;
	}
	return shader;
}
GLuint CreateProgram(const std::vector<GLuint> &shaderList){
	GLuint program = glCreateProgram();

	for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
		glAttachShader(program, shaderList[iLoop]);

	glLinkProgram(program);

	GLint status;
	glGetProgramiv (program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)	{
		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

	for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
	glDetachShader(program, shaderList[iLoop]);

	return program;
}


GLuint InitializeProgram(vstring src){
	if(src.size()==0)return 0;
	std::vector<GLuint> shaderList;

	lop(i,0,src.size()){
		int t=atoi(&src[i][0]);
		dbgv(t);
		triml(src[i],"0123456789");//dbgv(stype[t],src[i]);
		shaderList.push_back(CreateShader(stype[t], src[i]));
	}
//		shaderList.push_back(CreateShader(GL_VERTEX_SHADER, src[0]));
//		shaderList.push_back(CreateShader(GL_FRAGMENT_SHADER, src[1]));

	GLuint theProgram = CreateProgram(shaderList);

	std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);

	return theProgram;
}


void textext(const char * text,vfloat &vertices,vfloat &UVs,int size){
	int x=19; int y=19;
	unsigned int length = strlen(text);
	vertices=vfloat(8*length);
	UVs=vfloat(8*length);
	for ( unsigned int i=0 ; i<length ; i++ ){
		int p=i*8;
		vertices[p+0]=x+i*size; 			vertices[p+1]= y+size;
		vertices[p+2]=x+i*size; 			vertices[p+3]= y;
		vertices[p+4]=x+i*size+size; vertices[p+5]= y;
		vertices[p+6]=x+i*size+size; vertices[p+7]= y+size;
		char character = text[i];
		float uv_x = (character%16)/16.0f;
		float uv_y = (character/16)/16.0f;
		UVs[p+0]=uv_x; 						UVs[p+1]= uv_y;
		UVs[p+2]=uv_x; 						UVs[p+3]= (uv_y + 1.0f/16.0f);
		UVs[p+4]=uv_x+1.0f/16.0f;	UVs[p+5]= (uv_y + 1.0f/16.0f);
		UVs[p+6]=uv_x+1.0f/16.0f;	UVs[p+7]= uv_y;
	}

}

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

GLuint loadDDS(const char * imagepath){

	unsigned char header[124];

	FILE *fp;

	/* try to open the file */
	fp = fopen(imagepath, "rb");
	if (fp == NULL){
		printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath); getchar();
		return 0;
	}

	/* verify the type of file */
	char filecode[4];
	fread(filecode, 1, 4, fp);
	if (strncmp(filecode, "DDS ", 4) != 0) {
		fclose(fp);
		return 0;
	}

	/* get the surface desc */
	fread(&header, 124, 1, fp);

	unsigned int height      = *(unsigned int*)&(header[8 ]);
	unsigned int width	     = *(unsigned int*)&(header[12]);
	unsigned int linearSize	 = *(unsigned int*)&(header[16]);
	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
	unsigned int fourCC      = *(unsigned int*)&(header[80]);


	unsigned char * buffer;
	unsigned int bufsize;
	/* how big is it going to be including all mipmaps? */
	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
	fread(buffer, 1, bufsize, fp);
	/* close the file pointer */
	fclose(fp);

	unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4;
	unsigned int format;
	switch(fourCC)
	{
	case FOURCC_DXT1:
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		break;
	case FOURCC_DXT3:
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case FOURCC_DXT5:
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
	default:
		free(buffer);
		return 0;
	}

	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);

	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	unsigned int offset = 0;

	/* load the mipmaps */
	for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
	{
		unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
			0, size, buffer + offset);

		offset += size;
		width  /= 2;
		height /= 2;

		// Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
		if(width < 1) width = 1;
		if(height < 1) height = 1;

	}

	free(buffer);

	return textureID;


}

#endif


#endif // GLVIEW_HPP_INCLUDED
