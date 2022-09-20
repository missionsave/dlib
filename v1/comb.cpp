#include "regular.hpp"
#include "comb.hpp"

#include <math.hpp>
#include <arrayf.hpp>

#include <bitset>

int factorial(int n){
	int i;
	for(i = n-1; i > 1; i--)
		n *= i;
	return n;
}

void combtRm::init(vector<int> Nk,vector<int> RangesR){
    combtR::init(Nk,RangesR);
    ma=vector<matrixAsc>(rangesR.size());
}
void combtRm::convertToR(vector<vector<int>> cols,int rows){
    combtR::convertToR(cols);
    lop(i,0,rangesR.size())ma[i].setValues(R[i],rangesR[i],rows);
}
vector<vector<int>> combtRm::convertFromR(int *qtchaves,int returnEmptyIfMoreThan){
    vector<int> lrang(ma.size());
    int qchaves=1;lop(i,0,ma.size()){qchaves*=ma[i].remain.size();lrang[i]=ma[i].remain.size();}
    if(qtchaves!=NULL)*qtchaves=qchaves;
    if(returnEmptyIfMoreThan<qchaves)return {};
    combR lcr(lrang);
    combR cr(rangesR);
    comb cb(nk[0],nk[1]);
    vector<vector<int>> ch(qchaves);
    lop(i,0,lcr.range){
        vector<int> lcrc=lcr.toComb(i);
        lop(i2,0,lcrc.size())lcrc[i2]=ma[i2].remain[ lcrc[i2] ];
        int csnr=cr.toCsn(&lcrc[0]);
        ch[i]=cb.toComb(csnr);
    }
    return ch;
}
void combtR::init(vector<int> Nk,vector<int> RangesR){
    nk=Nk;
    rangesR=RangesR;
}
void combtR::convertToR(vector<vector<int>> cols){
    comb inp(nk[0],nk[1]);
    combR outp(rangesR);
    R=vector<vector<int>> (rangesR.size());
    lop(fi,0,rangesR.size())R[fi]=vector<int>(cols[0].size());
    lop(ci,0,cols[0].size()){

        //int chave[cols.size()];
		int* chave = new int[cols.size()];

        lop(ch,0,cols.size())chave[ch]=cols[ch][ci];
        int csn=inp.toCsn(chave);

        //int chaveR[rangesR.size()];
		int* chaveR = new int[rangesR.size()];

		outp.toComb(chaveR,csn);
        lop(ri,0,rangesR.size())R[ri][ci]=chaveR[ri];
    }
}
combR::combR(int n,int K,bool tocache){
    k=K;
    ranges=vector<int>(k);
    for(int i=0;i<k;i++)ranges[i]=n;
    range = combNumCombinIrregular();
    restoR=ranges;
    for(int i=k-2;i>=0;i--)restoR[i]=ranges[i]*restoR[i+1];
    if(tocache){
        cache.resize(k);
        for(int c=0;c<k;c++)cache[c]=new unsigned int [range];
        for(unsigned int  i=0;i<range;i++){
            vector<int> cf=toComb(i);
            for(int c=0;c<k;c++)cache[c][i]=cf[c];
        }
        cached=true;
    }
}
combR::combR(vector <int> Ranges,bool tocache){
    ranges=Ranges;
    k=ranges.size();
    range = combNumCombinIrregular();
    restoR=ranges;
    for(int i=k-2;i>=0;i--)restoR[i]=ranges[i]*restoR[i+1];
    if(tocache){
        cache.resize(k);
        for(int c=0;c<k;c++)cache[c]=new unsigned int [range];
        for(unsigned int  i=0;i<range;i++){
            vector<int> cf=toComb(i);
            for(int c=0;c<k;c++)cache[c][i]=cf[c];
        }
        cached=true;
    }
}
vector<int> combR::toComb(unsigned int csn){
    vector<int>res(k);
    res[k-1]=csn%restoR[k-1];
    for(int i=0;i<k-1;i++)res[i]=csn/restoR[i+1]%ranges[i];
    return res;
}
void combR::toComb(unsigned int csn,vector<int>&res){
    res[k-1]=csn%restoR[k-1];
    for(int i=0;i<k-1;i++)res[i]=csn/restoR[i+1];
    for(int i=1;i<k-1;i++)res[i]%=ranges[i];
}
void combR::toComb(int* res,unsigned int csn){
    res[k-1]=csn%restoR[k-1];
    for(int i=0;i<k-1;i++)res[i]=csn/restoR[i+1];
    for(int i=1;i<k-1;i++)res[i]%=ranges[i];
}
unsigned long long combR::combNumCombinIrregular(){
    unsigned long long res=1;
    for(int i=0;i<ranges.size();i++)res*=ranges[i];
    return res;
}
unsigned long long  combR::toCsn(int *comb){
    unsigned long long pos = 0;
    unsigned long long rangeval = range;
    for (int l = 0; l < k; l++) {
        int figura = comb[l];
        unsigned long long sector = rangeval / ranges[l];
        rangeval = sector;
        pos += sector * figura;
    }
    return pos;
}


