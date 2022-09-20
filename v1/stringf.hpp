#ifndef STRINGF_HPP_INCLUDED
#define STRINGF_HPP_INCLUDED


#include <regular.hpp>

#include "configuru.hpp"
using namespace configuru;
#define jsn Config

#define isString(tip) (typeid(tip)==typeid(string))
#define Jsn(vinto,jsout){try{vinto=(decltype(vinto))( jsout );}catch(...){ vinto=(isString(vinto)?"":0);}}

void jsndeletearrayidx(jsn &jsna,int index);
jsn jsnaddobject(jsn &jsna);
string fjson(string ss);

std::string tail(std::string const& source, size_t const length);

bool stringMatch(const char *first, const char * second) ;

void string_toHeaderFile(string name,string &toCompress);

string string_escape(string &in);
string base64_encode(const std::string &in);
string base64_decode(const std::string &in);

int removeChar(char *s, char c, int len) ;

FILE *fmemopen (void *buf, size_t size, const char *opentype);

//CP_ACP,CP_UTF8
char* stringConv(const char* szU8,uint cpfrom,uint cpto);

void trim(string &str,string what=" \n\r\t");
void triml(string &str,string what=" \n\r\t");
void trimr(string &str,string what=" \n\r\t");

int isComment(string &buffline);

bool contains(string container,string containthis,bool matchcase=false);
bool containsAny(string container,vector <string> containAnyOfthis,bool matchcase=false);

int _snprintf_s(   char *buffer,   std::size_t sizeOfBuffer,   size_t count,   const char *format,   ...);

string replaceAll( std::string const& original, std::string const before, std::string const& after );
void subst( string & original, string before, string  after );
void subst( string & original, string before,int  after );

static void ConvertCp1251ToUtf8(const char *out, const char *in);
int ConvertUtf8ToCp1251(const char* utf8, char* windows1251, size_t n);

///(?!time=)(ola)  find time=ola but excludes time=
string regexSearch(string st,string pattern,int idx);
vector<string> regexSearch(string &st,string &pattern);
vector<string> regexSearcher(string &st,string &pattern);

vector<int> stringPositions(char * pbTarget, char * pbPattern, uint32_t cbTarget, uint32_t cbPattern);
char * Railgun_Swampshine_BailOut (char * pbTarget, char * pbPattern, uint32_t cbTarget, uint32_t cbPattern);

bool stringCompare( const string &left, const string &right );

string to_string(float Number,char* format);

const char* toChar(int Number);
//format "%.2f"=2decimais sempre, "%.2g"=2 decimais quando tem
const char* toChar(float Number,char* format);
string toLower(string data);


#ifdef __linux__
struct Convertible{
    int m_Integer;
    bool m_Bool;
    double m_Double;
    float m_Float;
    char* m_Char;
    const char* m_CChar;
    const unsigned char* m_CUChar;
    string m_SChar;
    Convertible() : m_Integer(0), m_Bool(false), m_Double(0.0), m_Float(0.0), m_Char(""),m_CChar(""), m_CUChar(0) {};
    inline operator int() const { return m_Integer;}
    inline operator bool() const{ return m_Bool; }
    inline operator double() const{ return m_Double; }
    inline operator float() const{ return m_Float; }
    inline operator char*() const { return m_Char; }
    inline operator const char*() const { return m_CChar; }
    inline operator const unsigned char*() const { return m_CUChar; }
    inline operator string() const { return m_SChar; }
};
#endif // __linux__
#endif // STRINGF_HPP_INCLUDED
