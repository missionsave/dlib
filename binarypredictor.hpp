#include <bitset>
#include "math.hpp"
#include "neurones.hpp"

struct bpsimple{
	bool result;
	float resultf;
	string bitdata="";
	int ni=3; 
	int hidden=4;
	int lendata=9;
	int run(int index=0){ 
		if(bitdata.size()<lendata)return 0;
		bitdata=bitdata.substr(bitdata.size() -lendata); 
		int len=bitdata.size();
		// cot(len);
		vfloat fa;
		vvfloat fan;
		lop(i,0,len)fa.push_back(atof(bitdata.substr(i,1).c_str()));
		addContinuos(fan,fa,ni,1); 
		// cot(fa);
		// cot(fan);
		
		randsafe(65454643);
		
		neurone nr(ni,1,hidden); 
		nr.its=10000;
		int its; 
		its= nr.trainf(0.02,fan);
		// cot(its);
		vfloat tc=vfloat(fa.end()-ni,fa.end());
		float cres=nr.calc(tc)[0];
		
		result=mathRound(cres,0)==1?0:1; 
		// cot(result);
		return result; 
	}
};
struct binarypredictor{
	bool result;
	float resultf;
	string bitdata="10111101111001000101011111100101111110111110101011000001111100000011110011001001111000011100000000000110000100000111011101010000011100011011100100110100010000011111011100010111011000000111000100010110000111100011010011101001111000001111000011000011110000110001100101110011110000100001110010000110011100100011101110100010110110110100100010000011111111111110001000001100110000000100010011001101101111101100010000111010000111110000101011101111111110100100110010111011111111111100011001111000101110001010000111001110100001100111101101111110000100011";
	int qtbits=3;
	int qtbitstart=3;
	int lendata=15;
	int hidden=80;
	// int qtbits=3;
	// int qtbitstart=3;
	// int lendata=120;
	// int hidden=40;
	int deputados=1;
	vvstring ba;
	vvint na;
	vvfloat fa; 
	vvvfloat fan; //	vvfloat inp({ {0,0,0}, {0,1,1}, {1,0,1}, {1,1,0}});
	// neurone nr(2,1,3);
	// nr.its=3000;
	// vvfloat inp({ {0,0,0}, {0,1,1}, {1,0,1}, {1,1,0}});
	// nr.trainf(0.001,inp);
	// vfloat inpc({1,0});
	// vfloat ic=nr.calc(inpc);
	
	// vfloat res;
	int resn;
	
	vector<vector<neurone*>> nrs;
	