vector<vector<int>> combConvertToR(vector<vector<int>> &cols,vector<int> &nk,vector<int> rangesR){
    comb inp(nk[0],nk[1]);
    combR outp(rangesR);
    vector<vector<int>> res(rangesR.size());
    lop(fi,0,rangesR.size())res[fi]=vector<int>(cols[0].size());
    lop(ci,0,cols[0].size()){
        vint chave(cols.size());
        lop(ch,0,cols.size())chave[ch]=cols[ch][ci];
        int csn=inp.toCsn(chave);
		//int chaveR[rangesR.size()];
		int* chaveR=new int[rangesR.size()];
        outp.toComb(chaveR,csn);
        lop(ri,0,rangesR.size())res[ri][ci]=chaveR[ri];
    }
    return res;
};
vector<vector<int>> combConvertToBinPairBalanced(vector<vector<int>> &cols,vector<int> nk,int startfrom){
    comb inp(nk[0],nk[1] ,false,startfrom);
    combBinPairBalanced outp(inp.range);
    vector<vector<int>> res(outp.k);
    lop(fi,0,outp.k)res[fi]=vector<int>(cols[0].size());
    lop(ci,0,cols[0].size()){
        int chave[cols.size()];
        lop(ch,0,cols.size())chave[ch]=cols[ch][ci];
        int csn=inp.toCsn(chave);
        int chaveR[outp.k];
        outp.toComb(chaveR,csn);
        lop(ri,0,outp.k)res[ri][ci]=chaveR[ri];
    }
    return res;
};

