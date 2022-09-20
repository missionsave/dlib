#include "threads.hpp"
#include "regular.hpp"
#include "stringf.hpp"
#include "arrayf.hpp"
#include <fstream>
#include <stdio.h>

#include <boost/predef.h>
#if BOOST_OS_WINDOWS
#include "windows.h"
#include "Wtsapi32.h"
#include <windef.h>
#endif
 

#if BOOST_OS_LINUX 
#include <unistd.h>
#include <sys/wait.h> 
#include <sys/types.h>
#include <dirent.h>
#endif
//~ #include "Userenv.h"
//~ #include <tchar.h>

 
//#include <strsafe.h>

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp> 

#define BUFSIZE 32*1024

   
#ifdef WIN32
#include <tlhelp32.h>
bool pidIsRunning(int pid) {   
	HANDLE pss = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);   
	PROCESSENTRY32 pe = { 0 };  
	pe.dwSize = sizeof(pe);  
	if (Process32First(pss, &pe)){  
		do {  
			// pe.szExeFile can also be useful  
			if (pe.th32ProcessID == pid)  
				return true;   
			}  
		while(Process32Next(pss, &pe));  
	}
	CloseHandle(pss);
	return false; 
}
#endif

#ifdef __linux__
bool pidIsRunning(int pid) { 
	return 0 == kill(pid, 0); 
}
#endif

void mtxlock(void* mtex){
	if(!mtex)mtex=new boost::mutex;
	((boost::mutex*)mtex)->lock();
}
void mtxunlock(void* mtex){
	((boost::mutex*)mtex)->unlock();
} 
 
vector<boost::mutex> mtx=vector<boost::mutex>(10);
vector<bool> mtxl=vbool(10);
vector<boost::thread> thr=vector<boost::thread>(10);
void mtxlock(int id){
//	if(mtxl[id]==0){
		mtxl[id]=1;
//		mtx[id].unlock();
		mtx[id].lock();
//	} 
} 
void mtxunlock(int id){	
//	if(mtxl[id]==1){
		mtxl[id]=0;
//		mtx[id].lock();
		mtx[id].unlock();
//	}
}
void threadf(int id,const function<void()> tf){
	thr[id]=boost::thread(tf);
}
void threadjoin(int id){
	thr[id].join();
}

void threadgsame(int qt,const function<void()> tf){
	boost::thread_group group;
for (int i = 0; i < qt; ++i)
    group.create_thread(tf);
	group.join_all();
}

void* threadDetach(std::function<void()> tf){
    boost::thread th(tf);
//    SetPriorityClass(th.native_handle(), REALTIME_PRIORITY_CLASS);
    th.detach();
//    boost::thread(tf).detach();
//	return (void*)&th;
	return (void*)th.native_handle();
}
void  threadJoin(std::function<void()> tf){
    boost::thread th(tf);
    th.join(); 
}
void threadTerminate(void* th){
//	TerminateThread(th, 0);
} 
 
 
void startRunAsAdmin(string cmd,string params){
#if BOOST_OS_WINDOWS
//    if(IsRunAsAdmin())return;
    ShellExecuteA  (
        NULL,
        ("runas"),
        cmd.c_str(),
        (params.c_str()),    // params
        NULL,        // directory
        SW_SHOW
        );
    exit(0);
#endif
}
 
  

#if BOOST_OS_LINUX

void OpenWebsite (char * cpURL){
threadDetach([=]{
string o="xdg-open \""+string(cpURL)+"\"";
exec((char*)o.c_str());
}); 
}

string AppRunStdoutr(string cmd, const function<void(string out)> p) { 
	cmd+=" 2>&1";
	FILE *in;
	char buff[512];
	if(!(in = popen(cmd.c_str(), "r"))){
		return "";
	} 
	string sout="";
	while(fgets(buff, sizeof(buff), in)!=NULL){
		sout+=buff;
		if(p){
			p(buff);
			fflush(stdout);
		}
	} 
	pclose(in);
	fflush(stdout);
	return sout;
}
void AppRunStdout(string cmd, const function<void(string out)> p,const function<void(string out)> done) { 
	cmd+=" 2>&1";
	FILE *in;
	char buff[512];
	if(!(in = popen(cmd.c_str(), "r"))){
		return ;
	} 
	string sout="";
	while(fgets(buff, sizeof(buff), in)!=NULL){
		sout+=buff;
		if(p)p(buff);
	} 
	pclose(in);	
	fflush(stdout);
	if(done)done(sout);
 
/*not threadsafe
	trim(cmd," ");
	lop(i,0,5)subst(cmd,"  "," ");
	vstring theArgs=split(cmd," ");	
	char * exec_args[128]; 
	exec_args[theArgs.size()] = NULL; 
	for (int x = 0; x < theArgs.size(); x++) {
		trim(theArgs[x]," ");
		exec_args[x] = strdup(theArgs[x].c_str());
		dbgv(exec_args[x]);
	} 
 	string sout;
	int len=512;
	char buffer[len];
	int fd[3];
	pipe(fd);

	pid_t pid = fork();
	if(pid == 0) {
		dup2(fd[1], STDERR_FILENO);
		close(fd[0]);
 		//execv(), the first argument is a path to the executable. execvp(), the first argument is a filename. It must be converted to a path before it can used. This involves looking for the filename in all of the directories in the PATH environment variable.
		execvp(exec_args[0], exec_args);
		//execlp("g++", "g++","-c","/mnt/sda1/Desk/Mpm/_lib/stringf.cpp", NULL);
	}
	else {
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		string lout;
		while (fgets(buffer, len, stdin)) { 
			lout=string(buffer);
			sout+=lout; 
			if(p)p(lout);
		}
		waitpid(pid, NULL, 0);
		if(done)done(sout);
	} 
	*/
}

