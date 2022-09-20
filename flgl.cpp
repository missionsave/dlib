#include "fl.hpp"
#include <functional>
#include <typeinfo>
#include <unordered_map>
#include <glview.hpp>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
//#include <ohlcs.hpp>
#include "threads.hpp"
#include <flgl.hpp>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/x.H>
#include <algorithm>

void fl_gl::draw(){
	if ( !valid() ) {
		valid(1);

		glLoadIdentity();
		glClearColor(255,255,255,0)  ;
		glv.view(0, 0, w(), h());
	}

	glClear(GL_COLOR_BUFFER_BIT);
	lop(i,0,onDraw.size())
		if( (bool)(onDraw[i]))
			onDraw[i]();

}

int fl_gl::handle(int e) {
	int ret = Fl_Gl_Window::handle(e);

	if(e==FL_PUSH){
		if(Fl::event_clicks()==1)return 1;
		Fl::add_timeout(0.03, [](void* th){
			fl_gl* fg=(fl_gl*)th;
			///single
			if(Fl::event_clicks()==0){
				for(int i=0;i<fg->onMc.size();i++)
				if( (bool)(fg->onMc[i])){
					fg->onMc[i]();
				}
			}

		///double
		///dbgv(fg->onMcc.size(),Fl::event_clicks());
		if(Fl::event_clicks()>=1){
			for(int i=0;i<fg->onMcc.size();i++)
			if( (bool)(fg->onMcc[i])){
				fg->onMcc[i]();
			}
		};

	},(void*)this);
	if(onMc.size()>0)return 1;
	}


	if(e==FL_RELEASE){
		lop(i,0,onMr.size()){
			if( (bool)(onMr[i])){
				onMr[i]();
			}
		}
		if(onMc.size()>0)return 1;
	}

	if(e==FL_MOUSEWHEEL)
		lop(i,0,onMw.size())
			if( (bool)(onMw[i])){
				onMw[i]();
				return 1;
			}


	if((e==FL_MOVE || e==FL_DRAG)){
		lop(i,0,onMm.size())
			if( (bool)(onMm[i])){
					onMm[i]();
		}
	}

		return ret;
}


void glLine::draw(){
//	dbgv("draw",r1,r2,g1,g2);
//	glColor3f(0.3, 0.4, 0.3);
	glLineWidth(w);
	glBegin(GL_LINES);
	glColor3f(r1,g1,b1);
	glVertex3f( x1 , y1, 0 );
	glColor3f(r2,g2,b2);
	glVertex3f( x2 , y2, 0 );
	glEnd();
}
glLine::glLine(){
	v(r1)=0;v(g1)=0;v(b1)=0;v(r2)=0;v(g2)=0;v(b2)=0;v(w)=1;
}
;
glLine* fl_gl::lineAdd( vector<float> indexes,vector<float> vals){
	glLine* gc=new glLine();
	lop(i,0,indexes.size())gc->vals[indexes[i] ] =vals[i];
	function<void()> lfv=std::bind(&glLine::draw, gc);
  function<void()>* ffn=new std::function<void()>(lfv);
  onDraw.push_back(*ffn);
	redraw();
	return gc;
}
void glLine::lineSet(vector<float> indexes,vector<float> vals){
    lop(i,0,indexes.size())vals[indexes[i] ] =vals[i];
}

void glCrosshair::draw(){
//		flgl->make_current();
	glColor3f(0.3, 0.4, 0.3);
	glBegin(GL_LINES);
	glVertex3f( -1000000,*y,0);
	glVertex3f( 1000000,*y,0);
	glVertex3f( *x,-1000000,0);
	glVertex3f( *x,1000000,0);
	glEnd();
//		lop(i,0,flgl->linkcrosshairx.size()){
////			flgl->linkcrosshairx[i]->gc->x=flgl->gc->x;
//   flgl->linkcrosshairx[i]->make_current();
//			flgl->linkcrosshairx[i]->glv.layout();
//			flgl->linkcrosshairx[i]->redraw();
//		}
//		flgl->make_current();
}
glCrosshair::glCrosshair(fl_gl* Flgl){
	flgl=Flgl;
	x=&flgl->glv.crossX;
	y=&flgl->glv.crossY;
	flgl->onMm.push_back([=]{
		flgl->glv.updCoords(Fl::event_x_root()-flgl->x_root() , Fl::event_y_root()-flgl->y_root() );
		*x=flgl->glv.wX;
		*y=flgl->glv.wY;
		flgl->redraw();
		if(onMm)voidToFunc(onMm)();
	});

}

