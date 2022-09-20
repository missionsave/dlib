#ifndef CLEAN_H
#define CLEAN_H

#define haveboost 1
#if haveboost
    #define bstd boost
#else
    #define bstd std
#endif // haveboost

#ifdef src
#define _src(...) __VA_ARGS__
#else
#define _src(...)
#endif // src


#if haveboost
    #include <boost/thread/thread.hpp>
#else
    #include <thread>
#endif // bstd

#include <cmath>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#define WINVER 0x0500
#define _WIN32_WINNT 0x0500
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#ifdef src
#include <wininet.h>
#include <ctime>
#define CURL_STATICLIB
#include <curl/curl.h>
#include <curl/easy.h>
#include "unzip.h"
#include <zlib.h>
#include <fstream>
#include <unistd.h>
#if haveboost
    #include <boost/filesystem.hpp>
    #include <boost/thread/mutex.hpp>
#else
    #include <mutex>
#endif // bstd
#else
unsigned long long mathPow2a[64]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216,33554432,67108864,134217728,268435456,536870912,1073741824,2147483648,4294967296,8589934592,17179869184,34359738368,68719476736,137438953472,274877906944,549755813888,1099511627776,2199023255552,4398046511104,8796093022208,17592186044416,35184372088832,70368744177664,140737488355328,281474976710656,562949953421312,1125899906842624,2251799813685248,4503599627370496,9007199254740992,18014398509481984,36028797018963968,72057594037927936,144115188075855872,288230376151711744,576460752303423488,1152921504606846976,2305843009213693952,4611686018427387904,9223372036854775808};
//#include <WinDef.h>
#endif // src


#include "sqlite3.h"
using namespace std;

#define vraw(vec) &vec[0]
#define lop(var,from,to)for(int var=(from);var<(to);var++)
#define fori_(from,to)lop(i_,from,to)
#define fori(from,to)lop(i,from,to)

#define joina(vs,from,to,delim)({std::stringstream result_; fori_(from,(to)-1){result_ << vs[i_];result_ << delim;}result_ << vs[to-1];result_.str();})
#define joinai(vs,from,to,delim)({std::stringstream result_; lop(joini_,from,(to)-1){result_<<joini_; result_<<":";result_ << vs[joini_];result_ << delim;}result_<<((to)-1); result_<<":"; result_ << vs[(to)-1];result_.str();})

#define floatEqual(f,v)({float f1=f,f2=v; (abs(*(int*)&f1 - *(int*)&f2)<2)?1:0; })

#define bitreversei(arr,idx)({arr[idx]==0?arr[idx]=1:arr[idx]=0; arr[idx];})
#define bitreverse(val)((val)==0?1:0)

#define rotateY(val,qt,min,max) (max-min+qt+val-min)%(max-min)+min
#define rotateYa(thename,arr,from,to,qt,min,max)thename[to];{lop(_ari,from,to)thename[_ari]=rotateY(arr[_ari],qt,min,max);}

#define mathNumscale(num,factorx,min,max,midletarget)({float _mnsfd = (factorx)/2.0-(midletarget); float _mnsfactor = (float)(factorx) / ((max) - (min));( ((num) - (min)) * _mnsfactor - _mnsfd);})
#define mathNumdescale(num,factorx,min,max,midletarget)({float _mndsfd = (factorx)/2.0-(midletarget); float _mndsfactor = (float)(factorx) / ((max) - (min));( ((num) + _mndsfd) / _mndsfactor + (min) );})
#define mathFactorial(n)({unsigned long long mathFactorialf=1;lop(mathFactoriali,1,n+1) mathFactorialf*=mathFactoriali; mathFactorialf;})


#define mathRound(n,d) ({float _pow10=pow(10,d); floorf((n) * _pow10 + 0.5) / _pow10;})

#define mathSum(arr,from,to)({float sum=0; lop(msi_,from,to)sum+=arr[msi_]; sum;})
#define mathAvg(arr,from,to)mathSum(arr,from,to)/(float)((to)-(from))
#define mathDevsq(arr,from,to)({float ave=mathAvg(arr,from,to); float E=0; lop(_i,from,to) E+=(arr[_i] - ave)*(arr[_i] - ave); E;})
#define mathStdev(arr,from,to)sqrt( mathDevsq(arr,from,to)/(float)(((to)-(from))-1))
#define mathStdevp(arr,from,to)sqrt( mathDevsq(arr,from,to)/(float)(((to)-(from))))
#define mathVariance(arr,from,to)mathDevsq(arr,from,to)/(float)(((to)-(from))-1)
#define mathMedian(arr,from,to)({float _median;int len_=(to)-(from); float _ext[len_]; lop(_im,0,len_)_ext[_im]=arr[(from)+_im]; std::sort(_ext,_ext+len_);  if(len_%2==0)_median=(_ext[len_/2]+_ext[len_/2-1])/2; else _median= _ext[len_/2]; _median;})
#define mathSkewness2(arr,from,to)(mathAvg(arr,from,to)-mathMedian(arr,from,to))/mathStdev(arr,from,to)
#define mathSkewness1(arr,from,to)3*(mathAvg(arr,from,to)-mathMedian(arr,from,to))/mathStdev(arr,from,to)
#define mathSkewness(arr,from,to)({float skewness_=0;float S=mathStdev(arr,from,to); float ave=mathAvg(arr,from,to); lop(si_,from,to)skewness_ += (arr[si_] - ave)*(arr[si_] - ave)*(arr[si_] - ave); skewness_/(((to)-(from)) * S * S * S); })
#define mathKurtosis(arr,from,to)({float Kurtosis=0;float S=mathStdev(arr,from,to); float ave=mathAvg(arr,from,to); lop(si_,from,to)Kurtosis += (arr[si_]-ave)*(arr[si_]-ave)*(arr[si_] - ave)*(arr[si_] - ave); (Kurtosis/(((to)-(from)) * S*S*S*S))-3; })
#define mathSkew(arr,from,to)({float skewness_=0;float S=mathStdev(arr,from,to); float ave=mathAvg(arr,from,to); int iCount =((to)-(from));lop(si_,from,to)skewness_ += pow(((arr[si_] - ave) / S),3); skewness_*((iCount) /(float)((iCount - 1) * (iCount - 2)));})
#define mathKurt(arr,from,to)({float Kurt_=0;float S=mathStdev(arr,from,to); float ave=mathAvg(arr,from,to); int iCount =((to)-(from));lop(si_,from,to)Kurt_ += pow(((arr[si_] - ave) / S),4); Kurt_*(((iCount)*(iCount+1)) / (float)((iCount - 1) * (iCount - 2)*(iCount-3))) - (3 * (pow(iCount - 1, 2)) /(float)((iCount - 2) * (iCount - 3)));})

#define mathFastExp(y) ({ double d; *((int*)(&d) + 0) = 0; *((int*)(&d) + 1) = (int)(1512775 * y + 1072632447); d;})
#define mathSigmoid(x)  1.0 / (1 + mathFastExp(-(x)))

#define mathLog2(xx)({float x=xx;union{ float f; unsigned int i; } vx = { x }; float y = vx.i; y *= 1.1920928955078125e-7f; x=(y - 126.94269504f); x;})
#define mathPow2(pp)({float p=pp; float clipp = (p < -126) ? -126.0f : p;  union { unsigned int i; float f; } v = { (unsigned int) ( (1 << 23) * (clipp + 126.94269504f) ) }; float r=v.f; r;})
#define mathPow(x ,p ) (mathPow2 ((p) * mathLog2 (x)) )
#define mathDiffPer(baseone,confront,ratio)({float _b=(baseone)*ratio; (_b-(confront))/((_b+(confront))/2.0);})
#define mathNomial(thename,qt,n)float thename[(qt)];({lop(mnui_,0,qt){thename[mnui_]=(1 )/(pow(n,(mnui_+2)))*pow(n-1,mnui_);}})
#define mathBinomialCoefficient(m,n)( (float)(mathFactorial(n) / (double) (mathFactorial(m) * mathFactorial((n) - (m) ))) )
#define mathBinomialNodeValue(m, n, p) ( mathBinomialCoefficient(m, n) * pow(p,(float)(m)) * pow(1.0 - p, (float)((n) - (m))) )
#define mathBinomialNodeValues(thename,n, p)float thename[n+1];{lop(mbnvsi,0, (n)+1 )thename[mbnvsi] = mathBinomialNodeValue(mbnvsi, n, p); }

