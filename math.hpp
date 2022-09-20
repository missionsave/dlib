#ifndef MATH_HPP_INCLUDED
#define MATH_HPP_INCLUDED
//https://gcc.gnu.org/onlinedocs/gcc-4.1.2/gcc/Other-Builtins.html
//http://www.azillionmonkeys.com/qed/asmexample.html
///https://graphics.stanford.edu/~seander/bithacks.html#ParityWith64Bits

#include "regular.hpp"
#include <cmath>

#define CHAR_BIT 8

//float mathRound(float val, int dp);

extern unsigned long long bit[64];
extern unsigned long long mathPow2a[64];
vector<int>  mathFastModulofill(int div,int qt);


#define mathRand01 (bool)mathRound( ((double) rand() / (RAND_MAX)) ,0)

#define mathBinaryRep(_var_)({string binrep; for(int i_= sizeof((_var_))*CHAR_BIT;i_--;){binrep+= ('0'+ (((_var_) >>i_)&1));} binrep;})

#define floatEqual(f,v)({float f1=f,f2=v; (abs(*(int*)&f1 - *(int*)&f2)<2)?1:0; })


#define toByteFbigendian(hs,otp)*((unsigned char *)&otp+3)=hs++; *((unsigned char *)&otp+2)=hs++; *((unsigned char *)&otp+1)=hs++; *((unsigned char *)&otp+0)=hs++;

#define bitGet(bitarray,index)((bitarray[(index)/8] >> 7-((index) & 0x7)) & 0x1 )
#define bitSet(bitarray,index,value)( bitarray[(index)/8] = bitarray[(index)/8] | (value & 0x1) << 7-((index) & 0x7) )

#define bitreversei(arr,idx)({arr[idx]==0?arr[idx]=1:arr[idx]=0; arr[idx];})
#define bitreverse(val)((val)==0?1:0)

#define rotateY(val,qt,min,max) (max-min+qt+val-min)%(max-min)+min
#define rotateYa(thename,arr,from,to,qt,min,max)thename[to];{lop(_ari,from,to)thename[_ari]=rotateY(arr[_ari],qt,min,max);}

#define mathStepsBetween(A,B,steptotal) ({ (( (B)-(A))/steptotal); })

#define mathRadToDec(x) ((x)/0.01745329251994329576923690768489)
#define mathDecToRad(x) ((x)*0.01745329251994329576923690768489)
#define mathTrigRectFrt(angulo,down) (tan( mathDecToRad(angulo) )*(down))
#define mathTrigRectDown(angulo,frt) ((frt)/tan( mathDecToRad(angulo) ) )
#define mathTrigRectAng(down,frt) mathRadToDec(atan((frt)/(down)))
#define mathTrigRectHip(angulo,frt)  ((frt)/sin( mathDecToRad(angulo) ) )
#define mathTrigRectHipD(angulo,down)  ((down)/cos( mathDecToRad(angulo) ) )
#define mathTrigRectHipC(down,frt)  (down)==0?abs(frt):({float mth_ = (frt)/(down); abs(down) * sqrtf(1 + mth_*mth_); })

#define mathNumscale(num,factorx,min,max,midletarget)({float _mnsfd = (factorx)/2.0-(midletarget); float _mnsfactor = (float)(factorx) / ((max) - (min));( ((num) - (min)) * _mnsfactor - _mnsfd);})
#define mathNumdescale(num,factorx,min,max,midletarget)({float _mndsfd = (factorx)/2.0-(midletarget); float _mndsfactor = (float)(factorx) / ((max) - (min));( ((num) + _mndsfd) / _mndsfactor + (min) );})
#define mathFactorial(n)({unsigned long long mathFactorialf=1;lop(mathFactoriali,1,n+1) mathFactorialf*=mathFactoriali; mathFactorialf;})

//#define mathRound(i_,nmb_)  asm {asm fld nmb_   asm fistp i_}
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
#define mathSigmoidf(x)  1.0 / (1 + mathFastExp(-(x)))
#define mathSigmoid(x)  1.0 / (1 + exp (-(x)))
void mathSigmoidLutInit(void);
extern vfloat mathSigmoidLut;
#define mathSigmoidLutf(x) ({((x) < 0)?1.0f-mathSigmoidLut [(int)(-(x) * 400000.0f + 0.5f)]:mathSigmoidLut[(int)((x) * 400000.0f + 0.5f)];})


//d==0=1, d==1=2, d==2=4, d==3=8,
#define Modulofast(n,d) ({ n & ((1U << d) - 1); })

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

int mathForecastStat(int* vals,int idx,int ampStart,int ampEnd,int lb);
float mathRsi(vector<float> vals,int from, int to);

float mathEma(vector<float> &vals,int range=12,float previousEma=0);

float mathSmma(vector<float> &vals,int range,float previoussmma);

///vals.size must be biguer than sma bigger val
float mathMACD(vector<float> &vals, float &outMACDSignal, float &outMACDHist,int maslow=12, int mafast=26, int sma3=9);

float mathMyfunc(vector<float> vals,int sma1=12, int sma2=26, int sma3=9);

#define mathProbNearInt(sname,probAc,from,to) struct {float val; int range;}sname; { float near_=1; lop(_nearidx,(from),(to)){	float nn_=abs( ((probAc)*_nearidx)-floorf((probAc)*_nearidx+.5));	if(near_>nn_){near_=nn_;sname.range=_nearidx; sname.val=(probAc)*_nearidx;} } }


void randsafe(int seed=-1);
void randGen(vint &rands,int _min,int _max);
unsigned int randx();


static inline int isnan_(float f){
    union { float f; uint32_t x; } u = { f };
    return (u.x << 1) > 0xff000000u;
}

#endif // MATH_HPP_INCLUDED
