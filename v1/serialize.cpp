
#include "serializes.hpp"
#include <vector>
#include <sstream>
void serStrR(stringstream &in,string &str){
    int ssz;
    in.read((char *)(&ssz), sizeof(int));
    std::vector<char> tmp(ssz);
    in.read(&tmp[0] ,ssz);
    str.assign(&tmp[0],ssz);
}
void serStringR(ifstream &in,string &str){
    int ssz;
    in.read((char *)(&ssz), sizeof(int));
    std::vector<char> tmp(ssz);
    in.read(&tmp[0] ,ssz);
    str.assign(&tmp[0],ssz);
}
void serStringW(ofstream &out,string &str){
    int ssz=str.size();
    out.write((char *)(&ssz), sizeof(ssz));
    out<<str;
}
/*
#include <fstream>
#include <unordered_map>
#include <boost/serialization/extended_type_info.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filter/bzip2.hpp>
#include <boost/iostreams/copy.hpp>
using namespace boost;
using namespace boost::iostreams;
*/

template void serializeSaveLoad(string filename,vstring &content, bool saveIt,bool bin,bool compress);

template void serializeSaveLoad(string filename,vshort &content, bool saveIt,bool,bool);
template void serializeSaveLoad(string filename,vector<int> &content, bool saveIt,bool,bool);
template void serializeSaveLoad(string filename,vector<vector<int>> &content, bool saveIt,bool,bool);
template void serializeSaveLoad(string filename,vector<vector<vector<int>>> &content, bool saveIt,bool,bool);
template void serializeSaveLoad(string filename,vvvvint &content, bool saveIt,bool,bool);
template void serializeSaveLoad(string filename,vector<float> &content, bool saveIt,bool,bool);
template void serializeSaveLoad(string filename,vector<bool> &content, bool saveIt,bool,bool);
template void serializeSaveLoad(string filename,vvvvbool &content, bool saveIt,bool,bool);
template void serializeSaveLoad(string filename,vector<vector<bool>> &content, bool saveIt,bool,bool);
template void serializeSaveLoad(string filename,string &content, bool saveIt,bool,bool);
template void serializeSaveLoad(string filename,time_t &content, bool saveIt,bool,bool);


template void serializeSaveLoad(string filename,unordered_map<string,string> &content, bool saveIt,bool,bool);
template void serializeSaveLoad(string filename,unordered_map<string,int> &content, bool saveIt,bool,bool);
template void serializeSaveLoad(string filename,unordered_map<string,vfloat> &content, bool saveIt,bool,bool);

template void serializeSaveLoad<std::unordered_map<std::string, char, std::hash<std::string>, std::equal_to<std::string>, std::allocator<std::pair<std::string const, char> > > >(std::string, std::unordered_map<std::string, char, std::hash<std::string>, std::equal_to<std::string>, std::allocator<std::pair<std::string const, char> > >&, bool,bool,bool);