#define mathLinearRegression(px,x,y,from,to)({int n=(to)-(from); float slope,intercept,A=0.0,B=0.0,C=0.0,D=0.0;for(int i=from;i<to;i++) {A+=x[i];B+=y[i];C+=x[i]*x[i];D+=x[i]*y[i];} slope=(n*D-A*B)/(n*C-A*A);intercept=(B-slope*A)/n; slope*(px)+intercept;})
#define mathLinearRegressionOne(y,from,to)({int x[to]; for(int i=from;i<to;i++)x[i]=i+1;mathLinearRegression(to+1,x,y,from,to);})

#define mathBintodec(arr,len)({int dec=0;int ci_;for(ci_=0;ci_<len; ci_++ )dec+=arr[ci_]*pow(2,len-ci_-1); dec;})
#define mathBintodec(arr,from,to)({int len=(to)-(from);unsigned long long dec=0;int ci_;for(ci_=from;ci_<to;ci_++) dec+=arr[ci_]*mathPow2a[len-ci_-1+(from)]; dec;})
#define mathBintodecReversed(arr,from,to)({unsigned long long dec=0;for(int ci_=from;ci_<to;ci_++) dec+=arr[ci_]*mathPow2a[ci_-(from)]; dec;})

#define mathGaussConvergence(thename,amostra,from,to,amp,probof0)float thename[amp + 1];{int mgcxs[amp + 1]; fill(mgcxs,mgcxs+(amp+1),0); lop(mgci,amp+from,to+1) { int mgccount0=0; lop(mgca,mgci-amp,mgci){if(amostra[mgca]==0)mgccount0++;} mgcxs[mgccount0]++;}float mgctot=mathSum(mgcxs,0,amp+1); lop(mgca,0,amp+1) thename[mgca]=mgcxs[mgca]/mgctot;}

#define mathGaussConvergencePer(thename,amostra,from,to,amp,probof0)float thename[amp + 1];{ mathGaussConvergence(mgco_,amostra,from,to,amp,probof0); mathBinomialNodeValues(mgcpb,amp, probof0); lop(mgcpa,0,amp+1)thename[mgcpa]=mathDiffPer(mgco_[mgcpa],mgcpb[mgcpa],1);}

#define mathGaussConvergenceSubtract(tofill,amostra,from,to,amp,probof0)({float mgco_[amp + 1]; mathGaussConvergence(mgco_,amostra,from,to,amp,probof0);  mathBinomialNodeValues(mgcpb,amp, probof0); lop(mgcpa,0,amp+1)tofill[mgcpa]=mgcpb[mgcpa]-mgco_[mgcpa];})

#define mathRichExtrapolation(y,length)({float mrecalc[100][100]={0};float mreresult;for(int mrei=0; mrei<length; mrei++)mrecalc[0][mrei]=y[mrei]; for(int mrei=1; mrei<length; mrei++){for(int mrej=0; mrej<((length)-mrei); mrej++){mrecalc[mrei][mrej] = mrecalc[mrei-1][mrej+1] + (mrecalc[mrei-1][mrej+1] - mrecalc[mrei-1][mrej])/pow(2.0,mrei);}} mrecalc[length-1][0];})

int mathForecastStat(int* vals,int idx,int ampStart,int ampEnd,int lb)_src({
    int qt=0;
    float minstdev=  1000;
    lop(qti,ampStart,ampEnd){
        int rotateYa(valsr,vals,idx- lb,idx,qti,ampStart,ampEnd);
        float stdev=mathKurt (valsr,idx- lb,idx)*mathStdev(valsr,idx- lb,idx);
        if(minstdev>stdev){minstdev=stdev;qt=qti;}
    }
    int rotateYa(valsr,vals,idx- lb,idx,qt,ampStart,ampEnd);
    float mr=mathLinearRegressionOne(valsr,idx- lb,idx);
    float r=mathSkew(valsr,idx- lb,idx);
    float ro=r>0?0.5:-0.5;
    ro=abs(r)>0.5?ro*3 :ro;
    int mri=floorf(mr+ro);
    mri=rotateY(mri,-qt,ampStart,ampEnd);
    return mri;
});




#define arrCount(a,from,to,condition) ({int a__count=0; lop(a__i,from,to)if(a[a__i] condition)a__count++; a__count;})

#define arrInv(vals,sza) vals##Inv[sza]; {lop(vals##_i,0,sza)vals##Inv[vals[vals##_i]]=vals##_i;}

#define sortGiveIndexDirectAsc(res,vals,sza) res[sza];({ res[0]=0; int sgIi, sgIj,sgIkeyv; float sgIkey; for(sgIi = 1; sgIi < sza; sgIi++){   sgIkey = vals[sgIi]; res[sgIi]=sgIi; sgIkeyv = sgIi; sgIj = sgIi - 1; while(sgIj >= 0 && vals[sgIj] > sgIkey ){vals[sgIj + 1] =vals[sgIj]; res[sgIj + 1] = res[sgIj]; sgIj--;}vals[sgIj + 1] = sgIkey; res[sgIj + 1] = sgIkeyv;}})
#define sortGiveIndex(res,vals,sz,...)  res##Sorted[sz]; int res##I[sz]; {bool res##desc=#__VA_ARGS__=="desc"; res##I[0]=0; int sgIi, sgIj,sgIkeyv; float sgIkey; lop(sgIi,0,sz)res##Sorted[sgIi]=vals[sgIi];  for(sgIi = 1; sgIi < sz; sgIi++){   sgIkey = res##Sorted[sgIi]; res##I[sgIi]=sgIi; sgIkeyv = sgIi; sgIj = sgIi - 1; while(sgIj >= 0 && res##desc?(res##Sorted[sgIj]<sgIkey):(res##Sorted[sgIj]>sgIkey) ){res##Sorted[sgIj + 1] =res##Sorted[sgIj]; res##I[sgIj + 1] = res##I[sgIj]; sgIj--;}res##Sorted[sgIj + 1] = sgIkey; res##I[sgIj + 1] = sgIkeyv;}}


/*
    vector<vector<float>> ts={{1,2,1},{3,1,2},{2,3,3},{2,0,3},{2,1,3}};
    vector<int> id=sortMultiCol(ts,{1,2});
    vector<vector<float>> indexesMatchv(tss,ts,id);
    lop(i,0,ts.size())dbgpa(tss[i],0,ts[i].size());
    dbgpa(id,0,id.size());
*/
vector<int> sortMultiCol(vector<vector<float>> &tosort,vector<int> idxdirs)_src({
    int tsize=tosort.size();
    vector<int> indexes(tsize);
    lop(i,0,tsize)indexes[i]=i;
    int i, j,keyv;
    for(int idi=idxdirs.size()-1;idi>=0;idi--){
        int idid=abs(idxdirs[idi]-1);//desc sera negativo
        for(i = 1; i < tsize; i++){
            keyv = indexes[i];
            indexes[i]=i;
            j = i - 1;
            while(j >= 0 && tosort[indexes[j]][idid] > tosort[keyv][idid] ){
                indexes[j + 1] = indexes[j];
                j--;
            }
            indexes[j + 1] = keyv;
        }
    }
    return indexes;
});

vector<float> spiralA(float* vals,int sz)_src({
    vector<float> res(sz);
    float m0=vals[0]/2;
    res[0]=0;
    for(int i=1;i<sz;i+=2){
        if(i==1){res[i]=-(vals[i]/2+m0);continue;}
        float ac=0;
        for(int aci=1;aci<i;aci+=2)ac+=vals[aci];
        res[i]=-(vals[i]/2+m0+ac);
    }
    for(int i=2;i<sz;i+=2){
        if(i==2){res[i]= (vals[i]/2+m0);continue;}
        float ac=0;
        for(int aci=2;aci<i;aci+=2)ac+=vals[aci];
        res[i]= (vals[i]/2+m0+ac);
    }
    return res;
});

#define indexOf(arrayo,from,to,val)({int i_of=-1;lop(li_of,from,to){if(arrayo[li_of]==val){i_of=li_of;break;}}i_of;})
#define indexOfLast(arrayo,from,to,val)({int i_of=-1;for(int li_of=(to)-1;li_of>=0;li_of--){if(arrayo[li_of]==val){i_of=li_of;break;}} i_of;})

