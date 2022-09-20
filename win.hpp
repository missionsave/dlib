#ifndef WIN_HPP_INCLUDED
#define WIN_HPP_INCLUDED
#include "windef.h" 
#include "regular.hpp" 

HWND flxid(void* w);

bool IsRunAsAdmin();
void startRunAsAdmin();

//0x0816 pt_PT//0x0416 pt_BR//
int GetLanguage();

void AppAllwaysOnTop(HWND hw ); 
void AppAllwaysOnTop(void* hw ); 
 void transparency(HWND hw,float TransparencyPercentage);
void transparency(void* hw,float TransparencyPercentage);//0-100%

void AppAllwaysOnTopNoTitle(void* hw );
void AppNormNoTitle(HWND hw );
void AppNormNoTitle(void* hw );
 long gwl(HWND hw);

vlong  getWindowSt(HWND hw);
 vlong  getWindowSt(void* hw);
void setWindowSt(HWND hw,vlong st);
 void setWindowSt(void* hw,vlong st);

#define singInstance(win,arg)if(singleInstance(win->label(), arg!=NULL?arg:"")) exit(0); 
string cpdataread(void* p);
bool singleInstance(string appname,string msg);

void showCursor(int id);


void setPriorityClass(int p );

void ftype(string app,string exts,bool install);


void setFocus(HWND hw);

void AppMax(HWND hw );
void AppMax(void* hw );
 


struct Win7TaskbarProgress{
    Win7TaskbarProgress(unsigned long long ullTotal,HWND Hwnd=NULL);
    Win7TaskbarProgress(HWND Hwnd=NULL);
    void SetProgressValue( unsigned long long ullCompleted );
    virtual ~Win7TaskbarProgress();
    void SetProgressStateINDETERMINATE( );
    void SetProgressStateNORMAL( );
    void SetProgressState( int flag);
    void SetProgressValue( unsigned long long ullCompleted, unsigned long long ullTotal );
    bool Init();
    void* m_pITaskBarList3;
    bool m_bFailed;
    HWND hwnd7 ;
    unsigned long long w7tbpTotal ;
    unsigned int segment;
};

string RegRead (HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue);
//só funca com privilegios
bool RegWrite(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue, LPCTSTR pszString,int rtype=REG_SZ);
void RegPathSet(const char* toset,const char* delim="\n");
#endif  
 