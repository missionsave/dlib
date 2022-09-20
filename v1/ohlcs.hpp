//D'Elcortese 2014-04-28

#ifndef OHLCS_HPP_INCLUDED
#define OHLCS_HPP_INCLUDED

using namespace std;
#include <vector>

struct ohlcs{
    vector<vector<float>> ohlc=vector<vector<float>>(4);
    int aglomerado=10;
    int offset=2;
    int maxsize;
    int sizeofLastBar;
    int ymax;
    int ymin;
    vector<float> lastvals;
    void angScanMatches();
    float ymaxRange(int from,int to);
    float yminRange(int from,int to);
    vector<vector<float>> toOhLcFromBin(vector<bool> vals);

    vector<vector<float>> toOhLcFromNrange(vector<int> vals,int nrange);
    vector<vector<float>> toOhLcDirect(vector<int> vals);

    template <typename T> vector<vector<float>> toOhLc(vector<T> vals=vector<T>(),bool allowShowLastIfEmpty=true);
};


#endif // OHLCS_HPP_INCLUDED
