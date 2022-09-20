#include "math.hpp"
#include "timef.hpp"
#include <boost/predef.h>

//~ #include <windows.h>
//#include <iostream>
#include <random>
//#include <chrono>

#define mathSigmoidLutSCALE 400000.0f
#define mathSigmoidLutRESOLUTION (2097151*32)
#define mathSigmoidLutMIN -RESOLUTION / SCALE
#define mathSigmoidLutMAX RESOLUTION / SCALE
vfloat mathSigmoidLut;//=vfloat(mathSigmoidLutRESOLUTION + 1);
void mathSigmoidLutInit(void) {
	if(!mathSigmoidLut.empty())return;
	mathSigmoidLut=vfloat(mathSigmoidLutRESOLUTION + 1);
    int i;
    for (i = 0; i < mathSigmoidLutRESOLUTION + 1; i++) {
        mathSigmoidLut[i] =  (1.0 / (1.0 + exp(-i / mathSigmoidLutSCALE)));
    }
}

//float mathRound(float val, int dp) {
//    int charsNeeded = 1 + snprintf(NULL, 0, "%.*f", dp, val);
//    char *buffer = malloc(charsNeeded);
//    snprintf(buffer, charsNeeded, "%.*f", dp, val);
//    float result = atof(buffer);
//    free(buffer);
//    return result;
//}


unsigned long long mathPow2a[64]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216,33554432,67108864,134217728,268435456,536870912,1073741824,2147483648,4294967296,8589934592,17179869184,34359738368,68719476736,137438953472,274877906944,549755813888,1099511627776,2199023255552,4398046511104,8796093022208,17592186044416,35184372088832,70368744177664,140737488355328,281474976710656,562949953421312,1125899906842624,2251799813685248,4503599627370496,9007199254740992,18014398509481984,36028797018963968,72057594037927936,144115188075855872,288230376151711744,576460752303423488,1152921504606846976,2305843009213693952,4611686018427387904,9223372036854775808};
unsigned long long bit[64]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216,33554432,67108864,134217728,268435456,536870912,1073741824,2147483648,4294967296,8589934592,17179869184,34359738368,68719476736,137438953472,274877906944,549755813888,1099511627776,2199023255552,4398046511104,8796093022208,17592186044416,35184372088832,70368744177664,140737488355328,281474976710656,562949953421312,1125899906842624,2251799813685248,4503599627370496,9007199254740992,18014398509481984,36028797018963968,72057594037927936,144115188075855872,288230376151711744,576460752303423488,1152921504606846976,2305843009213693952,4611686018427387904,9223372036854775808};

vector<int>  mathFastModulofill(int div,int qt){
	vector<int> res(qt);
	lop(i,0,qt){
		res[i]=i%div;
	}
	return res;
}

int mathForecastStat(int* vals,int idx,int ampStart,int ampEnd,int lb){
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
};
namespace g{enum{x1,x2,x3,y1,y2,y3,z1,z2,z3,r1,g1,b1,r2,g2,b2};};
#define glcrefsys(k)
#define glcref(vals) float & x1=vals[g::x1];float & y1=vals[g::y1];
vector<float> mathTrigExpand(vector<float> indexes={},int x2sizemore=100000){
    vector<float> res=indexes;
    glcref(res)
//    yt=ys+mathTrigRectFrt(ang,(xs-xt));
    return res;
}


//#if BOOST_OS_LINUX
void randsafe(int seed){ if(seed==-1)srand( now()  );else srand(seed);  }
//#endif

#if BOOST_OS_WINDOWS
//void randsafe(int seed){ if(seed==-1)srand(GetTickCount()+GetCurrentThreadId());else srand(seed);  }
#endif

void randGen(vint &rands,int _min,int _max){
//	typedef std::chrono::high_resolution_clock Clock;
//	typedef std::chrono::duration<double> sec;
//	Clock::time_point t0 = Clock::now();
	const int N = 10000000;
	rands=vint(N);
	typedef std::minstd_rand G;
	G g;
	typedef std::uniform_int_distribution<> D;
	D d(_min, _max);
	int c = 0;
	for (int i = 0; i < N; ++i) {
		rands[i]= d(g);
	}
//	Clock::time_point t1 = Clock::now();
//	std::cout << N/sec(t1-t0).count() << " random numbers per second.\n";
}


mt19937 randx_;
unsigned int randx(){return randx_();};


float mathEma(vector<float> &vals,int range,float previousEma){
	if(previousEma==0){
		return mathAvg(vals,vals.size()-range,vals.size());
	}
	 return (vals.back()*(2.0/(range+1))+previousEma*(1-(2.0/(range+1))));
}


float mathSmma(vector<float> &vals,int range,float previoussmma){
	if(previoussmma==0){
		return mathAvg(vals,vals.size()-range,vals.size());
	}
		float v=previoussmma*range;
		v= (v-previoussmma+vals.back()) / ((float)range);
		return v;
}

float mathMACD(vector<float> &vals, float &outMACDSignal, float &outMACDHist,int maslow, int mafast, int smasignal){
	float mafastv=0;
	float maslowv=0;
	vfloat sma(smasignal);
	lop(i,0,smasignal){
		int ri=smasignal-i;
		vfloat v=vfloat(vals.begin(),vals.end()-ri);
		mafastv=mathSmma(vals,mafast,mafastv);
		maslowv=mathSmma(vals,maslow,maslowv);
		sma[i]=maslowv-mafastv;
	}
	float outMACD=sma.back();
	outMACDSignal=mathAvg(sma,0,sma.size());
 outMACDHist=outMACD-outMACDSignal;
	return outMACD;
}


float mathMyfunc(vector<float> vals,int sma1, int sma2, int sma3){
	float sma1v=mathAvg(vals,vals.size()-sma1,vals.size());
	float sma2v=mathAvg(vals,vals.size()-sma2,vals.size());
	float sma3v=mathAvg(vals,vals.size()-sma3,vals.size());
	float out=sma2v/sma1v*sma3v;///how to calculate here
	return out;
}

float mathRsi(vector<float> vals,int from, int to){
	vector<float> prices=	vector<float>(vals.begin()+from,vals.begin()+to);

	double sumGain = 0;
	double sumLoss = 0;
	for (int i = 1; i < prices.size(); i++){
	float difference = prices[i] - prices[i - 1];
	if (difference >= 0){
			sumGain += difference;
			}
			else{
			sumLoss -= difference;
	}
	}
	sumGain/=(float)prices.size();
	sumLoss/=(float)prices.size();
	if (sumGain == 0) return 0;
//	        if (mathAbs(sumLoss) < Tolerance) return 100;
	float relativeStrength = sumGain / sumLoss;
	return 100.0 - (100.0 / (1 + relativeStrength));
}
