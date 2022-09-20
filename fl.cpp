#include "regular.hpp"
#include <FL/Fl_Button.H>
#include <FL/Fl.H>
#include <FL/x.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Browser.H>
#include <FL/fl_draw.H>
#include <FL/names.h>
#include "fl.hpp"
#include  <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Menu.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <boost/predef.h>
#include "stringf.hpp"

#define eventcheck fprintf(stderr, "EVENT: %s(%d)\n", fl_eventnames[e], e);

void OpenWebsite (char * cpURL);

//#include "win.hpp"

//#include "sqlite.hpp"
//string to_string(float Number,char* format);






string fileDialog(string title,string filter,string dir){
//    setlocale(LC_ALL, "");
//setlocale(0, ".1251");
    Fl_Native_File_Chooser fnfc;
    fnfc.title(title.c_str());
    fnfc.options(Fl_Native_File_Chooser::PREVIEW);
//    fnfc.type(Fl_Native_File_Chooser::BROWSE_FILE);
    fnfc.filter(filter.c_str());
    fnfc.directory(dir.c_str());
    int fres=fnfc.show();
    if(fres==-1 || fres==1)return "";
    return fnfc.filename();
}

void flonexit(Fl_Widget* w,int ask ,void (*sev)()  ){
struct s{int ask;void* sev;};
s* _s=new s({ask,(void*)sev});
w->callback([](Fl_Widget *, void* v){
	s* _s=(s*)v;
	if ((Fl::event()==FL_SHORTCUT &&
		Fl::event_key()==FL_Escape)||
		(Fl::event()==10)){
			if((_s->ask==1 && fl_ask("Are you sure you want to exit?")) || _s->ask==0){
				if(_s->sev)voidToFunc(_s->sev)();
				exit(0);
			}
		}
	},_s);
}

Fl_Box** FlDoubleLabel(int x,int y,int w,int h,void (*evclick)(int,void* ),void* sev  ){
	Fl_Box** lbl=new Fl_Box*[2];
	lbl[0]=new Fl_Box(x,y,w-20,h/2.0);
	lbl[0]->box(Fl_Boxtype::FL_THIN_DOWN_BOX);
	lbl[0]->align(16|1|4);
	lbl[1]=new Fl_Box(x,y+h/2.0,w-20,h/2.0);
	lbl[1]->box(Fl_Boxtype::FL_THIN_DOWN_BOX);
	lbl[1]->align(16|1|4);

	Fl_Button** btn=new Fl_Button*[2];
	btn[0]=new Fl_Button(x+w-20,y,20,h/2.0);
	btn[1]=new Fl_Button(x+w-20,y+h/2.0,20,h/2.0);

	struct bte{void* sev;void* e;int id;};

	bte* btv0=new bte({sev,(void*)evclick,1});
	btn[0]->callback([ ](Fl_Widget* fe,void *v){
			bte* btev=(bte*)v;
			voidToFunc(btev->e,int,void*)(btev->id,btev->sev);
	},btv0);
	bte* btv1=new bte({sev,(void*)evclick,-1});
	btn[1]->callback([ ](Fl_Widget* fe,void *v){
			bte* btev=(bte*)v;
			voidToFunc(btev->e,int,void*)(btev->id,btev->sev);
	},btv1);
	return lbl;
}