	struct nrcfg{
		int minhidden=32;
		int maxdatasize=500;
	};
	vector<nrcfg> ncfg;
	// vint minhid ={0,1,2,3,4,5,6,4,8,9,10,11,12};
	
 
	int run(int index=0){
	
		ba=vvstring(qtbits+1);
		na=vvint(qtbits+1);
		fa=vvfloat(qtbits+1);
		fan=vvvfloat(qtbits+1);
		// res=vfloat(qtbits+1);
		nrs=vector<vector<neurone*>>(qtbits+1);
		lop(bi,0,nrs.size())
			nrs[bi]=vector<neurone*>(deputados);
		
		
		ncfg=vector<nrcfg>(qtbits+1);
		ncfg[4].minhidden=32;
	
	
	
		// lendata=rand() % (60-19) + 19;
		// cot(lendata);
		// randsafe();
		if(bitdata.size() < lendata){
			////fill width random 
			while(lendata>bitdata.size()){
				bitdata=to_string( mathRand01 )+bitdata;
			}
		}
		// cot(bitdata);
		// pausa
		bitdata=bitdata.substr(bitdata.size() -lendata);
		// cot(bitdata);
		int len=bitdata.size();
		// cot(len);
		float medt=0;
		float medf=0;
		// if(len>500)
		lop(bi,qtbitstart,qtbits+1){
			int modl=len%bi;
			int nstart=modl+1;
			int nlen=len-modl-1; 
			// cot(modl);
			// cot(nstart);
			// cot(nlen); 
			string t=bitdata.substr(nstart,nlen);
			// cot(t);
			string tx=bitdata.substr(nstart,nlen-bi+1);
			// cot(tx);
			// cot(tx.size());
			int txqt=tx.size()/bi;
			// cot(txqt);
			ba[bi].reserve(txqt); 
			na[bi].reserve(txqt); 
			fa[bi].reserve(txqt); 
			for(int ti=0;ti<tx.size();ti+=bi){
				ba[bi].push_back(tx.substr(ti,bi));
				reverse(ba[bi].back().begin(),ba[bi].back().end());
				// cot(ba[bi].back());  
				std::bitset<16> bittxr(ba[bi].back()); 
				na[bi].push_back(bittxr.to_ulong());
				// cot(bittxr);
				// cot(na[bi].back());
				fa[bi].push_back( mathNumscale( na[bi].back(),1.0,0, mathPow2a[bi]-1,0.5 )  );
				// cot(fa[bi].back());
				// cot( mathNumdescale( fa[bi].back(),1.0,0, mathPow2a[bi]-1,0.5 ) );
			}
			
			//fill fan
			addContinuos(fan[bi],fa[bi],bi,1); 
			// cot(fan[bi]); 
			// pausa
			
			randsafe(7676776);
			// randsafe();
			
			//neurones
			float med=0;
			lop(di,0,deputados){
				nrs[bi][di]= new neurone(bi,1,hidden);
				// nrs[bi][di]= new neurone(bi,1,hidden,"fxeu","neurons" );
				// nrs[bi][di]= new neurone(bi,1,hidden ,"bit"+ to_string( len%bi )+ to_string(bi)+ to_string(di),"neurons");
				neurone &nr= *nrs[bi][di];
				// if(index==540)nr.save();
				// pausa
				nr.its=10000;
				int its;
				// cot(di);
				// cot(nr.filename);
				// if(di==1)
				its= nr.trainf(0.02,fan[bi]);
				// while(its==nr.its){
					// nr.resetWeights();
					// its= nr.trainf(0.02,fan[bi]);
					// cot(its);
				// }  
				// nr.save();
				// pausa
				// vfloat tc=fan[bi].back();
				vfloat tc=fan[bi][ fan[bi].size()-1 ];
				tc=vfloat(tc.begin()+1,tc.end());
				// cot(tc);
				float cres=nr.calc(tc)[0];
				// cot(cres);
				// cot(nr.errol);
				// cot(its);
				med+=cres;    
			}
			medf=med/(float)deputados;
			// cot(medf);
			//converte para num
			
			
			string tnext0=t.substr(t.size()-bi+1);
			string tnext1=tnext0+"1";
			tnext0+="0";
			// cot(tnext0);
			// cot(tnext1);
			string tnext0r=tnext0;
			string tnext1r=tnext1;
			reverse(tnext0r.begin(),tnext0r.end());
			reverse(tnext1r.begin(),tnext1r.end());
			bitset<8> bittnext0r(tnext0r);
			bitset<8> bittnext1r(tnext1r);
			// cot(bittnext0r.to_ulong());
			// cot(bittnext1r.to_ulong());
			float bittnext0rf=mathNumscale( bittnext0r.to_ulong(),1.0,0, mathPow2a[bi]-1,0.5 );
			float bittnext1rf=mathNumscale( bittnext1r.to_ulong(),1.0,0, mathPow2a[bi]-1,0.5 );
			float medc=nearest(medf,bittnext0rf,bittnext1rf);
			// cot(bittnext0rf);
			// cot(bittnext1rf);
			// cot(bi);
			// cot(medc);
			medt+=medc;
		} 
		medt/=(qtbits-(qtbitstart-1)); 
		// cot(medt);
		resultf=1.0-medf;
		// resultf=1.0-medt;
		result=mathRound(medt,0)==1?0:1;
		// cot((qtbits-(qtbitstart-1)));
		// cot(medt);
		// cot(result);
		return result;
	}
 

