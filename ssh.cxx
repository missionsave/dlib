#include "ssh.hpp"
#include "regular.hpp"
#include "stringf.hpp"

#include <string.h>

//#include "libssh2_config.h"
#include <libssh2.h>
#include <libssh2_sftp.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>




#include <iostream>
#include <sstream>
#include <unordered_map>
#include "zip.hpp"
#include <boost/filesystem.hpp>
#include <fstream>

void sleepms(int milisecs);

string sshconnect::exec(string cmd)
{
//  int rc;
//  char buffer[256];
//  int nbytes;
//  channel = libssh2_channel_new(session);
//  if (channel == NULL)
//    return SSH_ERROR;
//  rc = ssh_channel_open_session(channel);
//  if (rc != SSH_OK)
//  {
//    ssh_channel_free(channel);
//    return rc;
//  }
//  rc = ssh_channel_request_exec(channel, cmd.c_str());
//  if (rc != SSH_OK)
//  {
//    ssh_channel_close(channel);
//    ssh_channel_free(channel);
//    return rc;
//  }
//  nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
//  while (nbytes > 0)
//  {
//    if (write(1, buffer, nbytes) != (unsigned int) nbytes)
//    {
//      ssh_channel_close(channel);
//      ssh_channel_free(channel);
//      return SSH_ERROR;
//    }
//    nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
//  }
//
//  if (nbytes < 0)
//  {
//    ssh_channel_close(channel);
//    ssh_channel_free(channel);
//    return SSH_ERROR;
//  }
//  ssh_channel_send_eof(channel);
//  ssh_channel_close(channel);
//  ssh_channel_free(channel);
////  return SSH_OK;
//  return string(buffer,nbytes);

}



//where remotefile>filename, get filename+=remotefile-filename
void sshconnect::sftpgetAppend(string filename,string remotefile){
	struct stat fileinfolocal;
	_LIBSSH2_SFTP_ATTRIBUTES fileinfo;
	int rc;
//    LIBSSH2_SFTP *sftp_session;

    LIBSSH2_SFTP_HANDLE *sftp_handle;
  size_t got = 0;


	stat(filename.c_str(), &fileinfolocal);


    if(sftp_session==0){
    	fprintf(stderr, "libssh2_sftp_init()!\n");
    	sftp_session = libssh2_sftp_init(session);
    }

    if (!sftp_session) {
        fprintf(stderr, "Unable to init SFTP session\n");
        return;
    }

    sftp_handle = libssh2_sftp_open(sftp_session, remotefile.c_str(), LIBSSH2_FXF_READ, 0);

    if (!sftp_handle) {
        fprintf(stderr, "Unable to open file with SFTP: %ld\n",
                libssh2_sftp_last_error(sftp_session));
        return;
    }
//    fprintf(stderr, "libssh2_sftp_open() is done, now receive data!\n");

//    libssh2_sftp_fstat(sftp_handle,&fileinfo);

    //dbgv(fileinfo.filesize);return;
//		if(fileinfolocal.st_size>=fileinfo.filesize){
//			libssh2_sftp_close(sftp_handle);
////			libssh2_sftp_shutdown(sftp_session);
//			fprintf(stderr, "remote file is not bigger\n");
//			return;
//		}
//		libssh2_uint64_t offset=fileinfo.filesize-(fileinfo.filesize-fileinfolocal.st_size);
    libssh2_sftp_seek64(sftp_handle,fileinfolocal.st_size);
//    dbgv((int)offset);//return;
    int rcc=0;
    FILE* pFile = fopen (filename.c_str(), "ab");
        char mem[4096];
    do {

        /* loop until we fail */
//        fprintf(stderr, "libssh2_sftp_read()!\n");
        rc = libssh2_sftp_read(sftp_handle, mem, sizeof(mem));
//        dbgv(rc);
        if (rc > 0) {
        		fwrite (mem , sizeof(char), rc, pFile);
            //write(1, mem, rc);
//            dbgv(rcc+=rc);
        } else {
            break;
        }
    } while (1);
		fclose (pFile);
    libssh2_sftp_close(sftp_handle);
//    libssh2_sftp_shutdown(sftp_session);
}


