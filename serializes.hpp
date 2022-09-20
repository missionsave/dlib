#ifndef SERIALIZES_HPP_INCLUDED
#define SERIALIZES_HPP_INCLUDED

#include "serialize.hpp"
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/bzip2.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/copy.hpp>

using namespace boost;
using namespace boost::iostreams;
using namespace boost::archive;
namespace bio = boost::iostreams;

/*
#include "serializes.hpp"
struct ts{
	long a;
	vfloat b;
	structSerialize
}t;
structSerializer(ts,a & b);

void test(){
	t.b={0,2,4};
	t.a=15;
	serializeSaveLoad("test",t,1);
	serializeSaveLoad("test",t,0);
	dbgv(t.a)
}*/

template <typename  T> void serializeSaveLoad(string filename,T &content, bool saveIt ,bool bin ,bool compress ){
	if(saveIt){
		if(!bin && !compress){
		std::ofstream ofs( filename);

		if(!ofs.is_open())return;
			text_oarchive oa(ofs);
			oa<< content;
			ofs.close();
		}
		if(bin){
		std::ofstream ofs( filename,ios_base::binary);
		if(!ofs.is_open())return;
			if(ofs.is_open() ){
				if(compress){
					filtering_stream<bio::output> f;
					f.push(bzip2_compressor());
					f.push(ofs);
					binary_oarchive oa(f);
					oa<< content;
				}
				if(!compress){
					binary_oarchive oa(ofs);
					oa<< content;
				}
				ofs.close();}
		}
	}
	if(!saveIt){
	///load
		if(!bin && !compress){
		std::ifstream ofs( filename);
		if(!ofs.is_open())return;
 		///	content.clear();
			text_iarchive oa(ofs);
			oa>> content;
			ofs.close();
		}
		if(bin){
		std::ifstream ofs( filename,ios_base::binary);
		if(!ofs.is_open())return;
 	///	content.clear();
				if(compress){
					bio::filtering_stream<bio::input> f;
					f.push(bio::bzip2_decompressor());
					f.push(ofs);
					binary_iarchive oa(f);
					oa >> content;
				}
				if(!compress){
					binary_iarchive oa(ofs);
					oa>> content;
				}
				ofs.close();
		}


	}
}



#endif
