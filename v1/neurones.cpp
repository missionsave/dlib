//testar velocidade de malloc versus fixed arrays
//tirar da classe, isolar o maximo

#include <iostream>
#include <fstream>
#include <sstream>
#include <experimental/filesystem>
#include "math.hpp"
#include "comb.hpp"
#include "arrayf.hpp"
#include <numeric>
bool fileExist(string fname);

#include "neurones.hpp"
#define RNDF ({ float rnd=0; while(rnd<1 && rnd>-1)rnd=(((float)rand()-(float)rand())/(RAND_MAX/1.7)); rnd;})

//mathSigmoid SigmoidLutf



#define neuralForwardPass(input,_ni) for(jj=_ni;jj<hij;jj++){x=0;for(ii=0;ii<_ni;ii++)x+=(input[ii]*w[ii][jj]);y[jj]= SigmoidLutf(isnan(x-wt[jj])?0:x-wt[jj]); } for (kk=hij; kk<hik; kk++ ){x=0; for(jj=_ni; jj<hij; jj++ )x+=(y[jj]*w[jj][kk]); y[kk]=SigmoidLutf(isnan(x-wt[kk])?0:x-wt[kk]);}

// #define neuralForwardPass(input,_ni) for(jj=_ni;jj<hij;jj++){x=0;for(ii=0;ii<_ni;ii++)x+=(input[ii]*w[ii][jj]);y[jj]= SigmoidLutf( (x-wt[jj]) ); } for (kk=hij; kk<hik; kk++ ){x=0; for(jj=_ni; jj<hij; jj++ )x+=(y[jj]*w[jj][kk]); y[kk]=SigmoidLutf( (x-wt[kk]) );}

// #define SigmoidLutSCALE 400000.0f 
// #define SigmoidLutRESOLUTION (2097151*32)
#define SigmoidLutSCALE 8192.0f
#define SigmoidLutRESOLUTION (5000000)
#define SigmoidLutMIN -SigmoidLutRESOLUTION / SigmoidLutSCALE
#define SigmoidLutMAX SigmoidLutRESOLUTION / SigmoidLutSCALE
#define SigmoidLutfs(x) ({((x) < 0)?1.0f-SigmoidLut [(int)(-(x) * SigmoidLutSCALE + 0.5f)]:SigmoidLut[(int)((x) * SigmoidLutSCALE + 0.5f)];})

#define SigmoidLutf(x) ({  SigmoidLutMAX<=(x)?1: (SigmoidLutMIN>=(x)?0: (((x) < 0)?1.0f-SigmoidLut [(int)(-(x) * SigmoidLutSCALE + 0.5f)]:SigmoidLut[(int)((x) * SigmoidLutSCALE + 0.5f)] ));   })

// #define SigmoidLutf(x) ({  SigmoidLutMAX<=(x)?1: (SigmoidLutMIN>=(x)?0: (((x) < 0)?1.0f-SigmoidLut [(int)(-(x) * SigmoidLutSCALE + 0.5f)]:SigmoidLut[(int)((x) * SigmoidLutSCALE + 0.5f)] ));   })

// #define SigmoidLutf(x) ({  
// SigmoidLutMAX<=(x)
// 1 else
	// if(SigmoidLutMIN>=(x))
	// 0
	// else 
	// if(((x) < 0))
	// 1.0f-SigmoidLut [(int)(-(x) * SigmoidLutSCALE + 0.5f)]
	// else
		// SigmoidLut[(int)((x) * SigmoidLutSCALE + 0.5f)] ));   })

// float SigmoidLutf(float x){
	// if(SigmoidLutMAX<=(x)){
	
	// }else{
	// }
// }


vfloat SigmoidLut;
void SigmoidLutInit(void) {
	if(!SigmoidLut.empty())return;
	SigmoidLut=vfloat(SigmoidLutRESOLUTION + 1);
    int i;
    for (i = 0; i < SigmoidLutRESOLUTION + 1; i++) {
        SigmoidLut[i] =  (1.0 / (1.0 + exp(-i / SigmoidLutSCALE)));
    }
}
//void SigmoidLutInit(void){
//	if(!SigmoidLut.empty())return;
//	SigmoidLut=vfloat(SigmoidLutRESOLUTION + 1);
//    int i;
//    for (i = 0; i < SigmoidLutRESOLUTION + 1; i++) {
//        SigmoidLut[i] =  (1.0 / (1.0 + exp(-i / SigmoidLutSCALE)));
//    }
//}



