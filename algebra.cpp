#include "algebra.hpp"
#include "comb.hpp"
#include "arrayf.hpp"
#include "math.hpp"
#include <boost/unordered_map.hpp>
#include <numeric>
void AppSetWorkingDir();
template <typename T> void serializeSaveLoad(string filename,T &content, bool saveIt=false,bool b=0,bool c=0);

typedef boost::unordered_map<vector<int>,masc> uma;


memfeeling::memfeeling(){
	AppSetWorkingDir();
	mem=vvvvbool(56,vvvbool(56));
	saveload(0);
//	vvbool a={{1}};
//	mem[0][0].push_back(a);
}
void memfeeling::saveload(bool saveit){
	serializeSaveLoad("memfeeling.sav",mem,saveit);
}
void memfeeling::keep(int range,int bsize){
	prevcbin.push_back(prevdir);
	bool fe=1;
	lop(i,0,mem[range][bsize].size())
		if(mem[range][bsize][i]==prevcbin){fe=0;break;}
	if(fe)mem[range][bsize].push_back(prevcbin);
	saveload(1);
}





matrixAsc::matrixAsc(){
    umap=new uma;
}
vector<vector<int>> matrixAsc::getSets(){
    uma &um=*((uma*)umap);
    vector<vector<int>> gs;
    for(auto i : um){
        if(std::accumulate(i.second.dir.rbegin(), i.second.dir.rend(), 0)!=-i.second.dir.size())
            gs.push_back(i.first);
    }
    return gs;
}

void matrixAsc::setValues(vector<int> &Vals,int N,int K){
    uma* um=(uma*)umap;
    n=N;k=K;
    rmapi=combBinAsc(n,k).vmap;
    vals=Vals;
    um->clear();
    remain=vector<int>(n);
    iota(remain.begin(), remain.end(), 0);
}

void matrixAsc::addtomapEvent(masc* m){
    uma* um=(uma*)umap;
}
masc* matrixAsc::setdr(vector<int>  distvrange,int cbinfrom){
    uma* um=(uma*)umap;
//    dbgv(um->size());
    masc *m;
    auto got=um->find(distvrange);
    if(got==um->end()){
        um->emplace(distvrange,masc());
        got=um->find(distvrange);
        m=&got->second;
        m->dir=vector<int>(k,-1);
        m->remainIfSet=vector<vector<int>>(k,vector<int>(2));
        ///fill cbin
        int *syncdist=&distvrange[0];
        int *syncrange=&distvrange[1];
        int ldist=vals.size()- *syncdist;
        if(ldist<0)ldist=0;
        int lrangestart=ldist-*syncrange;
        if(lrangestart<0)lrangestart=0;
//        dbgv(ldist,lrangestart);
        int mvalgcount[n];
        fill(mvalgcount,mvalgcount+n,0);
        lop(i,lrangestart,ldist)mvalgcount[vals[i]]++;
        int sortGiveIndexDirectAsc(mi,mvalgcount,n);
        reverse(mi,mi+n);
        m->indexes=vector<int>(mi,mi+n);
        int minv[n];
        lop(i,0,n)minv[mi[i]]=i;
        m->indexesinv=vector<int>(minv,minv+n);
        m->cbin=vector<vector<bool>>(k,vector<bool>(vals.size()-cbinfrom));
        lop(idx,cbinfrom,vals.size())
            lop(c,0,k)m->cbin[c][idx-cbinfrom]=rmapi[ minv[vals[idx]] ][c];
//        vector<vector<bool>> cbinIndexes(k,vector<bool>(n));
//        dbgv("map",rmapi.size(),rmapi[0].size());
//        dbgvecall(rmapi[10]);

//        lop(ki,0,k)
//            lop(ni,0,n)
//                cbinIndexes[ki][ni]=
//        addtomapEvent(m);

    }else m=&got->second;

    ///fill remainifset
    remainIfSetDir(m);

    return m;
}
void matrixAsc::setDir(masc* m,int ki, int dir){
    m->dir[ki]=dir;

    uma* um=(uma*)umap;
    vector<int> dirspeedup=vector<int>(k,-1);
    vector<bool> cs(n,true);
    for (auto it=um->begin(); it!=um->end(); ++it){
        if(it->second.dir==dirspeedup){continue;}
        lop(idx,0,n){
            if(!cs[    it->second.indexes[idx]     ])continue;
            bool out=false;
            lop(i,0,k){
                if(it->second.dir [i]==-1)continue;
                if(rmapi[idx][i]!=it->second.dir[i]){out=true;break;}
            }
            if(out){
                cs[ it->second.indexes[idx]  ]=false;
            }
        }
    }

    remain.clear();
    lop(idx,0,n)if(cs[idx])remain.push_back( idx );
    sort(remain.begin(),remain.end());
    remainIfSetDir(m);
}
void matrixAsc::remainIfSetDir(masc* m){
    m->remainIfSet=vector<vector<int>>(k,vector<int>(2));
    lop(i,0,remain.size()){
        lop(ki,0,k)
            m->remainIfSet[ki][ rmapi[ m->indexesinv[  remain[  i ] ]  ][ki] ]++;
    }
}





