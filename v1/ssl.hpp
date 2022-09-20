#ifndef SSL_HPP_INCLUDED
#define SSL_HPP_INCLUDED
#include "regular.hpp"
#include "stringf.hpp"

#include <netinet/in.h>
//#include <winsock2.h>
#include <openssl/ssl.h>


//sendemail("smtp.gmail.com",587,"superbem@gmail.com","nempamigos.",{"superbem@gmail.com","danielchanfana@gmail.com"},"teste vitoria ","inocente vitoria ");
void sendemail(string hostname,int porti,string sender,string pass,vstring to,string subj,string msg);

///default load
void saveload(string fname,jsn &js,int load0save1=0,int encryptedversion=0);

struct sslconnect{
	SSL*     ssl=0;
	int sd;
	SSL_CTX* ctx;
	sslconnect(string hostname,int porti);
	void disconnect();
	jsn request(jsn &jj,bool dbg=0);
	jsn request(string hh,bool dbg=0);
	string requesturl(string hh,bool dbg=0);
};



string string_dencrypt(string text,int enc1dec0,int version=0);

int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,  unsigned char *iv, unsigned char *plaintext);
int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,  unsigned char *iv, unsigned char *ciphertext);


typedef struct
{
    char* address;
    int addressLen;
    char* request;
    int requestLen;
    char* protocol;
    int protocolLen;
    int port;
} URLPARTS_T;

void decodeRequest(const char* pRequest, char* pOut, int pOutSize);
void breakUrl(const char* pUrl, URLPARTS_T* pUrlStruct);


#endif // SSL_HPP_INCLUDED
