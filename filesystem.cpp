#include "regular.hpp"
//#include <basetsd.h>
#include "stdint.h"
#include "filesystem.hpp"
#include "math.hpp"
#include "stringf.hpp"
#include "arrayf.hpp"
#include <inttypes.h>
//#include "curl.hpp"
#define BOOST_FILESYSTEM_VERSION 3
#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>
//#include <boost/interprocess/file_mapping.hpp>
//#include <boost/interprocess/mapped_region.hpp>
//#include <boost/regex.hpp>
#include <regex>
#include <boost/predef.h>

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

#if _WIN32
//#include <direct.h>
#include <windows.h>
#include <shellapi.h>
#include <wininet.h>
//#include <unzip.h>
//#include "FL\fl_utf8.h"
string slash= "";//\\

#endif
#if BOOST_OS_LINUX
string slash= "/";
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
using namespace boost::interprocess;
#endif

#include <limits.h>

#if __linux__
#include <unistd.h>
#endif

#include <stringf.hpp>
using namespace boost::filesystem;
using namespace std;

extern "C" {
  int compkeys(const void *a,  const void *b) {
    return (strcmp(*((const char **)a), *((const char **)b)));
  }
}
///replace avariada no mingw
//#if __linux__
void autoExpandEnvironmentVariables( std::string & text ) {
dbgv(text);
    static regex env( "\\$\\{([^}]+)\\}" );
    smatch match;
    while ( regex_search( text, match, env ) ) {
        const char * s = getenv( match[1].str().c_str() );
        const std::string var( s == NULL ? "" : s );

//        text.replace( match[0].first, match[0].second, var );
    }
}
//#endif



size_t freadHuge(char * buf,size_t size,  size_t numBytesToRead,FILE * pFile,size_t bufSize){//rewind (pFile);
//    fseek(pFile,0,SEEK_END);
//    int tsize = ftell(pFile);dbgv(tsize);
//	size_t bufSize=8388608;//char buff[bufSize];
   size_t bytesRead = 0;//int c=0;
	size_t nextReadSize;
   while(bytesRead < numBytesToRead) {
      nextReadSize = fread(buf+bytesRead, 1, bufSize, pFile);//dbgv(nextReadSize,c++);
      if (nextReadSize <= 0) return -1;  // error or early EOF!
      bytesRead += nextReadSize;
   }
   return numBytesToRead;
}


