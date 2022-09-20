#ifdef WIN32

#include "regular.hpp"
#include <boost/predef.h>
#include "win.hpp"
#include "stringf.hpp"
#include "arrayf.hpp"
#include "windows.h" 
//#include <Shellapi.h>
#include <sstream>  
#include <FL/x.H>  
#include <FL/Fl_Window.H> 
bool dirExists(string  dirName_in);
string AppFullPath();

void startRunAsAdmin(string cmd,string params="");
string ExtractFilenameNoExt( const std::string& path );
 


uint  fl_msgmessage(){
	return fl_msg.message;
}
void* fl_msglParam(){
	return (void*)fl_msg.lParam;
} 

void redrawWin(void* win){
	RedrawWindow(flxid(win),NULL,NULL,RDW_INVALIDATE | RDW_ALLCHILDREN |   RDW_ERASE | RDW_NOFRAME  );
}

int GetLanguage(){
	return (GetSystemDefaultUILanguage()  ); 
}

HWND flxid(void* w){
	return fl_xid( (Fl_Window*)w);
} 
 
void AppAllwaysOnTop(void* hw ){ 
	AppAllwaysOnTop(flxid(hw) );
}
 
void AppAllwaysOnTop(HWND hw ){ 
	SetWindowPos((HWND)hw, HWND_TOPMOST, 0, 0, 0, 0, (SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW ));
};  