#define indexOfmin(arr,from,to) ({int iom_=from; lop(iomi,(from)+1,to)if(arr[iomi]<arr[iom_])iom_=iomi; iom_; })
#define indexOfmax(arr,from,to) ({int iom_=from; lop(iomi,(from)+1,to)if(arr[iomi]>arr[iom_])iom_=iomi; iom_; })


#define keepMin(memvar,arr,from,to){int _idxm=indexOfmin(arr,from,to);if(arr[_idxm]<memvar)memvar=arr[_idxm];}
#define keepMax(memvar,arr,from,to){int _idxm=indexOfmax(arr,from,to);if(arr[_idxm]>memvar)memvar=arr[_idxm];}

#define indexesInv(name,arr,sz) name[sz]; {lop(name##_i,0,sz)name[name##_i]=indexOf(arr,0,sz,name##_i);}

#define indexesMatchv(new,ori,idxs) new(ori.size()); {lop(ti,0,ori.size())new[ti]=ori[idxs[ti]];}

template<typename T>
inline vector<T> distinct(vector<T> vec){
    sort(vec.begin(), vec.end());
    vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
    return vec;
};
template<typename T>
inline vector<T> distinctCount(vector<T> &vecOrigin,vector<int> &targetCount){
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

_src( bstd::mutex mutexprintf; );
void dbgp(char * format, ...)_src({ mutexprintf.lock(); setlocale(LC_ALL,"C");va_list args;va_start (args, format);vprintf (format, args); va_end (args); mutexprintf.unlock();} );
#define dbgp1( ... )dbgp(__VA_ARGS__)
#define dbgp1(...)
#define dbgpa( ar,from,to ) dbgp ("\nDump array %s: %s",#ar,joinai(ar,from,to," ").c_str())
#define dbgpvrow(vs,idx,text_)({std::stringstream result;result<<(text_);result<<" "; fori_(0,vs.size()-1){result<<i_; result<<":";result << vs[i_][idx];result <<" ";}result<<(vs.size()-1); result<<":"; result << vs[vs.size()-1][idx];dbgp("\n%s",result.str().c_str());})
#define rprintf( ... )({ char buffer[256]; sprintf (buffer, __VA_ARGS__);  buffer; })
template <typename  T> void dbg(T current){cout<<current<<endl;}
template <typename  T,typename... remaining>void dbg(T current,remaining... params){cout<<current<<",";dbg(params...);}
#define dbgv(args...) cout<<endl<<#args<<": "; dbg(args)

#define pause(milisecs) bstd::this_thread::sleep_for(bstd::chrono::milliseconds(milisecs))
#define qtcpus 3
//bstd::thread::hardware_concurrency()

#define evaln(name) #name


void clipboardSet(const char *output)_src({
    const size_t len = strlen(output) + 1;
    HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem), output, len);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
});

string toLower(string data)_src({transform(data.begin(), data.end(), data.begin(), ::tolower);return data;});
bool contains(string container,string containthis,bool matchcase=false);
_src(bool contains(string container,string containthis,bool matchcase){ if(!matchcase){container=toLower(container);containthis=toLower(containthis);} if (string(container).find(containthis)!=string::npos)return true; return false;})
vector <string> fileReadAllLines(string file)_src({vector <string> lines;ifstream myfile;myfile.open(file.c_str());if (myfile.is_open()){ while ( myfile.good() ){string line; getline (myfile,line);lines.push_back(line);}myfile.close();}return lines;});
vector<string> split(const string& s, const string& delim, const bool keep_empty = true);
_src(vector<string> split(const string& s, const string& delim, const bool keep_empty) {vector<string> result;if (delim.empty()) {result.push_back(s);return result;}string::const_iterator substart = s.begin(), subend;while (true) {	subend = search(substart, s.end(), delim.begin(), delim.end());	string temp(substart, subend);	if (keep_empty || !temp.empty()) {	result.push_back(temp);	}if (subend == s.end()) {break;	}substart = subend + delim.size();	}	return result;});
#define replaceAll(ori,from_,to_)({ string context=ori;  string from__=from_; string to__=to_; std::size_t lookHere = 0; std::size_t foundHere; while((foundHere = context.find(from__, lookHere))!=std::string::npos){context.replace(foundHere, from__.size(), to__); lookHere = foundHere + to__.size();} context;})
#define stringSplitLoopTok(func,str_,delim_)({ string largechars  = str_; char* splitted = strtok((char*)largechars.c_str(), delim_); int tokit=0; while(splitted){  func;  tokit++; splitted = strtok(NULL, delim_);} })

bool fileExits(string fname)_src({return boost::filesystem::exists(fname);});

void setconsolecolor(int val)_src({SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),val);});

#define isNan( value ) ( ((*(UINT*)&value) & 0x7fffffff) > 0x7f800000)
#define szo(arraytomeasure)sizeof(arraytomeasure) / sizeof(arraytomeasure[0])



