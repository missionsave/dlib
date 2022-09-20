#include "ohlcs.hpp"
 
#include <algorithm>
#include "arrayf.hpp"
#include "math.hpp"
//#include "flw.hpp"
#define lop(var,from,to)for(int var=(from);var<(to);var++)
 
void ohlcs::angScanMatches(){
// float ang=mathTrigRectAng((wx-x1),(wy-y1));
//
//                x2=(wx-x1)>0?1000:-1000;
//                y2=y1+mathTrigRectFrt(ang,(x2-x1));rmatches[r+rmax]++;

//        ohlcGlWindow*  gl=mygl;
    int oc=3;
    int sz=ohlc[oc].size();
    int xs=sz-1;
    int nrange=4;//gl->nrange
    int rmax=nrange/2;
    int rmin=-rmax;
    vector<int> rmatches(nrange);
    lop(r,rmin,rmax){

        float ys=ohlc[3][sz-2]+r;
//            gl->addLine2d(xs,ys,xs+5,ys);//Sleep(100);window->_oh->handle(FL_SHOW);
//        int xt=sz-15;
        for(int xt=sz-3;xt>sz-16;xt--){

            float ang=-45;
            for(ang=-88;ang<88;ang+=0.1){
                float yt=ys+mathTrigRectFrt(ang,(xs-xt));
                if(abs((yt)-(ohlc[oc][xt]))<0.1)rmatches[r+rmax]++;
//                dbgv((yt),(ohc[3][xt]),abs((yt)-(ohc[3][xt]))<0.001);
//                    gl->addLine2d(xs,ys,xt,yt);//Sleep(100);window->_oh->handle(FL_SHOW);
            }
        }
    }
    float cora[]={1,.9,.8,.7,.6,.5,.4,.3,.1};
    lop(i,0,9){
        int yri=indexOfmax(rmatches,0,rmatches.size());
        int yr=yri-rmax;
        yr+=ohlc[3][sz-2];
//            gl->addLine2d(xs,yr,xs+8,yr,cora[i]);
        rmatches[yri]=0;
    }




//        gl->handle(FL_SHOW);
//        dbgv(yr,rmax,indexOfmax(rmatches,0,rmatches.size()));
        dbgvecall(rmatches);
    lop(i,0,nrange)dbgv(i+rmin,rmatches[i]);
}

float ohlcs::ymaxRange(int from,int to){
    return *max_element(ohlc[1].begin()+from,ohlc[1].begin()+to);
}
float ohlcs::yminRange(int from,int to){
    return *min_element(ohlc[2].begin()+from,ohlc[2].begin()+to);
}
vector<vector<float>> ohlcs::toOhLcFromBin(vector<bool> vals){
    ymax=-100000;
    ymin=100000;
    vals=vector<bool>(vals.begin()+offset,vals.end());
    int vs=vals.size();
    int vsa=vs;//-offset;
    sizeofLastBar= vsa % aglomerado;
    int sze=vsa/aglomerado;if(sizeofLastBar!=0)sze++;//sze--;
    ohlc=vector<vector<float>>(4,vector<float>(sze));//dbgv(sze);
    int candle=-1;
    int val=0;
    lop(i,0,vs){
        if(vals[i]==1)val++;
        if(vals[i]==0)val--;
        int x=i%aglomerado;
        if(x==0){
            candle++;
            ohlc[0][candle]=val;ohlc[1][candle]=val;ohlc[2][candle]=val;ohlc[3][candle]=val;
            continue;
        }
        if(val>ohlc[1][candle])ohlc[1][candle]=val;
        if(val<ohlc[2][candle])ohlc[2][candle]=val;

        if(ohlc[1][candle]>ymax)ymax=ohlc[1][candle];
        if(ohlc[2][candle]<ymin)ymin=ohlc[2][candle];
        if(x==aglomerado-1 || i==vs-1){
                //if(i==vs-1)dbgv(candle,i,vs,vsa);
                ohlc[3][candle]=val;
        }
    }
//        dbgpx(ohlc[1],0,ohlc[0].size());
//        dbgpx(ohlc[2],0,ohlc[0].size());

    return ohlc;
}

vector<vector<float>> ohlcs::toOhLcFromNrange(vector<int> vals,int nrange){
    ymax=-100000;
    ymin=100000;
    vals=vector<int>(vals.begin()+offset,vals.end());
    lop(i,0,vals.size()){
        vals[i]=vals[i]-nrange/2;
    }

    int vs=vals.size();
    ohlc=vector<vector<float>>(4,vector<float>(vs));//dbgv(sze);
    int candle=-1;
    int pval=0;
    lop(i,0,vs){
        ohlc[0][i]=pval;
        pval+=vals[i];
        ohlc[3][i]=pval;

        ohlc[1][i]=max(ohlc[0][i],ohlc[3][i]);
        ohlc[2][i]=min(ohlc[0][i],ohlc[3][i]);
//
        if(ohlc[1][i]>ymax)ymax=ohlc[1][i];
        if(ohlc[2][i]<ymin)ymin=ohlc[2][i];
    }
//        dbgpx(ohlc[1],0,ohlc[0].size());
//        dbgpx(ohlc[2],0,ohlc[0].size());

    return ohlc;
}
vector<vector<float>> ohlcs::toOhLcDirect(vector<int> vals){
    ymax=-100000;
    ymin=100000;
    vals=vector<int>(vals.begin()+offset,vals.end());

    int vs=vals.size();
    ohlc=vector<vector<float>>(4,vector<float>(vs));//dbgv(sze);
    int pval=vals[0];
    lop(i,0,vs){
        ohlc[0][i]=pval;
        pval=vals[i];
        ohlc[3][i]=pval;

        ohlc[1][i]=max(ohlc[0][i],ohlc[3][i]);
        ohlc[2][i]=min(ohlc[0][i],ohlc[3][i]);
//
        if(ohlc[1][i]>ymax)ymax=ohlc[1][i];
        if(ohlc[2][i]<ymin)ymin=ohlc[2][i];
    }
//        dbgpx(ohlc[1],0,ohlc[0].size());
//        dbgpx(ohlc[2],0,ohlc[0].size());

    return ohlc;
}
template vector<vector<float>> ohlcs::toOhLc <int> (vector<int> vals,bool allowShowLastIfEmpty);
template vector<vector<float>> ohlcs::toOhLc <float> (vector<float> vals,bool allowShowLastIfEmpty);
template <typename T> vector<vector<float>> ohlcs::toOhLc(vector<T> vals,bool allowShowLastIfEmpty){
    if(vals.empty() && allowShowLastIfEmpty)vals=vector<T> (lastvals.begin(), lastvals.end());
    lastvals=vector<float> (vals.begin(), vals.end());
    int sze=vals.size()/aglomerado;if(vals.size()%aglomerado!=0)sze++;
    ohlc=vector<vector<float>> (4,vector<float>(sze));
    int candle=-1;
    lop(i,0,vals.size()){
        int x=i%aglomerado;
        if(x==0){
            candle++;
            ohlc[0][candle]=vals[i];ohlc[1][candle]=vals[i];ohlc[2][candle]=vals[i];ohlc[3][candle]=vals[i];
            continue;
        }
        if(vals[i]>ohlc[1][candle])ohlc[1][candle]=vals[i];
        if(vals[i]<ohlc[2][candle])ohlc[2][candle]=vals[i];
        if(x==aglomerado-1 || i==vals.size()-1)ohlc[3][candle]=vals[i];
    }
    return ohlc;
}