void sshconnect::scpget(string filename,string remotefile){
	 struct stat fileinfo;
	int rc;
  size_t got = 0;

    channel = libssh2_scp_recv(session, remotefile.c_str(), &fileinfo);
//dbgv(fileinfo.st_size);libssh2_channel_free(channel);return;
    if (!channel) {
        fprintf(stderr, "Unable to open a session: %d\n",
                libssh2_session_last_errno(session));
        return;
    }


		FILE* pFile = fopen (filename.c_str(), "wb");
    while(got < fileinfo.st_size) {
        char mem[1024];
        int amount=sizeof(mem);

        if((fileinfo.st_size -got) < amount) {
            amount = (int)(fileinfo.st_size -got);
        }

        rc = libssh2_channel_read(channel, mem, amount);
        if(rc > 0) {
        		fwrite (mem , sizeof(char), rc, pFile);
            //write(1, mem, rc);
        }
        else if(rc < 0) {
            fprintf(stderr, "libssh2_channel_read() failed: %d\n", rc);
            break;
        }
        got += rc;
    }
    fclose (pFile);

    libssh2_channel_free(channel);
    channel = NULL;
}


void sshconnect::scpsendstr(string sbin,string remotefile){
	int rc;
	char *ptr;
  char mem[1024];
  size_t nread;

	    /* Send a file via scp. The mode parameter must only have permissions! */
    channel = libssh2_scp_send(session,remotefile.c_str(), 33279 & 0777,(unsigned long)sbin.size());

    if (!channel) {
        char *errmsg;
        int errlen;
        int err = libssh2_session_last_error(session, &errmsg, &errlen, 0);
        fprintf(stderr, "Unable to open a session: (%d) %s\n", err, errmsg);
        return;
    }
		nread=sbin.size();
		ptr=(char*)sbin.c_str();
 		rc = libssh2_channel_write(channel, ptr, nread);
		if (rc < 0) {
							fprintf(stderr, "ERROR %d\n", rc);
							return;
					}

	    fprintf(stderr, "Sending EOF\n");
    libssh2_channel_send_eof(channel);

    fprintf(stderr, "Waiting for EOF\n");
    libssh2_channel_wait_eof(channel);

    fprintf(stderr, "Waiting for channel to close\n");
    libssh2_channel_wait_closed(channel);

    libssh2_channel_free(channel);
    channel = NULL;
}
void sshconnect::scpsend(string fname,string remotefile){
	int rc;
	char *ptr;
  char mem[1024];
  size_t nread;
	struct stat fileinfo;
	FILE* local = fopen(fname.c_str(), "rb");
	if (!local) {
			fprintf(stderr, "Can't open local file %s\n", fname.c_str());
			return ;
	}
//remotefile="./fxcfg.jsn";
	stat(fname.c_str(), &fileinfo);

	    /* Send a file via scp. The mode parameter must only have permissions! */
    channel = libssh2_scp_send(session,remotefile.c_str(), fileinfo.st_mode & 0777,(unsigned long)fileinfo.st_size);

//	getchar();
    if (!channel) {
        char *errmsg;
        int errlen;
        int err = libssh2_session_last_error(session, &errmsg, &errlen, 0);
        fprintf(stderr, "Unable to open a session: (%d) %s\n", err, errmsg);
        return;
    }

	do {
			nread = fread(mem, 1, sizeof(mem), local);
			if (nread <= 0) {
					/* end of file */
					break;
			}
			ptr = mem;

			do {

					/* write the same data over and over, until error or completion */
					rc = libssh2_channel_write(channel, ptr, nread);
					if (rc < 0) {
							fprintf(stderr, "ERROR %d\n", rc);
							break;
					}
					else {
							/* rc indicates how many bytes were written this time */
							ptr += rc;
							nread -= rc;
					}
			} while (nread);

	} while (1);
	    fprintf(stderr, "Sending EOF\n");
    libssh2_channel_send_eof(channel);

    fprintf(stderr, "Waiting for EOF\n");
    libssh2_channel_wait_eof(channel);

    fprintf(stderr, "Waiting for channel to close\n");
    libssh2_channel_wait_closed(channel);

    libssh2_channel_free(channel);
    channel = NULL;
		if (local)fclose(local);
    fprintf(stderr, "Channel closed\n");
}