	bool nearest(float val,float test1, float test2){
		float t1=abs(val-test1);
		float t2=abs(val-test2);
		if(t1<t2)return 0;
		return 1;
	}  
};

struct binarypredictorv2{
	bool result;
	float resultf;
	string bitdata="10111101111001000101011111100101111110111110101011000001111100000011110011001001111000011100000000000110000100000111011101010000011100011011100100110100010000011111011100010111011000000111000100010110000111100011010011101001111000001111000011000011110000110001100101110011110000100001110010000110011100100011101110100010110110110100100010000011111111111110001000001100110000000100010011001101101111101100010000111010000111110000101011101111111110100100110010111011111111111100011001111000101110001010000111001110100001100111101101111110000100011";
	int qtbits=3;
	int qtbitstart=3;
	int lendata=15;
	int hidden=80;
	// int qtbits=3;
	// int qtbitstart=3;
	// int lendata=120;
	// int hidden=40;
	int deputados=1;
	vvstring ba;
	vvint na;
	vvfloat fa; 
	vvvfloat fan; //	vvfloat inp({ {0,0,0}, {0,1,1}, {1,0,1}, {1,1,0}});
	// neurone nr(2,1,3);
	// nr.its=3000;
	// vvfloat inp({ {0,0,0}, {0,1,1}, {1,0,1}, {1,1,0}});
	// nr.trainf(0.001,inp);
	// vfloat inpc({1,0});
	// vfloat ic=nr.calc(inpc);
	
	// vfloat res;
	int resn;
	
	vector<vector<neurone*>> nrs;
	
	struct nrcfg{
		int minhidden=32;
		int maxdatasize=500;
	};
	vector<nrcfg> ncfg;
	// vint minhid ={0,1,2,3,4,5,6,4,8,9,10,11,12};
	
