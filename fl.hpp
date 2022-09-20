#ifndef FL_HPP_INCLUDED
#define FL_HPP_INCLUDED

//http://www.fltk.org/doc-2.0/html/group__color.html
//http://doc.dvgu.ru/devel/FLTK/Fl_Browser.html
//http://www.fltk.org/doc-1.3/common.html
//http://www.fltk.org/doc-1.1/Fl_Browser.html

#define WINVER 0x0500
#define _WIN32_WINNT 0x0500
#define WIN32_LEAN_AND_MEAN
#define NOCOMM

#include "regular.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Secret_Input.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Hold_Browser.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Help_View.H>
#include <FL/Fl_Table.H>
#include <FL/Fl_Menu.H>
#include "fl_editor.hpp"
//#include <FL/x.H>

#undef hypot

//#include <functional>

#define flc(widgetname,func){ std::function<void()> * ff=new std::function<void()> ( [=]func ); widgetname->callback([](Fl_Widget *,void* v){ (*((std::function<void()>*) v))(); }, (void*)ff); }


#define flcall(thisstructname,widgetname,funcname) widgetname->callback([&](Fl_Widget *o,void* v){((thisstructname*)v)->funcname; },this);



#define sdoubleclick(single_,double_){\
	if(Fl::event_clicks()==1)return;  	\
	Fl::add_timeout(0.03, [](void*){		\
		if(Fl::event_clicks()==0)single_	\
		if(Fl::event_clicks()==1)double_	\
	});	}
#define sdoubleclickh(single_,double_){\
	if(Fl::event_clicks()!=1){  	\
	Fl::add_timeout(0.01, [](void*){		\
																		dbgv(Fl::event_clicks());\
																		Fl::lock();\
		if(Fl::event_clicks()==0)single_	\
		if(Fl::event_clicks()>=1)double_	\
			Fl::unlock();\
			Fl::event_clicks(0);\
	});	}	} return 1;															\


string fileDialog(string title,string filter,string dir="%userprofile%\\documents");

///usado no lotowinner
Fl_Box** FlDoubleLabel(int x,int y,int w,int h,void (*evclick)(int,void* ),void* sev=0 );

uint fl_msgmessage();
void* fl_msglParam();


typedef void (*ANY_FUNC)(...);
//flbtgroup(0,0,400,20,{"a","b","c"},(void*)bclik);bclik(int);
Fl_Button** flbtgroup(int x,int y,int w,int h,vstring labels,char opt,void (*evclick)(int,void* ),void* sev=0 );

void flonexit(Fl_Widget* w,int ask=0 ,void (*sev)() =0 );

void flbtmsg(int x,int y,int w,int h,string text,string messag);
void flmsg(string messag);
void flCenter(void* widget);
void flicon(void* win);
void fldonate(int x,int y,int w,int h,string text="Donate Please");

//struct textbf:Fl_Text_Buffer{
//};
//class Derived : public Fl_Text_Selection {
//	friend class textbf;
//  protected:
//    int includes(int pos) const{  dbgv(0); }
//};







struct MyBrowser : public Fl_Browser {
	vint idx;
	int ddp=0;
	void* ddpc=NULL;
	void* deletecallback=NULL;
	bool docallbackonmw=1;
	MyBrowser(int x, int y, int w, int h );
	void _clear();
	void _add(const char* newtext,int cindex);
	int val(int i=0);
	int handle(int e);
	string selectedstr();
};


//flc(o,{ if(o->event() == FL_PASTE)dbgv(o->event_text()); })
class Fl_DND_Box : public Fl_Box{
	public:
	static void callback_deferred(void *v);
	Fl_DND_Box(int X, int Y, int W, int H, const char *L = 0);
	virtual ~Fl_DND_Box();
	int event();
	const char* event_text();
	int event_length();
	int handle(int e);
	protected:
	// The event which caused Fl_DND_Box to execute its callback
	int evt;
	char *evt_txt;
	int evt_len;
};

//#include <unordered_map>
//#include "stringf.hpp"
//#include "sqlite3.h"
//class sqltable{
//    public:
//    vector<vector<int>> vi;
//    vector<vector<float>> vf;
//    vector<vector<const char*>> vc;
//    vector<vector<string>> vs;
//    vector<int> type;
//    vector<int> svec;
//    vector<int> maxcharcount;
//    vector<string> names;
//    unordered_map<string,int> namesmap;
//    unsigned int size=0;
//    const char* getAsChar(int col,int row);
//    Convertible get(string colname,int row);
//    Convertible get(int col,int row);
//    vector<string> ga;
//    sqltable(){}
//    sqltable(sqlite3* db,const char* zsql );
//    ~sqltable();
//};

//struct Spreadsheet : public Fl_Table {
//    int maxcols;
//    int maxrows;
//    sqltable *datable;
//    Fl_Input *input;
//    int row_edit, col_edit;
//    int s_left, s_top, s_right, s_bottom;
//    void draw_cell(TableContext context, int R,int C, int X,int Y,int W,int H);
//    void event_callback2();
//    static void event_callback(Fl_Widget*, void *v);
//    static void input_cb(Fl_Widget*, void* v);
//
//    Spreadsheet(sqltable* _datable,int X,int Y,int W,int H,const char* L=0);
//    ~Spreadsheet() { }
//    void load(sqltable *_datable);
//    void set_value_hide();
//    void rows(int val) { Fl_Table::rows(val); }
//    void cols(int val) { Fl_Table::cols(val); }
//    int rows() { return Fl_Table::rows(); }
//    int cols() { return Fl_Table::cols(); }
//    void start_editing(int R, int C);
//
//    void done_editing();
//};




class ColResizeBrowser : public Fl_Browser {
	Fl_Color  _colsepcolor;
	int       _showcolsep;
	Fl_Cursor _last_cursor;
	int       _dragging;
	int       _dragcol;
	int      *_widths;
	int       _nowidths[1];
	void change_cursor(Fl_Cursor newcursor);
	int which_col_near_mouse() ;
protected:
	int handle(int e);
	void draw();
public:
	bool showLines=1;
	ColResizeBrowser* obr=0;

	ColResizeBrowser(int X,int Y,int W,int H,const char*L=0);
	Fl_Color colsepcolor() const;
	void colsepcolor(Fl_Color val) ;
	int showcolsep() const;
	void showcolsep(int val,bool showlines=1);
	int *column_widths() const;
	void column_widths(int *val);
};


#endif // FL_HPP_INCLUDED
