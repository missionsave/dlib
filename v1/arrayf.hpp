#ifndef ARRAYF_HPP_INCLUDED
#define ARRAYF_HPP_INCLUDED

#include <regular.hpp>
#include <algorithm>
#include <numeric>
//namespace std{ template< class ForwardIt, class BinaryPredicate >ForwardIt unique( ForwardIt first, ForwardIt last, BinaryPredicate p );};
#include <map>
using namespace std;

#define malloc2(nome,tipo,s1,s2) nome=(tipo **)malloc(s1 * sizeof(tipo *));lop(mi_,0,s1)nome[mi_]=(tipo *)malloc(s2 * sizeof(tipo));
#define malloc1(tipo,s1) (tipo *)malloc(s1 * sizeof(tipo));


#define indexOf(arrayo,from,to,val)({int i_of=-1;lop(li_of,from,to){if(arrayo[li_of]==val){i_of=li_of;break;}}i_of;})
#define indexOfLast(arrayo,from,to,val)({int i_of=-1;for(int li_of=(to)-1;li_of>=0;li_of--){if(arrayo[li_of]==val){i_of=li_of;break;}} i_of;})

#define indexOfmin(arr,from,to) ({int iom_=from; lop(iomi,(from)+1,to)if(arr[iomi]<arr[iom_])iom_=iomi; iom_; })
#define indexOfmax(arr,from,to) ({int iom_=from; lop(iomi,(from)+1,to)if(arr[iomi]>arr[iom_])iom_=iomi; iom_; })

#define arrInvertFromBehind(arr,arrdest,sz,_nrange) {lop(iv,0,sz)arrdest[iv]=_nrange-  arr [sz-iv-1] +1; }

#define arrCount(a,from,to,condition) ({int a__count=0; lop(a__i,from,to)if(a[a__i] condition)a__count++; a__count;})

#define arrInv(vals,sza) vals##Inv[sza]; {lop(vals##_i,0,sza)vals##Inv[vals[vals##_i]]=vals##_i;}

#define sortGiveIndexFast(arrIndexs,vals,sza) { iota (arrIndexs,arrIndexs+sza,0); sort(arrIndexs,arrIndexs+sza, [&vals](size_t i1, size_t i2) {return vals[i1] < vals[i2];});}
#define sortGiveIndexFastStable(arrIndexs,vals,sza) { iota (arrIndexs,arrIndexs+sza,0); stable_sort(arrIndexs,arrIndexs+sza, [&vals](size_t i1, size_t i2) {return vals[i1] < vals[i2];});}

#define sortGiveIndexFastDesc(arrIndexs,vals,sza) { iota (arrIndexs,arrIndexs+sza,sza-1,-1); sort (arrIndexs,arrIndexs+sza, [&vals](size_t i1, size_t i2){return vals[i1] > vals[i2];});}
#define sortGiveIndexFastStableDesc(arrIndexs,vals,sza) { iota (arrIndexs,arrIndexs+sza,sza-1,-1); stable_sort (arrIndexs,arrIndexs+sza, [&vals](size_t i1, size_t i2){return vals[i1] > vals[i2];});}

#define sortGiveIndexDirectAsc(res,vals,sza) res[sza];({ res[0]=0; int sgIi, sgIj,sgIkeyv; float sgIkey; for(sgIi = 1; sgIi < sza; sgIi++){   sgIkey = vals[sgIi]; res[sgIi]=sgIi; sgIkeyv = sgIi; sgIj = sgIi - 1; while(sgIj >= 0 && vals[sgIj] > sgIkey ){vals[sgIj + 1] =vals[sgIj]; res[sgIj + 1] = res[sgIj]; sgIj--;}vals[sgIj + 1] = sgIkey; res[sgIj + 1] = sgIkeyv;}})
#define sortGiveIndex(res,vals,sz,...)  res##Sorted[sz]; int res##I[sz]; {bool res##desc=#__VA_ARGS__=="desc"; res##I[0]=0; int sgIi, sgIj,sgIkeyv; float sgIkey; lop(sgIi,0,sz)res##Sorted[sgIi]=vals[sgIi];  for(sgIi = 1; sgIi < sz; sgIi++){   sgIkey = res##Sorted[sgIi]; res##I[sgIi]=sgIi; sgIkeyv = sgIi; sgIj = sgIi - 1; while(sgIj >= 0 && res##desc?(res##Sorted[sgIj]<sgIkey):(res##Sorted[sgIj]>sgIkey) ){res##Sorted[sgIj + 1] =res##Sorted[sgIj]; res##I[sgIj + 1] = res##I[sgIj]; sgIj--;}res##Sorted[sgIj + 1] = sgIkey; res##I[sgIj + 1] = sgIkeyv;}}


#define sortGiveIndexAsc(res,vals,sz,...)std::vector<int> res##I(sz); std::size_t nidx(0);    std::generate(std::begin(res##I), std::end(res##I), [&]{ return nidx++; });    std::sort(  std::begin(res##I),   std::end(res##I), [&](int i1, int i2) { return vals[i1] < vals[i2]; } );
#define sortGiveIndexDesc(res,vals,sz,...)std::vector<int> res##I(sz); std::size_t nidx(0);    std::generate(std::begin(res##I), std::end(res##I), [&]{ return nidx++; });    std::sort(  std::begin(res##I),   std::end(res##I), [&](int i1, int i2) { return vals[i1] > vals[i2]; } );

int qtdiguais(vint &a,vint &b);

vvint vrotate(vvint &origin );


template<typename T>
inline vector<T> distinct(vector<T> vec){
    sort(vec.begin(), vec.end());
    vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
    return vec;
};
template<typename T> vector<T> distinctCount(vector<T> &vecOrigin,vector<int> &targetCount){
    map< T ,int> mp;
    lop(i,0,vecOrigin.size())mp[vecOrigin[i]]+=1;
    vector<T> d(mp.size());
    targetCount=vector<int>(mp.size());
    int co=0;
    for (typename map< T ,int>::const_iterator it = mp.begin(); it != mp.end(); ++it){
        d[co]=it->first;
        targetCount[co]=it->second;
        co++;
    }
    return d;
};

template <typename Iter, typename Initial_Value, typename Step>
void iota(Iter _First, Iter _Last, Initial_Value value, Step step){
	for (; _First != _Last; ++_First, value += step)
		*_First = value;
}

vstring split(const string& s, const string delim, const bool keep_empty = true);

vfloat numsFromStr(string& s);

string join(vint arr,string sep=" ");
#define joina(vs,from,to,delim)({std::stringstream result_; lop(i_,from,(to)-1){result_ << vs[i_];result_ << delim;}result_ << vs[to-1];result_.str();})

//int vboolToInt(vbool vb);
//bool vboolCompare(vbool &a,vbool &b);


void vecpushuni(vstring &vec,string val);
void vecpushuni(vint &vec,int val);

#endif // ARRAYF_HPP_INCLUDED