void sshconnect::disconnect(){
	if(sftp_session==0)return;
	libssh2_sftp_shutdown(sftp_session);
    libssh2_session_disconnect(session, "Normal Shutdown, Thank you for playing");
    libssh2_session_free(session);
#ifdef WIN32
    closesocket(sock);
#else
    close(sock);
#endif
    fprintf(stderr, "all done\n");
    libssh2_exit();
}
sshconnect::sshconnect(string hostname,string user,string pass){
	int rc;
	struct sockaddr_in sin;
	struct hostent *host;
	if((host=gethostbyname(hostname.c_str()))==0){printf("errorhost");return;}
	long hosti=*(long*)(host->h_addr);


	rc = libssh2_init (0);
	if (rc != 0) {
		fprintf (stderr, "libssh2 initialization failed (%d)\n", rc);
		return ;
	}

		sock = socket(AF_INET, SOCK_STREAM, 0);
		memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(22);
    sin.sin_addr.s_addr = hosti;
    if (connect(sock, (struct sockaddr*)(&sin), sizeof(sin)) != 0) {
        fprintf(stderr, "failed to connect!\n");
        return ;
    }
    session = libssh2_session_init();
    if(!session){
    		fprintf(stderr, "libssh2_session_init Failure establishing: %d\n", rc);
        return ;
    }
//libssh2_session_set_blocking(session, 1);
lop(tries,0,5){
    rc = libssh2_session_handshake(session, sock);
    if(rc) {
        fprintf(stderr, "Failure establishing SSH session: %d\n", rc);
        if(tries>3)return ;
				sleepms(200);
    }else break;
}
    const char *fingerprint=fingerprint = libssh2_hostkey_hash(session, LIBSSH2_HOSTKEY_HASH_SHA1);
    fprintf(stderr, "Fingerprint: ");
    for(int i = 0; i < 20; i++) {
        fprintf(stderr, "%02X ", (unsigned char)fingerprint[i]);
    }
    fprintf(stderr, "\n");

		if (libssh2_userauth_password(session, user.c_str(), pass.c_str())) {
		fprintf(stderr, "Authentication by password failed.\n");
			disconnect();
			return;
		}
    dbgv("connected");
}













 void error(const char* e){
dbgv(e);
}

unordered_map<string,long> gethosts;
long hosti(string hostname){
	//if(gethosts[hostname]!=0)return gethosts[hostname];
	struct hostent *host;
	if((host=gethostbyname(hostname.c_str()))==0){printf("errorhost");return 0;}
	//gethosts[hostname]= *(long*)(host->h_addr);
	return *(long*)(host->h_addr);;
}
int recv_to(int fd, char *buffer, int len, int flags, int to=4000) {

   fd_set readset,tempset;
   int result, iof = -1;
   struct timeval tv;

   // Initialize the set
   FD_ZERO(&readset);
   FD_SET(fd, &readset);

   // Initialize time out struct
   tv.tv_sec = 0;
   tv.tv_usec = to * 1000;
   // select()
   result = select(fd+1, &tempset, NULL, NULL, &tv);

   // Check status
   if (result < 0)
      return -1;
   else if (result > 0 && FD_ISSET(fd, &tempset)) {
      // Set non-blocking mode
      if ((iof = fcntl(fd, F_GETFL, 0)) != -1)
         fcntl(fd, F_SETFL, iof | O_NONBLOCK);
      // receive
      result = recv(fd, buffer, len, flags);
      // set as before
      if (iof != -1)
         fcntl(fd, F_SETFL, iof);
      return result;
   }
   return -2;
}