#define RNDF ({ float rnd=0; while(rnd<1 && rnd>-1)rnd=(((float)rand()-(float)rand())/(RAND_MAX/1.7)); rnd;})
enum neural{input,output,hidden,its,lr,errlevel,err};
#define neuralForwardPass(input) float x; for(j=num_input;j<hij;j++){x=0;for(i=0;i<num_input;i++)x+=(input[i]*w[i][j]);y[j]= mathSigmoid(x-wt[j]); } for (k=hij; k<hik; k++ ){x=0; for(j=num_input; j<hij; j++ )x+=(y[j]*w[j][k]); y[k]=mathSigmoid(x-wt[k]);}
#define neuralBiasReset(netw){int ni=netw[0],no=netw[1],nh=netw[2]; lop(lni,(11+(ni)*(nh)+(no)*(nh)),(11+(ni)*(nh)+(no)*(nh)+(nh)+(no))) netw[lni]=0;}
#define neuralTrainSetSheme(netw,_its,_lr,_errlevel) {netw[its]=_its;netw[lr]=_lr;netw[errlevel]=_errlevel;}
#define neuralInit(name,ni,no,nh) float name[11+(ni)*(nh)+(no)*(nh)+(nh)+(no)];{ lop(lni,11,11+(ni)*(nh)+(no)*(nh)+(nh)+(no))name[lni]=RNDF; name[0]=ni; name[1]=no; name[2]=nh; neuralTrainSetSheme(name,1000,0.7,5);  }
#define neuralInitv(ni,no,nh)({neuralInit(netw,ni,no,nh); vector<float>(netw,netw+(11+(ni)*(nh)+(no)*(nh)+(nh)+(no)));})
#define neuralToStr(netw)({int ni=netw[0],no=netw[1],nh=netw[2]; joina(netw,0,11+(ni)*(nh)+(no)*(nh)+(nh)+(no),",");})
#define neuralAddContinuos(vec,ni,no,inpc,from,to){int stf=vec.size();int stsz=(to)-(ni)-(from)-(no)+1; vec.resize((stsz+stf),vector<float>((ni)+(no))); lop(q_,0,stsz)lop(i_,0,(ni)+(no))vec[q_+stf][i_]=inpc[i_+q_+(from)];}
vector<float> neuralCalc(float *netw,float *inp,int idx)_src({
    int num_input=netw[0],num_output=netw[1],num_h=netw[2];
    int i,j,k,hij=num_input+num_h,hik=hij+num_output;
    vector<float> res(num_output);
    ///init
//    float** w=new float*[hik];
//    for (i=0; i<num_input; i++ ) w[i]  = &netw[3+(num_h*i)-num_input] ;
//    for(j=num_input; j<hij; j++ ) w[j]  = &netw[3+(num_output*j)-hij] ;
//    float* wt = &netw[3+num_input*num_h+num_output*num_h-2];
    float w[hij][hik];float wt[hik];
    {int p=10; for (i=0; i<num_input; i++ ) for(j=num_input; j<hij; j++ ) w[i][j] = netw[++p] ; for(j=num_input; j<hij; j++ ) for ( k=hij; k<hik; k++ ) w[j][k] = netw[++p];for(j=num_input; j<hij; j++ )wt[j] =  netw[++p]; for (k=hij; k<hik; k++ )wt[k] =  netw[++p];}
    float   y[hik];

    float *inpc=&inp[idx-num_input];
    neuralForwardPass(inpc);
    for (k=hij; k<hik; k++ )res[k-hij]=y[k];
    return res;
});
void neuralTrain(float *netw,vector<vector<float>> &inp)_src({
    int its=netw[3];float lr=netw[4];int errorlevel=netw[5];
    float *error=&netw[6];
    int num_input=netw[0],num_output=netw[1],num_h=netw[2];
    int i,j,k,hij=num_input+num_h,hik=hij+num_output;

//    float** w=new float*[hik];
//    for (i=0; i<num_input; i++ ) w[i]  = &netw[3+(num_h*i)-num_input] ;
//    for(j=num_input; j<hij; j++ ) w[j]  = &netw[3+(num_output*j)-hij] ;

    float w[hij][hik];float wt[hik];
    //dendrites começam no index 11
    {int p=10; for (i=0; i<num_input; i++ ) for(j=num_input; j<hij; j++ ) w[i][j] = netw[++p] ; for(j=num_input; j<hij; j++ ) for ( k=hij; k<hik; k++ ) w[j][k] = netw[++p];for(j=num_input; j<hij; j++ )wt[j] =  netw[++p]; for (k=hij; k<hik; k++ )wt[k] =  netw[++p];}

//    float* wt = &netw[3+num_input*num_h+num_output*num_h-2];
    float   y[hik];

    float dx[hik], dy[hik];
    int qt=inp.size();
    float errorstepcheck[7]{0.4,0.3,0.2,0.1,0.05,0.01,0.001};
    int errorstep=0;
    bool errorCheckedAll=true;
    for (int it = its; --it > 0; ){
        if(!errorCheckedAll)errorstep++;
        if(errorstep>errorlevel || errorstep>6)break;//{dbgv("errorcheck");break;}
        errorCheckedAll=false;
        for(int le=qt-1;le>=0;le--){
            neuralForwardPass(inp[le]);

            ///backpropagate
            //check error
            float ce=0;
            for (k=hij; k<hik; k++ ){
                ce+=abs(y[k] - inp[le] [k-num_h]);
            }
            ce/=num_output;
            if(ce<errorstepcheck[errorstep])continue;
            errorCheckedAll=true;
            //out
            for (k=hij; k<hik; k++ ){
                dy[k] = y[k] - inp[le] [k-num_h];
                dx[k] = ( dy[k] ) * y[k] * (1-y[k]);
                wt[k] -= ( lr * (dx[k] * (-1)) );
            }
            //hidden
            for(j=num_input; j<hij; j++ ){
                dy[j] = 0;
                for (k=hij; k<hik; k++ ){
                    dy[j] += ( dx[k] * w[j][k] );//*0.5;///
                    w[j][k] -= ( lr * (dx[k] * y[j]) );
                }
                dx[j] = ( dy[j] ) * y[j] * (1-y[j]);
                wt[j] -= ( lr * (dx[j] * (-1)) );
            }
            //in
            for (i=num_input; i--; )
                for(j=num_input; j<hij; j++ ){
                    w[i][j] -= ( lr * (dx[j] * inp[le] [i]) );
                }
        }
//        dbgv(it);
    }

    ///error
    *error=0;
    for(int ti=0;ti<qt;ti++){
        neuralForwardPass(inp[ti]);
        for (k=hij; k<hik; k++ ){float yv=y[k]-inp[ti][k-num_h];*error+=abs(yv);}// cout<<y[k]<<" "<<inp[ti][k-num_h];} cout<<endl;
    }
    *error/=qt;
//    delete[] w;
    {int p=10; for (i=0; i<num_input; i++ ) for(j=num_input; j<hij; j++ ) netw[++p]=w[i][j]; for(j=num_input; j<hij; j++ ) for ( k=hij; k<hik; k++ ) netw[++p]=w[j][k]; for(j=num_input; j<hij; j++ ) netw[++p]=wt[j]; for (k=hij; k<hik; k++ ) netw[++p]=wt[k];}

});

///char* ar="2,3,5"; int deserializeArray(l,ar);// => int l[2]={3,5}; //c_str()
#define deserializeArray(name,source)name[({int resd=0; stringSplitLoopTok({ resd=atoi(splitted); break; },source,",;"); resd; })]; {stringSplitLoopTok({if(tokit>0)name[tokit-1]=atof(splitted); },source,",;");}
#define serializeArray(source,from,to)({setlocale(LC_ALL,"C"); stringstream _buf; _buf<<(to-from);_buf<<";"; lop(_dsi,(from),(to)){ _buf << source[_dsi]; if(_dsi!=(to)-1)_buf << ","; } _buf.str(); })


//char bitarray[4]; // since 4*8 this array actually contains 32 bits
//fori(0,8*4){bitSet(bitarray,i,i%2);}
//unsigned long aaa=0;
//fori(0,8*4){aaa+=bitGet(bitarray,i);}
//dbgp("%d  ",aaa,bitarray);
#define bitGet(bitarray,index)((bitarray[(index)/8] >> 7-((index) & 0x7)) & 0x1 )
#define bitSet(bitarray,index,value)( bitarray[(index)/8] = bitarray[(index)/8] | (value & 0x1) << 7-((index) & 0x7) )

vector<bool> fileReadBin(const char* fileName)_src({
    vector<bool> v;
    ifstream is(fileName, ios::in|ios::binary);
    if (is) {
        is.seekg (0, is.end);
        int length = is.tellg();
        is.seekg (0, is.beg);
//        char buffer[length];
        char *buffer=new char[length];
        is.read( buffer, length);
        is.close();
        for(int ix = 0; ix < length*8; ix++) v.push_back(bitGet(buffer,ix));
        delete buffer;
    }
    return v;
});
string fileReadBinTostr(const char* fileName)_src({
    string v;
    ifstream is(fileName, ios::in|ios::binary);
    if (is) {
        is.seekg (0, is.end);
        int length = is.tellg();
        is.seekg (0, is.beg);
//        char buffer[length];
        char *buffer=new char[length];
        is.read( buffer, length);
        is.close();
        for(int ix = 0; ix < length*8; ix++) v.push_back(bitGet(buffer,ix)==0?'0':'1');
        delete buffer;
    }
    return v;
});



class performance{
    private:
    unsigned int pclock;
    char* pname;
    public:
    performance(char*  name="");
    void p(char* prefix="");
};
_src(performance::performance(char*  name){pname=name;pclock=clock();});
_src(void performance::p(char* prefix){if(prefix==""){pclock=clock();return;};dbgp("\n%s %s %dms ",pname,prefix,clock()-pclock);pclock=clock();});

class pauserc{
    unsigned int ini_;
    unsigned int minutestomilisecs=600000;
    unsigned int milisecondsToPause=35000;
    public:
    pauserc();
    pauserc(int minutes,int secondsToPause);
    void se();
};
_src(pauserc::pauserc(){ini_=clock();})
_src(pauserc::pauserc(int minutes,int secondsToPause){ini_=clock();minutestomilisecs=minutes*60000;milisecondsToPause=secondsToPause*1000;})
_src(void pauserc::se(){if(clock()-ini_>minutestomilisecs){pause(milisecondsToPause);ini_=clock();}})

#ifndef src
pauserc pauser;
performance perf;
#endif // src

extern unsigned int randtmax;
extern unsigned int randtsize;
extern int randtpos;
extern int truerandom[];

#ifdef src
#include <stdlib.h>
#include <random>
mt19937 randx_;
unsigned int randtmax=9999999;
unsigned int randtsize= 50000;
int randtpos=0;
#endif // src

unsigned int randx()_src({return randx_();});
void randxsafe()_src( { randx_.seed(GetTickCount()+GetCurrentThreadId());} );
void fillrandx(int* arr,int arrsize,int min,int max) _src( {  int mm=max-min; for(int i=0;i<arrsize;++i)arr[i]=randx()%mm+min;  } );
void fillrandx(float* arr,int arrsize,int min,int max)_src({  int mm=max-min; for(int i=0;i<arrsize;++i)arr[i]=randx()%mm+min;  } );
void randsafe()_src({ srand(GetTickCount()+GetCurrentThreadId());} );
void fillrand(int* arr,int arrsize,int min,int max)_src({  int mm=max-min; for(int i=0;i<arrsize;++i)arr[i]=rand()%mm+min;  } );