void AppMax(HWND hw ){ 
			SendMessage(hw, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
};
void AppMax(void* hw ){ 
	AppMax(flxid(hw) );
};
 long gwl(HWND hw){
	return GetWindowLong( hw, GWL_STYLE );

 
}
void AppAllwaysOnTopNoTitle(HWND hw ){ 
SetWindowLongPtr (hw, GWL_STYLE, 0);
SetWindowLongPtr(hw, GWL_EXSTYLE,0);
	SetWindowPos((HWND)hw, HWND_TOPMOST, 0, 0, 0, 0, (    SWP_NOMOVE  | SWP_SHOWWINDOW  ));
};
void AppAllwaysOnTopNoTitle(void* hw ){ 
	AppAllwaysOnTopNoTitle(flxid(hw) );
}
 
void AppNormNoTitle(HWND hw ){ 
SetWindowLongPtr (hw, GWL_STYLE, 0);
SetWindowLongPtr(hw, GWL_EXSTYLE,0);
	SetWindowPos((HWND)hw, HWND_NOTOPMOST, 0, 0, 0, 0, (    SWP_NOMOVE  | SWP_SHOWWINDOW  ));
};
void AppNormNoTitleh(HWND hw ){ 
//SetWindowLongPtr (hw, GWL_STYLE, 0);
//SetWindowLongPtr(hw, GWL_EXSTYLE,0);
	SetWindowPos((HWND)hw, HWND_NOTOPMOST, 0, 0, 0, 0, (    SWP_NOMOVE  |SWP_HIDEWINDOW   )); 
};
void AppNormNoTitles(HWND hw ){ 
//SetWindowLongPtr (hw, GWL_STYLE, 0);
//SetWindowLongPtr(hw, GWL_EXSTYLE,0);
	SetWindowPos((HWND)hw, HWND_NOTOPMOST, 0, 0, 0, 0, (    SWP_NOMOVE  |SWP_SHOWWINDOW   )); 
};
void AppNormNoTitle(void* hw ){ 
	AppNormNoTitle(flxid(hw) );
}
 void transparency(HWND hw,float TransparencyPercentage){
    LONG ExtendedStyle = GetWindowLong( hw, GWL_EXSTYLE );
    SetWindowLong( hw,GWL_EXSTYLE,ExtendedStyle | WS_EX_LAYERED );//| WS_EX_TRANSPARENT bom p log
    float fAlpha = TransparencyPercentage * ( 255.0 /100.0 );
    BYTE byAlpha = static_cast<BYTE>( fAlpha );
    SetLayeredWindowAttributes( hw, 0,byAlpha, LWA_ALPHA );
}
 void transparency(void* hw,float TransparencyPercentage){
	transparency(flxid(hw),TransparencyPercentage );
}
 vlong  getWindowSt(HWND hw){
		vlong a(2);
		a[0]= GetWindowLong( hw, GWL_STYLE );
		a[1]= GetWindowLong( hw, GWL_EXSTYLE );
    return a; 
} 
 void setWindowSt(HWND hw,vlong st){ 
		SetWindowLong( hw, GWL_STYLE,st[0] );
		SetWindowLong( hw, GWL_EXSTYLE,st[1] ); 
}
 vlong  getWindowSt(void* hw){ 
    return getWindowSt(flxid( hw)); 
}  
 void setWindowSt(void* hw,vlong st){ 
		setWindowSt( flxid( hw), st ); 
}

void showCursor(int id){
HWND hWnd = GetForegroundWindow();
DWORD foregroundThreadID = GetWindowThreadProcessId(hWnd, 0);
DWORD currentThreadID = GetCurrentThreadId();

AttachThreadInput(foregroundThreadID, currentThreadID, TRUE);
LPSTR cr[]={0,IDC_ARROW}; 
SetCursor(LoadCursor(0,cr[id]));
AttachThreadInput(foregroundThreadID, currentThreadID, FALSE); 
}

string cpdataread(void* p){
COPYDATASTRUCT* cds=(COPYDATASTRUCT*)p;
string snc=string(( char*)(cds->lpData),cds->cbData); 
	return snc; 
}  
bool singleInstance(string appname,string msg){
	 HWND windowHandle = FindWindowA(NULL, (LPCSTR)appname.c_str());   
	if(windowHandle){ 
		COPYDATASTRUCT   cds;   
		cds.	dwData=0;
		cds.	cbData=msg.size();
		cds.	lpData=(PVOID)msg.c_str();
		SendMessage(windowHandle, WM_COPYDATA,0,(LPARAM ) (&cds));
		Sleep(800);
		return 1; 
	}
	return 0;
};  

struct singleInst{
	HANDLE  m_hStartEvent ;
	bool CheckOneInstance(string appname,string msg);
	void close();
};
void singleInst::close(){
	CloseHandle( m_hStartEvent ); 
	m_hStartEvent = NULL;
}
bool singleInst::CheckOneInstance(string appname,string msg){
	m_hStartEvent = CreateEventW( NULL, FALSE, FALSE, (LPCWSTR)appname.c_str() );

	if(m_hStartEvent == NULL){
		close();
		return false;
	} 

	if ( GetLastError() == ERROR_ALREADY_EXISTS ) {
		close();
		// already exist
//		SendMessage(
//  _In_ HWND   hWnd,
//  _In_ UINT   Msg,
//  _In_ WPARAM wParam,
//  _In_ LPARAM lParam
//);
		return false;
	}
	// the only instance, start in a usual way
	return true;
} 

void ftype(string app,string exts,bool install){
app="C:\\Desk\\Programas\\_Multimedia\\spl\\spl.exe";
	string regc="REG ADD \"HKEY_CURRENT_USER\\Software\\Classes\\Applications\\%exe%\\shell\\open\\command\"  /t REG_SZ /d \"\\\"%path%\\\" \\\"%1\\\"\" /f";

	string reg="REG ADD \"HKEY_CLASSES_ROOT\\Applications\\%exe%\\shell\\open\\command\" /v @ /t REG_SZ /d \"\\\"%path%\\\" \\\"%1\\\"\" /f";
reg=regc;

	string rege="REG ADD \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.%ext%\" /v \"Application\" /t REG_SZ /d \"%exe%\" /f & REG ADD \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.%ext%\\OpenWithList\" /v \"g\" /t REG_SZ /d \"%exe%\" /f ";
	string exe=ExtractFilenameNoExt(app)+".exe";
	trim(exts,";");
	exts=replaceAll(exts,";;",";");

	vstring vext=split(exts,";");
	stringstream cmds;
	lop(i,0,vext.size()){
		dbgv(vext[i]);
		string r="";//rege;
		r=replaceAll(r,"%exe%",exe);
		r=replaceAll(r,"%ext%",vext[i]);
		cmds<<"& "<<r;
		cmds<<"& assoc ."<<vext[i]<<"=spl ";
	}

	reg=replaceAll(reg,"%exe%",exe);
	reg=replaceAll(reg,"%path%",app);
reg="";


	cmds<<"& "<<reg<<" & ftype spl=\""<<app<<"\"  \"%1\"";
	string cmd=cmds.str();
	triml(cmd,"&"); 

	string params="/c "+cmd+" & pause";
 dbgv(params);
    ShellExecuteA  (
        NULL,
        ("runas"),
        "cmd",
        params.c_str(),    // params
        NULL,        // directory
        SW_SHOW
        );
}
  

void setPriorityClass(int p ){
	int pp[]={REALTIME_PRIORITY_CLASS,HIGH_PRIORITY_CLASS};
	SetPriorityClass(GetCurrentProcess(), pp[p]);
}



void setFocus(HWND hw){
	SetFocus(hw);
}

 



#include <ShObjIdl.h>

void Win7TaskbarProgress::SetProgressValue( unsigned long long ullCompleted, unsigned long long ullTotal ){
ITaskbarList3* m_pITaskBarList3_= ((ITaskbarList3*)m_pITaskBarList3);
m_pITaskBarList3_->SetProgressValue(hwnd7, ullCompleted, ullTotal);
}
bool Win7TaskbarProgress::Init(){

if (m_pITaskBarList3)
return true;
if (m_bFailed)
return false;
ITaskbarList3* m_pITaskBarList3_;
// Initialize COM for this thread...
CoInitialize(NULL);
CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_INPROC_SERVER, IID_ITaskbarList3, (void **)&m_pITaskBarList3_);
if (m_pITaskBarList3_){
	m_pITaskBarList3= ((void*)m_pITaskBarList3_);
return true;
}
m_bFailed = true;
CoUninitialize();
return false;
}
Win7TaskbarProgress::Win7TaskbarProgress(unsigned long long ullTotal,HWND Hwnd ){
w7tbpTotal=ullTotal;
segment=w7tbpTotal/50.0;//50 segmentos
if(w7tbpTotal<50)segment=1;
if(Hwnd==NULL)Hwnd=GetConsoleWindow();
hwnd7=Hwnd;
m_pITaskBarList3 = NULL;
m_bFailed = false;
Init();
}
Win7TaskbarProgress::Win7TaskbarProgress(HWND Hwnd ){
if(Hwnd==NULL)Hwnd=GetConsoleWindow();
hwnd7=Hwnd;
m_pITaskBarList3 = NULL;
m_bFailed = false;
Init();
}
Win7TaskbarProgress::~Win7TaskbarProgress(){
ITaskbarList3* m_pITaskBarList3_= ((ITaskbarList3*)m_pITaskBarList3);
if (m_pITaskBarList3_) {
m_pITaskBarList3_->Release();
CoUninitialize();
}
} 
void Win7TaskbarProgress::SetProgressValue( unsigned long long ullCompleted ){  
if(ullCompleted==w7tbpTotal){SetProgressStateINDETERMINATE();return;}
if(ullCompleted%segment!=0)return;
ITaskbarList3* m_pITaskBarList3_= ((ITaskbarList3*)m_pITaskBarList3);
m_pITaskBarList3_->SetProgressValue(hwnd7, ullCompleted, w7tbpTotal);
}
void Win7TaskbarProgress::SetProgressState( int flag){
ITaskbarList3* m_pITaskBarList3_= ((ITaskbarList3*)m_pITaskBarList3);
m_pITaskBarList3_->SetProgressState(hwnd7,(TBPFLAG)flag);
}
void Win7TaskbarProgress::SetProgressStateINDETERMINATE( ){
ITaskbarList3* m_pITaskBarList3_= ((ITaskbarList3*)m_pITaskBarList3);
m_pITaskBarList3_-> SetProgressState(hwnd7,TBPFLAG::TBPF_INDETERMINATE );
}
void Win7TaskbarProgress::SetProgressStateNORMAL( ){
((ITaskbarList3*)m_pITaskBarList3)->SetProgressState(hwnd7,TBPFLAG::TBPF_NOPROGRESS );
}


