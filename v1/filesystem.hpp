#ifndef FILE_SYSTEM_HPP_INCLUDED
#define FILE_SYSTEM_HPP_INCLUDED

using namespace std;
#include <string>
#include <vector>
//#include <windows.h>


//vreadfilebin(ushort,smb.hist,fname);
#define vreadfilebin(vtype,vectorname,fname) {ifstream file(fname, ios::binary); file.unsetf(ios::skipws); file.seekg(0, ios::end); streampos fileSize = file.tellg(); file.seekg(0, std::ios::beg); vectorname.resize(fileSize/sizeof(vtype));file.read((char*) &vectorname[0], fileSize);}

#define vreadfilebinfrom(vtype,vectorname,fname,from) {ifstream file(fname, ios::binary); file.unsetf(ios::skipws); file.seekg(0, ios::end); streampos fileSize = file.tellg(); file.seekg(from, std::ios::beg); vectorname.resize((fileSize-from)/sizeof(vtype));file.read((char*) &vectorname[0], fileSize);}


#define fileExistJs(fn) (fileExist(fn+".json") || fileExist(fn+".jsn"))

//#define stringFrormFileText(fname)({string str; ifstream is (fname ); if(is){is.seekg (0, is.end);int length = is.tellg(); is.seekg (0, is.beg); char buffer[length];is.read (buffer,length); str=string(buffer,length); is.close();} str;})


void autoExpandEnvironmentVariables( std::string & text );

size_t freadHuge(char * buf,size_t size,  size_t numBytesToRead,FILE * pFile,size_t bufSize=131072);



bool fileExist(string fname);

string stringFromFileText(string fname);

time_t fileLastw(string file);
void fileLastw(string file,time_t tm);

string ExtractDirectory( string path ,bool withSlashLast=true);
string ExtractExtention( const std::string& file ,bool wdot=0);
string ExtractFilename( const std::string& path );
string ExtractFilenameNoExt( const std::string& path );
string ExtractPathNoExt( const std::string& path );
string ChangeExtension( const string& path, const string& ext );

int mdir(string pathd);

string AppFullPath();

inline string AppPath(){return ExtractDirectory(AppFullPath());};

string AppName();

void AppSetWorkingDir(string path);

void AppSetWorkingDir();

//void AppAllwaysOnTop(HWND hw) ;

bool ExplorerGoTo (const string &Path);

bool dirExists(string  dirName_in);

vector<string> dirWildcard(string path,string wildcard,bool onlyfilename=1);

vector<string> dir(const char* dirnamewildcardacepted,bool absolutepath=true);
vector<string> dir(const char* dirnamewildcardacepted,string exts,bool absolutepathh=true);
void getSubdirs(std::vector<std::string>& output, const std::string& path);
void getSubdirsRecursive(std::vector<std::string>& output, const std::string path, const std::string prependStr="");
vector<string> dirFilesIncludingSubdirs(string path,string filewildcard);
void get_all(string path ,  string ext, vector<string>& ret);
string unzipFileFromUrl(string url,string fileToUnzip,string dest);

//string httpget(string url);

string fileRead(string fname);

vector <string> fileReadAllLines(string file);

vector<bool> fileReadBin(const char* fileName);



string binToStr(vector<bool> &a);

string fileReadBinTostr(const char* fileName);

unsigned long long analizefileOSHahs(char *fileName);

#endif // FILESYSTEM_HPP_INCLUDED
