#ifndef ALGEBRA_HPP_INCLUDED
#define ALGEBRA_HPP_INCLUDED

#include "regular.hpp"

/*
		ull* currents=new ull[128];//>ltcn*2+4
		fill(currents,currents+128,0);
		maxAus0a(2,1,mabin,100,4,&currents);
		int sortGiveIndex(nam,currents,2+1,desc);
		if(namI[0]==2)btmacalc->color(FL_GRAY);
		int dif=abs(currents[1]-currents[2]);
		if(namI[0]==2)btmacalc->color(FL_GREEN);
		if(namI[0]==1)btmacalc->color(FL_RED);
		if(currents[1]==currents[2])btmacalc->color(FL_YELLOW);
		delete currents;
	*/
void maxAus0a(int const ltn,int const ltk,vvint  hist,int const cbn,int const cbk,ull** currents,ull cbrange=0);
void maxAus0b(int const ltn,int const ltk,vvint  hist,int const cbn,int const cbk,ull** currents);

struct memfeeling{
	vvvvbool mem;
	vbool prevcbin;
	bool prevdir;
	void saveload(bool saveit);
	void keep(int range,int bsize);
	bool seek(vector<bool> & conj);
	memfeeling();
};


///Do NOT set dir directly, use setDir
///use masc to read only
struct masc{
    vector<int> dir;
    vector<vector<bool>> cbin;
    vector<vector<int>> remainIfSet;
    vector<int> indexes;
    vector<int> indexesinv;
};


class matrixAsc{
    public:
    vector<vector<int>> rmapi ;
    vector<int> vals;
    void* umap;
    int n,k;
    void remainIfSetDir(masc* m);
    virtual void addtomapEvent(masc* m);
//    public:
    matrixAsc();
    void setValues(vector<int> &Vals,int n,int k);
    masc* setdr(vector<int>  distvrange,int cbinfrom=0);
    void setDir(masc* m,int ki, int dir);
    vector<vector<int>> getSets();
    vector<int> remain;
};

#if test
#include "algebra.hpp"
//int main(){
    matrixAsc p;
    vector<int> v={30,32,19,9,0,3,22,8,11,22,16,2,7,26,23,22,26,24,6,13,9,9,4,16,36,18,14,5,28,5};
    p.setValues(v,37,3);
    masc* mx=p.setdr({10,10});
    p.setDir(mx,1,1);
    dbgvecall(p.remain);
    masc* m=p.setdr({0,18});
    p.setDir(m,1,1);
    p.setDir(m,2,0);
    dbgv(m->remainIfSet[1][1]);
    p.setDir(m,1,1);
    dbgvecall(p.remain);
    dbgvecall(m->dir);
}
#endif // test



struct masco{
    vector<int> dir;
    vector<vector<bool>> cbin;
    vector<vector<int>> remainIfSet;
    vector<int> indexes;
    vector<int> indexesinv;
};

#endif // ALGEBRA_HPP_INCLUDED
