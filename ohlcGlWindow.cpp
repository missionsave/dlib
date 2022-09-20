#include <functional>
#include <glview.hpp>
#include <ohlcs.hpp>
#include "fl.hpp"


#include "ohlcGlWindow.hpp"

#define glcandle_(x,y,h,l,c,raio) {glBegin(GL_LINES); glVertex2f(x , h);glVertex2f(x , l);glEnd(); if(y!=c){\
glBegin(GL_QUADS); (y>c)?glColor3f(1, 0, 0):glColor3f(1, 1, 1);glVertex2f(x-raio,y);(y>c)?glColor3f(1, 1, 0):glColor3f(0, 1, 1); glVertex2f(x+raio,y);(y>c)?glColor3f(1, 0, 1):glColor3f(1, 1, 0); glVertex2f(x+raio,c);(y>c)?glColor3f(1, 1, 1):glColor3f(0, 1, 0); glVertex2f(x-raio,c);glEnd();        }else{glBegin(GL_LINES); glVertex2f(x-raio,y);  glVertex2f(x+raio,y);glEnd();}}

#define glCandleArray(ohlc,from,to,step) lop(i,from,to){ float raio=step*.4; glcandle_( (i*step ),ohlc[0][i],ohlc[1][i],ohlc[2][i],ohlc[3][i],raio); }

 #if 1
#define wx glv.wX
#define wy glv.wY
#define wz glv.wZ
#define mx glv.mX
#define my glv.mY
#define X1 objpoints[iob][0]
#define Y1 objpoints[iob][1]
#define z1 objpoints[iob][2]
#define x2 objpoints[iob][3]
#define Y2 objpoints[iob][4]
#define z2 objpoints[iob][5]
#define x3 objpoints[iob][6]
#define y3 objpoints[iob][7]
#define z3 objpoints[iob][8]
#define x4 objpoints[iob][9]
#define y4 objpoints[iob][10]
#define z4 objpoints[iob][11]
#define x5 objpoints[iob][12]
#define y5 objpoints[iob][13]
#define z5 objpoints[iob][14]
#define x6 objpoints[iob][15]
#define y6 objpoints[iob][16]
#define z6 objpoints[iob][17]
#define x7 objpoints[iob][18]
#define y7 objpoints[iob][19]
#define z7 objpoints[iob][20]
#define x8 objpoints[iob][21]
#define y8 objpoints[iob][22]
#define z8 objpoints[iob][23]
#endif

void ohlcGlWindow::addLine2d(float _x1,float _y1,float _x2,float _y2,float cora){
            objpoints.push_back( {_x1,_y1,0,_x2,_y2,0,cora,cora,cora}  );
    objTipo.push_back("Line");
}

void ohlcGlWindow::Timer_CB(void *userdata){
    ohlcGlWindow *mygl = (ohlcGlWindow*)userdata;
    if(mygl->refresh){
        mygl->refresh=!mygl->refresh;
        mygl->make_current();
        mygl->handle(FL_MOVE);
//            mygl->swap_buffers();
    }
    Fl::repeat_timeout(1, Timer_CB, userdata);
}

void ohlcGlWindow::FixViewport(int W,int H) {
    glLoadIdentity();
    glv.view(0,0,W,H);
}
void ohlcGlWindow::draw() {  handle(FL_SHOW);    }
void ohlcGlWindow::cls(){make_current(); glClear(GL_COLOR_BUFFER_BIT); swap_buffers();}
void ohlcGlWindow::resize(int X,int Y,int W,int H) {
    Fl_Gl_Window::resize(X,Y,W,H);
    FixViewport(W,H);
    handle(FL_SHOW);
}
ohlcGlWindow::ohlcGlWindow(int X,int Y,int W,int H,const char*L) : Fl_Gl_Window(X,Y,W,H,L) {
    Fl::add_timeout(1, Timer_CB, (void*)this);
    ohlc.aglomerado=2;
    ohlc.offset=0;
		draw();
    end();
      }
