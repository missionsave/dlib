#ifndef SSHc_HPP_INCLUDED
#define SSHc_HPP_INCLUDED
#include "regular.hpp"
#include "stringf.hpp"

#include <libssh2.h>
#include <netinet/in.h>
#include <libssh2_sftp.h> 

struct sshconnect{
	LIBSSH2_SESSION *session;
	LIBSSH2_CHANNEL *channel;
	LIBSSH2_SFTP *sftp_session=0;
	int sock;
	void disconnect();
	sshconnect(string host,string user,string pass);
	void scpsend(string filename,string remotefile);
	void scpget(string filename,string remotefile);
	void sftpgetAppend(string filename,string remotefile);
	void scpsendstr(string sbin,string toremotefile);
	string exec(string cmd);
};
 
long hosti(string hostname); 

void httpget(string &into,string hostname, string urlreq);

#endif / 