combBinAsc::combBinAsc(int _n,int _k){
    n=_n;k=_k;
    B=pow(2,k);
    C=n/(float)B;
    D=C-floor(C);
    E=0.5/ ( B/2.0 );
    F=0.5-D;
    G=F/E;
    H=B/2.0+G;
    I=B-H;
    J=n-I;
    K=I/2;
    vmap=vector<vector<int>>(n,vector<int>(k));

//        combBinPairBalanced cbp(n);
//        lop(o,0,n){
//            int r[6];
//            cbp.toComb(r,o);
//            lop(v,0,k)vmap[o][v]=r[v];
//        }
    lop(o,0,J){
        bitset< 32 > bset(o );
        lop(v,0,k)vmap[o][v]=bset[v];
//            dbgpx(vmap[o],0,k);
    }
    lop(o,J,J+K){
        int i=o-J+1;
        bitset< 32 > bset(i );
        lop(v,0,k)vmap[o][v]=bset[v];
//            dbgpx(vmap[o],0,k);
    }
    lop(o,J+K,J+K+K){
        lop(v,0,k)vmap[o][v]=vmap[o-K][v]==1?0:1;
    }

    ///put ones first
    vector<vector<int>> _vmap;
    while(vmap.size()>0){
        float bstdev=100;int bsum=0;int bidx=-1;
        vector<int> csum(k);
        lop(v,0,_vmap.size())lop(ki,0,k)csum[ki]+=_vmap[v][ki];

//            dbgpx(csum,0,k);
        lop(v,0,vmap.size()){
            vector<int> fsum=csum;
            lop(ki,0,k)fsum[ki]+=vmap[v][ki];
            int rsum=mathSum(fsum,0,k);
            float rstdev=mathStdev(fsum,0,k);
            if( rsum>bsum || (rsum==bsum && bstdev>rstdev)){
                bstdev=rstdev;bsum=rsum; bidx=v;
            }
        }
        _vmap.push_back(vmap[bidx]);
        vmap.erase(vmap.begin()+bidx);
    }
    vmap=_vmap;
//
//    ///gtrend calc
//    vector<float> gtrend=vector<float>(k);
//    lop(i,0,n){
////            dbgpx(vmap[i],0,k);
//        lop(c,0,gtrend.size()){
//            if(vmap[i][c]==1)gtrend[c]+=1;else gtrend[c]-=1;
//        }
//    }
////        dbgpx(gtrend,0,k);

}
vector<vector<bool>> combBinAsc::hmapg(){
    vector<vector<bool>> hmap=vector<vector<bool>>(k,vector<bool>(n));
    lop(i,0,vmap.size()){
        lop(x,0,vmap[i].size())hmap[x][i]=vmap[i][x];
    }
    return hmap;
}

combBinPairBalanced::combBinPairBalanced(unsigned long long Range){
    range=Range;
    k=floorf(log2(range)+0.999999);
    crx=new combR(2,k);
    rangematrix=crx->range;
}
void combBinPairBalanced::toComb(int* res,unsigned int csn){
    if(csn%2!=0)csn=rangematrix-csn ;
//    dbgp("\nc%d",csn);
    crx->toComb(res,csn);
}
unsigned int combBinPairBalanced::toCsn(int *comb){
    unsigned int csn=crx->toCsn(comb);
    if(csn%2!=0)csn=rangematrix-csn ;
    return csn;
}
vector<unsigned int> combBinPairBalanced::toCsnsNot(int *comb){
    vector<unsigned int> res;
//    unsigned int csn=crx->toCsn(comb);
//    if(csn%2!=0)csn=rangematrix-csn ;
    return res;
}
vector<vector<bool>> combBinPairBalanced::hmapg(){
    vector<vector<bool>> hmap=vector<vector<bool>>(k,vector<bool>(range));
    lop(i,0,range){
        int a[k];
        toComb(a,i);
        lop(x,0,k)hmap[x][i]=a[x];
    }
    return hmap;
}
comb::~comb(){}//for(auto i:cache)delete[] i;}

#include <sstream>
comb::comb(int N,int K,bool tocache,int Startfrom){
        n=N;k=K;
        startfrom=Startfrom;
        range = numCombin(n,k);
        ncomb=vector<int*>(n);
        lop(nx,0,n)ncomb[nx]=new int[k];
        lop(nx,0,n)lop(kx,0,k){ncomb[nx][kx]=numCombin(nx,kx);}


//        stringstream strm;
//        lop(nx,0,n){
//            strm<<nx<<" ";
//            lop(kx,0,k){
//                strm<<" "<<kx<<" "<<ncomb[nx][kx];
//            }
//            strm<<",";
//        }
//        dbgv(strm.str());
//        pausa;


        if(tocache){
            cache=vector<vector<int>>(k,vector<int>(range));
//            cache.resize(k);
//            for(int c=0;c<k;c++)cache[c]=new unsigned int [range];
            int cf[k];
            for( int  i=0;i<range;i++){
                toComb(i,cf);
                for(int c=0;c<k;c++)cache[c][i]=cf[c];
            }
            cached=true;
        }
    }