void randtsafe()_src({ randtpos=(GetTickCount()+GetCurrentThreadId())%randtsize;   });
inline int randt(){if(randtpos>randtsize-1)randtpos=randtpos%randtsize; return truerandom[randtpos++];} ;
inline void fillrandt(int* arr,int arrsize,int min,int max){  int mm=max-min; for(int i=0;i<arrsize;++i)arr[i]=randt()%mm+min;  } ;
void randtposSet(int val)_src({randtpos=val%randtsize;} );
inline int randtI(int min,int max){ return randt()% (max-min) + min;} ;

int randIrregular(int min,int max,unordered_map<int, int> strengthOf)_src({
    vector<int> mat(max-min);
    for(unsigned int i=0;i<mat.size();i++)mat[i]=i+min;
    for (unordered_map<int, int>::const_iterator it = strengthOf.begin(); it != strengthOf.end(); ++it)
        mat.insert (mat.end(), it->second, it->first);
//    for(int i=0;i<mat.size();i++)printf("\nm%d",mat[i]);
    int randi=randx()%mat.size();
    return mat[randi];
});

void fillrandxIrregular(int* arr,int arrsize,int min,int max,unordered_map<int, int> strengthOf) _src( {
    vector<int> mat(max-min);
    for(unsigned int i=0;i<mat.size();i++)mat[i]=i+min;
    for (unordered_map<int, int>::const_iterator it = strengthOf.begin(); it != strengthOf.end(); ++it)
        mat.insert (mat.end(), it->second, it->first);
    int matsize=mat.size();
    for(int i=0;i<arrsize;++i)arr[i]=mat[randx()%matsize];
});

#if UINTPTR_MAX != 0xffffffff
#ifndef src
struct Win7TaskbarProgress{
    Win7TaskbarProgress(unsigned long long ullTotal,HWND Hwnd=NULL);
    Win7TaskbarProgress(HWND Hwnd=NULL);
    void SetProgressValue( unsigned long long ullCompleted );
    void SetProgressState( int flag);
    virtual ~Win7TaskbarProgress();
    HWND hwnd7 ;
    unsigned long long w7tbpTotal ;
    unsigned int segment;
};
#endif // src

void soundbeep(int h=523,int t=500);
#ifdef src
void soundbeep(int h,int t ){ Beep(h*0.5,t*0.8);Beep(h*2,t*1.5);}
#include <ShObjIdl.h>
struct Win7TaskbarProgress{
    Win7TaskbarProgress(unsigned long long ullTotal,HWND Hwnd=NULL);
    Win7TaskbarProgress(HWND Hwnd=NULL);
    void SetProgressValue( unsigned long long ullCompleted );
    virtual ~Win7TaskbarProgress();
    void SetProgressState( int flag);
    void SetProgressValue( unsigned long long ullCompleted, unsigned long long ullTotal ){
        m_pITaskBarList3->SetProgressValue(hwnd7, ullCompleted, ullTotal);
    }
    bool Init(){
        if (m_pITaskBarList3)
            return true;
        if (m_bFailed)
            return false;
        // Initialize COM for this thread...
        CoInitialize(NULL);
        CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_INPROC_SERVER, IID_ITaskbarList3, (void **)&m_pITaskBarList3);
        if (m_pITaskBarList3)
            return true;
        m_bFailed = true;
        CoUninitialize();
        return false;
    }
    ITaskbarList3* m_pITaskBarList3;
    bool m_bFailed;
    HWND hwnd7 ;
    unsigned long long w7tbpTotal ;
    unsigned int segment;
};
Win7TaskbarProgress::Win7TaskbarProgress(unsigned long long ullTotal,HWND Hwnd ){
    w7tbpTotal=ullTotal;
    segment=w7tbpTotal/50;//50 segmentos
    if(w7tbpTotal<50)segment=1;
    if(Hwnd==NULL)Hwnd=GetConsoleWindow();
    hwnd7=Hwnd;
    m_pITaskBarList3 = NULL;
    m_bFailed = false;
    Init();
}
Win7TaskbarProgress::Win7TaskbarProgress(HWND Hwnd ){
    if(Hwnd==NULL)Hwnd=GetConsoleWindow();
    hwnd7=Hwnd;
    m_pITaskBarList3 = NULL;
    m_bFailed = false;
    Init();
}
Win7TaskbarProgress::~Win7TaskbarProgress(){
    if (m_pITaskBarList3) {
        m_pITaskBarList3->Release();
        CoUninitialize();
    }
}
void Win7TaskbarProgress::SetProgressValue( unsigned long long ullCompleted ){
    if(ullCompleted==w7tbpTotal-1){SetProgressState(0);return;}
    if(ullCompleted%segment!=0)return;
    m_pITaskBarList3->SetProgressValue(hwnd7, ullCompleted, w7tbpTotal);
}
void Win7TaskbarProgress::SetProgressState( int flag){
        m_pITaskBarList3->SetProgressState(hwnd7, (TBPFLAG)flag);
    }
#endif // src
#endif // UINTPTR_MAX

#define threadsAllCpuJoin(func)({ auto tothread=[&](unsigned int tid){func}; bstd::thread thr[qtcpus];for(int ti=0;ti<qtcpus;ti++) thr[ti]= bstd::thread(tothread,ti); for(int ti=0;ti<qtcpus;ti++)thr[ti].join();})

#define threadsAllCpuJoinLoopPB(func,iters,...)({ Win7TaskbarProgress wtpr(iters);unsigned int totalit=0; auto tothread=[&](unsigned int tid){for(unsigned int it=0;it<iters;it++){if((it+tid)%qtcpus!=0)continue;  func totalit++; wtpr.SetProgressValue(totalit);}}; bstd::thread thr[qtcpus];for(int ti=0;ti<qtcpus;ti++) thr[ti]= bstd::thread(tothread,ti); for(int ti=0;ti<qtcpus;ti++)thr[ti].join(); wtpr.SetProgressState(0); __VA_ARGS__; })

#define threadsAllCpuJoinLoop(func,iters,...)({  unsigned int totalit=0; auto tothread=[&](unsigned int tid){for(unsigned int it=0;it<iters;it++){if((it+tid)%qtcpus!=0)continue;   func totalit++;}}; bstd::thread thr[qtcpus];for(int ti=0;ti<qtcpus;ti++) thr[ti]= bstd::thread(tothread,ti); for(int ti=0;ti<qtcpus;ti++)thr[ti].join(); __VA_ARGS__; })





//    comb cb(9,2,true,0);
//    for(int i=0;i<cb.range;i++)dbgp("\n%d %d",cb.cache[0][i],cb.cache[1][i]);
class comb{
    public:
    vector<int*> ncomb;
    int startfrom=1;
    bool cached=false;
    vector<vector<int>> cache;
//    vector<unsigned int*> cache;
    vector<unsigned int*> cacheh;
    unsigned long long range;
    int n,k;
    comb(int N,int K,bool tocache=false,int Startfrom=1);
    comb(){};
    ~comb();
    void fillCacheH();
    unsigned long long numCombin(int n, int k);
    void toComb(int csn, vector<int> &toFill);
    void toComb(int csn, int *toFill);
    int toCsn(int* combi);
    vector<int> toCsn(vector<vector<int>> &cols);
    vector<vector<float>> percentagesEachCol;
    void percentagesEachColFill(){ if(cache.size()==0){dbgp("\npercentagesEachColFill need comb class started with cache=true\n");return;} percentagesEachCol=percentagesEachColFill(cache,0,range);}
    vector<vector<float>> percentagesEachColFill(vector<vector<int>> &cols,int from,int to);


    vector< float > pEachConj;
    void pEachConjFill();
    map<float, float > pEachConjFill(vector<vector<int>> &cols,int from,int to);
};
#ifdef src
comb::~comb(){}//for(auto i:cache)delete[] i;}
comb::comb(int N,int K,bool tocache,int Startfrom){
        n=N;k=K;
        startfrom=Startfrom;
        range = numCombin(n,k);
        ncomb=vector<int*>(n);
        lop(nx,0,n)ncomb[nx]=new int[k];
        lop(nx,0,n)lop(kx,0,k){ncomb[nx][kx]=numCombin(nx,kx);}
        if(tocache){
            cache=vector<vector<int>>(k,vector<int>(range));
//            cache.resize(k);
//            for(int c=0;c<k;c++)cache[c]=new unsigned int [range];
            int cf[k];
            for(unsigned int  i=0;i<range;i++){
                toComb(i,cf);
                for(int c=0;c<k;c++)cache[c][i]=cf[c];
            }
            cached=true;
        }
    }