int httpg(string &into,string hostname, string urlreq) {
    struct sockaddr_in addr_s;
    char *addr;
    short int fd=-1;
    int port;
    fd_set fdset;
    struct timeval tv;
    int rc;
    int so_error;
    socklen_t len;
    struct timespec tstart={0,0}, tend={0,0};
    int seconds;

//    if (argc != 4) {
//        fprintf(stderr, "Usage: %s <ip> <port> <timeout_seconds>\n", argv[0]);
//        return 1;
//    }

//    addr = (char*)hostname.c_str();//argv[1];
    port = 80;//atoi(argv[2]);
    seconds = 5;//atoi(argv[3]);

    addr_s.sin_family = AF_INET; // utilizzo IPv4
    addr_s.sin_addr.s_addr = hosti(hostname);// inet_addr(addr);
    addr_s.sin_port = htons(port);

    clock_gettime(CLOCK_MONOTONIC, &tstart);

    fd = socket(AF_INET, SOCK_STREAM, 0);
    fcntl(fd, F_SETFL, O_NONBLOCK); // setup non blocking socket

    // make the connection
    rc = connect(fd, (struct sockaddr *)&addr_s, sizeof(addr_s));
    if ((rc == -1) && (errno != EINPROGRESS)) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        close(fd);
        return 1;
    }
    if (rc == 0) {
        // connection has succeeded immediately
        clock_gettime(CLOCK_MONOTONIC, &tend);
        printf("socket %s:%d connected. It took %.5f seconds\n",
            hostname.c_str(), port, (((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec)));

        close(fd);
        return 0;
    } /*else {
        // connection attempt is in progress
    } */

    FD_ZERO(&fdset);
    FD_SET(fd, &fdset);
    tv.tv_sec = seconds;
    tv.tv_usec = 0;

    rc = select(fd + 1, NULL, &fdset, NULL, &tv);
    switch(rc) {
    case 1: // data to read
        len = sizeof(so_error);

        getsockopt(fd, SOL_SOCKET, SO_ERROR, &so_error, &len);

        if (so_error == 0) {
            clock_gettime(CLOCK_MONOTONIC, &tend);
            printf("socket %s:%d connected.. It took %.5f seconds\n",
                hostname.c_str(), port, (((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec)));


                char buffer[1024*4];
    //Make and send get request
    sprintf(buffer, "GET %s HTTP/1.1\r\n"
        "Host: %s\r\n"
        "Connection: close\r\n"
        "\r\n", urlreq.c_str(), hostname.c_str());
//        dbgv(buffer);
    int rc =send(fd, buffer, (strlen(buffer)), 0);

   dbgv(0,rc);
//    bool success = false;
    const char * text=buffer;
//sleepms(200);
//	for(int i=0;i<4;i++){
		rc=recv(fd, buffer, sizeof(buffer),0);
//	if(rc<0)sleepms(200);
//	if(rc<=0)
//		dbgv(rc);
//	}



//dbgv(rc,buffer);
	int start=0;
	for(start; start <rc; start++){
		text++;
		if(strncmp(text, "\r\n\r\n", 4) == 0){
			text+=4;
			start+=5;
//			dbgv(start);
			break;
		}
	}
//	stringstream strb;
//dbgv(rc,start,rc-start);
//	if(rc==start){
//		into=string(buffer);
//		close(sockfd);
//		return;
//	}
dbgv(rc,start,text,rc-start);
getchar();
	into=string(text,rc-start);
	getchar();
//	dbgv(rc,sizeof(buffer));
//	if(rc<sizeof(buffer)){
//		close(sockfd);
//		return;
//
//	}
//	string str(text);
//	into.append(str);
//	into.append(string(text,rc-start));
//	dbgv(str);
//	dbgv(sizeof(text),sizeof(buffer)-start,str.size());
	do {
//		char mem[1024];

		rc = recv(fd, buffer, sizeof(buffer),0);
		getchar();
//		dbgv(rc);
		if (rc > 0) {
//				strb<<mem;
		into.append(string(buffer,rc));
		//fwrite (mem , sizeof(char), rc, pFile);
		//write(1, mem, rc);
		//dbgv(rcc+=rc);
		} else {
//			if(rc<0)dbgv(rc);
		break;
		}
	} while (1);




            close(fd);
            return 0;
        } else { // error
            printf("socket %s:%d NOT connected: %s\n", addr, port, strerror(so_error));
        }
        break;
    case 0: //timeout
        fprintf(stderr, "connection timeout trying to connect to %s:%d\n", addr, port);
        break;
    }

    close(fd);
    return 0;
}


void httpget(string &into,string hostname, string urlreq){
	int sockfd, portno, n;
	struct sockaddr_in sin;

		sockfd = socket(AF_INET, SOCK_STREAM, 0);
//		fcntl(sockfd, F_SETFL, O_NONBLOCK);
		memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(80);
    sin.sin_addr.s_addr = hosti(hostname);
    int tryes=3;
    while (connect(sockfd, (struct sockaddr*)(&sin), sizeof(sin)) != 0) {
        fprintf(stderr, "failed to connect!\n");
        sleepms(400);
        if(tryes--<0)return ;
    }
    if(tryes!=3)dbgv(tryes,"reconnected");

    char buffer[1024*4];
    //Make and send get request
    sprintf(buffer, "GET %s HTTP/1.1\r\n"
        "Host: %s\r\n"
        "Connection: close\r\n"
        "\r\n", urlreq.c_str(), hostname.c_str());
         //dbgv(buffer);
    int rc =send(sockfd, buffer, (strlen(buffer)), 0);

   //dbgv(0,rc);
//    bool success = false;
    const char * text=buffer;
//sleepms(200);
//	for(int i=0;i<4;i++){
		rc=recv(sockfd, buffer, sizeof(buffer),0);

///if moved permanently
dbgv(buffer);

//	if(rc<0)sleepms(200);
//	if(rc<=0)
//		dbgv(rc);
//	}



//dbgv(rc,buffer);
	int start=0;
	for(start; start <rc; start++){
		text++;
		if(strncmp(text, "\r\n\r\n", 4) == 0){
			text+=4;
			start+=5;
//			dbgv(start);
			break;
		}
	}
//	stringstream strb;
//dbgv(rc,start,rc-start);
//	if(rc==start){
//		into=string(buffer);
//		close(sockfd);
//		return;
//	}
//dbgv(rc,start,text,rc-start);
//getchar();
	into=string(text,rc-start);
//	dbgv(rc,sizeof(buffer));
//	if(rc<sizeof(buffer)){
//		close(sockfd);
//		return;
//
//	}
//	string str(text);
//	into.append(str);
//	into.append(string(text,rc-start));
//	dbgv(str);
//	dbgv(sizeof(text),sizeof(buffer)-start,str.size());
	do {
//		char mem[1024];

		rc = recv(sockfd, buffer, sizeof(buffer),0);
//		dbgv(rc);
		if (rc > 0) {
//				strb<<mem;
		into.append(string(buffer,rc));
		//fwrite (mem , sizeof(char), rc, pFile);
		//write(1, mem, rc);
		//dbgv(rcc+=rc);
		} else {
//			if(rc<0)dbgv(rc);
		break;
		}
	} while (1);

     close(sockfd);
//     dbgv(into.size());
//     dbgv(7);
    //return strb.str();
}
#include <boost/asio.hpp>
string get_http_data(const std::string& server, const std::string& file)
{
	try
	{
		boost::asio::ip::tcp::iostream s(server, "http");
		s.expires_from_now(boost::posix_time::seconds(60));

		if (!s){ throw "Unable to connect: " + s.error().message(); }

		// ask for the file
		s << "GET " << file << " HTTP/1.0\r\n";
		s << "Host: " << server << "\r\n";
		s << "Accept: */*\r\n";
		s << "Connection: close\r\n\r\n";

		// Check that response is OK.
		std::string http_version;
		s >> http_version;
		unsigned int status_code;
		s >> status_code;
		std::string status_message;
		std::getline(s, status_message);
		if (!s && http_version.substr(0, 5) != "HTTP/"){ throw "Invalid response\n"; }
		if (status_code != 200){ throw "Response returned with status code " + status_code; }

		// Process the response headers, which are terminated by a blank line.
		std::string header;
		while (std::getline(s, header) && header != "\r"){}

		// Write the remaining data to output.
		std::stringstream ss;
		ss << s.rdbuf();
		return ss.str();
	}
	catch(std::exception& e)
	{
		dbgv("error");

		return e.what();
	}
}