//histrows
void maxAus0a(int const ltn,int const ltk,vvint  hist,int const cbn,int const cbk,ull** currents,ull cbrange){
//usage-> int* currents=new int[ltn+2];

//const int ltcn2=(ltn+2)==52?52:1;

	int histidx=hist.size();


	ull numbermaxaus[64];//>=ltn+2 +ltcn
	lop(i,0,ltn+2)numbermaxaus[i]=(*currents)[i];
	ull *prev=*currents;
	*currents= &numbermaxaus[0];

	unsigned long long &csn=numbermaxaus[ltn+1];
//	unsigned int csn=0;

//	unsigned int* numbersumaus= &numbermaxaus[ltc->n+3];

	comb cb(cbn,cbk);
	if(cbrange==0)cbrange=cb.range;
	// dbgv(cbrange)
//	dbgv(cb.range);
	vector<int>  mfmod_=mathFastModulofill(ltn,16384);
	int mfmod[16384];
	lop(i,0,mfmod_.size())mfmod[i]=mfmod_[i];

	int* soma=(int *)malloc(histidx * sizeof(int));
	fill(soma,soma+histidx,0);
	lop(i,0,histidx)lop(ki,0,ltk)soma[i]+=hist[i][ki] ;


	int ausnumber, ausdist;
	int cbp[16]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};//>=cbk
	int xi[16];//>=ltk
	int ki;
	int cvar, cvarnow;
	long long ab, abfull=mathPow2a[ltn]-1;
	long long abx[64];//>=ltc->n+1
	lop(i,0,ltn+1)abx[i]=(0x1*mathPow2a[ i ]);



auto caus=[&](int &idx,int &ki){
	int &xik=xi[ki];
	xik=mfmod[ hist[idx][ki] +cvar ];
	if(ausdist==0){
		ab|=abx[xik];
		if(ab==abfull){
			ausdist=histidx-idx;
			ausnumber=ltn-mfmod[(cvarnow-xik)];
//			numbersumaus[ausnumber]+=ausdist;
			if(numbermaxaus[ausnumber]<ausdist){
				numbermaxaus[ausnumber]=ausdist;
			}
		}
	}
};

int j;
//pausa
#define somac(cvarx,idx,cbk_) cvarx=100; for(ki=0;ki<cbk_;ki++) cvarx+= soma[idx-cbp[ki] ];

//fill(cbp,cbp+16,0);
//	cb.toComb(csn,cbp);
#define bloop(cbk_,ltck_)\
	if(cbk==cbk_ && ltk==ltck_)\
	for(csn;csn<cbrange;csn++){\
		ab=0;\
		ausdist=0;\
		somac(cvarnow,histidx,cbk_);\
		for(int i=histidx-1;i>histidx-840;i--){\
			if(ausdist!=0)break;\
			somac(cvar,i,cbk_);\
			for(ki=ltck_;ki--;)caus(i,ki);\
		}\
		combNextEvenFastest(cbp,cbn+1,cbk_);\
	}
//dbgpa(cbp,0,cbk_);dbgv(csn);getchar();\1000000000
 //2118760 1000000000

bloop(1,1);
bloop(2,1);
bloop(3,1);
bloop(4,1);
bloop(5,1);
bloop(6,1);
bloop(7,1);
bloop(8,1);
bloop(9,1)
bloop(10,1)
bloop(11,1)
bloop(12,1)
bloop(13,1);
bloop(14,1);
bloop(15,1);
bloop(16,1);
bloop(1,2);
bloop(2,2);
bloop(3,2);
bloop(4,2);
bloop(5,2);
bloop(6,2);
bloop(7,2);
bloop(8,2);
bloop(9,2);
bloop(11,2);
bloop(1,5);
bloop(2,5);
bloop(3,5);
bloop(4,5);
bloop(5,5);
bloop(6,5);
bloop(7,5);
bloop(8,5);
bloop(9,5);
bloop(10,5);
bloop(11,5);
bloop(12,5);
bloop(13,5);
bloop(14,5);
bloop(15,5);
bloop(16,5);

