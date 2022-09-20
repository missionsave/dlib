#ifndef THREADS_HPP_INCLUDED
#define THREADS_HPP_INCLUDED

#define singleinstance(app) if(getProcIdByName( #app ).size()>1)exit(0);

#define bstd boost
#define qtcpus 3

#define threadsAllCpuJoin(func)({ auto tothread=[&](unsigned int tid){func}; bstd::thread thr[qtcpus];for(int ti=0;ti<qtcpus;ti++) thr[ti]= bstd::thread(tothread,ti); for(int ti=0;ti<qtcpus;ti++)thr[ti].join();})

#define threadsAllCpuJoinLoopPB(func,iters,...)({ Win7TaskbarProgress wtpr(iters);unsigned int totalit=0; auto tothread=[&](unsigned int tid){for(unsigned int it=0;it<iters;it++){if((it+tid)%qtcpus!=0)continue;  func totalit++; wtpr.SetProgressValue(totalit);}}; bstd::thread thr[qtcpus];for(int ti=0;ti<qtcpus;ti++) thr[ti]= bstd::thread(tothread,ti); for(int ti=0;ti<qtcpus;ti++)thr[ti].join(); wtpr.SetProgressState(0); __VA_ARGS__; })

#define threadsAllCpuJoinLoop(func,iters,...)({  unsigned int totalit=0; auto tothread=[&](unsigned int tid){for(unsigned int it=0;it<iters;it++){if((it+tid)%qtcpus!=0)continue;   func totalit++;}}; bstd::thread thr[qtcpus];for(int ti=0;ti<qtcpus;ti++) thr[ti]= bstd::thread(tothread,ti); for(int ti=0;ti<qtcpus;ti++)thr[ti].join(); __VA_ARGS__; })

#include "regular.hpp"
#include <functional> 

bool pidIsRunning(int pid);

void OpenWebsite (char * cpURL);

void sleep(int milisecs); 

void mtxlock(void* mtex);
void mtxunlock(void* mtex);

void mtxlock(int id);
void mtxunlock(int id);
void threadf(int id,const std::function<void()> tf);
void threadjoin(int id);

void threadgsame(int qt,const function<void()> tf);

void  threadJoin(std::function<void()> tf);
void* threadDetach(std::function<void()> tf);
void threadTerminate(void* th);

vint getProcIdByName(string procName);

void startRunAsAdmin(string cmd,string params);

long unsigned int AppRunWaitHidden(std::string cmd);

string exec(char* cmd);
string AppRunStdoutr(string cmd, const function<void(string out)> p=NULL) ;
void AppRunStdout(string cmd, const function<void(string out)> p=NULL,const function<void(string out)> done=NULL);
 

void beep();
void soundbeep(int h,int t ); 

#endif // THREAD_HPP_INCLUDED
