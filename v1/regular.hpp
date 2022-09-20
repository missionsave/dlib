#ifndef REGULAR_HPP_INCLUDED
#define REGULAR_HPP_INCLUDED

#include <vector>
#include <string>

#define cot(var) cout<<#var<<" "<<var<<endl;

//#include <boost/predef.h>

#include "Escape_Sequences_Colors.h"

using namespace std;

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned long ulong;
typedef unsigned long long ullong;
typedef unsigned long long ull;

typedef vector<int> vint;
typedef vector<vector<int>> vvint;
typedef vector<vector<vector<int>>> vvvint;
typedef vector<vector<vector<vector<int>>>> vvvvint;
typedef vector<vector<vector<vector<vector<int>>>>> vvvvvint;
typedef vector<short> vshort;
typedef vector<vector<short>> vvshort;
typedef vector<ushort> vushort;
typedef vector<char> vchar;
typedef vector<vector<char>> vvchar;
typedef vector<uchar> vuchar;
typedef vector<vector<uchar>> vvuchar;
typedef vector<string> vstring;
typedef vector<vector<string>> vvstring;
typedef vector<double> vdouble;
typedef vector<float> vfloat;
typedef vector<vector<float>> vvfloat;
typedef vector<vector<vector<float>>> vvvfloat;
typedef vector<vector<vector<vector<float>>>> vvvvfloat;
typedef vector<bool> vbool;
typedef vector<vector<bool>> vvbool;
typedef vector<vector<vector<bool>>> vvvbool;
typedef vector<vector<vector<vector<bool>>>> vvvvbool;
typedef vector<long> vlong;
typedef vector<vector<long>> vvlong;


template <typename  T> void dbg(T current);
template <typename  T,typename... remaining>void dbg(T current,remaining... params){dbg(current); dbg(","); dbg(params...);}

void dbgp(char * format, ...);

#define dbgpvrow(vs,idx,text_)({std::stringstream result;result<<(text_);result<<" "; lop(i_,0,vs.size()-1){result<<i_; result<<":";result << vs[i_][idx];result <<" ";}result<<(vs.size()-1); result<<":"; result << vs[vs.size()-1][idx];dbgp("\n%s",result.str().c_str());})

#define dbgv(args...){ dbg("\n"); dbg(#args);dbg(": ");dbg(args);}

#define dbgpa(vec,from,to){ dbg("\n"); lop(_i,from,to){dbg(vec[_i]); dbg(" ");} }

#define dbgpai(vec,from,to){ dbg("\n"); lop(_i,from,to){printf("%d:",_i); dbg(vec[_i]); dbg(" ");} }

#define dstrm(sname,vec,from,to){ sname<<"\n"; lop(_i,from,to){sname<<(vec[_i])<<" ";} }

#define dbgvecall(vec,...) { dbg("\n"); lop(i_,0,vec.size()){dbg(vec[i_]); dbg(" ");} }

#define vraw(vec) &vec[0]
#define lop(var,from,to)for(int var=(from);var<(to);var++)

#define rprintf( ... )({ char buffer[256]; sprintf (buffer, __VA_ARGS__);  buffer; })

//voidToFunc(evclick,int)(1);
#define voidToFunc(voidf,...) ( ( void(*)(__VA_ARGS__)) voidf )
#define voidToFuncsafe(voidf) reinterpret_cast<void(*)()>(voidf)

#define pausa getchar();

#define incrVar(var,ammount,boundDown,boundUp){var+=ammount;if(var>boundUp)var=boundUp;if(var<boundDown)var=boundDown;}






///	cout << FBLU("I'm blue.") << endl;
///	cout << BOLD(FBLU("I'm blue-bold.")) << endl;
#ifndef _COLORS_
#define _COLORS_

/* FOREGROUND */
#define RST  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST
#define FWHT(x) KWHT x RST

#define BOLD(x) "\x1B[1m" x RST
#define UNDL(x) "\x1B[4m" x RST

#endif  /* _COLORS_ */









#endif // REGULAR_HPP_INCLUDED
