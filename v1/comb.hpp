#ifndef COMB_HPP_INCLUDED
#define COMB_HPP_INCLUDED

#include <map>
#include <vector>
#include "algebra.hpp"

using namespace std;

int factorial(int n);

///may take a while to calculate
vector<int> combRBestMultiples(int range,int qtMultiples,int tolerance);

vector<vector<int>> combConvertToR(vector<vector<int>> &cols,vector<int> &nk,vector<int> rangesR);
vector<vector<int>> combConvertToBinPairBalanced(vector<vector<int>> &cols,vector<int> nk,int startfrom);


struct combtR{
    vector<vector<int>> R;
//    vector<vector<int>> hist;
    vector<int> rangesR;
    bool inverted=false;
    vector<int> nk;
    virtual void init(vector<int> nk,vector<int> rangesR);
    virtual void convertToR(vector<vector<int>> cols);
    vector<vector<int>> convertFromR(vector<vector<int>> R);
    vector<vector<int>> convertFromMtx(vector<vector<int>> &mtx,int limit=1000);
};

struct combtRm:combtR{
    vector<matrixAsc> ma;
    void init(vector<int> nk,vector<int> rangesR);
    void convertToR(vector<vector<int>> cols,int rows);
    vector<vector<int>> convertFromR(int *qtchaves=NULL,int returnEmptyIfMoreThan=100);
};
struct combR{
    bool cached=false;
    vector<unsigned int*> cache;
    vector<int> ranges;
    vector<int> restoR;
    unsigned long long range;
    int k;//=ranges.size();
    combR(){}
    ~combR(){}
    combR(int n,int K,bool tocache=false);
    combR(vector <int> Ranges,bool tocache=false);
    vector<int> toComb(unsigned int csn);
    void toComb(unsigned int csn,vector<int>&res);
    vvint toCombV(vint &hist);
    void toComb(int* res,unsigned int csn);
    unsigned long long combNumCombinIrregular();
    unsigned long long toCsn(int *comb);
};


struct combBinAsc{
    int n;
    int k;
    vector<vector<int>> vmap;
    int B,G,H,I,J,K;
    float C,D,E,F;
    combBinAsc(int _n,int _k);
    vector<vector<bool>> hmapg();

};

	// combBinPairBalanced cb(37);
	// cot(cb.k);
	// int cbr[cb.k];
	// lop(j,0,cb.range){
		// cb.toComb(cbr,j);
		// lop(i,0,cb.k)cout<<(cbr[i]);
		// cout<<" "<<j<<endl;
	// }
	// cbr[0]=0;cbr[1]=0;cbr[2]=1;cbr[3]=0;cbr[4]=1;cbr[5]=0;
	// cot(cb.toCsn(cbr));
struct combBinPairBalanced{
    combR* crx;
    int k;
    unsigned long long range;
    unsigned long long rangematrix;
    combBinPairBalanced(unsigned long long Range);
    combBinPairBalanced(){}
    ~combBinPairBalanced(){delete crx;}
    void toComb(int* res,unsigned int csn);
    vvint toCombV(vint &hist);
    unsigned int toCsn(int *comb);
    ///toCsnsNot ocorrencias comb[x]=-1 são todos excluidos, comb[x]=1 == ocorrencia not comb[x]=0
    vector<unsigned int> toCsnsNot(int *comb);
    vector<vector<bool>> hmapg();
};

#define combVNextRange(m,n) ({pow(m,n);})
#define combVNextFastest(vector,m,n) {if(vector[n - 1] < m - 1) { vector[n - 1]++; }else{		int j;		for(j = n - 2; j >= 0; j--) { vector[j + 1] = 0; if(vector[j] < m - 1)  break; }vector[j]++; 	}}

#define combRNextFastest(vector,n,k) {if(vector[k - 1] < n - 1) { vector[k - 1]++; }else{		int j;		for(j = k - 1; j--;)		if(vector[j] != n - 1)	break;vector[j]++; for(j += 1; j < k; j++) vector[j] = vector[j - 1];	}}

//combNextFastest binary rep(w)
//unsigned int t = w | (w - 1);
//w=(t+1)|(((~t & -~t)-1) >> (__builtin_ctz(w) + 1));

//unsigned long long t,w=31==5;
#define combNextFastBin t=w|(w-1);w=(t+1)|(((~t & -~t)-1) >> (__builtin_ctzll(w)+1));

//must define int j;
#define combNextEvenFastest(vector,n,k) {if(vector[k - 1] < n - 1) { vector[k - 1]++; }else{		for(j = k - 1; j--;)		if(vector[j] < n - k + j)		break;					vector[j]++;while(j < k - 1)	{	vector[j + 1] = vector[j] + 1;	j++;		}	}}
#define combNextFastest(vector,n,k) {if(vector[k - 1] < n - 1) { vector[k - 1]++; }else{		int j;		for(j = k - 1; j--;)		if(vector[j] < n - k + j)		break;					vector[j]++;while(j < k - 1)	{	vector[j + 1] = vector[j] + 1;	j++;		}	}}
#define combNextFast(vector,n,k) {if(vector[k - 1] < n - 1) { vector[k - 1]++; }else{		int j;		for(j = k - 2; j >= 0; j--)		if(vector[j] < n - k + j)		break;		if(j >= 0){			vector[j]++;while(j < k - 1)	{	vector[j + 1] = vector[j] + 1;	j++;	}	}	}}
struct comb{
    vector<int*> ncomb;
    int startfrom=1;
    bool cached=false;
    vector<vector<int>> cache;
//    vector<unsigned int*> cache;
    vector< int*> cacheh;
    unsigned long long range;
    int n,k;
    comb(int N,int K,bool tocache=false,int Startfrom=1);
    comb(){};
    ~comb();
    void fillCacheH();
	unsigned char* cachehcontinuos;
    void fillCacheHc();
    vector<vector<unsigned char>> cachehc;
    vector<unsigned char*> cachehc1;
    vector<vector<char>> cachehc2;
    unsigned long long numCombin(int n, int k);
    string toCombStr(int csn);
    vector<int> toComb(int csn);
    void toComb(int csn, vector<int> &toFill);
    void toComb(int csn, int *toFill);
    void toCombFaster(int csn, int *toFill);
		void toCombNext(unsigned char *vector);//fastest
    int toCsn(int* combi);
    int toCsn(vector<int> &combi);
    vector<int> toCsn(vector<vector<int>> &cols);
    vector<vector<float>> percentagesEachCol;
    void percentagesEachColFill(){ if(cache.size()==0){printf("%s","\npercentagesEachColFill need comb class started with cache=true\n");return;} percentagesEachCol=percentagesEachColFill(cache,0,range);}
    vector<vector<float>> percentagesEachColFill(vector<vector<int>> &cols,int from,int to);
    vector< float > pEachConj;
    void pEachConjFill();
    map<float, float > pEachConjFill(vector<vector<int>> &cols,int from,int to);
};
#endif // COMBBINASC_HPP_INCLUDED