string RegRead (HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue){
    HKEY hKey;
    DWORD Type;
    int r1=RegOpenKeyExA(hKeyRoot,pszSubKey,0,KEY_QUERY_VALUE,&hKey);
    char res[8096];
    DWORD lin=sizeof(res);
    int result=RegQueryValueExA(hKey,pszValue,NULL,&Type,(LPBYTE)res,&lin);
    RegCloseKey(hKey);  
return res;
}
 
bool RegWrite(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue, LPCTSTR pszString,int rtype){
    HKEY  hKey;
    LONG  lRes;
    DWORD dwSize = lstrlen(pszString) * sizeof(TCHAR);
	lRes = RegOpenKeyEx(hKeyRoot,pszSubKey, 0, KEY_WRITE, &hKey);
    if(lRes != ERROR_SUCCESS)    {
        SetLastError(lRes);
        return false;
    }
    lRes = RegSetValueEx(hKey, pszValue, 0, rtype, (unsigned char*)pszString, dwSize);
	//BYTE* pp=new BYTE[sizeof(pszString)];
	//wsprintf((LPWSTR)pp,_T("%s"),pszString);
 //   lRes = RegSetValueEx(hKey, pszValue, 0, REG_BINARY, pp, dwSize);
    RegCloseKey(hKey);
    if(lRes!=ERROR_SUCCESS) {
        SetLastError(lRes);
        return false;
    }
    return true;
}
 