void comb::fillCacheHc(){
//	cachehc2=vector<vector< char>>(range,vector< char>(k));
//	cachehc1=vector<unsigned char* >(range );
//	int cf[k];
//	for( int  i=range-1;i--;){
//		toCombFaster(i,cf);
//		cachehc1[i]=(unsigned char*) malloc (k);
//		for(int c=k-1;c--;)cachehc1[i][c]= cf[c];
//	}
//
	cachehcontinuos=( unsigned char*) malloc (k*range);
	int id=0;
	int cf[k];
	for( int  i=0;i<range;i++){
		toCombFaster(i,cf);
		for(int c=0;c<k;c++)cachehcontinuos[id++]=( unsigned char) cf[c];
	}
}
void comb::fillCacheH(){
        cacheh=vector<int*>(range);
        for( int  i=0;i<range;i++){
            cacheh[i]=new  int[k];
            for(int c=0;c<k;c++)cacheh[i][c]=cache[c][i];
        }
    }
unsigned long long comb::numCombin(int n, int k){
        int dif = n - k;
        if (k < dif){
            dif = k;
            k = n - dif;
        }
        unsigned long long combs = k + 1;
        if (dif == 0) combs = 1;
        else if (dif >= 2)
            for (int i = 2; i <= dif; i++) {
                combs = (combs * (k + i)) / i;
                if (combs < 0)return 0;
            }
        return combs;
    }

string comb::toCombStr(int csn){
    int tf[k];
    toComb(csn,tf);
		string res="";
		lop(i,0,k){
			res=res+to_string(tf[i]);
			if(i<k-1)res=res+" ";
		}
	return res;
}
vector<int> comb::toComb(int csn){
    int tf[k];
    toComb(csn,tf);
    vector<int> toFill=vector<int>(tf,tf+k);
    return toFill;
}
void comb::toComb(int csn, vector<int> &toFill){
    int tf[k];
    toComb(csn,tf);
    toFill=vector<int>(tf,tf+k);
}
void comb::toComb(int csn, int *toFill){
	  if(cached){for(int i=0;i<k;i++)toFill[i]=cache[i][csn];return;}
	  if(k==1){toFill[0]=csn+startfrom;return;}
	  csn += 1;
	  int lbound = 0;
	  int r = 0;
	  for (int i = 0; i < (k - 1); i++) {
			toFill[i] = 0;
			if (i != 0) toFill[i] = toFill[i - 1];
			do{
				 toFill[i]++;
//                r = numCombin(n - toFill[i], (k - 1) - i);
				 r = ncomb[n - toFill[i]][ (k - 1) - i]; //now is cache :)
				 lbound += r;
			} while (lbound < csn);
			lbound -= r;
	  }
	  toFill[k - 1] = toFill[k - 2] + csn - lbound;
	  if(startfrom!=1)for(int i=0;i<k;i++)toFill[i]+=startfrom-1;
 }

//void comb::toCombFaster(int csn, int *toFill){
//	int k_1=(k - 1);
//	  csn += 1;
//	  int lbound = 0;
//	  int r = 0;
//	  for (int i = 0; i < k_1; i++) {
//			toFill[i] = 0;
//			if (i != 0) toFill[i] = toFill[i - 1];
//			do{
//				 toFill[i]++;
//				 r = ncomb[n - toFill[i]][ k_1 - i];
//				 lbound += r;
//			} while (lbound < csn);
//			lbound -= r;
//	  }
//	  toFill[k_1] = toFill[k - 2] + csn - lbound;
// }
void comb::toCombFaster(int csn, int *toFill){
	int k_1=(k - 1);
	  csn += 1;
	  int lbound = 0;
	  int r = 0;
toFill[0] = 0;
do{
toFill[0]++;
r = ncomb[n - toFill[0]][ k_1 ];
lbound += r;
} while (lbound < csn);
lbound -= r;

	  for (int i = 1; i < k_1; i++) {
			toFill[i] = toFill[i - 1];
			do{
				 toFill[i]++;
				 r = ncomb[n - toFill[i]][ k_1 - i];
				 lbound += r;
			} while (lbound < csn);
			lbound -= r;
	  }
	  toFill[k_1] = toFill[k - 2] + csn - lbound;
 }
