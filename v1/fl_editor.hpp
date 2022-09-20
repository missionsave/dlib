#ifndef FL_EDITOR_HPP_INCLUDED
#define FL_EDITOR_HPP_INCLUDED
//o
#include "regular.hpp"
#include <FL/Fl.H>
#include <FL/Fl_Menu.H>
#include <FL/Fl_Text_Editor.H>

struct content{
	Fl_Text_Buffer  *textbuf = 0;
	Fl_Text_Buffer  *stylebuf = 0;
	int mTopLineNum;
	bool modified=0;
	int loading=0;
};

struct Fl_Editor:Fl_Text_Editor{
	Fl_Editor (int x, int y, int w, int h );
	Fl_Menu_Item mi;
	string search;
	string filenamecurrent="";
	string nameonly="";
	//bool stmodified=0;/mnt/sda1/Desk/devtools/.GccLinux64/
	//bool modified=0;
	content* cnt=0;
	//Style_Table_Entry* styletable;
	void (*onSave)(string) =0;
	void (*onUpdate)() =0;
	void (*onFocus)() =0;
	Fl_Text_Buffer  *textbuf = 0;
	Fl_Text_Buffer  *stylebuf = 0;
	void style_init(void);
	string text();
	void text(string val);
	void setStyle();
	void commentUncommment(int flag);
	void foldAll(int flag);
	void highLightAll(string word);
	void highLightbrace();
	void save(string filename="");
	void load(string filename);
	void addText(string txt);
	void find_cb( );
	void find2_cb( );
	vint highsp;
	void highlightsel();
	int handle(int e);
	void draw_string(int style,int X, int Y, int toX, const char *string, int nChars) const;
/*

	void draw_stringp(int style,int X, int Y, int toX,const char *string, int nChars) const;
		void drawp();
	void resizep(int x, int y, int w, int h );
	void draw_line_numbersp(bool);
*/
};


#endif
