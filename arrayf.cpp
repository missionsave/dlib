#include "arrayf.hpp"
#include "stringf.hpp"
#include <algorithm>
#include <sstream>


vvint vrotate(vvint &origin){
	vvint resh;
	resh=vvint(origin[0].size(),vint(origin.size()));
	lop(i,0,resh.size())
		lop(r,0,origin.size())resh[i][r]=origin[r][i];

	return resh;
}


int qtdiguais(vint &a,vint &b){
int qtdig=0;
lop(i,0,a.size())
	lop(o,0,b.size())
		if(a[i]==b[o])
			qtdig++;
	return qtdig;
}

vector<string> split(const string& s, const string delim, const bool keep_empty) {
	vector<string> result;
	if (delim.empty()) {result.push_back(s);
	return result;}
	string::const_iterator substart = s.begin(), subend;while (true) {
		subend = search(substart, s.end(), delim.begin(), delim.end());	
		string temp(substart, subend);	if (keep_empty || !temp.empty()) {	
			result.push_back(temp);	}if (subend == s.end()) {break;	}
			substart = subend + delim.size();	}	
	return result;}


vfloat numsFromStr(string& s){
	trim(s);
	vstring v=split((s),",");
	vfloat r;
	lop(i,0,v.size()){
		trim( v[i]);
		if(v[i].size()==0)continue;
		r.push_back(atof(v[i].c_str()));
	}
	return r;
}


string join(vint v,string sep){
stringstream ss;
for(size_t i = 0; i < v.size(); ++i)
{
  if(i != 0)
    ss << sep;
  ss << v[i];
}
return ss.str();
}

void vecpushuni(vstring &vec,string val){
	bool flag=0;
	lop(i,0,vec.size()){
		if(vec[i]==val)flag=1;
	}
	if(!flag)vec.push_back(val);
}
void vecpushuni(vint &vec,int val){
	bool flag=0;
	lop(i,0,vec.size()){
		if(vec[i]==val)flag=1;
	}
	if(!flag)vec.push_back(val);
}

//int vboolToInt(vbool b){
//	return accumulate(b.rbegin(), b.rend(), 0, [](int x, int y) { return (x << 1) + y; });
//}

//not tested
//vbool intTovbool(uint vb,int sz=32){
//	vbool ret(sz);
//	int i=0;
//  for (unsigned int mask=0x80000000; mask; mask>>=1) {
//    if (x & mask) ret[i]=1;
//		if(i++>sz)break;
//  }
//  return ret;
//}

//= a==b
//bool vboolCompare(vbool &a,vbool &b){
//	return a.begin()._M_p==b.begin()._M_p;
//}
