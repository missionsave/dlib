#ifndef FLSQLITE_HPP_INCLUDED
#define FLSQLITE_HPP_INCLUDED


#include "fl.hpp"
#include "sqlite3.h"

 
 
struct sqb;
struct mbr: public ColResizeBrowser{ 
	sqb* br;
	mbr(int x, int y, int w, int h );
	int handle(int e);
};
struct Fl_Inputc: Fl_Input{
	sqb* br;
	Fl_Inputc(int X,int Y,int W,int H,const char*L=0): Fl_Input(X,Y,W,H,L){} ;
	int handle(int e);
};
struct sqb: public Fl_Box{
	void* EventKd=0;
	void* EventSelect=0;
	void* EventEnterSelected=0;
	void* EventEnterNotSelected=0;
	void* EventEnterCtrlR=0;
	
	sqlite3* db;
	vector< vector<vector< char*>>> cr;
	ColResizeBrowser* mbt=0;
	mbr* mb=0;
	vint colsw;  
	int indexcol=-1;
	int indexsq;
	int mbi;
	int mbid=-1;
	int idcol=-1;
	const char* indexsel;
	vstring cols; //cols to show
	vstring colsql;
	vint typec;
	vstring fmt;
	vstring fmtr=vstring(10); //row
	vstring sqi=vstring(10);
	vstring sqiprev=vstring(10); //if equal dont load
	Fl_Inputc* inp1;
	bool inpmode=0;
	string inpmode0="";
	const char* mbselvs();//
	void load();
	sqb(int x, int y, int w, int h );
	int handle(int e);
};










#endif