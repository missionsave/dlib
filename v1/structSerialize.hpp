#ifndef STRUCTSERIALIZE_HPP_INCLUDED
#define STRUCTSERIALIZE_HPP_INCLUDED

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
//#include <boost/archive/binary_iarchive.hpp>
//#include <boost/archive/binary_oarchive.hpp>

#define structSeriallize friend class boost::serialization::access; template<typename Archive>  void serialize(Archive& ar, const unsigned version);
#define structSerializer(structname,items) template<typename Archive>  void structname::serialize(Archive& ar, const unsigned version){ ar & items;}



//#define structSerial(...)  friend class boost::serialization::access; template<typename Archive>  void serialize(Archive& ar, const unsigned version) { ar __VA_ARGS__; }

#endif // STRUCTSERIALIZE_HPP_INCLUDED



//load
//        std::ifstream ofs( folder+account+ string(".combi"), std::ios::binary);
//        if(ofs.is_open() ){boost::archive::binary_iarchive oa(ofs); oa>> mc; ofs.close();}

//save
//        std::ofstream ofs( folder+account+ string(".combi"), std::ios::binary);
//        if(ofs.is_open() ){boost::archive::binary_oarchive oa(ofs); oa<< mc; ofs.close();}
