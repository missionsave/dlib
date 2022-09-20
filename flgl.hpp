#ifndef FLGL_HPP_INCLUDED
#define FLGL_HPP_INCLUDED

#include "regular.hpp"
#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <functional>
#include <glview.hpp>

namespace g{enum{x1,x2,x3,y1,y2,y3,z1,z2,z3,r1,g1,b1,r2,g2,b2,w};};
using namespace g;

struct fl_gl;
struct glCrosshair{
	fl_gl* flgl;
	float *x,*y;
	void (*onMm)() =0;
	void draw();
	glCrosshair(fl_gl* Flgl);
};

struct glLine{
	vector<float> vals=vector<float>(24);
	#define v(xx) vals[xx]
	float & x1=vals[g::x1];float & x2=vals[g::x2];float & x3=vals[g::x3];
	float & y1=vals[g::y1];float & y2=vals[g::y2];float & y3=vals[g::y3];
	float & z1=vals[g::z1];float & z2=vals[g::z2];float & z3=vals[g::z3];
	float & r1=vals[g::r1];float & r2=vals[g::r2];
	float & g1=vals[g::g1];float & g2=vals[g::g2];
	float & b1=vals[g::b1];float & b2=vals[g::b2];
	float & w=vals[g::w];
	void draw();
	glLine();
	void lineSet(vector<float> indexes,vector<float> vals);

};

struct glohlc{
	fl_gl* flgl;
	glohlc(fl_gl* Flgl);
	vfloat vals;
	int aglomerado=1440;
	float cdist=0.00010f;
	void draw();
	void gen();
};
struct gllines{
	fl_gl* flgl;
	GLuint* gllinesinit=0;
	gllines(fl_gl* Flgl);
	vfloat vals;
	vfloat colors={0,0,0,1};
	void draw();
	void gen();
};

struct glvideo{
	fl_gl* flgl;
	glvideo(fl_gl* Flgl);

};



struct fl_gl : public Fl_Gl_Window {
	glview3 glv;
	///l==1 ZoomlinkeYenabled
	fl_gl(int x, int y, int w, int h, const char* l=0);
	vector<fl_gl*> linkzoomx;
	void glinit();
	void draw();
	int handle(int event);
	vector<function<void()>> onMcc;
	vector<function<void()>> onMc;
	vector<function<void()>> onMr;
	vector<function<void()>> onMw;
	vector<function<void()>> onMwrd;
	vector<function<void()>> onMm;
	vector<function<void()>> onDraw;
	void zoomxYlinkedAdd(Fl_Window* w);
	void pan(vector<fl_gl*> xlink);
	vector<fl_gl*> linkcrosshairx;
	glLine* lineAdd(vector<float> indexes={},vector<float> vals={});
	int* lineprmptdrawids=0;
	void lineprompt();
	bool linepromptactive=0;
	float linepromptstartY=0;
	glCrosshair* gc;
	glohlc* gohlc;
	GLuint* glohlcinit=0;
	glohlc* glohlcAdd();
	gllines* glines;
	gllines* gllinesAdd();
};




#endif // FLW_HPP_INCLUDED
