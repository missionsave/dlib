//D'Elcortese 2014-04-20
#ifdef WIN32
#include <windef.h> // According to comments above
#include <GL/glew.h> // Before any gl headers
#include <GL/gl.h>
#endif // WIN32

#include <algorithm>
#include <glview.hpp>
#include <stringf.hpp>
#include <string.h>




void glview3::mousePanStart(){
	if(mousePan)return;
	mousePan=true;
	mousePanStartCords[0]=wX;
	mousePanStartCords[1]=wY;
}
void glview3::mousePanMotion(bool &redisplay){
	if(!mousePan)return;
	float xmove=wX-mousePanStartCords[0], ymove=wY-mousePanStartCords[1];
	xLeft-=xmove;xRight-=xmove;yBottom-=ymove;yTop-=ymove;
	layout();
	redisplay=1;
}
void glview3::view() {
	view(wW,wH,viewport[0],viewport[1]);
}
void glview3::view(GLint xpos,GLint ypos,GLint ww,GLint wh) {
	wW=(ww);wH=(wh);
	glViewport(xpos, ypos, wW, wH);
	viewport[0]=xpos;viewport[1]=ypos;viewport[2]=ww;viewport[3]=wh;
	layout();////2014-11-07
}
glview3::glview3( )  {

}
void glview3::setnew(GLint xpos,GLint ypos,GLint ww,GLint wh) {
	wW=ww;wH=wh;
  view(xpos, ypos, wW, wH);
}
void glview3::lookAt(){
	gluLookAt(eyeX,eyeY,eyeZ, atX, atY,atZ,upX,upY,upZ);
}
void glview3::scale(){
	glScalef(xScale,yScale,zScale);
}
void glview3::zoomCentered(GLdouble xFactor,GLdouble yFactor){
	GLdouble centerx = ( xRight + xLeft ) * 0.5f;
	GLdouble centery = ( yBottom + yTop ) * 0.5f;

	xLeft = centerx + ((xLeft - centerx) * xFactor);
	yTop = centery + ((yTop - centery) * yFactor);
	xRight = centerx + ((xRight - centerx) * xFactor);
	yBottom = centery + ((yBottom - centery) * yFactor);
}
void glview3::layout(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	switch (orto0Frustum1Perspective2){
		case 0:
			glOrtho(xLeft,  xRight,  yBottom,  yTop,  zNear, zFar);
			mvp= glm::ortho(xLeft,  xRight,  yBottom,  yTop,  zNear, zFar);
			xLeftRightStep=mathStepsBetween(xLeft,xRight,100);
			yBottomTopStep=mathStepsBetween(yBottom,yTop,100);
		break;
		case 1:
			glFrustum(xLeft,xRight,yBottom,yTop,  zNear, zFar);
			xLeftRightStep=mathStepsBetween(xLeft,xRight,100);
			yBottomTopStep=mathStepsBetween(yBottom,yTop,100);
		break;
		case 2:
			gluPerspective(45.0f, 1.0f * wW / wH,  zNear, zFar);
		break;
	}
	glGetDoublev(GL_PROJECTION_MATRIX, matrixProjection);
	//glGetFloatv(GL_PROJECTION_MATRIX, (GLfloat*)&projection);
	//glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)&modelView);
	//accum = projection * modelView;
}
void glview3::updCoords(GLint mx,GLint my,bool updateWorldCoords){
	if(mx==mX && my==mY)return;

	mX=mx;mY=my;

	//        mouseOverViewport=GlWindowMouseViewportIndexes[glv.mX][glv.mY];
	glPushMatrix();
	GLdouble modelview[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glPopMatrix();
	gluUnProject(mX, wH-mY,0.5,modelview,matrixProjection, viewport,&wX,&wY,&wZ);

}
//tem q ter  o updCoords antes
int glview3::select(void *displayfunc){
	GLint hits;
	glSelectBuffer(bufferSize, selectBuf);
	glRenderMode(GL_SELECT); glInitNames(); glPushName(0);
	//        GLdouble projection[16];   glGetDoublev(GL_MODELVIEW_MATRIX, projection);dbgpa(projection,0,16);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluPickMatrix(mX,  wH-mY, 7, 7, viewport);
	glOrtho(xLeft,  xRight,  yBottom,  yTop,  zNear, zFar);
	//gluPerspective(45.0f, (G Lfloat) (viewport[2]-viewport[0])/(GLfloat) (viewport[3]-viewport[1]), 0.1f, 100.0f);//persp
	glMatrixMode(GL_MODELVIEW);                     // Select The Modelview Matrix
	//        voidToType(function<void()>,fxv,displayfunc);
	//chamada à funçao display poderá ser mais rapida ?? Ha sempre a macro
	selecting=true;   ((void (*)()) displayfunc)(); selecting=false;
	glMatrixMode(GL_PROJECTION);                        // Select The Projection Matrix
	glPopMatrix();                              // Pop The Projection Matrix
	glMatrixMode(GL_MODELVIEW);                     // Select The Modelview Matrix
	hits=glRenderMode(GL_RENDER);
	int sel=-1; if (hits!=0){sel=selectBuf[(hits - 1) * 4 + 3]; }     //dbgv(sel);
	return sel;
}










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