#include <vector>
typedef std::vector<float> vfloat;
typedef std::vector<std::vector<float>> vvfloat;

neurone::~neurone(){
//dbgv("delete");
	free(		wt);
	lop(i,0,hij)
		free(		w[i]);
	free(		w);
	free(y);
	free(dx);
	free(dy);
}

void neurone::resetWeights(){
		lop(i,0,hij){
			wt[i]=RNDF;
			// cot(wt[i]);
			lop(ik,0,hik){
				w[i][ik]=RNDF;
				// cot(w[i][ik]);
			}
		}
};

neurone::neurone(int Ni,int No,int Nh, string identifier,string folder,bool autoload){SigmoidLutInit();
	ni=Ni,no=No,nh=Nh;
	hij=ni+nh;
	hik=hij+no;
	if(wt){
		

	}else{
		wt=(float *)malloc(hik * sizeof(float));
		w=(float **)malloc(hij * sizeof(float *));
		lop(i,0,hij)
			w[i]=(float *)malloc(hik * sizeof(float));

		y=(float *)malloc(hik * sizeof(float));
		dx=(float *)malloc(hik * sizeof(float));
		dy=(float *)malloc(hik * sizeof(float));

//srand( 29310); randsafe
	if(identifier==""){
		resetWeights();
		return;
	}
	
	
		//CREATE DIR
		// filesystem::path path(pathd);
		experimental::filesystem::create_directories(folder);
		// mdir(folder);
	
		stringstream strm;
		strm<<(folder==""?"":(folder+"/"));
		strm<<identifier<<"_"<<ni<<"_"<<no<<"_"<<nh<<".ntw";
		filename=strm.str();
		fileExists=fileExist(filename);
//	 dbgv(filename,fileExits(filename));

	if(!autoload){
		resetWeights();
	return;}


		ifstream in(filename,std::ios::binary);
		if(in.good()){
//				dbgv("nload",filename);
//			getchar();
			lop(i,0,hik)in.read((char*)(&wt[i]), sizeof(float));
			lop(i,0,hij){
				lop(ik,0,hik)in.read((char*)(&w[i][ik]), sizeof(float));
			}
			// dbgv("neuron loaded");
      in.close();
		}else{
			resetWeights();
		}
	}


}
void neurone::save(){
		// AppSetWorkingDir();
		ofstream in(filename,std::ios::binary);
		// cot(filename);
		// cot(in.good()); 
		// pausa
		if(in.good()){
				// dbgv("nsave",filename)
//				getchar();
			lop(i,0,hik)in.write((char*)(&wt[i]), sizeof(float));
			lop(i,0,hij){
				lop(ik,0,hik)in.write((char*)(&w[i][ik]), sizeof(float));
			}
      in.close();
		}

}

//need int jj,ii,kk;float x;
#define calc0(inp)({neuralForwardPass(inp,ni);y[hij];})

///cuidado com este se deve ter -no
vfloat neurone::calc(vfloat &inp){
//dbgpa(inp,0,16);
	return calc( &inp[inp.size()-ni ] );
}
vfloat neurone::calc(float *inp){
	vfloat res(no);
//dbgv(ni,no,nh,hij,hik);
//getchar();
	int  jj,ii,kk;	float x;
	neuralForwardPass(inp,ni);
//getchar();
	for (int k=hij; k<hik; k++ )res[k-hij]=y[k];
	return res;
}



int neurone::traingradual(float maxerror,vvfloat &inputs){
	vvfloat inp;

	int gits=0;
	lop(i,1,inputs.size()){
		inp=vvfloat(inputs.begin(),inputs.begin()+i);
		gits+=trainf(maxerror,inp);
	}
	return gits;
}