void comb::fillCacheH(){
        cacheh=vector<unsigned int*>(range);
        for(unsigned int  i=0;i<range;i++){
            cacheh[i]=new unsigned int[k];
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
        dbgp("\npEachConjFill need comb class started with cache=true and percentagesEachColFill()\n");
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
//    dbgv(eachperdistinct.size(),eachperdistinct[indexOfmin(eachperdistinct,0,eachperdistinct.size())]);
    for(map<float, float>::const_iterator it = eachdistinct.begin(); it != eachdistinct.end(); ++it){
        eachdistinct[it->first]=it->second/(float)to;
//        dbgv(it->first,eachdistinct[it->first]);
    }
//    dbgpa(eachper,10000,10050);

    lop(i,from,to)eachper[i]=eachdistinct[eachper[i]];
    pEachConj=eachper;//pEachConjFill(cache,0,range);
}
#endif // src
class combR{
    public:
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
    void toComb(int* res,unsigned int csn);
    unsigned long long combNumCombinIrregular();
    unsigned long long toCsn(int *comb);
};
#ifdef src
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
#endif // src
struct combBinPairBalanced{
    combR* crx;
    int k;
    unsigned long long range;
    unsigned long long rangematrix;
    combBinPairBalanced(unsigned long long Range);
    combBinPairBalanced(){}
    ~combBinPairBalanced(){delete crx;}
    void toComb(int* res,unsigned int csn);
    unsigned int toCsn(int *comb);
};
#ifdef src
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
#endif // src
vector<vector<int>> combConvertToR(vector<vector<int>> &cols,vector<int> &nk,vector<int> rangesR)_src({
    comb inp(nk[0],nk[1]);
    combR outp(rangesR);
    vector<vector<int>> res(rangesR.size());
    lop(fi,0,rangesR.size())res[fi]=vector<int>(cols[0].size());
    lop(ci,0,cols[0].size()){
        int chave[cols.size()];
        lop(ch,0,cols.size())chave[ch]=cols[ch][ci];
        int csn=inp.toCsn(chave);
        int chaveR[rangesR.size()];
        outp.toComb(chaveR,csn);
        lop(ri,0,rangesR.size())res[ri][ci]=chaveR[ri];
    }
    return res;
});
vector<vector<int>> combConvertToBinPairBalanced(vector<vector<int>> &cols,vector<int> nk,int startfrom)_src({
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
});

#define sqstep(stmt_)({int m_=sqlite3_step(stmt_); if(m_>0 && m_<100)dbgp("\nSQL ERROR:%s |%d %s",sqlite3_sql(stmt_),m_, sqlite3_errstr(m_)); m_;})

#define sqlStmtLoop(func,_db,...)({ char buffer[8192]; sprintf (buffer, __VA_ARGS__); sqlite3_stmt* stmt; sqlite3_prepare_v2(_db, buffer,-1, &stmt, NULL); while(sqstep(stmt)==SQLITE_ROW)func; sqlite3_finalize(stmt);   })

//    perf.p();
//    sqlite3* db;
//    sqlite3_open(":memory:", &db);
////    sqlite3_open("test.sqlite", &db);
//    sqlex(db,"CREATE TABLE IF NOT EXISTS n (idm int,c int,cb int,cc int)");//sheme int,w0 int,w1 int,w2 int,w3 int,w4 int,w5 int)");
////    sqlex(db,"CREATE INDEX i2a ON n (idm)");
//    sqlitetrans sqb (db,"insert into n(idm,c,cb,cc ) values (?,?,?,?);");
//    for (unsigned int i=0;i<1000000;i++){
//        sqb.add( i,i+10,randt(),i+67467);
//    }
//    sqb.update(db);
//    perf.p("t");//5000ms
struct sqlitetrans{
    sqlite3_stmt *stmt;
    sqlitetrans(){}
    sqlitetrans(sqlite3* &db,char* zsql){
        sqlite3_exec(db, "BEGIN   TRANSACTION", 0, 0, 0);
        sqlite3_prepare_v2(db,  zsql , -1, &stmt, NULL);
    }
    void update(sqlite3* db){
        sqlite3_finalize(stmt);
        sqlite3_exec(db, "COMMIT TRANSACTION", 0, 0, 0);
    }
    template <class... Params>
    void add(Params... params) {
        addcomedia(1,params...);
        sqstep(stmt);
        sqlite3_reset(stmt);
    }
    template<typename = void>void addcomedia(int id) { }//incrivel...
    template <typename  T,typename... remaining>
    void addcomedia(int id,T current,remaining... params){
        bind(current,id);
        addcomedia(++id, params...);
    }
    template <class... Params>
    void f(Params... params) {std::array<int, sizeof...(params)> list = {params...};}//a estudar
    void bind(int x,int id){if(x==INT_MIN)sqlite3_bind_null(stmt, id);else sqlite3_bind_int(stmt, id, x);}
    void bind(unsigned int x,int id){sqlite3_bind_int(stmt, id, x);}
    void bind(double x,int id){sqlite3_bind_double(stmt, id, x);}
    void bind(float x,int id){sqlite3_bind_double(stmt, id, x);}
    void bind(const char* x,int id){sqlite3_bind_text(stmt, id, x ,-1,NULL);}
};


class certoerrado{
    public:
    float ratio=0;
    int intervalcert=0;
    int intervalerr=0;
    map<int,int> mapcert;
    map<int,int> maperr;
    map<int,float> mapratio1;
    map<int,float> mapratio1cert;
    map<int,float> mapratio1err;
    int cert=0;
    int err=0;
    bool ceperm100=false;
    int cecurrent=0;
    int ceper[100];
    int ceperpos=0;
    char ceperm[2000000];
    void ceperf(int dir);
    certoerrado(float bruteratio=1){ratio=bruteratio;}
    void errado();
    void certo();
    void end();
    float DiffPer();
    void stats();
};
#ifdef src
void certoerrado::ceperf(int dir){
    cecurrent+=dir;
    ceper[ceperpos%100]=dir;
    if(ceperm100){
        int count1=mathSum(ceper,0,100);
        int c1=mathDiffPer(count1,(100-count1),1)*100;
        c1=c1>127?127:c1;
        c1=c1<-127?-127:c1;
        ceperm[ceperpos-99]=c1;
//        if(ceperpos%50==0)dbgp("\n%d",ceperm[ceperpos-99]);
    }
    if(ceperpos==99)ceperm100=true;
    ceperpos++;
}
float certoerrado::DiffPer(){return mathDiffPer(cert,err,ratio);}
void certoerrado::errado(){
    ceperf(0);
    err++;
    intervalerr++;
    if(intervalcert!=0){ mapcert[intervalcert]++;intervalcert=0;}
}
void certoerrado::certo(){
    ceperf(1);
    cert++;
    intervalcert++;
    if(intervalerr!=0){ maperr[intervalerr]++; intervalerr=0;}
}
void certoerrado::end(){
    //update remains
    if(intervalcert!=0){ mapcert[intervalcert]++;intervalcert=0;} if(intervalerr!=0){ maperr[intervalerr]++; intervalerr=0;}
    //for ratio 1 only...
    float r=(cert+err)/4.0; fori(1,20){r/=2.0; mapratio1[i]=r; mapratio1cert[i]=mathDiffPer(mapcert[i],mapratio1[i],1); mapratio1err[i]=mathDiffPer(maperr[i],mapratio1[i],1); }
}
void certoerrado::stats(){
    printf("\n%f, Total:%d",DiffPer(),cert+err);
    for (map<int,int>::iterator it=mapcert.begin(); it!=mapcert.end(); ++it){
        dbgp("\ncert %d %d",it->first,it->second);
    }
////        for (map<int,float>::iterator it=mapratio1cert.begin(); it!=mapratio1cert.end(); ++it){
////            dbgp("\nerr %d %f",it->first,it->second);
////        }
    for (map<int,int>::iterator it=maperr.begin(); it!=maperr.end(); ++it){
        dbgp("\nerr %d %d",it->first,it->second);
    }
}
#endif // src



string string_escape(string &in)_src({
    stringstream str;
    for(int i=0;i<in.size();i++)
        switch (in[i])
        {
//            case '\0':  str << "\\000"; break;
//            case '\a':  str << "\\a"; break;
//            case '\b':  str << "\\b"; break;
//            case '\f':  str << "\\f"; break;
//            case '\v':  str << "\\v"; break;
            case '\"':  str << "\\\""; break;
            case '\'':  str << "\\\'"; break;
            case '\\':  str << "\\\\"; break;
            case '\n':  str << "\\n"; break;
            case '\r':  str << "\\r"; break;
            case '\t':  str << "\\t"; break;
            case '\?':  str << "\\?"; break;
            default: str << in[i];
        }
    return str.str();
});
string string_compress(const std::string& str, int compressionlevel = 9);
string string_decompress(const std::string& str);
#ifdef src
string string_compress(const std::string& str, int compressionlevel)
{
    z_stream zs;                        // z_stream is zlib's control structure
    memset(&zs, 0, sizeof(zs));

    if (deflateInit(&zs, compressionlevel) != Z_OK)
        cout <<"deflateInit failed while compressing.";
//        throw(std::runtime_error("deflateInit failed while compressing."));

    zs.next_in = (Bytef*)str.data();
    zs.avail_in = str.size();           // set the z_stream's input

    int ret;
//    unsigned long dsize=str.size()+ (str.size() * 0.1f) + 16;
    char outbuffer[262144];
    std::string outstring;

    // retrieve the compressed bytes blockwise
    do {
        zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
        zs.avail_out = sizeof(outbuffer);

        ret = deflate(&zs, Z_FINISH);

        if (outstring.size() < zs.total_out) {
            // append the block to the output string
            outstring.append(outbuffer,
                             zs.total_out - outstring.size());
        }
    } while (ret == Z_OK);

    deflateEnd(&zs);

    if (ret != Z_STREAM_END) dbgp("\nzlibfail:%s",zs.msg);
    if (ret != Z_STREAM_END) {          // an error occurred that was not EOF
//        std::ostringstream oss;
        cout << "Exception during zlib compression: (" << ret << ") " << zs.msg;
//        throw(std::runtime_error(oss.str()));
    }

    return outstring;
}
string string_decompress(const std::string& str){
    z_stream zs;                        // z_stream is zlib's control structure
    memset(&zs, 0, sizeof(zs));

    if (inflateInit(&zs) != Z_OK)
        cout<<"inflateInit failed while decompressing.";
//        throw(std::runtime_error("inflateInit failed while decompressing."));

    zs.next_in = (Bytef*)str.data();
    zs.avail_in = str.size();

    int ret;
//    char outbuffer[str.size() ];
    char outbuffer[32768];
    std::string outstring;

    // get the decompressed bytes blockwise using repeated calls to inflate
    do {
        zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
        zs.avail_out = sizeof(outbuffer);

        ret = inflate(&zs,  1);

        if (outstring.size() < zs.total_out) {
            outstring.append(outbuffer,
                             zs.total_out - outstring.size());
        }
//        dbgp("\n%d",zs.total_out);

    } while (ret == Z_OK);
//        free(zs.next_out);

    inflateEnd(&zs);

    if (ret != Z_STREAM_END) dbgp("\nzlibfail:%s",zs.msg);//{          // an error occurred that was not EOF
//        std::ostringstream oss;
//        oss << "Exception during zlib decompression: (" << ret << ") "
//            << zs.msg;
//        throw(std::runtime_error(oss.str()));
//    }
//    (void)inflateEnd(&zs);
    return  outstring;
}
#endif // src
string stringFromFile(string fname)_src({
    string str;
    ifstream is (fname , std::ifstream::binary);
    if(is){
        is.seekg (0, is.end);
        int length = is.tellg();
        is.seekg (0, is.beg);
        char buffer[length];
        is.read (buffer,length);
        str=string(buffer,length);
        is.close();
    }
    return str;
});
void stringToFile(string fname,string &str)_src({
    ofstream m; m.open(fname, std::ofstream::binary);m<<str;m.close();
});
void string_compressToHeaderFile(string name,string &toCompress)_src({
    string b=string_compress(toCompress,9);
    string fn=name+".h";
    ofstream m; m.open(fn);m<<"string ";m<<name;m<<"(\"";m<<string_escape(b);m<<"\",";m<<b.size();m<<");";m.close();
});

#define stringResToFileH(name,...){string bcomp_=string_compress(name); ofstream srtmf_; srtmf_.open((string().append(#name).append(".cpp")).c_str());srtmf_<<"string ";srtmf_<<#name;srtmf_<<"(\"";srtmf_<<string_escape(bcomp_);srtmf_<<"\",";srtmf_<<bcomp_.size();srtmf_<<");";srtmf_.close();}
void stringResToFileCppF(string name,string tname,string path="");
#ifdef src
void stringResToFileCppF(string name,string tname,string path){
string bcomp_=string_compress(name);
ofstream srtmf_; srtmf_.open((string().append(path).append(tname).append(".cpp")).c_str());
srtmf_<<"#include <string>\nnamespace stringres{std::string "; srtmf_<<tname;srtmf_<<"(){return std::string(\"";srtmf_<<string_escape(bcomp_); srtmf_<<"\",";srtmf_<<bcomp_.size();srtmf_<<");}}";srtmf_.close();}
#endif // src
#define stringResToFileCpp(name,...)stringResToFileCppF(name,#name, ##__VA_ARGS__);
#define stringResFromFileCpp(name)namespace stringres{std::string name();} string name=string_decompress(stringres::name());


void* ReallocOrFree(void* original_ptr, size_t new_size)_src({
    void* temp = realloc(original_ptr, new_size);
    if (!temp) free(original_ptr);
    return temp;
});
string httpget(string url)_src({
LPCTSTR szURL=url.c_str();
size_t cbMaxSize=1000000; size_t* lpcbActualSize;
    HINTERNET hNet         = NULL;
    HINTERNET hUrlFile     = NULL;
    char*     buffer       = NULL;
    DWORD     cbBytesRead  = 0;
    SIZE_T    cbBytesTotal = 0;
    BOOL      bResult      = FALSE;
    const DWORD cbReadSize = 0x4000;

    if (!(hNet = InternetOpen(TEXT("CBOARD Downloader"), PRE_CONFIG_INTERNET_ACCESS, NULL, NULL, 0)))
        goto cleanup;

    if (!(hUrlFile = InternetOpenUrl(hNet, szURL, NULL, 0, INTERNET_FLAG_RESYNCHRONIZE, 0)))
        goto cleanup;

    do
    {
        if (!(buffer = (char*) ReallocOrFree(buffer, cbBytesTotal + cbReadSize)))
            goto cleanup;

        if (!InternetReadFile(hUrlFile, buffer + cbBytesTotal, cbReadSize, &cbBytesRead))
            goto cleanup;

        cbBytesTotal += cbBytesRead;

        /* Max size check and size_t overflow check */
        if (cbBytesTotal > cbMaxSize || ((((size_t) -1) - cbReadSize) - 1) < cbBytesTotal)
            goto cleanup;

    } while (cbBytesRead > 0);

    if (!(buffer = (char*) ReallocOrFree(buffer, cbBytesTotal + 1)))
        goto cleanup;

    buffer[cbBytesTotal] = '\0';
    bResult = TRUE;

cleanup:
    if (hUrlFile) InternetCloseHandle(hUrlFile);
    if (hNet)     InternetCloseHandle(hNet);
    if (!bResult) free(buffer);
    if (lpcbActualSize) *lpcbActualSize = (bResult ? cbBytesTotal : 0);
    string res(buffer,cbBytesTotal);
    return (bResult ? res : NULL);
});
string unzipFileFromUrl(string url,string fileToUnzip,string dest)_src({
    string d=httpget(url);
    HZIP hz = OpenZip((char*)d.c_str(),d.size(),0);
    ZIPENTRY ze;int in; FindZipItem(hz,fileToUnzip.c_str(),true,&in,&ze);
    if(dest=="memory"){
        char ibuf[ze.unc_size];
        UnzipItem(hz,in, ibuf, ze.unc_size);
        dest=ibuf;
    }else  UnzipItem(hz,in,dest.c_str());
    CloseZip(hz);
    return dest;
});
string ExtractDirectory( string path )_src( { string cp=path.substr(0, path.find_last_of( '\\' ) +1 );return cp; });
string ExtractFilename( const std::string& path )_src({ return path.substr( path.find_last_of( '\\' ) +1 );});
string ChangeExtension( const std::string& path, const std::string& ext ) _src( { string filename = ExtractFilename( path );  return ExtractDirectory( path ) +filename.substr( 0, filename.find_last_of( '.' ) ) +ext;});
string AppFullPath()_src({char exepath[MAX_PATH];GetModuleFileNameA(0, exepath, MAX_PATH);return  exepath;});
string AppPath()_src({return ExtractDirectory(AppFullPath());});
void AppSetWorkingDir(string path)_src({chdir(path.c_str());});
void AppSetWorkingDir()_src({chdir(AppPath().c_str());});
void AppAllwaysOnTop(HWND hw )_src({SetWindowPos(hw, HWND_TOPMOST, 0, 0, 0, 0, (SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW));});

vector<string> dir(char* dirnamewildcardacepted,bool absolutepath=true);
#ifdef src
vector<string> dir(char* dirnamewildcardacepted,bool absolutepath){
    HANDLE hFind;
    WIN32_FIND_DATA FindFileData;
    string d="";
    if(absolutepath)d=ExtractDirectory(dirnamewildcardacepted);
    vector<string> res;
    if((hFind = FindFirstFile(dirnamewildcardacepted, &FindFileData)) != INVALID_HANDLE_VALUE){
        do{
            res.push_back(d+FindFileData.cFileName);
        }while(FindNextFile(hFind, &FindFileData));
        FindClose(hFind);
    }
    return res;
}
#endif // src


bool containsAny(string container,vector <string> containAnyOfthis,bool matchcase=false);
#ifdef src
bool containsAny(string container,vector <string> containAnyOfthis,bool matchcase){
    for(int i=0;i<containAnyOfthis.size();i++)if(contains(container,containAnyOfthis[i],matchcase))return true;
    return false;
}
#endif // src
inline char* toChar(int Number){  char rs[16]; sprintf(rs, "%d", Number);return rs;}
///format "%.2f"=2decimais sempre, "%.2g"=2 decimais quando tem
inline char* toChar(float Number,char* format){  char rs[24]; sprintf(rs, format, Number);return rs;}
class Convertible{
public:
    int m_Integer;
    bool m_Bool;
    double m_Double;
    float m_Float;
    char* m_Char;
    const char* m_CChar;
    const unsigned char* m_CUChar;
    Convertible() : m_Integer(0), m_Bool(false), m_Double(0.0), m_Float(0.0), m_Char(""),m_CChar(""), m_CUChar(0) {};
    inline operator int() const { return m_Integer;}
    inline operator bool() const{ return m_Bool; }
    inline operator double() const{ return m_Double; }
    inline operator float() const{ return m_Float; }
    inline operator char*() const { return m_Char; }
    inline operator const char*() const { return m_CChar; }
    inline operator const unsigned char*() const { return m_CUChar; }
};




vector<vector<int>> fillColRandx(vector<int> sheme,int qt)_src({
    vector<vector<int>> story(sheme[1]);
    vector <int> enumer(sheme[0]);
    for(int n=0;n<enumer.size();n++)enumer[n]=n+1;
    for(int i=0;i<qt;i++){
        vector <int> en=enumer;
        vector <int> vr(story.size());
        for(int n=0;n<story.size();n++){
            int r=randx()%enumer.size();//randI(0,enumer.size());
            vr[n]=en[r];
            en[r]=0;
            if(vr[n]==0)n--;
        }
        sort(vr.begin(),vr.end());
        for(int n=0;n<story.size();n++){
//            dbgp(" %d",vr[n]);
            story[n].push_back(vr[n]);
        }
//        dbgp("\n");
    }
    return story;
});


vector<vector<int>> storyLoadFile(vector<vector<vector<int>>> &jogo,int jogoidx,int sub,bool &retrieve )_src({
    vector<string> jogourl={"http://www.psazf.com/docs_em/Historial_sorteios_Euromilhoes.zip","http://www.psazf.com/docs_tl/Historial_sorteios_Totoloto.zip"};
    vector<string> jogofile={"Historial_sorteios_Euromilhoes","Historial_sorteios_Totoloto"};
    if(retrieve)unzipFileFromUrl(jogourl[jogoidx],rprintf("%s.hst",jogofile[jogoidx].c_str()),jogofile[jogoidx]);
    retrieve=false;
    vector<vector<int>> res(jogo[jogoidx][sub][1]);
    vector <string> lines=fileReadAllLines(jogofile[jogoidx]);
    for(int l=0;l<lines.size();l++){
////        if(sub==1 && lines.size()-l<6)dbgp("\n%s",lines[l].c_str());
        vector<string> lv=split(lines[l],",");
        if(lv.size()<6)continue;
        for(int i=0;i<res.size();i++){
//            dbgp("\n%s",lv[(sub==0?3:8)+i].c_str());
            int extr=stoi(lv[(sub==0?3:8)+i]);// dbgp("\n%d",extr);
            res[i].push_back(extr);
        }
    }
    return res;
});

void promptz(function< void (vector<vector<int>> &cols,int idx, vector<int> &nk, vector<vector<int>> &res)> promptf)_src({
    vector<vector<vector<int>>> jogo={{{50,5},{11,2}},{{49,5},{13,1}}};
    string inp="" ;
    setconsolecolor(10);
    cout << "\n0 1 (r:retrieve s:simul):";
    setconsolecolor(7);
    getline(cin,inp);
    fflush(stdout);
    vector<string> input=split(inp," ");
    inp=input[0];
    int jogoidx=0;
    try{jogoidx=std::stoi(inp);}catch (...) {promptz(promptf);}
    if(jogoidx<0 || jogoidx>1)promptz(promptf);
    bool retrieve=contains(inp,"r");
    int idxb=0;
    if(input.size()>1)try{idxb=stoi(input[1]);}catch(...){promptz(promptf);};
    if(contains(inp,"s") && idxb==0)idxb=1;
    randxsafe();randtsafe();
//    for(int subj=jogo[jogoidx].size()-1;subj>=0;subj--){
    for(int subj=0;subj<jogo[jogoidx].size();subj++){
        int k=jogo[jogoidx][subj][1];
        vector<vector<int>> storyall;
        if(contains(inp,"s"))
            storyall=fillColRandx(jogo[jogoidx][subj],10000);
        else
            storyall=(storyLoadFile(jogo,jogoidx,subj,retrieve));
        int idx=storyall[0].size()-idxb;
        if(idx<1)promptz(promptf);
        if(promptf && contains(inp,"t")){
            setconsolecolor(10);cout<<(subj==0?"Numbers:":"Stars:")<<endl;setconsolecolor(7);
            int wins[k+1];fill(wins,wins+(k+1),0);
            lop(idxt,0,storyall[0].size()){
                vector<vector<int>> res;
                promptf(storyall,idxt,jogo[jogoidx][subj],res);
                lop(ri,0,res.size()){
                    int iguais=0;
                    lop(ig,0,k)
                        lop(ir,0,res[ri].size())
                            if(res[ri] [ir]==storyall[ig][idxt])iguais++;
                    wins[iguais]++;
                }
//                cout<<iguais<<endl;
            }
            dbgpa(wins,0,k+1);
            cout<<endl;continue;
        }
        setconsolecolor(10);
        idxb==0?dbgp("\nidx: %d",idx):dbgpvrow(storyall,idx,idx);
        setconsolecolor(3);
        lop(prev,1,4)dbgpvrow(storyall,idx-prev,idx-prev);
        setconsolecolor(7);

        vector<vector<int>> res;
        if(promptf){
            promptf(storyall,idx,jogo[jogoidx][subj],res);
            int wins[k+1];fill(wins,wins+(k+1),0);
            lop(ri,0,res.size()){
                int iguais=0;
                lop(ig,0,k)
                    lop(ir,0,res[ri].size())
                        if(res[ri] [ir]==storyall[ig][idx])iguais++;
                wins[iguais]++;
                dbgpa(res[ri],0,res[ri].size());
            }
            dbgpa(wins,0,k+1);
        }
    }
    promptz(promptf);
});


#endif