//to pass int ,(void*)(new int(i)));then int i=*((int*)voidv);
//opt= |128 =vertical
//opt= |64 =multi
//opt= |32 =normal with switch off
Fl_Button** flbtgroup(int x,int y,int w,int h,vstring labels,char opt,void (*evclick)(int,void* ),void* sev ){
	int qtb=labels.size();
	Fl_Button** btn=new Fl_Button*[qtb];
	Fl_Group* g=new Fl_Group(x,y,w,h);
	struct bte{void* sev;char opt;Fl_Button** bc;void* e;int id;};
	int bw=w/(float)qtb;
	int bh=h/(float)qtb;
  lop(ib,0,qtb){
    if(opt&128)
			btn[ib]=new Fl_Button(x,y+bh*ib,w,bh);
			else
			btn[ib]=new Fl_Button(x+bw*ib,y,bw,h);
		btn[ib]->copy_label(labels[ib].c_str());
		if(!(opt&32 || opt&64))btn[ib]->type(FL_RADIO_BUTTON);
		btn[ib]->selection_color(FL_DARK_RED);
		bte* btv=new bte({sev,opt,btn ,(void*)evclick,ib});
		btn[ib]->callback([ ](Fl_Widget*,void *v){
			bte* btev=(bte*)v;
			Fl_Button** btn=btev->bc;
			char opt=btev->opt;
			char qtb=opt&~(128|64|32) ;
			bool cv=btn[btev->id]->value();
			if(opt&32)lop(i,0,qtb)btn[i]->value(0);
			if(opt&32 || opt&64)btn[btev->id]->value(!cv);
			voidToFunc(btev->e,int,void*)(btev->id,btev->sev);
		},btv);
	}
	g->end();
	return btn;
//	btn[0]->setonly();
//	btn[0]->do_callback();
}
// win->position(Fl::w()/2-win->w()/2,Fl::h()/2-win->h()/2);
void flCenter(void* widget){
    ((Fl_Widget*)widget)->position(Fl::w()/2-((Fl_Widget*)widget)->w()/2,Fl::h()/2-((Fl_Widget*)widget)->h()/2);
}


#if BOOST_OS_WINDOWS
void flicon(void* win){
	Fl::scheme("gtk+");
	((Fl_Window*)win)->icon((char *)LoadIcon(fl_display, MAKEINTRESOURCE(101)));
  ((Fl_Window*)win)->color(0xbbddbb00);
}
#endif

#if BOOST_OS_LINUX
void flicon(void* win){
	//~ Fl::scheme("gtk+");
  ((Fl_Window*)win)->color(0xbbddbb00);
}
#endif

void fldonate(int x,int y,int w,int h,string text){
	Fl_Button *btd=new Fl_Button(x, y, w, h);
	btd->copy_label(text.c_str());
	btd->callback([](Fl_Widget*){ OpenWebsite("https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=FJN8LQ32CDBX2"); });
}


void flbtmsg(int x,int y,int w,int h,string text,string messag){
Fl_Button *btd=new Fl_Button(x, y, w, h);
	btd->copy_label(text.c_str());
	string *msg=new string(messag);
	btd->callback([](Fl_Widget*,void *v ){
		flmsg(  *((string*)v) );
	},msg );
}

void flmsg(string messag){
	Fl_Window* msg=new Fl_Window(0,0,450,200);
	Fl_Multiline_Output* fb=new Fl_Multiline_Output(0,0,450,180);
	fb->type(FL_MULTILINE_OUTPUT_WRAP);
	fb->box(Fl_Boxtype::FL_THIN_UP_BOX);
	fb->color(0xF0F0F0F0);
	fb->value(messag.c_str());

	Fl_Button* btc=new Fl_Button(390,180,60,20 );
	btc->copy_label("Close");
	btc->callback([](Fl_Widget *, void* v){
		((Fl_Window*)v)->hide();
		delete ((Fl_Window*)v);
	},msg);
	flCenter(msg);
	msg->set_modal();
	msg->show();
//	SetWindowLong(flxid(msg),GWL_STYLE,(GetWindowLong(flxid(msg),GWL_STYLE)&~WS_MAXIMIZEBOX));
//	SetWindowLong(flxid(msg),GWL_STYLE,(GetWindowLong(flxid(msg),GWL_STYLE)&~WS_MINIMIZEBOX));
}

MyBrowser::MyBrowser(int x, int y, int w, int h ): Fl_Browser(x,y,w, h ) {
		has_scrollbar(6);
		type(FL_HOLD_BROWSER);
//        when(FL_WHEN_CHANGED);
		//type(FL_MULTI_BROWSER);
}

