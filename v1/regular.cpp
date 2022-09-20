#include "regular.hpp"

using namespace std;
#include <iostream>

#include <cstdarg>
void dbgp(char * format, ...){   setlocale(LC_ALL,"C");va_list args;va_start (args, format);vprintf (format, args); va_end (args);  } ;


//template <typename  T> void dbg(T current)   try { stringstream _cout; _cout << current; printf("%s", _cout.str().c_str()); fflush(stdout); _cout.flush(); }catch (...) {}
template <typename  T> void dbg(T current)   try {   cout<<current; fflush(stdout);  }catch (...) {}
template void dbg<int>(int current);
template void dbg<const char*>(const char* current);
template void dbg<const unsigned char*>(const unsigned char* current);
template void dbg<const wchar_t*>(const wchar_t* current);
template void dbg<wchar_t*>(wchar_t* current);
template void dbg<string>(string current);
template void dbg<char*>(char* current);
template void dbg<char>(char current);
template void dbg<short>(short current);
template void dbg<unsigned short>(unsigned short current);
template void dbg<unsigned char>(unsigned char current);
template void dbg<void*>(void* current);
template void dbg<bool>(bool current);
//template void dbg<_Bit_reference>(_Bit_reference current);
template void dbg<float>(float current);
template void dbg<double>(double current);
template void dbg<unsigned long long>(unsigned long long current);
template void dbg< long >(  long current);
template void dbg< long long>( long long current);
template void dbg<long unsigned int>(long unsigned int current);
template void dbg<unsigned int>(unsigned int current);

//template void dbg<size_t>(size_t current);
//template  void dbg<std::vector<int, std::allocator<int> > >(std::vector<int, std::allocator<int> >) ;
//auto tt(auto &g){
//
//
//}