void ohlcGlWindow::updateChart(bool autozoom){
    ohlc.offset=0;
//        if(cbin[pr][col].size()%2==0)ohlc.offset=1;

    ///simulate on
//    //        dbgv(trevo==NULL);
//            if(trevo==NULL)return;
//            vector<bool> cbin=_parent->loto[_parent->radioindex].rolup[ _parent->loto[_parent->radioindex].rolupIndex ].cbin;
//    //        dbgpx(trevo->cbin,0,10);
//            if(trevo->resaid!=-1 && loto.mapr[*trevo]!=-1)cbin.push_back(loto.mapr[*trevo]);
//
//            ohlc.toOhLcDirect(mvalues);


     make_current();
    if(autozoom){
        glv.xLeft=-1;glv.xRight=ohlc.ohlc[0].size()+2;
        glv.yBottom=ohlc.ymin; glv.yTop=ohlc.ymax;
//                glv.yBottom=-1; glv.yTop=37;
//                int distfix=35;//bin=*2
//            if(trevo->resaid==-1)distfix=20;
        if(glv.xRight<distfix)glv.xRight=distfix;
        if(glv.xRight>distfix){
//            dbgs(ohlc.ymaxRange(0,distfix));
            glv.xLeft=glv.xRight-distfix;
            glv.yBottom=ohlc.yminRange(glv.xLeft,ohlc.ohlc[0].size());
            glv.yTop=ohlc.ymaxRange(glv.xLeft,ohlc.ohlc[0].size());
        }
        glv.zoomCentered(1,1.1);
    }

        glv.layout();
    handle(FL_SHOW);
}
void ohlcGlWindow::Regen(ohlcGlWindow* og){
    ohlcGlWindow* o;
    if(og==NULL)o=this; else o=og;
    o->make_current();
    o->glv.layout();
    if(o!=this || og==NULL)o->handle(FL_SHOW);
}
int ohlcGlWindow::handle(int event ) {


//            if(event==11){
//                SetForegroundWindow(fl_xid(this));
//                SetFocus(fl_xid(this));
//            }
//            if(event==FL_MOUSEWHEEL){
//                rolups* rl=&_parent->rolup;
//                rl->show(-Fl::event_dy());
//                    return 1;
//            }
    if(event==FL_SHOW){
        redraw();
        if (!valid()) {
            valid(1);
//                    GlInit();
            FixViewport(w(), h());
        }
        glClearDepth(1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    glv.updCoords(Fl::event_x_root()-x_root() , Fl::event_y_root()-y_root() );
    int rc=Fl_Gl_Window::handle(event);
    bool redisplay=0;

//        if(event==FL_KEYUP)dbgs(Fl::event_key());

    if(event==FL_MOVE){make_current();redisplay=1;}


    ///horizontal crosshair
//    if(event==FL_ENTER){ window()->cursor(FL_CURSOR_NONE); }
    if(event==FL_LEAVE){ window()->cursor(FL_CURSOR_DEFAULT);}
    if(event==FL_SHOW && Fl::belowmouse()==this){
            lop(p,0,_panXlink.size()){ if(_panXlink[p]==this)continue; Regen(_panXlink[p]);} Regen(this);
                glColor3f(0.3, 0.4, 0.3);
                glBegin(GL_LINES);
                glVertex3f( 0,glv.wY,0);
                glVertex3f( 10000,glv.wY,0);
                glVertex3f( glv.wX,-10000,0);
                glVertex3f( glv.wX,10000,0);
                glEnd();
    }

    ///horizontal ltn
//            if(ohlc.ohlc.size()>0)
//            if(event==FL_SHOW ){
//                        glColor3f(0.8, 0.3, 0.8);
//                        glBegin(GL_LINES);
//                        glVertex3f( ohlc.ohlc[3].size()-1,ltn,0);
//                        glVertex3f( ohlc.ohlc[3].size()+2,ltn,0);
//                        glEnd();
//            }




    ///HLine
    if(event==FL_SHOW){
        lop(iob,0,objTipo.size()){
            if(objTipo[iob]!="HLine")continue;
            glColor3f(x3,y3,z3);
            glBegin(GL_LINES);
            glVertex2f( -1000000,X1 );
            glVertex2f( 1000000,X1 );
            glEnd();
        }
    }

    ///pan
    if(event==FL_PUSH && Fl::event_button()==FL_RIGHT_MOUSE){glv.mousePanStart(); redisplay=1; rc=1; } //dbgs(Fl::focus());
    if(event==FL_RELEASE){  glv.mousePan=false;redisplay=1;  }
    if(event==FL_DRAG &&  glv.mousePan){glv.mousePanMotion(redisplay);
        lop(p,0,_panXlink.size()){
            if(_panXlink[p]==this)continue;
            _panXlink[p]->glv.xLeft=glv.xLeft;
            _panXlink[p]->glv.xRight=glv.xRight;
            _panXlink[p]->make_current();
            _panXlink[p]->glv.layout();
            _panXlink[p]->handle(FL_SHOW);
        }

        make_current();
        glv.layout();
//                return 1;
    }//varsOrthoVerticalLockPan(glv.xLeft,glv.xRight);}


    ///Line
    if(event==FL_SHOW){
        lop(iob,0,objTipo.size()){
            if(objTipo[iob]!="Line")continue;
            glBegin(GL_LINES);
            glColor3f(x3,y3,z3);
            glVertex2f( X1,Y1);
            glVertex2f( x2,Y2);
            glEnd();
        }
    }
//if(event==FL_SHOW){
//    if(glLines.size()>0)dbgv(glLines.size());
//    lop(i,0,glLines.size())glLines[i].draw();
//}
    ///candle
    if(event==FL_SHOW){

//                glBegin(GL_LINES); glVertex2f(-1 , 0);glVertex2f(1 , 0);glEnd();
        glCandleArray(ohlc.ohlc,0,ohlc.ohlc[0].size() ,1);//glEnd();
//
//            //horizontal line
            if(ohlc.ohlc[3].size()>0){
                glBegin(GL_LINES);
                glColor3f(0.1, 0.3, 0.1);
                glVertex2f( 0,ohlc.ohlc[3].back());
                glVertex2f( ohlc.ohlc[3].size()-1,ohlc.ohlc[3].back());
                glEnd();
            }


            //median horizontal line
//                    if(ohlc.ohlc[3].size()>0){
//                        float ymax=*max_element(ohlc.ohlc[1].begin(),ohlc.ohlc[1].end());
//                        float ymin=*min_element(ohlc.ohlc[1].begin(),ohlc.ohlc[1].end());
//                        float ymedian=(ymax-ymin)/2+ymin;
//                        glColor3f(0.6, 0.7, 0.3);
//                        glBegin(GL_LINES);
//                        glVertex3f( ohlc.ohlc[3].size()-1, ymedian ,0);
//                        glVertex3f( ohlc.ohlc[3].size()+2, ymedian ,0);
//                        glEnd();
//                    }
//            rc= FL_SHOW;
    }

     ///movProjectado
    #if 1
    if(event==FL_KEYUP){
        //dbgv(Fl::event_key());
        if(Fl::event_key()==65507000000)
            if(objAction==""){
                objAction="movProjectado";
                objpoints.push_back(vector<float>(28));
                objTipo.push_back("movProjectado");
                objActionIndex=objTipo.size()-1;
                redisplay=1;
            }
    }
    if(event==FL_SHOW){
//                if(objAction=="movProjectado")
        lop(iob,0,objTipo.size()){
            if(objTipo[iob]!="movProjectado")continue;
            glBegin(GL_LINES);
            glVertex3f( X1,Y1,z1);
            glVertex3f( x2,Y2,z2);
            glVertex3f(x3,y3,z3);
            glVertex3f(x4,y4,z4);
            glVertex3f(x5,y5,z5);
            glVertex3f(x6,y6,z6);
            glVertex3f(x8,y8,z8);
            glVertex3f(x7,y7,z7);
            glEnd();
        }
    }
    if(objAction=="movProjectado"){
        int iob=objActionIndex;
        function<void()> drawf=[&](){
            float ang=mathTrigRectAng((x2-X1),(Y2-Y1));
            float frt=mathTrigRectFrt(ang, (wx-X1) );

            if(y4==0 &&x4==0)return;
            y3=wy-frt;
            x3=X1;

            x5=x2+(x4-X1);
            y5= (y4)+ mathTrigRectFrt(ang,(x5-x4));

            x6=x5;
            y6=Y2;

            //extend
            x7=0;
            y7=Y1-mathTrigRectFrt(ang,X1);

            //extend
            x8=1000;
            y8=Y2+mathTrigRectFrt(ang,(x8-x2));
        };
        if(event==FL_MOVE){
            //dbgv(objActionStage);
            if(objActionStage==1){ x2 = wx; Y2 = wy; drawf();  }
            if(objActionStage==2){ y4=wy; x4=wx; drawf();  }
            redisplay=1;
        }
        if(event==FL_PUSH && Fl::event_button()==FL_LEFT_MOUSE){
            if(objActionStage==0){ X1 =x2 = wx; Y1 =Y2 = wy; }
            objActionStage++;
            rc=1;
        }
        if(event==FL_RELEASE){ if(objActionStage==3){ objAction=""; objActionStage=0;  objActionIndex=-1;} }
    }
    #endif

    ///movTrendLine
    #if 1
    if(event==FL_PUSH){
        if(Fl::event_button()==FL_LEFT_MOUSE)
            if(objAction==""){
                objAction="movTrendLine";
                objpoints.push_back(vector<float>(6));
                objActionIndex=objpoints.size()-1;
                redisplay=1;
            }
    }
    if(objAction=="movTrendLine"){
        int iob=objActionIndex;
        if(event==FL_SHOW){
            glBegin(GL_LINES);
            glColor3f(0.9, 0.9, 0.9);
            glVertex2f( X1,Y1);//,z1);
            glVertex2f( x2,Y2);//,z2);
            glEnd();
        }
        if(event==FL_MOVE){
            if(objActionStage==1){
//                        x2 = wx; Y2 = wy;
                float ang=mathTrigRectAng((wx-X1),(wy-Y1));

                x2=(wx-X1)>0?1000:-1000;
                Y2=Y1+mathTrigRectFrt(ang,(x2-X1));
//                        ang=abs(mathDecToRad(ang));
//                        x2=cos(ang)*10000;
//                        Y2=sin(ang)*10000;
//                        Y2=Y1-mathTrigRectFrt(ang,X1);
            }
            redisplay=1;
        }
        if(event==FL_PUSH && Fl::event_button()==FL_LEFT_MOUSE){
            if(objActionStage==0){ X1 =x2 = wx; Y1 =Y2 = wy; }
            objActionStage++;
            rc=1;
        }
        if(event==FL_RELEASE){ if(objActionStage==2){ objAction=""; objActionStage=0;  objActionIndex=-1;} }
        if(event==FL_SHORTCUT && Fl::event_key()==FL_Escape){
            objpoints.pop_back();objAction="";objActionStage=0;  objActionIndex=-1; rc=1;
        }
    }
    #endif

    ///end
    if(redisplay){handle(FL_SHOW);}
//    glFlush();
//    swap_buffers();
    return rc;
}