void MyBrowser::_clear(){
	idx=vint(0);
	idx.reserve(0);
	clear();
}
string MyBrowser::selectedstr(){
	return text(value());
}
void MyBrowser::_add(const char* newtext,int cindex){
	if(idx.size()==0)idx.reserve(10000);
	idx.push_back(cindex);
	add(newtext,(void*)&idx.back());
	int didx=*((int*)data(size()));
}
int MyBrowser::val(int i){
	if(i==0)i=value();if(i==0)return 0;
	int didx=*((int*)data(i));
	return didx;
}
int MyBrowser::handle(int e) {
			int ret = Fl_Browser::handle(e);
//		dbgv(e,Fl::event_state());
//			if(e==FL_PUSH){
//				dbgv(1,value());
//
//			}
	///deletecallback
			if(e==FL_KEYDOWN){//
					if(Fl::event_original_key()==65535)
						if(deletecallback)
							voidToFunc(deletecallback)();
//				eventcheck

			}
			if(e==FL_RELEASE){
				ddp=0;

			}
			if(e==5 && Fl::event_button1() && ddp!=value()){
				if(ddp==0){ddp=value(); return 1;}
				if(ddpc)voidToFunc(ddpc,int,int)(ddp,value());
				string pdt=text(ddp);
				string pdt1=text(value());
				text(ddp,pdt1.c_str());
				text(value(),(pdt.c_str()));
				ddp=value();
			}
			switch (e) {
					case FL_MOUSEWHEEL:
							if(this==Fl::belowmouse()){
									select( (value()) + Fl::event_dy());
									if(docallbackonmw)do_callback();
							}
							break;
			}
			return (ret);
	}


void Fl_DND_Box::callback_deferred(void *v)        {
	Fl_DND_Box *w = (Fl_DND_Box*)v;
	w->do_callback();
}
Fl_DND_Box::Fl_DND_Box(int X, int Y, int W, int H, const char *L): Fl_Box(X,Y,W,H,L), evt(FL_NO_EVENT), evt_txt(0), evt_len(0) {
	labeltype(FL_NO_LABEL);
	box(FL_NO_BOX);
	clear_visible_focus();
}
Fl_DND_Box::~Fl_DND_Box()        {
		delete [] evt_txt;
}
int Fl_DND_Box::event() {
		return evt;
}
const char* Fl_DND_Box::event_text(){
		return evt_txt;
}
int Fl_DND_Box::event_length(){
		return evt_len;
}
int Fl_DND_Box::handle(int e){
//dbgv(Fl::event_x_root());
	switch(e)	{
		case FL_DND_ENTER:
		case FL_DND_RELEASE:
		case FL_DND_LEAVE:
		case FL_DND_DRAG:
				evt = e;
				return 1;
		case FL_PASTE:
				evt = e;

				// make a copy of the DND payload
				evt_len = Fl::event_length();
				delete [] evt_txt;
//dbgv(evt_len,Fl::event_text());
				evt_txt = new char[evt_len*2];
//                    sprintf(evt_txt,"%s",Fl::event_text());
				strcpy(evt_txt, Fl::event_text());
//                    getchar();

				// If there is a callback registered, call it.
				// The callback must access Fl::event_text() to
				// get the string or file path that was dropped.
				// Note that do_callback() is not called directly.
				// Instead it will be executed by the FLTK main-loop
				// once we have finished handling the DND event.
				// This allows caller to popup a window or change widget focus.
				if(callback() && ((when() & FL_WHEN_RELEASE) || (when() & FL_WHEN_CHANGED)))
						Fl::add_timeout(0.0, Fl_DND_Box::callback_deferred, (void*)this);
				return 1;
	}
	return Fl_Box::handle(e);
}


ColResizeBrowser::ColResizeBrowser(int X,int Y,int W,int H,const char*L) : Fl_Browser(X,Y,W,H,L) {
	_colsepcolor = Fl_Color(FL_GRAY);
	_last_cursor = FL_CURSOR_DEFAULT;
	_showcolsep  = 0;
	_dragging    = 0;
	_nowidths[0] = 0;
	_widths      = _nowidths;
}