void comb::toCombNext(unsigned char *vector){
//http://www.aconnect.de/friends/editions/computer/combinatoricode_e.html#k-combinations_without_repetition_in_lexicographic_order
	int j; //index

	//easy case, increase rightmost element
	if(vector[k - 1] < n - 1)
	{
	vector[k - 1]++;
	return;
	}

	//find rightmost element to increase
	for(j = k - 2; j >= 0; j--)
	if(vector[j] < n - k + j)
	break;

	//terminate if vector[0] == n - k
	if(j < 0)
	return;

	//increase
	vector[j]++;

	//set right-hand elements
	while(j < k - 1)
	{
	vector[j + 1] = vector[j] + 1;
	j++;
	}
}
int comb::toCsn(int* combi) {
    int lbound = 0;
    int r = 0;
    for (int i = 1; i <= k; i++) {
        r = n - combi[k - i]+startfrom-1;
        if (r >= i)
            lbound += numCombin(r, i);
    }
    return (numCombin(n, k) - lbound - 1);
}
int comb::toCsn(vector<int> &combi){
    return toCsn(vraw(combi));
}
vector<vector<float>> comb::percentagesEachColFill(vector<vector<int>> &cols,int from,int to){
    vector<vector<float>> percentagesEach =vector<vector<float>>(k,vector<float>(n+startfrom));
    int range=to-from;
    lop(ki,0,k)lop(ri,from,to)percentagesEach[ki][cols[ki][ri]]++;
    lop(ki,0,k)lop(ni,0,n+startfrom)percentagesEach[ki][ni]/=range;
    return percentagesEach;
}
vector<int> comb::toCsn(vector<vector<int>> &cols){
    vector<int> res(cols[0].size());
    lop(i,0,cols[0].size()){
        int cr[k];
        lop(ci,0,k)cr[ci]=cols[ci][i];
        res[i]=toCsn(cr);
    }
    return res;
}
map<float,float > comb::pEachConjFill(vector<vector<int>> &cols,int from,int to){
    map<float,float> eachdistinct;
    vector<float> eachper(to);//fill(eachper,eachper+cb.range,0);
    int j=0;
    lop(i,from,to){
        lop(ki,0,k)
            eachper[i]+=percentagesEachCol[ki][cols[ki][i]];
        eachper[i]=mathRound(eachper[i],2);
//        vector<int> vcb;cb.toComb(i,vcb);
//        if(floatEqual(eachper[i],0.33)){dbgv(++j);dbgpa(vcb,0,k);}
        eachdistinct[eachper[i]]++;
    }
    float range=to-from;
    vector<float> eachperdistinct=distinct(eachper);
//    dbgv(eachperdistinct.size(),eachperdistinct[indexOfmin(eachperdistinct,0,eachperdistinct.size())]);
    for(map<float, float>::const_iterator it = eachdistinct.begin(); it != eachdistinct.end(); ++it){
        eachdistinct[it->first]=it->second/range;
//        dbgv(it->first,eachdistinct[it->first]);
    }
//    dbgpa(eachper,10000,10050);

//    lop(i,from,to)eachper[i]=eachdistinct[eachper[i]];
    return eachdistinct;
}
void comb::pEachConjFill(){
    if(cache.size()==0 || percentagesEachCol.size()==0){
        dbgv("\npEachConjFill need comb class started with cache=true and percentagesEachColFill()\n");
        return;
    }
    map<float,float> eachdistinct;
    int from=0,to=range;
    vector<float> eachper(to);//fill(eachper,eachper+cb.range,0);
    int j=0;
    lop(i,from,to){
        lop(ki,0,k)
            eachper[i]+=percentagesEachCol[ki][cache[ki][i]];
        eachper[i]=mathRound(eachper[i],2);
//        vector<int> vcb;cb.toComb(i,vcb);
//        if(floatEqual(eachper[i],0.33)){dbgv(++j);dbgpa(vcb,0,k);}
        eachdistinct[eachper[i]]++;
    }
    vector<float> eachperdistinct=distinct(eachper);
//     dbgv(eachperdistinct.size(),eachperdistinct[indexOfmin(eachperdistinct,0,eachperdistinct.size())]);
    for(map<float, float>::const_iterator it = eachdistinct.begin(); it != eachdistinct.end(); ++it){
        eachdistinct[it->first]=it->second/(float)to;
//        dbgv(it->first,eachdistinct[it->first]);
    }
//    dbgpa(eachper,10000,10050);

    lop(i,from,to)eachper[i]=eachdistinct[eachper[i]];
    pEachConj=eachper;//pEachConjFill(cache,0,range);
}
vector<int> combRBestMultiples(int range,int qtMultiples,int tolerance){
    int bmultiple=pow(range,1./qtMultiples)-tolerance;
    combR cbm(tolerance*2,qtMultiples);
    float stdevlesser=range;
    int lesser=range;
    int lesseri=0;
    vector<int> coi;
    vector<int> co(qtMultiples);
    lop(i,0,cbm.range){
//        vector<int> co;//(qtMultiples);
        cbm.toComb(i,co);
//        vector<int> co=cbm.toComb(i);
        lop(x,0,qtMultiples)co[x]+=bmultiple;
        // int qtimpars =  from (co) >> where ([](int i) {return i%2 !=0;}) >> cpplinq::count();
        // if(qtimpars!=qtMultiples)continue;
        int lesserlocal=1;
        lop(x,0,qtMultiples)lesserlocal*=(co[x]);
        if(lesserlocal>range)continue;
        float stdevlesserlocal=mathStdev(co,0,qtMultiples);
        if(range-lesserlocal<lesser || (range-lesserlocal==lesser && stdevlesserlocal<stdevlesser) ){
            lesseri=i;;
            lesser=range-lesserlocal;
            stdevlesser=stdevlesserlocal;
            coi=co;
			dbgv(cbm.range,i,lesser);
			printf("\n");lop(ci,0,coi.size())printf("%d,",coi[ci]);
			//dbgvecall(coi);
        }
    }
    dbgv(lesser);
    printf("\n");lop(ci,0,coi.size())printf("%d,",coi[ci]);
//    dbgvecall(coi);
//    dbgpx(coi,0,qtMultiples);
    return coi;
}