void RegPathSet(const char* toset,const char* delim){
    string rr=RegRead (HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment","Path");
    vector<string> rrl=split(rr,";");
    vector<string> wr=split(toset,delim);
    for(int w=0;w<wr.size();w++){
        if(contains(wr[w],"//",0)==false){
            //add
            if(dirExists(wr[w])&& indexOf(rrl,0,rrl.size(),wr[w])==-1)rrl.push_back(wr[w]);
        }else{
            //remove
            string tor=replaceAll(wr[w],"//","");
            int iotor=indexOf(rrl,0,rrl.size(),tor);
            if(iotor!=-1)rrl.erase(rrl.begin()+iotor);
        }
    }
//    dbgp("\n %s",join(rrl,"\n").c_str());
    string rrw=joina(rrl,0,rrl.size(),";");
    rrw=replaceAll(rrw,";;",";");
    //só funca com privilegios
    RegWrite(HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment","Path",rrw.c_str(),REG_EXPAND_SZ);
    SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, 0,(LPARAM) "Environment", SMTO_ABORTIFHUNG, 5000,NULL);
}

bool IsRunAsAdmin(){
    BOOL fIsRunAsAdmin = FALSE;
    DWORD dwError = ERROR_SUCCESS;
    PSID pAdministratorsGroup = NULL;

    // Allocate and initialize a SID of the administrators group.
    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    if (!AllocateAndInitializeSid(
        &NtAuthority,
        2,
        SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_ADMINS,
        0, 0, 0, 0, 0, 0,
        &pAdministratorsGroup))
    {
        dwError = GetLastError();
        goto Cleanup;
    }
    // Determine whether the SID of administrators group is enabled in
    // the primary access token of the process.
    if (!CheckTokenMembership(NULL, pAdministratorsGroup, &fIsRunAsAdmin))
    {
        dwError = GetLastError();
        goto Cleanup;
    }
Cleanup:
    // Centralized cleanup for all allocated resources.
    if (pAdministratorsGroup)
    {
        FreeSid(pAdministratorsGroup);
        pAdministratorsGroup = NULL;
    }

    // Throw the error if something failed in the function.
    if (ERROR_SUCCESS != dwError)
    {
        throw dwError;
    }

    return fIsRunAsAdmin;
}

void startRunAsAdmin(){
    if(IsRunAsAdmin())return;
    ShellExecuteA  (
        NULL,
        ("runas"),
        AppFullPath().c_str(),
        (""),    // params
        NULL,        // directory
        SW_SHOW
        );
    exit(0);
}


#endif