vint getProcIdByName(string procName){
    vint pid;
    // Open the /proc directory
    DIR *dp = opendir("/proc");
    if (dp != NULL)  {
        // Enumerate all entries in directory until process found
        struct dirent *dirp;
        while (dirp = readdir(dp))  {
            // Skip non-numeric entries
            int id = atoi(dirp->d_name);
            if (id > 0)            {
                // Read contents of virtual /proc/{pid}/cmdline file
                string cmdPath = string("/proc/") + dirp->d_name + "/cmdline";
                ifstream cmdFile(cmdPath.c_str());
                string cmdLine;
                getline(cmdFile, cmdLine);
                if (!cmdLine.empty())                {
                    // Keep first cmdline item which contains the program path
                    size_t pos = cmdLine.find('\0');
                    if (pos != string::npos)
                        cmdLine = cmdLine.substr(0, pos);
                    // Keep program name only, removing the path
                    pos = cmdLine.rfind('/');
                    if (pos != string::npos)
                        cmdLine = cmdLine.substr(pos + 1);
                    // Compare against requested process name
                    if (procName == cmdLine)
                        pid.push_back(id);
                }
            }
        }
    }
    closedir(dp);
    return pid;
}


#endif

void sleep(int milisecs){
	boost::this_thread::sleep_for( boost::chrono::milliseconds(milisecs) );
}
#if BOOST_OS_WINDOWS

/*
void sleep(int milisecs){
	Sleep(milisecs);
} 
*/

