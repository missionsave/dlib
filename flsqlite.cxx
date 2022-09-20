
#include "flsqlite.hpp"
string to_string(float Number,char* format);
string toLower(string data);
bool containsAny(string container,vector <string> containAnyOfthis,bool matchcase=false);


mbr::mbr(int x, int y, int w, int h ):ColResizeBrowser(x,y,w, h ) {};

int sqb::handle(int e){
	int ret=Fl_Box::handle(e);
//	dbgv(e); 

	return ret;
}
 
const char* sqb::mbselvs(){
	mbi=mb->value()-1;
	mbid=-1;
	if(mbi<0)return "";
	int mbr=mbi;
	int q=0;
	lop(i,0,cr.size()){
//		dbgv(mbi,q,q+cr[i].size());
		if(q<=mbi && q+cr[i].size()>mbi){
			indexsq=i;
			mbr=mbi-q;
		}
		q+=cr[i].size();
	}

	if(indexcol>=0)mbid=atoi(cr[indexsq][mbi][indexcol]);
//	dbgv(mbid);
	
	if(EventSelect)voidToFunc(EventSelect)();
//	dbgv( mbi,mbr,indexsq );
	return cr[indexsq][mbr][1];

}
int Fl_Inputc::handle(int e){
	int ret=Fl_Input::handle(e);

//	br->mbselvs();

	if(Fl::focus()==br->inp1){
			if(box()!=_FL_PLASTIC_UP_BOX){ 
				box(_FL_PLASTIC_UP_BOX);
				redraw(); Fl::check(); 
			}
	}else{ box(FL_DOWN_BOX); redraw();}

	if(br->inpmode && color()!=FL_YELLOW){
		color(FL_YELLOW);redraw();
	}else if(!br->inpmode && color()!=FL_WHITE){
		color(FL_WHITE); redraw();
	}
	
	if(e==FL_KEYDOWN){ 
 
		int _mbi=br->mb->value();
//		dbgv(value(),br->mb->value(),Fl::event_key());
		if(Fl::event_key()==FL_Up  ){
			if(br->mb->active())br->mb->select(_mbi-1);
			br->mbselvs();
			return 1;
		}
		if(Fl::event_key()==FL_Down){
			if(br->mb->active())br->mb->select(_mbi+1);
			br->mbselvs();
			return 1;
		} 

		if(!br->inpmode){
//			
			br->inpmode0=value();
//			dbgv(br->inpmode); 
		}
		if(Fl::event_key(FL_Control_R)){
			br->inpmode=!br->inpmode;
			if(!br->inpmode){
				br->mb->activate();
				value(br->inpmode0.c_str());
			}
			if(br->inpmode){
				br->mb->deactivate();
				value(br->mbselvs());

			}
			return 1;
		}

		br->mbselvs();
		if(Fl::event_key(FL_Enter) && br->mbi==-1 ){
			if(br->EventEnterNotSelected)
				voidToFunc(br->EventEnterNotSelected)(); 
		}
		if(Fl::event_key(FL_Enter) && br->mbi!=-1 ){
			if(br->EventEnterSelected)
				voidToFunc(br->EventEnterSelected)();
//			dbgv("adiciona ao comp",br->inpmode0);
		}
		if(Fl::event_key(FL_Enter) && Fl::event_key(FL_Control_R)){
			voidToFunc(br->EventEnterCtrlR)();
		}

		if(br->EventKd)voidToFunc(br->EventKd)();

//		dbgv(br->mbi, br->indexsq);

		if(Fl::event_key()==FL_Enter)return 1; 
	}

	return ret;
}

sqb::sqb(int x, int y, int w, int h ):Fl_Box(x,y,w, h ) {
	mbt=new ColResizeBrowser(x,y+20,w,20);
	mbt->has_scrollbar(0);
	mbt->showcolsep(1);
	mb=new mbr(x,y+40,w,h-40);
	mb->type(FL_HOLD_BROWSER);
	mb->showcolsep(1,0);
	mbt->obr=mb;
	mb->obr=mbt;
	inp1=new Fl_Inputc(x,y+ 0,w,20);
	inp1->br=this;
	mb->br=this;  
	mb->hscrollbar.callback([&](Fl_Widget *s, void* v){ 
		((ColResizeBrowser*)(s->parent()))->hposition(int(((Fl_Scrollbar*)s)->value())); 
		((sqb*)v)->mbt->hposition(int(((Fl_Scrollbar*)s)->value()));

//((sqb*)v)->mbt->hscrollbar.slider_size(    ((ColResizeBrowser*)(s->parent()))->hscrollbar.slider_size()   ) ;

//dbgv(((sqb*)v)->mbt->hscrollbar.slider_size() ,((ColResizeBrowser*)(s->parent()))->hscrollbar.slider_size() );
 
 },(void*)this);
	fmtr=vstring(10);//,"@B23");
}; 