vvint combR::toCombV(vector<int>&hist){
	vvint cvertical(k,vint(hist.size()) );
	int r[k];
	lop(i,0,hist.size()){
		toComb( r, hist[i] );
		lop(ki,0,k)
			cvertical[ki] [i] = r[ki];
	}
	return cvertical;
}


vvint combBinPairBalanced::toCombV(vector<int>&hist){
	vvint cvertical(k,vint(hist.size()) );
	int r[k];
	lop(i,0,hist.size()){
		toComb( r, hist[i] );
		lop(ki,0,k)
			cvertical[ki] [i] = r[ki];
	}
	return cvertical;
}

//inverted not defined
//vvint a={{10,20},{0,20}, {0,30,22},{0,40} };
vvint combtR::convertFromMtx(vvint &mtx,int limit){
	vint tbets(mtx.size());
	lop(i,0,tbets.size())tbets[i]=mtx[i].size();
	combR cbr(tbets);
//	dbgv(cbr.range);
	vint csb(cbr.k);
	int csn;
	comb cb(nk[0],nk[1]);
	combR cbrl(rangesR);
	vvint res(cbr.range);
	lop(i,0,cbr.range){
		if(i>limit)break;
		cbr.toComb(i,csb);
		lop(ki,0,cbr.k)
			csb[ki]=mtx[ki][csb[ki]];
		csn=cbrl.toCsn(&csb[0]);
		cb.toComb(csn,csb);
		res[i]=csb;
	}
	return res;
}