delete soma;

*currents=prev;
lop(i,0,64)(*currents)[i]=numbermaxaus[i];

#undef bloop
#undef somac
}

//histrows
void maxAus0b(int const ltn,int const ltk,vvint  hist,int const cbn,int const cbk,ull** currents){
//usage-> int* currents=new int[ltn+2];

//const int ltcn2=(ltn+2)==52?52:1;

	int histidx=hist.size();


	ull numbermaxaus[64];//>=ltn+2 +ltcn
	lop(i,0,ltn+2)numbermaxaus[i]=(*currents)[i];
	ull *prev=*currents;
	*currents= &numbermaxaus[0];

	unsigned long long &csn=numbermaxaus[ltn+1];
//	unsigned int csn=0;

//	unsigned int* numbersumaus= &numbermaxaus[ltc->n+3];

	comb cb(cbn,cbk);
//	dbgv(cb.range);
	vector<int>  mfmod_=mathFastModulofill(ltn,16384);
	int mfmod[16384];
	lop(i,0,mfmod_.size())mfmod[i]=mfmod_[i];

	int* soma=(int *)malloc(histidx * sizeof(int));
	fill(soma,soma+histidx,0);
	lop(i,0,histidx)lop(ki,0,ltk)soma[i]+=hist[i][ki] ;


	int ausnumber, ausdist;
	int cbp[16]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};//>=cbk
	int xi[16];//>=ltk
	int ki;
	int cvar, cvarnow;
	long long ab, abfull=mathPow2a[ltn]-1;
	long long abx[64];//>=ltc->n+1
	lop(i,0,ltn+1)abx[i]=(0x1*mathPow2a[ i ]);



auto caus=[&](int &idx,int &ki){
	int &xik=xi[ki];
	xik=mfmod[ hist[idx][ki] +cvar ];
	if(ausdist==0){
		ab|=abx[xik];
		if(ab==abfull){
			ausdist=histidx-idx;
			ausnumber=ltn-mfmod[(cvarnow-xik)];
			numbermaxaus[ausnumber]+=ausdist;
//			if(numbermaxaus[ausnumber]<ausdist){
//				numbermaxaus[ausnumber]=ausdist;
//			}
		}
	}
};

int j;

#define somac(cvarx,idx,cbk_) cvarx=100; for(ki=0;ki<cbk_;ki++) cvarx+= soma[idx-cbp[ki] ];

//fill(cbp,cbp+16,0);
//	cb.toComb(csn,cbp);
#define bloop(cbk_,ltck_)\
	if(cbk==cbk_ && ltk==ltck_)\
	for(csn;csn<cb.range;csn++){\
		ab=0;\
		ausdist=0;\
		somac(cvarnow,histidx,cbk_);\
		for(int i=histidx-1;i>histidx-840;i--){\
			if(ausdist!=0)break;\
			somac(cvar,i,cbk_);\
			for(ki=ltck_;ki--;)caus(i,ki);\
		}\
		combNextEvenFastest(cbp,cbn+1,cbk_);\
	}
//dbgpa(cbp,0,cbk_);dbgv(csn);getchar();\1000000000
 //2118760 1000000000

bloop(1,1);
bloop(2,1);
bloop(3,1);
bloop(4,1);
bloop(5,1);
bloop(6,1);
bloop(7,1);
bloop(8,1);
bloop(9,1)
bloop(10,1)
bloop(11,1)
bloop(12,1)
bloop(13,1);
bloop(14,1);
bloop(15,1);
bloop(16,1);
bloop(1,2);
bloop(2,2);
bloop(3,2);
bloop(4,2);
bloop(5,2);
bloop(6,2);
bloop(7,2);
bloop(8,2);
bloop(9,2);
bloop(11,2);
bloop(1,5);
bloop(2,5);
bloop(3,5);
bloop(4,5);
bloop(5,5);
bloop(6,5);
bloop(7,5);
bloop(8,5);
bloop(9,5);
bloop(10,5);
bloop(11,5);
bloop(12,5);
bloop(13,5);
bloop(14,5);
bloop(15,5);
bloop(16,5);

delete soma;

*currents=prev;
lop(i,0,64)(*currents)[i]=numbermaxaus[i];

#undef bloop
#undef somac
}
