#ifndef ZIP_HPP_INCLUDED
#define ZIP_HPP_INCLUDED

#include <regular.hpp>


#include <easylzma/compress.h>
#include <easylzma/decompress.h>


//inData is deleted carefull if is referenced
int simpleDecompress(elzma_file_format format,
                     const unsigned char * inData,
                     size_t inLen,
                     unsigned char ** outData,
                     size_t * outLen);




string string_compresslzma(string &data,int comp1dec0);












#endif