int neurone::trainf(float maxerror,vvfloat &inputs){
//	return trainfm(netw, inputs,maxerror);
    int i,j,k;
		int jj,ii,kk;float x;
    int qt=inputs.size();

int le;
bool notyet=false;
bool noneedtotrain;
//float errol;

#define xtrain(num_input,num_h,hij,hik) {\
neuralForwardPass(inputs[le],num_input);\
	for (k=hij; k<hik; k++ ){\
		errol=(y[k] - inputs[le] [k-num_h]);\
		noneedtotrain=(errol<0?-errol:errol)>maxerror;\
		if(noneedtotrain)notyet=true;\
	}\
	if(!noneedtotrain)continue;\
	for (k=hij; k<hik; k++ ){\
			dy[k] = y[k] - inputs[le] [k-num_h];\
			dx[k] = ( dy[k] ) * y[k] * (1-y[k]);\
			wt[k] -= ( lr * (dx[k] * (-1)) );\
	}\
	for(j=num_input; j<hij; j++ ){\
			dy[j] = 0;\
			for (k=hij; k<hik; k++ ){\
					dy[j] += ( dx[k] * w[j][k] );\
					w[j][k] -= ( lr * (dx[k] * y[j]) );\
			}\
			dx[j] = ( dy[j] ) * y[j] * (1-y[j]);\
			wt[j] -= ( lr * (dx[j] * (-1)) );\
	}\
	for (i=num_input; i--; )\
			for(j=num_input; j<hij; j++ ){\
					w[i][j] -= ( lr * (dx[j] * inputs[le] [i]) );\
			}	\
};

int it;
#define mtrain(_ni,_no,_nh) \
if(_ni==ni &&_no==no && _nh==nh){\
    for ( it = 0; it<its; it++ ){\
				notyet=false;\
        for(le=0;le<qt;le++){\
            xtrain(_ni,_nh,_ni+_nh,_ni+_nh+_no);\
        }\
				if(!notyet)break;\
    }return it;\
	};



//GENERATOR
//lop(i,2,64)lop(hi,2,64){
//	printf("mtrain(%d,1,%d) ",i,hi);
//}
//speedy's:

mtrain(10,1,150)
mtrain(10,1,100)

mtrain(5,1,40)
mtrain(6,1,40)
mtrain(7,1,40)
mtrain(6,1,2)
mtrain(7,1,3)

