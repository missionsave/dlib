

#ifndef OHLCGLWINDOW_HPP_INCLUDED
#define OHLCGLWINDOW_HPP_INCLUDED

#include <FL/Fl_Gl_Window.H>
#include <glview.hpp>
#include <ohlcs.hpp>

//struct glLine{
//    float x1, y1,z1=0;
//    float r1,g1,b1,a1;
//    float x2, y2,z2=0;
//    float r2,g2,b2,a2;
//    void draw(){
//        dbgv(r1,y1);
//        glBegin(GL_LINES);
//        glColor4f(r1,g1,b1,a1);
//        glVertex3f( x1,y1,z1);
//        glColor4f(r2,g2,b2,a2);
//        glVertex3f( x2,y2,z2);
//        glEnd();
//    }
//    void erase(vector<glLine*> &vg){
////        vg.erase((vector<glLine*>::iterator) this);
//    }
//    void add(vector<glLine*> &vg){
////        vg.push_back(this);glLine*gli=&vg.back();
//    }
//    static glLine* addnew(vector<glLine*> &vg,vector<float> rgb1=vector<float>(),vector<float> rgb2=vector<float>()){
////        vg.push_back(glLine());
////        glLine*gli=&vg.back();
//        glLine*gli=new glLine();
//        if(!rgb1.empty()){
//            if(rgb1.size()>0)gli->r1=rgb1[0];
//            if(rgb1.size()>1)gli->g1=rgb1[1];
//            if(rgb1.size()>2)gli->b1=rgb1[2];
//            if(rgb1.size()>3)gli->a1=rgb1[3];
//            if(rgb2.empty())rgb2=rgb1;
//            if(rgb2.size()>0)gli->r2=rgb2[0];
//            if(rgb2.size()>1)gli->g2=rgb2[1];
//            if(rgb2.size()>2)gli->b2=rgb2[2];
//            if(rgb2.size()>3)gli->a2=rgb2[3];
//        }
//        vg.push_back(gli);
//        return vg[vg.size()-1];
//    }
//};
//extern glLine _glLine;

class ohlcGlWindow : public Fl_Gl_Window {
    public:
//        MyWindow* _parent;
        bool refresh;
        static void Timer_CB(void *userdata);
        vector<ohlcGlWindow*> _panXlink;
        vector<ohlcGlWindow*> _crossYlink;
        int ltn=25;
        string fname;
        bool autosave=false;
        glview3 glv;
        ohlcs ohlc;
        int distfix=35;
        vector<int> mvalues;
        int nrange;
        string objAction="";
        int objActionIndex=-1;
        int objActionStage=0;
        vector<vector<float>> objpoints;
        vector<string> objTipo;
//        vector<glLine*> glLines;

        void addLine2d(float _x1,float _y1,float _x2,float _y2,float cora=1);
//        friend class boost::serialization::access;
//        template<typename Archive>
//        void serialize(Archive& ar, const unsigned version) {
//            ar & objpoints & objTipo;
//        }

        void FixViewport(int W,int H) ;
        void draw() ;
        void cls();
        void resize(int X,int Y,int W,int H);
        ohlcGlWindow(int X,int Y,int W,int H,const char*L=0);
        void updateChart(bool autozoom=true);
        void Regen(ohlcGlWindow* og=NULL);
        int handle(int event ) ;
    };


#endif // OHLCGLWINDOW_HPP_INCLUDED