string fileRead(string fname){
	std::ifstream t(fname);
	std::string str((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());
	return str;
}

string AppName(){return ChangeExtension(ExtractFilename(AppFullPath()),"");}

vector<bool> fileReadBin(const char* fileName){
    vector<bool> v;
    std::ifstream is(fileName, ios::in|ios::binary);
    if (is) {
        is.seekg (0, is.end);
        int length = is.tellg();
        is.seekg (0, is.beg);
//        char buffer[length];
        char *buffer=new char[length];
        is.read( buffer, length);
        is.close();
        for(int ix = 0; ix < length*8; ix++) v.push_back(bitGet(buffer,ix));
        delete buffer;
    }
    return v;
};

string binToStr(vector<bool> &a){
    stringstream strm;
    for (auto it = a.begin(); it != a.end();) // see 0x for meaning of auto
    {
        char b = 0;
        for (int i = 0; i < 8*sizeof(b); ++i)
        {
            b |= (*it & 1) << (8*sizeof(b) - 1 - i);
            ++it;
            if(it == a.end())break;
        }
//       strm.write((char *)(&b), sizeof(b));
        strm<<b;
        // flush 'b'
    }
    return strm.str();
}
string fileReadBinTostr(const char* fileName){
    string v;
    std::ifstream is(fileName, ios::in|ios::binary);
    if (is) {
        is.seekg (0, is.end);
        int length = is.tellg();
        is.seekg (0, is.beg);
//        char buffer[length];
        char *buffer=new char[length];
        is.read( buffer, length);
        is.close();
        for(int ix = 0; ix < length*8; ix++) v.push_back(bitGet(buffer,ix)==0?'0':'1');
        delete buffer;
    }
    return v;
};







#if BOOST_OS_LINUX
///isnt working right, no way to delete mapped_region
std::size_t fileMapRead(const char* fl, float* &vals){
    file_mapping fm(fl, read_only);
    mapped_region* region=new mapped_region(fm, read_only);
    vals = (float *)region->get_address();
//    delete region;
    return region->get_size()/sizeof(float);
}
std::size_t fileMapSize(const char* fl ){
    file_mapping fm(fl, read_only);
    mapped_region region(fm, read_only);
    std::size_t elements= region.get_size()/sizeof(float);
    return elements;
}
vector<float> fileMapReadToEnd(const char* fl, int from){
    try{
        file_mapping fm;
        mapped_region region;
        fm=file_mapping(fl, read_only);
        region=mapped_region(fm, read_only);
        float* vals = (float *)region.get_address();
        size_t elements= region.get_size()/sizeof(float);
        vector<float> res(elements-from);
        for(int i=from;i<elements;i++){
            res[i-from]=vals[i];
        }
        return res;
    }catch(...){  std::cout<<endl<<"error!!!! "<<endl; return {};}
}
#endif // BOOST_OS_LINUX

string stringFromFileText(string fname){
    string str;
    std::ifstream is (fname  );
    if(is){
        is.seekg (0, is.end);
        int length = is.tellg();
        is.seekg (0, is.beg);
        char* buffer=new char[length];
        is.read (buffer,length);
        str=string(buffer,length);
		delete buffer;
        is.close();
    }
    return str;
}

time_t fileLastw(string file){  //error if not exists
	return boost::filesystem::last_write_time(file);
};
void fileLastw(string file,time_t tm){  //error if not exists
	try{
	boost::filesystem::last_write_time(file,tm);
	}catch(...){}
};

string ExtractFilename( const std::string& pathf ){
	boost::filesystem::path path(pathf);
	return path.filename().string();
};
string ExtractPathNoExt( const std::string& path ){
return ChangeExtension(path.substr( path.find_last_of( slash ) +1 ),"" );
};
string ExtractFilenameNoExt( const std::string& pathf ){
	boost::filesystem::path path(pathf);
	return path.stem().string();
};

string ExtractDirectory( string pathf ,bool withSlashLast) {
	boost::filesystem::path path(pathf);
	return path.parent_path().string()+(withSlashLast?slash:"");
};

string ExtractExtention( const std::string& file,bool wdot ){
	boost::filesystem::path path(file);
	string res=path.extension().string();
	if(!wdot)trim(res,".");
  return res;
}
string ChangeExtension( const std::string& path, const std::string& ext )  { string filename = ExtractFilename( path );
return ExtractDirectory( path) +filename.substr( 0, filename.find_last_of( '.' ) ) +ext; };


bool fileExist(string fname){
	return boost::filesystem::exists(fname);
}
//bool fileisDir(string pathf){
//	return boost::filesystem::is_directory(fname);
//}

int mdir(string pathd){
	try{
		boost::filesystem::path path(pathd);
		boost::filesystem::create_directories(path.parent_path());
	}catch(...){return 1;}
	return 0;
}

//#include <direct.h>
//#include <stdio.h>
#ifdef _WIN32
#include <direct.h>
// MSDN recommends against using getcwd & chdir names
#define cwd _getcwd
#define cd _chdir
#else
#include "unistd.h"
#define cwd getcwd
#define cd chdir
#endif
void AppSetWorkingDir(string path){chdir(path.c_str());};
void AppSetWorkingDir(){chdir(AppPath().c_str());};
//void AppAllwaysOnTop(HWND hw ){SetWindowPos(hw, HWND_TOPMOST, 0, 0, 0, 0, (SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW));};


void* ReallocOrFree(void* original_ptr, size_t new_size){
    void* temp = realloc(original_ptr, new_size);
    if (!temp) free(original_ptr);
    return temp;
};

vector <string> fileReadAllLines(string file){vector <string> lines;std::ifstream myfile;myfile.open(file.c_str());if (myfile.is_open()){ while ( myfile.good() ){string line; getline (myfile,line);lines.push_back(line);}myfile.close();}return lines;}



unsigned long long analizefileOSHahs(char *fileName){
 /*
  * Public Domain implementation by Kamil Dziobek. turbos11(at)gmail.com
  * This code implements Gibest hash algorithm first use in Media Player Classics
  * For more implementation(various languages and authors) see:
  * http://trac.opensubtitles.org/projects/opensubtitles/wiki/HashSourceCodes
  *
  * -works only on little-endian procesor DEC, Intel and compatible
  * -sizeof(unsigned long long) must be 8
  */

  //FILE        *file;
  //int i;
  unsigned long long t1=0;
  //unsigned long long buffer1[8192*2];
  //file = fopen(fileName, "rb");
  //fread(buffer1, 8192, 8, file);
  //fseek(file, -65536, SEEK_END);
  //fread(&buffer1[8192], 8192, 8, file);
  //for (i=0;i<8192*2;i++)
  //  t1+=buffer1[i];
  //t1+= ftell(file); //add filesize
  //fclose(file);
  return  t1;
};


namespace fs = ::boost::filesystem;

// return the filenames of all files that have the specified extension
// in the specified directory and all subdirectories
void get_all(string path ,  string ext, vector<string>& ret){
	fs::path root=path;
	if(!fs::exists(root) || !fs::is_directory(root)) return;

	fs::recursive_directory_iterator it(root);
	fs::recursive_directory_iterator endit;
string h;
	while(it != endit)	{
		if(fs::is_regular_file(*it) && ext.find(it->path().extension().string())!=string::npos   ){
			ret.push_back(it->path().filename().string());
		}
	++it;

	}
}

vstring dirWildcard(string path,string wildcard,bool onlyfilename){
	vstring res;
	if(!fileExist(path))return res;
	wildcard=toLower(wildcard);
	vstring w=split(wildcard,";");
	string fname;
	string fnamewpath;
	bool add;
	for(auto & p : boost::filesystem::directory_iterator( path )){ 
		const boost::filesystem::path cp = (p);
		fnamewpath=cp.string();
		fname=ExtractFilename(fnamewpath);
		add=0;
		lop(i,0,w.size()){
			if(stringMatch(w[i].c_str(),toLower(fname).c_str())){ add=1; break;}
		}
		if(!add)continue;
		if(onlyfilename)
			res.push_back(fname);
		else
			res.push_back(fnamewpath);
	}
	return res;
}

vstring dirFilesIncludingSubdirs(string srcdir,string exts ){
  autoExpandEnvironmentVariables(srcdir);
		dbgv(srcdir);
	boost::system::error_code ec,no_err;
	boost::filesystem::path current_dir(srcdir);
	vstring res;
	res.reserve(500);
	string fn;
	trim(exts,";");
	vstring code_types ={"c","cpp","hpp"};
	code_types = split(exts,";");
	sort (code_types.begin(), code_types.end());
	size_t sa=code_types.size();
	lop(i,0,sa)code_types[i]= "."+code_types[i] ;
	size_t sb=sizeof(code_types[0]);

	using namespace boost::filesystem;
	recursive_directory_iterator dir( current_dir), end;
	try{
		while (dir != end)  {
			fn = dir->path().extension().string() ;
			//		if(!boost::filesystem::is_regular_file(dir->path()))
			//			continue;//not directory
			if (bsearch(&fn , &code_types[0],sa, sb, compkeys)){
			//    if (contains(exts, fn)){
				res.push_back(dir->path().string());
			}
			++dir;
		}
}catch(...){++dir; }
//}catch(boost::filesystem::filesystem_error e){dir.no_push();}

	return res;
}









#if _WIN32

/*
string unzipFileFromUrl(string url,string fileToUnzip,string dest){
    string d=httpget(url);
    HZIP hz = OpenZip((char*)d.c_str(),d.size(),0);
    ZIPENTRY ze;int in; FindZipItem(hz,fileToUnzip.c_str(),true,&in,&ze);
    if(dest=="memory"){
        char ibuf[ze.unc_size];
        UnzipItem(hz,in, ibuf, ze.unc_size);
        dest=ibuf;
    }else  UnzipItem(hz,in,dest.c_str());
    CloseZip(hz);
    return dest;
}
*/

string AppFullPath(){
	char exepath[MAX_PATH];
	GetModuleFileNameA(0, exepath, MAX_PATH);
	return  exepath;
};

bool dirExists(string  dirName_in){
  DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
  if (ftyp == INVALID_FILE_ATTRIBUTES)
    return false;  //something is wrong with your path!

  if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
    return true;   // this is a directory!
  return false;    // this is not a directory!
}

/*
vector<string> dir(const char* dirnamewildcardacepted,string exts,bool absolutepath){
    HANDLE hFind;
    WIN32_FIND_DATA FindFileData;
    string d="",f;//dbgv(dirnamewildcardacepted);
    if(absolutepath)d=ExtractDirectory(dirnamewildcardacepted);
    vector<string> res;
		string ext;
    if((hFind = FindFirstFile(dirnamewildcardacepted, &FindFileData)) != INVALID_HANDLE_VALUE){
        do{
					if ( FindFileData.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY)continue;
					ext=";"+ExtractExtention(FindFileData.cFileName)+";";
					if(exts.find(ext)==string::npos)continue;
					f=d+FindFileData.cFileName;
					f=stringConv(f.c_str(),CP_ACP,CP_UTF8);
          res.push_back(f);
        }while(FindNextFile(hFind, &FindFileData));
        FindClose(hFind);
    }
    return res;
}
*/
/*
vector<string> dir(const char* dirnamewildcardacepted,bool absolutepath){
    HANDLE hFind;
    WIN32_FIND_DATA FindFileData;
    string d="",f;
    if(absolutepath)d=ExtractDirectory(dirnamewildcardacepted);
    vector<string> res;
    if((hFind = FindFirstFile(dirnamewildcardacepted, &FindFileData)) != INVALID_HANDLE_VALUE){
        do{
					f=d+FindFileData.cFileName;
					f=stringConv(f.c_str(),CP_ACP,CP_UTF8);
          res.push_back(f);
        }while(FindNextFile(hFind, &FindFileData));
        FindClose(hFind);
    }
    return res;
}

/// Gets a list of subdirectories under a specified path
/// @param[out] output Empty vector to be filled with result
/// @param[in]  path   Input path, may be a relative path from working dir
void getSubdirs(std::vector<std::string>& output, const std::string& path)
{
    WIN32_FIND_DATA findfiledata;
    HANDLE hFind = INVALID_HANDLE_VALUE;

    char fullpath[MAX_PATH];
    GetFullPathName(path.c_str(), MAX_PATH, fullpath, 0);
    std::string fp(fullpath),f;

    hFind = FindFirstFile((LPCSTR)(fp + "\\*").c_str(), &findfiledata);
    if (hFind != INVALID_HANDLE_VALUE)
    {
        do
        {
            if ( findfiledata.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY
                && (findfiledata.cFileName[0] != '.'))
            {f=findfiledata.cFileName;f=stringConv(f.c_str(),CP_ACP,CP_UTF8);
                output.push_back(f);
            }
        }
        while (FindNextFile(hFind, &findfiledata) != 0);
    }
//			dbgv(output.size()); getchar();
}

/// Gets a list of subdirectory and their subdirs under a specified path
/// @param[out] output Empty vector to be filled with result
/// @param[in]  path   Input path, may be a relative path from working dir
/// @param[in]  prependStr String to be pre-appended before each result
///                        for top level path, this should be an empty string
void getSubdirsRecursive(std::vector<std::string>& output, const std::string path, const std::string prependStr){
    std::vector<std::string> firstLvl;
    getSubdirs(firstLvl, path);
    for (std::vector<std::string>::iterator i = firstLvl.begin();
         i != firstLvl.end(); ++i)
    {
        output.push_back(prependStr + *i);
        getSubdirsRecursive(output,
            path + std::string("\\") + *i + std::string("\\"),
            prependStr + *i + std::string("\\"));
    }
}
vector<string> dirFilesIncludingSubdirs_(string path,string filewildcard){
//	path=replaceAll(path,"/","\\");dbgv(path);
	filewildcard=";"+filewildcard+";";//dbgv(filewildcard);
	vector<string> output;
	vector<string> dird;
	char buf[MAX_PATH];
	ExpandEnvironmentStrings(path.c_str(), buf, MAX_PATH);
	path=buf;
	getSubdirsRecursive(dird,path);
	output=dir(string(path+"*.*").c_str(),filewildcard,true);
	lop(i,0,dird.size()){
			vector<string> dirx=dir(string(path+dird[i]+"\\*.*").c_str(),filewildcard,true);
//        dbgv((dird[i]+"\\*.c*").c_str());
			lop(id,0,dirx.size())output.push_back(dirx[id]);
	}
	return output;
}



bool ExplorerGoTo (const string &path){
	char* Path =new char(2048);
    ConvertUtf8ToCp1251(path.c_str(),Path,2048);

    TCHAR tcBuff[8] = {0};
    lstrcpyn(tcBuff, Path, 5);

    string stParams =  ("/n, /select, ");

    if( lstrcmpi( ("\\??\\"), tcBuff) == 0 )   {
        stParams += (Path[4]);
    }  else  {
        stParams += Path;
    }
    string stExplorer =  ("explorer.exe");
    //ExpandPath(stExplorer);
    if (stExplorer.empty ()) stExplorer =  ("explorer.exe");
    SHELLEXECUTEINFO shi = { 0 };
    shi.cbSize          = sizeof (SHELLEXECUTEINFO);
    shi.lpVerb          =  ("open");
    shi.lpFile          = stExplorer.c_str ();
    shi.lpParameters    = stParams.c_str ();
    shi.nShow           = SW_SHOW;
    bool bRes = ShellExecuteEx( &shi );
    if( bRes == FALSE && GetLastError() != 0 )    {
        Sleep(200);
        return ShellExecuteEx( &shi );
    }
    return bRes;
}
*/
#endif


#if BOOST_OS_LINUX

string AppFullPath(){
  char result[ PATH_MAX ];
  ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
  return std::string( result, (count > 0) ? count : 0 );
};


#endif