mtrain(32,1,16)
mtrain(8,1,32)
mtrain(6,1,6)
mtrain(32,1,32)
#if speed
mtrain(64,1,64)
mtrain(32,1,32)
mtrain(3,1,20)
mtrain(3,1,40)
mtrain(3,1,60)
mtrain(5,1,53)
mtrain(4,1,48)
mtrain(8,1,48)
mtrain(16,1,48)
mtrain(24,1,48)
mtrain(32,1,48)
mtrain(48,1,48)
mtrain(64,1,48)
mtrain(80,1,48)
mtrain(128,1,48)
mtrain(5,1,16)
mtrain(13,1,13)
mtrain(5,1,24)
mtrain(6,1,24)
mtrain(7,1,24)
mtrain(8,1,24)
mtrain(9,1,24)
mtrain(10,1,24)
mtrain(11,1,24)
mtrain(12,1,24)
mtrain(13,1,24)
mtrain(14,1,24)
mtrain(15,1,24)
mtrain(16,1,24)
mtrain(17,1,24)
mtrain(18,1,24)
mtrain(19,1,24)
mtrain(20,1,24)
mtrain(21,1,24)
mtrain(22,1,24)
mtrain(23,1,24)
mtrain(24,1,24)
mtrain(32,1,24)
mtrain(36,1,24)
mtrain(16,1,32)
mtrain(24,1,32)
mtrain(32,1,32)
mtrain(48,1,32)
mtrain(64,1,32)
mtrain(80,1,32)
mtrain(96,1,32)
mtrain(128,1,32)
mtrain(32,1,64)
mtrain(32,1,16)
mtrain(48,1,48)
//mtrain(30,1,30) mtrain(30,1,31) mtrain(30,1,32) mtrain(30,1,33) mtrain(30,1,34) mtrain(30,1,35) mtrain(30,1,36) mtrain(30,1,37) mtrain(30,1,38) mtrain(31,1,30) mtrain(31,1,31) mtrain(31,1,32) mtrain(31,1,33) mtrain(31,1,34) mtrain(31,1,35) mtrain(31,1,36) mtrain(31,1,37) mtrain(31,1,38) mtrain(32,1,30) mtrain(32,1,31) mtrain(32,1,32) mtrain(32,1,33) mtrain(32,1,34) mtrain(32,1,35) mtrain(32,1,36) mtrain(32,1,37) mtrain(32,1,38) mtrain(33,1,30) mtrain(33,1,31) mtrain(33,1,32) mtrain(33,1,33) mtrain(33,1,34) mtrain(33,1,35) mtrain(33,1,36) mtrain(33,1,37) mtrain(33,1,38) mtrain(33,1,24); mtrain(33,1,25); mtrain(33,1,26);
//mtrain(10,1,18) mtrain(10,1,19) mtrain(10,1,20) mtrain(10,1,21) mtrain(10,1,22) mtrain(10,1,23) mtrain(10,1,24) mtrain(10,1,25) mtrain(10,1,26) mtrain(11,1,18) mtrain(11,1,19) mtrain(11,1,20) mtrain(11,1,21) mtrain(11,1,22) mtrain(11,1,23) mtrain(11,1,24) mtrain(11,1,25) mtrain(11,1,26) mtrain(12,1,18) mtrain(12,1,19) mtrain(12,1,20) mtrain(12,1,21) mtrain(12,1,22) mtrain(12,1,23) mtrain(12,1,24) mtrain(12,1,25) mtrain(12,1,26) mtrain(13,1,18) mtrain(13,1,19) mtrain(13,1,20) mtrain(13,1,21) mtrain(13,1,22) mtrain(13,1,23) mtrain(13,1,24) mtrain(13,1,25) mtrain(13,1,26)
//mtrain(4,1,8)
//mtrain(4,1,9)
//mtrain(4,1,10)
//mtrain(4,1,11)
//mtrain(4,1,12)
//mtrain(4,1,13)
//mtrain(4,1,14)
//mtrain(4,1,15)
//mtrain(4,1,16)
//mtrain(4,1,17)
//mtrain(4,1,18)
//mtrain(5,1,8)
//mtrain(5,1,9)
//mtrain(5,1,10)
//mtrain(5,1,11)
//mtrain(5,1,12)
//mtrain(5,1,13)
//mtrain(5,1,14)
//mtrain(5,1,15)
//mtrain(5,1,16)
//mtrain(5,1,17)
//mtrain(5,1,18)
//mtrain(6,1,8)
//mtrain(6,1,9)
//mtrain(6,1,10)
//mtrain(6,1,11)
//mtrain(6,1,12)
//mtrain(6,1,13)
//mtrain(6,1,14)
//mtrain(6,1,15)
//mtrain(6,1,16)
//mtrain(6,1,17)
//mtrain(6,1,18) mtrain(6,1,36)
//mtrain(7,1,16)
//mtrain(7,1,32)
//mtrain(8,1,36)
//mtrain(9,1,36)
//mtrain(9,1,37)
//mtrain(32,1,32)
//mtrain(32,1,16)
//mtrain(16,1,32)
//mtrain(32,1,12)
//mtrain(20,1,40)
//
//
//
////printf("mtrain(%d,%d,%d); //WARNING number of inputs or outputs or hidden layer not fully compiled optimized!",num_input,num_output,num_h);
//
#endif // speed

mtrain(ni,no,nh)

return it;
}

scaler nscale;

void scaler::scale(vfloat &vals,float boundUp,float boundDown,float boundbox){
	lop(i,0,vals.size())vals[i]=
		mathNumscale (vals[i],boundbox,boundDown,boundUp,.5);
}
void scaler::deScale(vfloat&vals,float boundUp,float boundDown,float boundbox){
	lop(i,0,vals.size())vals[i]=
		mathNumdescale (vals[i],boundbox,boundDown,boundUp,.5);
}
void addContinuos(vvfloat &inputs,vfloat &inp,int ni,int no){
//	neuralAddContinuos(inputs,ni,no,inp,0,inp.size());
if(inp.size()<ni+no)return;
	int stf=inputs.size();
	int stsz=(inp.size())-(ni)-(0)-(no)+1;
	inputs.resize((stsz+stf),vfloat((ni)+(no)));
	lop(q_,0,stsz)
		lop(i_,0,(ni)+(no))inputs[q_+stf][i_]=inp[i_+q_+(0)];
}