void fl_gl::zoomxYlinkedAdd(Fl_Window* w){
	///zoom enabled


}
Fl_Slider* fv;
Fl_Scrollbar* fs;

void zoomxc(Fl_Widget*,void* v){
	fl_gl* flgl=(fl_gl*)v;
	vfloat &vals=flgl->glines->vals;
	fv->bounds(50,vals.size());
	fs->bounds(0,vals.size()-50);
	volatile float vmax=-1000000;
	volatile float vmin=1000000;

	int xr=fv->value()+fs->value();
	int xl=fs->value();

	vmax=*max_element(vals.begin()+xl,vals.begin()+xr);
	vmin=*min_element(vals.begin()+xl,vals.begin()+xr);

	flgl->make_current();
	flgl->glv.xRight=xr;
	flgl->glv.xLeft=xl;
	flgl->glv.yBottom=vmin;
	flgl->glv.yTop=vmax;

	flgl->glv.zoomCentered(1,1.3);
	flgl->glv.layout();
	flgl->redraw();

	lop(i,0,flgl->linkzoomx.size()){
		fl_gl* fgl=flgl->linkzoomx[i];
		vfloat &vals=fgl->glines->vals;
		if(vals.size()==0)continue;
		vmax=*max_element(vals.begin()+xl,vals.begin()+xr);
		vmin=*min_element(vals.begin()+xl,vals.begin()+xr);
		fgl->make_current();
		fgl->glv.xRight=xr;
		fgl->glv.xLeft=xl;
		fgl->glv.yBottom=vmin;
		fgl->glv.yTop=vmax;

		fgl->glv.zoomCentered(1,1.3);
		fgl->glv.layout();
		fgl->redraw();

	}
}

fl_gl::fl_gl(int x, int y, int w, int h,const char* l ): Fl_Gl_Window(x,y, w, h, l) {

if(l=="1")	{
	this->h(h-20);
	fs=new Fl_Scrollbar(x+100,y+h-20,w-100,20);
	fs->show();
	fs->type(FL_HORIZONTAL);
	fv=new Fl_Slider(x,y+h-20,100,20);
	fv->type(1);
	fv->show();
 fv->slider_size(.5);
 fv->callback(zoomxc,this);
 fs->slider_size(.5);
 fs->bounds(100,200);

 fs->callback(zoomxc, this);
}
//Flgl->parent()->add(fv);
}

void fl_gl::glinit(){
	make_current();
	glewExperimental = GL_TRUE;
//  if(glewInit() != GLEW_OK)
//		throw std::runtime_error("glewInit failed");

 	gc=new glCrosshair(this);
	function<void()> lfv=std::bind(&glCrosshair::draw, gc);
	function<void()>* ffn=new std::function<void()>(lfv);
	onDraw.push_back(*ffn);

//	pan({});
	lineprompt();

	onMw.push_back([&]{
									float v=Fl::event_dy();
									//dbgv(event_button()==FL_RIGHT_MOUSE)
									glv.zoomCentered(v+v*0.1,v+v*0.1);
									make_current();
									redraw();
									Fl::check();

	});
const unsigned char* vv= glGetString(GL_VERSION);
const unsigned char* v= glGetString(GL_SHADING_LANGUAGE_VERSION);
dbgv(vv,v);
}


void fl_gl::pan(vector<fl_gl*> xlink){
    onMc.push_back([=]{
//        if(Fl::event_button()==FL_RIGHT_MOUSE)
										glv.mousePanStart();
    });
    onMm.push_back([=]{
        if(glv.mousePan){
									//dbgv(0);
            bool dumy;
//            make_current();
            glv.mousePanMotion(dumy);
        }
            lop(p,0,xlink.size()){
                if(xlink[p]==this)continue;
                fl_gl* widl=xlink[p];
                glview3 &glvl=widl->glv;
                if(glv.mousePan){
                    glvl.xLeft=glv.xLeft;
                    glvl.xRight=glv.xRight;
                }
                glvl.crossX=glv.crossX;
                widl->make_current();
                glvl.layout();
                widl->redraw();
            }
            make_current();
            glv.layout();
            redraw();
    });
    onMr.push_back([=]{
        if(glv.mousePan)glv.mousePan=false;
    });
}