void sqb::load(){ 
//	if(sqi==sqiprev)return;
	
	sqiprev=sqi;
	vbool colsi;
	lop(si,0,cr.size())lop(r,0,cr[si].size())lop(c,0,cr[si][r].size())delete cr[si][r][c];
	cr.clear();
	cr.resize(sqi.size());
	colsql=vstring(0); 
	fmt=vstring(0);
	typec=vint(0);
	mb->clear();
	mbt->clear();
	char* sep="\t";
	lop(si,0,sqi.size()){
//	for(int si=sqi.size()-1;si>=0;si--){
		if(sqi[si]=="")continue;  

		if(si==1)mb->add("@B80@b@cComposição");

    sqlite3_stmt* st;
    sqlite3_prepare_v2(db, sqi[si].c_str(),-1, &st, 0);
		const char* sc;
		string sr;
    int cc=sqlite3_column_count(st);
		bool cs=0;//first cols show 
		colsql.resize(cc);
		colsi.resize(cc);
		typec.resize(cc); 
		fmt.resize(cc);
		lop(i,0,cc){  
			colsql[i]=sqlite3_column_name(st,i);
			const char* typedecl=sqlite3_column_decltype(st,i);
			string dtype=typedecl==0?"expression":toLower(typedecl);
			typec[i]=3;
			if(containsAny(dtype,{"bool", "int"},0))typec[i]=1;
			if(containsAny(dtype,{"real","float", "double"},0))
				typec[i]=2;
			fmt[i]=typec[i]==3?"@s@C73@.":"@s@r@C73@."; 
			lop(j,0,cols.size())
				if(cols[j]==colsql[i]){
					colsi[i]=1; 
					break;
				}  
			if(colsi[i]){
				if(!cs)cs=1; else sr.append(sep);
				sr.append(fmt[i]);
				sr.append(colsql[i]);
			}
		}
		sr.append("\t");
		if(mbt->size()==0)
		mbt->add(sr.c_str());  
		vstring fmtl(cc);//=fmt;
		cs=0;
		lop(i,0,cc){//fmtl[i]=fmtr[si]+fmtl[i];
			if(colsi[i])if(!cs)cs=1;else fmtl[i]="\t" +fmtl[i];
		} 
		int r=0;
    while(sqlite3_step(st)== SQLITE_ROW){
			sr="";
			cr[si].push_back(vector< char*>(cc));
			lop(i,0,cc){  
				sc=(const  char*)sqlite3_column_text(st,i); 
				cr[si][r][i]=strdup(sc?sc:""); 
				if(colsi[i]){
					sr.append(fmtl[i]);
					sr.append(sc?sc:"");
				}
			} 
			r++;
					sr.append("\t");////
				mb->add( sr.c_str()); 
		}  
    sqlite3_finalize(st); 
	}   
 	if(colsw.size()==0)colsw=vint(cols.size()-1,120); 
		colsw=vint(colsw.begin(),colsw.begin()+cols.size()+1);
	colsw.back()=1;
	mb->column_widths(&colsw[0]); 
	mbt->column_widths(&colsw[0]);


	//select same mbid
	int lmbid=mbid;mbid=-1;
	if(indexcol>=0 && lmbid>=0 && indexsq>=0){ 
		lop(i,0,cr[indexsq].size()){ 
			if(lmbid==atoi(cr[indexsq][i][indexcol])){
				mb->select(i+1);
				mbid=lmbid;
				break;
			}
		}
	}
	if(mbid==-1 && cr[indexsq].size()>0){
		mb->select(1);dbgv(indexsq); 
	}

}

 
 

int mbr::handle(int e){
	int ret=ColResizeBrowser::handle(e);
//dbgv(e);
if(e==2  ){
			br->mbselvs();
			br->inp1->handle(577);
	return 1;
}

//	if(e==11116){redraw();Fl::check(); return ret;}
//dbgv(e);
	if(e==FL_PUSH && Fl::event_clicks()==1){
//		dbgv(Fl::event_x());
//		brs->load();
		return 1;
	}
	if(Fl::focus()==this){ 
		Fl::focus(br->inp1); br->inp1->handle(577);
		return 1;
	}
	return ret;
}