int ColResizeBrowser::handle(int e) {
	// Not showing column separators? Use default Fl_Browser::handle() logic
	if ( ! showcolsep() ) return(Fl_Browser::handle(e));
	// Handle column resizing
	int ret = 0;
	switch ( e ) {
			case FL_ENTER: {
					ret = 1;
					break;
			}
			case FL_MOVE: {
					if ( which_col_near_mouse() >= 0 ) {
							change_cursor(FL_CURSOR_WE);
					} else {
							change_cursor(FL_CURSOR_DEFAULT);
					}
					ret = 1;
					break;
			}
			case FL_PUSH: {
					int whichcol = which_col_near_mouse();
					if ( whichcol >= 0 ) {
							// CLICKED ON RESIZER? START DRAGGING
							ret = 1;
							_dragging = 1;
							_dragcol = whichcol;
							change_cursor(FL_CURSOR_DEFAULT);
					}
					break;
			}
			case FL_DRAG: {
					if ( _dragging ) {
							ret = 1;
							// Sum up column widths to determine position
							int mousex = Fl::event_x() + hposition();
							int newwidth = mousex - x();
							for ( int t=0; _widths[t] && t<_dragcol; t++ ) {
									newwidth -= _widths[t];
							}
							if ( newwidth > 0 ) {
									// Apply new width, redraw interface
									_widths[_dragcol] = newwidth;
									if ( _widths[_dragcol] < 2 ) {
											_widths[_dragcol] = 2;
									}
									redraw();
									if(obr){
//										obr->_widths=(_widths);
										obr->column_widths(_widths);
										obr->redraw();
										Fl::check();
									}
							}
					}
					break;
			}
			case FL_LEAVE:
			case FL_RELEASE: {
					_dragging = 0;                          // disable drag mode
					change_cursor(FL_CURSOR_DEFAULT);       // ensure normal cursor
					ret = 1;
					break;
			}
	}
	if ( _dragging ) return(1);                     // dragging? don't pass event to Fl_Browser
	return(Fl_Browser::handle(e) ? 1 : ret);
}
void ColResizeBrowser::draw() {
	// DRAW BROWSER
	Fl_Browser::draw();
//	if(obr && obr->hposition()!=hposition() )obr->handle(11116);
	if ( _showcolsep ) {
			// DRAW COLUMN SEPARATORS
			int colx = this->x() - hposition();
			int X,Y,W,H;
			Fl_Browser::bbox(X,Y,W,H);
			fl_color(_colsepcolor);
			for ( int t=0; _widths[t]; t++ ) {
					colx += _widths[t];
					if ( colx > X && colx < (X+W) ) {
							if(showLines)fl_line(colx, Y, colx, Y+H-1);
					}
			}
	}
}

void ColResizeBrowser::change_cursor(Fl_Cursor newcursor) {
	if ( newcursor != _last_cursor ) {
			fl_cursor(newcursor, FL_BLACK, FL_WHITE);
			_last_cursor = newcursor;
	}
}
// RETURN THE COLUMN MOUSE IS 'NEAR'
//     Returns -1 if none.
//
int ColResizeBrowser::which_col_near_mouse() {
	int X,Y,W,H;
	Fl_Browser::bbox(X,Y,W,H);            // area inside browser's box()
	// EVENT NOT INSIDE BROWSER AREA? (eg. on a scrollbar)
	if ( ! Fl::event_inside(X,Y,W,H) ) {
			return(-1);
	}
	int mousex = Fl::event_x() + hposition();
	int colx = this->x();
	for ( int t=0; _widths[t]; t++ ) {
			colx += _widths[t];
			int diff = mousex - colx;
			// MOUSE 'NEAR' A COLUMN?
			//     Return column #
			//
			if ( diff >= -4 && diff <= 4 ) {
					return(t);
			}
	}
	return(-1);
}
Fl_Color ColResizeBrowser::colsepcolor() const {
		return(_colsepcolor);
}
void ColResizeBrowser::colsepcolor(Fl_Color val) {
		_colsepcolor = val;
}

int ColResizeBrowser::showcolsep() const {
		return(_showcolsep);
}
void ColResizeBrowser::showcolsep(int val,bool showlines) {
		_showcolsep = val;dbgv(val);
		showLines=showlines;
}
// GET/SET COLUMN WIDTHS ARRAY
//    Just like fltk method, but array is non-const.
//
int *ColResizeBrowser::column_widths() const {
		return(_widths);
}
void ColResizeBrowser::column_widths(int *val) {
		_widths = val;
		Fl_Browser::column_widths(val);
}