void fl_gl::lineprompt(){
	glLine* gc=new glLine;
	auto mmove=[=]{
		float ang=mathTrigRectAng((glv.wX-gc->x1),(glv.wY-gc->y1));
		gc->x2=(glv.wX-gc->x1)>0?1000000:-1000000;
		gc->y2=gc->y1+mathTrigRectFrt(ang,(gc->x2-gc->x1));
		linepromptstartY=gc->y1;
	};
	onMc.push_back([=]{
		if(Fl::event_button()==FL_LEFT_MOUSE){
//			if(!linepromptactive)return;
//			linepromptactive=1;
			if(lineprmptdrawids!=0){
				onDraw.erase(onDraw.begin()+lineprmptdrawids[0]);
				onMm.erase(onMm.begin()+lineprmptdrawids[1]);
				delete lineprmptdrawids;
				lineprmptdrawids=0;
				return;
			}
			lineprmptdrawids=new int[2];
			std::function<void()> lfv=std::bind(&glLine::draw, gc);
			std::function<void()>* ffn=new std::function<void()>(lfv);
			onDraw.push_back(*ffn);
			lineprmptdrawids[0]=onDraw.size()-1;
			gc->x1 =gc->x2 = glv.wX; gc->y1 =gc->y2 = glv.wY;
			std::function<void()>* ffn1=new std::function<void()>(mmove);
			onMm.push_back(*ffn1);
			lineprmptdrawids[1]=onMm.size()-1;
		}
	});
}

#if 1 ///glohlc
// 1
//#define cdist 0.00010f
glohlc::glohlc(fl_gl* Flgl){
	flgl=Flgl;
	if(flgl->glohlcinit==0){
		flgl->glohlcinit=new GLuint[9];
		GLuint &program=flgl->glohlcinit[0];
		GLuint &vao=flgl->glohlcinit[1];
		GLuint &pbo=flgl->glohlcinit[2];
		GLuint &mvp=flgl->glohlcinit[3];
		GLuint &qtv=flgl->glohlcinit[4];
		GLuint &pbo1=flgl->glohlcinit[5];
		GLuint &vao1=flgl->glohlcinit[6];
		GLuint &pbo0=flgl->glohlcinit[7];
		GLuint &aglom=flgl->glohlcinit[8];

		vstring shaders = {
			glslv(
				layout(location = 0) in float pos;
				layout(location = 1) in float cor;
				uniform  mat4 mvp;
				uniform  float aglom;
				out vec4 vpos;

				out float fcor;
				int xp;
				float xpf;
				void main(){
					xp=gl_VertexID%2==0?gl_VertexID:gl_VertexID-1;
					xpf=float(xp)*aglom;
					gl_Position =  mvp*vec4(xpf,  pos,0, 1.0);
					fcor=cor;
				}
			),
			glslf(
				in float fcor;
				out vec4 outputColor;
				vec4 outc;
				void main(){
					float fc=gl_FragCoord.x;
					outc=vec4(1.0f, 0.0f, 0.1f, 1.0f);
					if(fcor>0.1f)outc = vec4(0.3f, 1.0f, 0.3f, 1.0f);
					outputColor=outc;
				}
			)
		};
		program=InitializeProgram(shaders);

		mvp = glGetUniformLocation(program, "mvp");
		aglom = glGetUniformLocation(program, "aglom");

		glGenBuffers(1, &pbo0);

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &pbo);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, pbo);
		glVertexAttribPointer((GLuint)0, 1, GL_FLOAT, GL_FALSE, sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);
		///cor
		glBindBuffer(GL_ARRAY_BUFFER, pbo0);
		glVertexAttribPointer((GLuint)1, 1, GL_FLOAT, GL_FALSE, sizeof(GLfloat), 0);
		glEnableVertexAttribArray(1);


		glGenVertexArrays(1, &vao1);
		glGenBuffers(1, &pbo1);
		glBindVertexArray(vao1);
		glBindBuffer(GL_ARRAY_BUFFER, pbo1);
		glVertexAttribPointer((GLuint)0, 1, GL_FLOAT, GL_FALSE, sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);
		///cor
		glBindBuffer(GL_ARRAY_BUFFER, pbo0);
		glVertexAttribPointer((GLuint)1, 1, GL_FLOAT, GL_FALSE, sizeof(GLfloat), 0);
		glEnableVertexAttribArray(1);


	}

}