	binarypredictorv2(){
		nrs=vector<vector<neurone*>>(qtbits+1);
		lop(bi,0,nrs.size())
			nrs[bi]=vector<neurone*>(deputados);
 
 
 }
	int run(int index=0){
	
		ba=vvstring(qtbits+1);
		na=vvint(qtbits+1);
		fa=vvfloat(qtbits+1);
		fan=vvvfloat(qtbits+1);
		// res=vfloat(qtbits+1);
		// nrs=vector<vector<neurone*>>(qtbits+1);
		// lop(bi,0,nrs.size())
			// nrs[bi]=vector<neurone*>(deputados);
		
		
		ncfg=vector<nrcfg>(qtbits+1);
		ncfg[4].minhidden=32;
	
	
	
		// lendata=rand() % (60-19) + 19;
		// cot(lendata);
		// randsafe();
		if(bitdata.size() < lendata){
			////fill width random 
			while(lendata>bitdata.size()){
				bitdata=to_string( mathRand01 )+bitdata;
			}
		}
		// cot(bitdata);
		// pausa
		bitdata=bitdata.substr(bitdata.size() -lendata);
		// cot(bitdata);
		int len=bitdata.size();
		// cot(len);
		float medt=0;
		float medf=0;
		// if(len>500)
		lop(bi,qtbitstart,qtbits+1){
			int modl=len%bi;
			int nstart=modl+1;
			int nlen=len-modl-1; 
			// cot(modl);
			// cot(nstart);
			// cot(nlen); 
			string t=bitdata.substr(nstart,nlen);
			// cot(t);
			string tx=bitdata.substr(nstart,nlen-bi+1);
			// cot(tx);
			// cot(tx.size());
			int txqt=tx.size()/bi;
			// cot(txqt);
			ba[bi].reserve(txqt); 
			na[bi].reserve(txqt); 
			fa[bi].reserve(txqt); 
			for(int ti=0;ti<tx.size();ti+=bi){
				ba[bi].push_back(tx.substr(ti,bi));
				reverse(ba[bi].back().begin(),ba[bi].back().end());
				// cot(ba[bi].back());  
				std::bitset<16> bittxr(ba[bi].back()); 
				na[bi].push_back(bittxr.to_ulong());
				// cot(bittxr);
				// cot(na[bi].back());
				fa[bi].push_back( mathNumscale( na[bi].back(),1.0,0, mathPow2a[bi]-1,0.5 )  );
				// cot(fa[bi].back());
				// cot( mathNumdescale( fa[bi].back(),1.0,0, mathPow2a[bi]-1,0.5 ) );
			}
			
			//fill fan
			addContinuos(fan[bi],fa[bi],bi,1); 
			// cot(fan[bi]); 
			// pausa
			
			int r=525;
			randsafe(r);
			// randsafe(7676776);
			// randsafe();
			
			//neurones
			float med=0;
			lop(di,0,deputados){
				if(nrs[bi][di]==0){
					nrs[bi][di]= new neurone(bi,1,hidden,"fxeus"+to_string(r),"neuron" );
					nrs[bi][di]->save();
					// pausa
				}
				// nrs[bi][di]= new neurone(bi,1,hidden,"fxeu","neurons" );
				// nrs[bi][di]= new neurone(bi,1,hidden ,"bit"+ to_string( len%bi )+ to_string(bi)+ to_string(di),"neurons");
				neurone &nr= *nrs[bi][di];
				// if(index==540)nr.save();
				// pausa
				nr.its=10000;
				int its;
				// cot(di);
				// cot(nr.filename);
				// if(di==1)
				its= nr.trainf(0.02,fan[bi]);
				// while(its==nr.its){
					// nr.resetWeights();
					// its= nr.trainf(0.02,fan[bi]);
					// cot(its);
				// }  
				// nr.save();
				// pausa
				// vfloat tc=fan[bi].back();
				vfloat tc=fan[bi][ fan[bi].size()-1 ];
				tc=vfloat(tc.begin()+1,tc.end());
				// cot(tc);
				float cres=nr.calc(tc)[0];
				// cot(cres);
				// cot(nr.errol);
				// cot(its);
				med+=cres;    
			}
			medf=med/(float)deputados;
			// cot(medf);
			//converte para num
			
			
			string tnext0=t.substr(t.size()-bi+1);
			string tnext1=tnext0+"1";
			tnext0+="0";
			// cot(tnext0);
			// cot(tnext1);
			string tnext0r=tnext0;
			string tnext1r=tnext1;
			reverse(tnext0r.begin(),tnext0r.end());
			reverse(tnext1r.begin(),tnext1r.end());
			bitset<8> bittnext0r(tnext0r);
			bitset<8> bittnext1r(tnext1r);
			// cot(bittnext0r.to_ulong());
			// cot(bittnext1r.to_ulong());
			float bittnext0rf=mathNumscale( bittnext0r.to_ulong(),1.0,0, mathPow2a[bi]-1,0.5 );
			float bittnext1rf=mathNumscale( bittnext1r.to_ulong(),1.0,0, mathPow2a[bi]-1,0.5 );
			float medc=nearest(medf,bittnext0rf,bittnext1rf);
			// cot(bittnext0rf);
			// cot(bittnext1rf);
			// cot(bi);
			// cot(medc);
			medt+=medc;
		} 
		medt/=(qtbits-(qtbitstart-1)); 
		// cot(medt);
		resultf=1.0-medf;
		// resultf=1.0-medt;
		result=mathRound(medt,0)==1?0:1;
		// cot((qtbits-(qtbitstart-1)));
		// cot(medt);
		// cot(result);
		return result;
	}
 

	bool nearest(float val,float test1, float test2){
		float t1=abs(val-test1);
		float t2=abs(val-test2);
		if(t1<t2)return 0;
		return 1;
	}  
};