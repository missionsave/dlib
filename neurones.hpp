#ifndef NEURONES_HPP_INCLUDED
#define NEURONES_HPP_INCLUDED

#include "regular.hpp"

/*
void neuronexor(){
	neurone nr(2,1,3);
	nr.its=3000;
	vvfloat inp({ {0,0,0}, {0,1,1}, {1,0,1}, {1,1,0}});
	nr.trainf(0.001,inp);
	vfloat inpc({1,0});
	vfloat ic=nr.calc(inpc);
	dbgvecall(ic)
	pausa
}
*/
//ALL READ ONLY EXCEPT inputs
struct neurone{
	float *wt=NULL;
	float** w;
	float *y;
	float *dx;
	float *dy;
	int ni,no,nh,hij,hik;
	string identifier;
	bool fileExists;
	neurone(){};
	void save();
	vfloat calc(float *inp);
	vfloat calc(vfloat &inp);
	void resetWeights();
	void setScaleVals(float up,float down);
	float scaleBoundUp=0;
	float scaleBoundDown=0;
	void scale(vfloat &vals);
	void deScale(vfloat &vals);
	void addContinuos(vfloat &inp);
	neurone(int Ni,int No,int Nh, string identifier="",string folder="",bool autoload=1);
	~neurone();
	string filename;
//	int trainf(float stopaterror=0.001);
	int its=1000;
	float lr=0.7;
	float errol;
	int trainf(float maxerror,vvfloat &inputs);
	int traincontinuos(float maxerror,vfloat &inputs);
	int traingradual(float maxerror,vvfloat &inputs);
	float stfDevProbDistr(int nrange);
	float stfDevProbDistrBin(int nrange);
};
struct scaler{
void scale(vfloat &vals,float boundUp,float boundDown=0,float boundbox=.99);
void deScale(vfloat &vals,float boundUp,float boundDown=0,float boundbox=.99);
};
extern scaler nscale;

void addContinuos(vvfloat &inputs,vfloat &inp,int ni,int no);

//strip input duplicates with different output

#endif // NEURONS_HPP_INCLUDED