#define neuralForwardPassc(input,_ni) float x; for(j=_ni;j<hij;j++){x=0;for(i=0;i<_ni;i++)x+=(input[le+i]*w[i][j]);y[j]= SigmoidLutf(x-wt[j]); } for (k=hij; k<hik; k++ ){x=0; for(j=_ni; j<hij; j++ )x+=(y[j]*w[j][k]); y[k]=SigmoidLutf(x-wt[k]);}
int neurone::traincontinuos(float maxerror,vfloat &inputs){
//	return trainfm(netw, inputs,maxerror);
    int i,j,k;
    int qt=inputs.size();

int le;
bool notyet=false;
bool noneedtotrain;
float errol;

#define xtrain(num_input,num_h,hij,hik) {\
neuralForwardPassc(inputs,num_input);\
	for (k=hij; k<hik; k++ ){\
		errol=(y[k] - inputs[le + k-num_h]);\
		noneedtotrain=(errol<0?-errol:errol)>maxerror;\
		if(noneedtotrain)notyet=true;\
	}\
	if(!noneedtotrain)continue;\
	for (k=hij; k<hik; k++ ){\
			dy[k] = y[k] - inputs[le + k-num_h];\
			dx[k] = ( dy[k] ) * y[k] * (1-y[k]);\
			wt[k] -= ( lr * (dx[k] * (-1)) );\
	}\
	for(j=num_input; j<hij; j++ ){\
			dy[j] = 0;\
			for (k=hij; k<hik; k++ ){\
					dy[j] += ( dx[k] * w[j][k] );\
					w[j][k] -= ( lr * (dx[k] * y[j]) );\
			}\
			dx[j] = ( dy[j] ) * y[j] * (1-y[j]);\
			wt[j] -= ( lr * (dx[j] * (-1)) );\
	}\
	for (i=num_input; i--; )\
			for(j=num_input; j<hij; j++ ){\
					w[i][j] -= ( lr * (dx[j] * inputs[le + i]) );\
			}	\
};

int it;
#define mtrain(_ni,_no,_nh) \
if(_ni==ni &&_no==no && _nh==nh){\
    for ( it = 0; it<its; it++ ){\
				notyet=false;\
        for(le=0;le<qt-_ni-_no;le++){\
            xtrain(_ni,_nh,_ni+_nh,_ni+_nh+_no);\
        }\
				if(!notyet)break;\
    }return it;\
	};



//GENERATOR
//lop(i,2,64)lop(hi,2,64){
//	printf("mtrain(%d,1,%d) ",i,hi);
//}
//speedy's:
mtrain(16,1,64)
mtrain(ni,no,nh)

return it;
}

float neurone::stfDevProbDistr(int nrange){
	int k=ni;
	float stdev;
	vint t(nrange,0);
	vfloat se(nrange);
	std::iota(se.begin(),se.end(),0);
//		dbgvecall(se);
	nscale.scale(se,0,nrange);
	vint a(k,0); vfloat ck(k,0);vfloat res(1);
	int ires;
	uint cvr=combVNextRange(nrange,k);
//	dbgv(cvr);
	lop(i,0,cvr){
//		dbgvecall(a);
		lop(ki,0,k)ck[ki]=se[a[ki]];
		res=calc(ck);
		nscale.deScale(res,0,nrange);
		ires=int(res[0]+.5f);
		if(ires<0)ires=0;
		if(ires>nrange-1)ires=nrange-1;
		t[ires]++;
		combVNextFastest(a,nrange,k);
	}
	stdev=mathStdevp(t,0,nrange);
//	dbgv( stdev); getchar();
	return stdev;
}

float neurone::stfDevProbDistrBin(int nrange){
	int k=ni;
	float stdev;
	vint t(nrange,0);
	vfloat se(nrange);
	iota(se.begin(),se.end(),0);
//		dbgvecall(se);
//	nscale.scale(se,0,nrange);
	vint a(k,0); vfloat ck(k,0);
	float res;
	int ires;
	int jj,ii,kk;float x;
	uint cvr=combVNextRange(nrange,k);
//	dbgv(cvr);
	lop(i,0,cvr){
//		dbgvecall(a);
		lop(ki,0,k)ck[ki]=se[a[ki]];
		res=calc0(ck);
//		nscale.deScale(res,0,nrange);
		ires=int(res+.5f);
		if(ires<0)ires=0;
		if(ires>nrange-1)ires=nrange-1;
		t[ires]++;
		combVNextFastest(a,nrange,k);
	}
//		dbgvecall(t);
	stdev=mathStdevp(t,0,nrange);
//	dbgv( stdev); //getchar();
	return stdev;
}
