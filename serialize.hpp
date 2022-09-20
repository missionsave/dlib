#ifndef SERIALIZE_HPP_INCLUDED
#define SERIALIZE_HPP_INCLUDED

#define structSerialize friend class boost::serialization::access; template<typename Archive>  void serialize(Archive& ar, const unsigned version);

#define structSerializer(structname,items) template<typename Archive>  void structname::serialize(Archive& ar, const unsigned version){ ar & items;}

#define structSerializeInline(...)  friend class boost::serialization::access; template<typename Archive>  void serialize(Archive& ar, const unsigned version) { ar __VA_ARGS__; }

#include <string>
#include "regular.hpp"
 
using namespace std;  

string AppName();

void serStrR(stringstream &in,string &str);
void serStringR(ifstream &in,string &str);
void serStringW(ofstream &out,string &str);
#define serw(sl) out.write((char *)(&sl), sizeof(sl));
#define serr(sl) in.read((char*)(&sl), sizeof(sl));

//int serializetype=0;//0=text 1=binary
template <typename T> void serializeSaveLoad(string filename,T &content, bool saveIt=0 ,bool bin=0,bool compress=0);















#include <fstream>
#include <functional>
namespace boost{namespace archive{struct text_oarchive;}; };
namespace boost{namespace serialization{struct access;}; };


#endif // SERIALIZE_HPP_INCLUDED
 