void glohlc::gen(  ){
	GLuint &pbo=flgl->glohlcinit[2];
	GLuint &pbo1=flgl->glohlcinit[5];
	GLuint &pbo0=flgl->glohlcinit[7];




		volatile float vmax=-1000000;
		volatile float vvmin=1000000;
    int sze=vals.size()/(float)aglomerado;
    if(vals.size()%aglomerado!=0)sze++;
		vfloat vert(sze*2);
		vfloat vert1(sze*2);
		vfloat vert0(sze*2);

		int ui=0;
    int shocand=60;
    int candle=-2;
    lop(i,0,vals.size()){
//    	dbgv(vals[i]);getchar();
        int x=i%aglomerado;
        if(x==0 || i==0)candle+=2;
        float &o=vert[candle];
        float &c=vert[candle+1];
        float &h=vert1[candle+1];
        float &l=vert1[candle];
        if(x==0 || i==0){
          o=vals[i];
          h=vals[i];
          l=vals[i];
          c=vals[i];
//          dbgv(o,h,l,c);  getchar();
            continue;
        }
//        dbgv(vals[i]);
        if(candle>((sze-shocand)*2)){
//dbgv(vals.size(),aglomerado,candle,sze,ui++);
        		if(vals[i]>vmax){
        			vmax=vals[i];
//dbgv(vmax);
}
					if(vals[i]<vvmin){
						vvmin=vals[i];
//dbgv(vmin);
}
        }
        if(vals[i]>h)
        	h=vals[i];
        if(vals[i]<l)
        	l=vals[i];
        if(x==aglomerado-1 || i==vals.size()-1){
        	c=vals[i]+0.0001;
        		if(c>o){vert0[candle]=1;vert0[candle+1]=1;}
//        dbgv(x,o,h,l,c);
        }
    }

///dbgv(sze,vals.size(),aglomerado,candle,vmax,vvmin);

	//dbgv(sze,vals.size(),aglomerado);

		flgl->make_current();
		flgl->glv.xRight=(sze*+2)*(cdist*aglomerado);//sze
		flgl->glv.xLeft=(((sze-shocand)*+2)*(cdist*aglomerado));
		flgl->glv.yBottom=vvmin;
		flgl->glv.yTop=vmax;

		flgl->glv.zoomCentered(1,1.3);
		flgl->glv.layout();
///dbgv(flgl->glv.xLeft,flgl->glv.xRight,(((sze-100)*+2)*(cdist*aglomerado)));

		glBindBuffer(GL_ARRAY_BUFFER, pbo1);
		glBufferData(GL_ARRAY_BUFFER, vert1.size()*sizeof(float), &vert1[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, pbo);
		glBufferData(GL_ARRAY_BUFFER, vert.size()*sizeof(float), &vert[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, pbo0);
		glBufferData(GL_ARRAY_BUFFER, vert0.size()*sizeof(float), &vert0[0], GL_STATIC_DRAW);

		GLuint &qtv=flgl->glohlcinit[4];
		qtv=vert.size()/1; ///2==layout(location = 0) in vec2 pos
dbgv(qtv)
		flgl->redraw();

}

void glohlc::draw(){
	GLuint &program=flgl->glohlcinit[0];
	GLuint &vao=flgl->glohlcinit[1];
	GLuint &vao1=flgl->glohlcinit[6];
	GLuint &mvp=flgl->glohlcinit[3];
	GLuint &qtv=flgl->glohlcinit[4];
	GLuint &aglom=flgl->glohlcinit[8];
	glUseProgram(program);

	glUniformMatrix4fv(mvp , 1, GL_FALSE, glm::value_ptr(flgl->glv.mvp));
	glUniform1f(aglom , cdist*aglomerado);

	glBindVertexArray(vao);
	glLineWidth(8.0f);
	glDrawArrays(GL_LINES, 0,  qtv );

	glBindVertexArray(vao1);
	glLineWidth(1.0f);
	glDrawArrays(GL_LINES, 0,  qtv );

	glUseProgram(0);

}



glohlc* fl_gl::glohlcAdd(){
 	glohlc* gc=new glohlc(this);
	function<void()> lfv=std::bind(&glohlc::draw, gc);
	function<void()>* ffn=new std::function<void()>(lfv);
	onDraw.push_back(*ffn);
	redraw();
	gohlc=gc;
	return gc;
}


#endif

#if 1 ///gllines

//#define cdist 0.00010f
gllines::gllines(fl_gl* Flgl){
	flgl=Flgl;
	if(gllinesinit==0){
		gllinesinit=new GLuint[9];
		GLuint &program=gllinesinit[0];
		GLuint &vao=gllinesinit[1];
		GLuint &pbo=gllinesinit[2];
		GLuint &mvp=gllinesinit[3];
		GLuint &qtv=gllinesinit[4];
		GLuint &color=gllinesinit[5];

		vstring shaders = {
			glslv(
				layout(location = 0) in float pos;
				uniform vec4 colorx;
				uniform  mat4 mvp;
				out vec4 colorV;
 			float xpf;
				void main(){
					xpf=float(gl_VertexID);
					gl_Position =  mvp*vec4(xpf,  pos,0, 1.0);
					colorV = colorx;
				}
			),
			glslf(
				in vec4 colorV;
				out vec4 outputF;
				void main(){
					outputF =colorV;
//					outputF = vec4( 0 , 0.8f, 0.1f, 1.0f);
//					color = vec3(0,0,0);
				}
			)
		};
		program=InitializeProgram(shaders);

		mvp = glGetUniformLocation(program, "mvp");


//		GLfloat* myFloats[4] = { 0 , 0.8f, 0.1f, 1.0f};
color = glGetUniformLocation(program, "colorx");
//if (loc != -1)

//		GLuint colorbuffer;
//    glGenBuffers(1, &colorbuffer);
//		 glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
// glBufferData(GL_ARRAY_BUFFER, sizeof(myFloats), myFloats, GL_STATIC_DRAW);
//		GLint myLoc = glGetUniformLocation(program, "color");
//		glBindAttribLocation(program, 2, "color");
//glProgramUniform4fv(program, myLoc, 4, myFloats);

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &pbo);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, pbo);
		glVertexAttribPointer((GLuint)0, 1, GL_FLOAT, GL_FALSE, sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);


	qtv=0;
	}

}