void OpenWebsite (char * cpURL){
	ShellExecute (NULL, "open", cpURL, NULL, NULL, SW_SHOWNORMAL);
}
string AppRunStdoutr(string cmd, const function<void(string out)> p){ 
//	HANDLE std_IN[2]; 
	HANDLE std_OUT[2];
	HANDLE std_ERR[2];
	SECURITY_ATTRIBUTES saAttr;
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = NULL;
	if(!CreatePipe(&std_OUT[0],&std_OUT[1],&saAttr,0))return "";
	if(!SetHandleInformation(std_OUT[0],HANDLE_FLAG_INHERIT,0))
		return "";// "Error 1 "+cmd;
//	if (!CreatePipe(&std_ERR[0],&std_ERR[1], &saAttr,0))return;
//	if(!SetHandleInformation(std_ERR[0],HANDLE_FLAG_INHERIT,0))
//		return "";// "Error 2 "+cmd;
//	if (!CreatePipe(&std_IN[0],&std_IN[1], &saAttr,0))return;
//	if(!SetHandleInformation(std_IN[1],HANDLE_FLAG_INHERIT,0))
//		return "";// "Error 2 "+cmd;
	PROCESS_INFORMATION piProcInfo;
	STARTUPINFO siStartInfo;
	BOOL bSuccess = FALSE;
	ZeroMemory( &piProcInfo, sizeof(PROCESS_INFORMATION) );
	ZeroMemory( &siStartInfo, sizeof(STARTUPINFO) );
	siStartInfo.cb = sizeof(STARTUPINFO);
	siStartInfo.hStdError = std_OUT[1];
	siStartInfo.hStdOutput = std_OUT[1]; 
	siStartInfo.dwFlags |= STARTF_USESTDHANDLES;
	char res[2048];
	ConvertUtf8ToCp1251(cmd.c_str(),res,2048);
	bSuccess = CreateProcess(NULL,
		res,     // command line
		NULL,          // process security attributes
		NULL,          // primary thread security attributes
		TRUE,          // handles are inherited
		CREATE_NO_WINDOW,//  |DETACHED_PROCESS|CREATE_NEW_PROCESS_GROUP,             // creation flags
		NULL,          // use parent's environment
		NULL,          // use parent's current directory
		&siStartInfo,  // STARTUPINFO pointer
		&piProcInfo);  // receives PROCESS_INFORMATION
	if ( ! bSuccess )
		return "";// "Error 3 "+cmd;
	else{ 
		CloseHandle(piProcInfo.hProcess);
		CloseHandle(piProcInfo.hThread);
		CloseHandle(std_OUT[1]);
	}
	DWORD dwRead;
	CHAR chBuf[BUFSIZE];
	std::string out = "", err = "";
	for (;;) {
		bSuccess=ReadFile( std_OUT[0], chBuf, BUFSIZE, &dwRead, NULL);
		if( ! bSuccess || dwRead == 0 ) break; 
		std::string s(chBuf, dwRead);
		out += s; 
		if(p)p(s);
	}
		CloseHandle(piProcInfo.hProcess);
		CloseHandle(piProcInfo.hThread);
		CloseHandle(std_OUT[1]);
	return out;
}
void AppRunStdout(string cmd, const function<void(string out)> p,const function<void(string out)> done){ 
//	HANDLE std_IN[2]; 
	HANDLE std_OUT[2];
	HANDLE std_ERR[2];
	SECURITY_ATTRIBUTES saAttr;
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = NULL;
	if(!CreatePipe(&std_OUT[0],&std_OUT[1],&saAttr,0))return;
	if(!SetHandleInformation(std_OUT[0],HANDLE_FLAG_INHERIT,0))
		return;// "Error 1 "+cmd;
//	if (!CreatePipe(&std_ERR[0],&std_ERR[1], &saAttr,0))return;
//	if(!SetHandleInformation(std_ERR[0],HANDLE_FLAG_INHERIT,0))
//		return;// "Error 2 "+cmd;
//	if (!CreatePipe(&std_IN[0],&std_IN[1], &saAttr,0))return;
//	if(!SetHandleInformation(std_IN[1],HANDLE_FLAG_INHERIT,0))
//		return;// "Error 2 "+cmd;
	PROCESS_INFORMATION piProcInfo;
	STARTUPINFO siStartInfo;
	BOOL bSuccess = FALSE;
	ZeroMemory( &piProcInfo, sizeof(PROCESS_INFORMATION) );
	ZeroMemory( &siStartInfo, sizeof(STARTUPINFO) );
	siStartInfo.cb = sizeof(STARTUPINFO);
	siStartInfo.hStdError = std_OUT[1];
	siStartInfo.hStdOutput = std_OUT[1]; 
	siStartInfo.dwFlags |= STARTF_USESTDHANDLES;
	char res[2048];
	ConvertUtf8ToCp1251(cmd.c_str(),res,2048);
	bSuccess = CreateProcess(NULL,
		res,     // command line
		NULL,          // process security attributes
		NULL,          // primary thread security attributes
		TRUE,          // handles are inherited
		CREATE_NO_WINDOW,//  |DETACHED_PROCESS|CREATE_NEW_PROCESS_GROUP,             // creation flags
		NULL,          // use parent's environment
		NULL,          // use parent's current directory
		&siStartInfo,  // STARTUPINFO pointer
		&piProcInfo);  // receives PROCESS_INFORMATION
	if ( ! bSuccess )
		return;// "Error 3 "+cmd;
	else{ 
		CloseHandle(piProcInfo.hProcess);
		CloseHandle(piProcInfo.hThread);
		CloseHandle(std_OUT[1]);
	}
	DWORD dwRead;
	CHAR chBuf[BUFSIZE];
	std::string out = "", err = "";
	for (;;) {
		bSuccess=ReadFile( std_OUT[0], chBuf, BUFSIZE, &dwRead, NULL);
		if( ! bSuccess || dwRead == 0 ) break; 
		std::string s(chBuf, dwRead);
		out += s; 
		if(p)p(s);
	}
		CloseHandle(piProcInfo.hProcess);
		CloseHandle(piProcInfo.hThread);
		CloseHandle(std_OUT[1]);
	if(done)done(out); 
}

long unsigned int AppRunWaitHidden(string cmd){
    char* szCmdline=(char*)cmd.c_str();
    PROCESS_INFORMATION piProcInfo;
    ZeroMemory( &piProcInfo, sizeof(PROCESS_INFORMATION) );

    STARTUPINFO siStartInfo;
    ZeroMemory( &siStartInfo, sizeof(STARTUPINFO) );
    siStartInfo.cb = sizeof(STARTUPINFO);
//    siStartInfo.hStdError = g_hChildStd_ERR_Wr;
//    siStartInfo.hStdOutput = g_hChildStd_OUT_Wr;
    siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

    bool b=CreateProcess(NULL,
        szCmdline,     // command line
        NULL,          // process security attributes
        NULL,          // primary thread security attributes
        FALSE,          // handles are inherited
        CREATE_NO_WINDOW,             // creation flags
        NULL,          // use parent's environment
        NULL,          // use parent's current directory
        &siStartInfo,  // STARTUPINFO pointer
        &piProcInfo);  // receives PROCESS_INFORMATION

    long unsigned int dwErr = 0;
    if( b ) {
        WaitForSingleObject( piProcInfo.hProcess, INFINITE );
        GetExitCodeProcess( piProcInfo.hProcess, &dwErr );
        CloseHandle( piProcInfo.hProcess );
    } else {
        dwErr = GetLastError();
    }
    if( dwErr ) {
        // deal with error here
    }
    return dwErr;
}



void soundbeep(int h,int t ){ Beep(h*0.5,t*0.8);Beep(h*2,t*1.5);}
void beep(){threadDetach([]{Beep(2000,100);});}
#endif

std::string exec(char* cmd) {
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while(!feof(pipe)) {
    	if(fgets(buffer, 128, pipe) != NULL)
    		result += buffer;
    }
    pclose(pipe);
    return result;
}
 
 