void gllines::gen(  ){
	GLuint &program=gllinesinit[0];
	GLuint &pbo=gllinesinit[2];
	GLuint &qtv=gllinesinit[4];

		volatile float vmax=-1000000;
		volatile float vmin=1000000;
		vmax=*max_element(vals.begin(),vals.end());
		vmin=*min_element(vals.begin(),vals.end());

		flgl->make_current();
		flgl->glv.xRight=vals.size();
		flgl->glv.xLeft=0;
		flgl->glv.yBottom=vmin;
		flgl->glv.yTop=vmax;

		flgl->glv.zoomCentered(1,1.3);
		flgl->glv.layout();


		glBindBuffer(GL_ARRAY_BUFFER, pbo);
		glBufferData(GL_ARRAY_BUFFER, vals.size()*sizeof(float), &vals[0], GL_STATIC_DRAW);

		qtv=vals.size()/1; ///2==layout(location = 0) in vec2 pos
		flgl->redraw();
}

void gllines::draw(){
	GLuint &program=gllinesinit[0];
	GLuint &vao=gllinesinit[1];
	GLuint &mvp=gllinesinit[3];
	GLuint &qtv=gllinesinit[4];
		GLuint &color=gllinesinit[5];

	glUseProgram(program);


		glUniform4f(color,colors[0],colors[1],colors[2],colors[3] );

	glUniformMatrix4fv(mvp , 1, GL_FALSE, glm::value_ptr(flgl->glv.mvp));


	glBindVertexArray(vao);
	glLineWidth(2.0f);
	glDrawArrays(GL_LINE_LOOP , 0,  qtv );
	glLineWidth(1.0f);

	glUseProgram(0);

}

gllines* fl_gl::gllinesAdd(){
 	gllines* gc=new gllines(this);
	function<void()> lfv=std::bind(&gllines::draw, gc);
	function<void()>* ffn=new std::function<void()>(lfv);
	onDraw.push_back(*ffn);
	redraw();
	glines=gc;
	return gc;
}

#endif // 0
