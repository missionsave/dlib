#ifdef __linux__

#include "ssl.hpp"
#include "regular.hpp"
#include "stringf.hpp"

#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>


#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <ctype.h>
#ifdef __linux__
	#include <sys/socket.h>
	#include <netdb.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>		
#endif
#include <unistd.h>

#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>


#define CHK_NULL(x) if ((x)==NULL) exit (1)
#define CHK_ERR(err,s) if ((err)==-1) { perror(s); exit(1); }
#define CHK_SSL(err) if ((err)==-1) { ERR_print_errors_fp(stderr);   }

#include <iostream>
#include <sstream>
#include <unordered_map>
#include "zip.hpp"
#include <boost/filesystem.hpp>
#include <fstream>

void sleepms(int milisecs);


int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,  unsigned char *iv, unsigned char *plaintext){
  EVP_CIPHER_CTX *ctx;

  int len;

  int plaintext_len;

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new())){
		dbgv("erro0");
		return 0;

  }//handleErrors();

  /* Initialise the decryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * In this example we are using 256 bit AES (i.e. a 256 bit key). The
   * IV size for *most* modes is the same as the block size. For AES this
   * is 128 bits */
  if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    {
		dbgv("erro1");
		return 0;

  }//handleErrors();
  /* Provide the message to be decrypted, and obtain the plaintext output.
   * EVP_DecryptUpdate can be called multiple times if necessary
   */
  if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
    {
		dbgv("erro2");
		return 0;

  }//handleErrors();
  plaintext_len = len;

  /* Finalise the decryption. Further plaintext bytes may be written at
   * this stage.
   */
  if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) {
		dbgv("erro3");
		return 0;

  }//handleErrors();
  plaintext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return plaintext_len;
}
int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,  unsigned char *iv, unsigned char *ciphertext){
  EVP_CIPHER_CTX *ctx;
//dbgv(plaintext_len);
  int len;

  int ciphertext_len;

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new())) {
		dbgv("erro4");
		return 0;

  }//handleErrors();

  /* Initialise the encryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * In this example we are using 256 bit AES (i.e. a 256 bit key). The
   * IV size for *most* modes is the same as the block size. For AES this
   * is 128 bits */
  if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    {
		dbgv("erro5");
		return 0;

  }//handleErrors();

  /* Provide the message to be encrypted, and obtain the encrypted output.
   * EVP_EncryptUpdate can be called multiple times if necessary
   */
  if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
    {
		dbgv("erro6");
		return 0;

  }//handleErrors();
  ciphertext_len = len;

  /* Finalise the encryption. Further ciphertext bytes may be written at
   * this stage.
   */
  if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) {
		dbgv("erro7");
		return 0;

  }//handleErrors();
  ciphertext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return ciphertext_len;
}










///load ignores encrypted
void saveload(string fname,jsn &js,int load0save1,int encryptedversion){

if(load0save1){
		string str=dump_string(js, JSON);

//		if(encryptedversion){
//			str=string_compresslzma(str,1);
		if(encryptedversion>0){
			str=string_dencrypt(str,1,encryptedversion);
			fname+=".jsn";
		}
			else fname+=".json";
//		}
		FILE* pFile = fopen (fname.c_str(), "wb");
		fwrite (str.c_str() , sizeof(char), str.size(), pFile);
		fclose(pFile);
}
//read file
//js=parse_file("file.json", JSON);

if(load0save1==0){
	bool is_unencrypted=0;
	if(boost::filesystem::exists(fname+".json")){
		is_unencrypted=1;
		fname+=".json";
	}	else{
			if(!boost::filesystem::exists(fname+".jsn")){
				js="{}";
				return;
			}
		fname+=".jsn";
	}

	ifstream t(fname);
	string str((istreambuf_iterator<char>(t)),
		istreambuf_iterator<char>());
//		if(encryptedversion){
		if(!is_unencrypted)
			str=string_dencrypt(str,0);
//			str=string_compresslzma(str,0);
//			str=string_escape(str);
//		}
js=parse_string(str.c_str(),JSON,fname.c_str());
//		ofstream m;
//		m.open(fname,std::ios::binary );
//		m<<str;
//		m.close();

//dump_file("file.json",js,JSON);


}


}


jsn sslconnect::request(jsn &jj,bool dbg){
	return request(dump_string(jj, JSON),dbg);
}
jsn sslconnect::request(string hh,bool dbg){
	if(dbg)printf("%s\n",hh.c_str());
	int er;
	string res="";

	///check connected, look for a better way
	//if(ssl==0)fxsslinit();
//	dbgv(SSL_get_error(ssl,1));
	er = SSL_write (ssl, hh.c_str(), hh.size());
	CHK_SSL(er);
	char     bf [1024*16];
	lop(i,0,555){
		er = SSL_read (ssl, bf, sizeof(bf) - 1);
		CHK_SSL(er);
		bf[er] = '\0';
		res+=bf;
		if(bf[er-1]=='\n')break;
		if(i>5)sleepms(200);
	}
//	dbgv(res);
	return parse_string(res.c_str(), JSON,"nn");
}
string sslconnect::requesturl(string hh,bool dbg){
	if(dbg)printf("%s\n",hh.c_str());
	int er;
	string res="";

	///check connected, look for a better way
	//if(ssl==0)fxsslinit();
//	dbgv(SSL_get_error(ssl,1));
	er = SSL_write (ssl, hh.c_str(), hh.size());
	CHK_SSL(er);
	char     bf [1024*16];
	lop(i,0,555){
		er = SSL_read (ssl, bf, sizeof(bf) - 1);
		CHK_SSL(er);
		bf[er] = '\0';
		res+=bf;
		if(bf[er-1]=='\n')break;
//		if(i>5)sleepms(200);
	}
//	dbgv(res);
	return res.c_str();
}
sslconnect::sslconnect(string hostname,int porti){
	if(ssl!=0)return;
//	string hostname=(string)conf["host_name"];
//	int porti=(int)conf["port"];
//	dbgv(hostname,porti);
	struct hostent *host;
	if((host=gethostbyname(hostname.c_str()))==0){printf("errorhost");return;}
	long hosti=*(long*)(host->h_addr);


  int err;
  struct sockaddr_in sa;
  X509*    server_cert;
  char*    str;
  const SSL_METHOD *meth;

  OpenSSL_add_ssl_algorithms();
  meth = SSLv23_client_method();
  //meth = TLS_client_method();
  SSL_load_error_strings();
  ctx = SSL_CTX_new (meth);

 sd = socket (AF_INET, SOCK_STREAM,0);
CHK_ERR(sd, "socket");

 memset(&sa, 0, sizeof(sa));
 sa.sin_family      = AF_INET;
 sa.sin_addr.s_addr =hosti;
 sa.sin_port        = htons     (porti);
 err = connect(sd, (struct sockaddr*) &sa,	sizeof(sa));
 CHK_ERR(err, "connect");

ssl = SSL_new (ctx);
//SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv3);
//ctx = SSL_CTX_new(TLSv1_2_client_method());
CHK_NULL(ssl);

SSL_set_fd (ssl, sd);
err = SSL_connect (ssl);
CHK_SSL(err);

return;
//printf ("SSL connection using %s\n", SSL_get_cipher (ssl));
server_cert = SSL_get_peer_certificate (ssl);
CHK_NULL(server_cert);
//printf ("Server certificate:\n");

 str = X509_NAME_oneline (X509_get_subject_name (server_cert),0,0);
CHK_NULL(str);
//printf ("\t subject: %s\n", str);
OPENSSL_free (str);
X509_free (server_cert);

}

void sslconnect::disconnect(){
	SSL_shutdown (ssl);
	close (sd);
	SSL_free (ssl);
	ssl=0;
	SSL_CTX_free (ctx);
}






string ReceiveData(int hSocket,SSL* ssl=0){
	int res,i = 0;
	fd_set fdread;
	timeval time;

	time.tv_sec = 3;
	time.tv_usec = 0;
	char RecvBuf[4096];
	assert(RecvBuf);
	string ret;
	while(1){
		FD_ZERO(&fdread);
		FD_SET(hSocket,&fdread);
		if((res = select(hSocket+1, &fdread, NULL, NULL, &time)) == -1)		{
			FD_CLR(hSocket,&fdread);
		}

		if(!res){
			//timeout
			FD_CLR(hSocket,&fdread);
		}

		if(res && FD_ISSET(hSocket,&fdread)){
			if(i >= (4096*16)){
				FD_CLR(hSocket,&fdread);
			}
			int nosend;
			if(!ssl)
				nosend=recv(hSocket,RecvBuf,4096,0) ;
			else
				nosend=SSL_read(ssl,RecvBuf,4096);
			RecvBuf[nosend]='\0';
			ret+=RecvBuf;
//dbgv(nosend);
			if(nosend<4096)	{
				//FD_CLR(hSocket,&fdread);
				break;
			}

if(i>216)break;
			if(RecvBuf[i-1]=='\n'){
				RecvBuf[i] = '\0';
				break;
			}
		}
	}
	FD_CLR(hSocket,&fdread);
	return ret;
}
void SendData(int hSocket,const char* SendBuf,SSL* ssl=0){
	int idx = 0,res,nLeft = strlen(SendBuf);
	fd_set fdwrite;
	timeval time;
	time.tv_sec = 3;
	time.tv_usec = 0;
	assert(SendBuf);

//int sfd;
//if(ssl){sfd = SSL_get_fd (ssl);dbgv(hSocket,sfd);}

	while(1)	{
		FD_ZERO(&fdwrite);
		FD_SET(hSocket,&fdwrite);
		if((res = select(hSocket+1,NULL,&fdwrite,NULL,&time)) == -1){
			FD_CLR(hSocket,&fdwrite);
		}
		if(!res){
			//timeout
			FD_CLR(hSocket,&fdwrite);
 		}

		if(res && FD_ISSET(hSocket,&fdwrite))		{
			if(nLeft > 0)	{
				bool nosend;
				if(ssl)
				nosend=(res = SSL_write(ssl,&SendBuf[idx],nLeft)) == -1;
				else
				nosend=(res = send(hSocket,&SendBuf[idx],nLeft,0)) == -1;
				if(nosend)	{
					FD_CLR(hSocket,&fdwrite);
				}
				if(!res)
					break;
				nLeft -= res;
				idx += res;
			}
			else
				break;
		}
	}
	FD_CLR(hSocket,&fdwrite);
}
void sendemail(string hostname,int porti,string sender,string pass,vstring to,string subj,string msg){
SSL* ssl;
	int sd;
	SSL_CTX* ctx;

//	string hostname=(string)conf["host_name"];
//	int porti=(int)conf["port"];
//	dbgv(hostname,porti);
	struct hostent *host;
	if((host=gethostbyname(hostname.c_str()))==0){printf("errorhost");return;}
	long hosti=*(long*)(host->h_addr);


  int err;
  struct sockaddr_in sa;
  X509*    server_cert;
  char*    str;
  const SSL_METHOD *meth;

  OpenSSL_add_ssl_algorithms();
  //meth = SSLv23_client_method();
  meth = SSLv23_client_method();
  SSL_load_error_strings();
  ctx = SSL_CTX_new (meth);

 sd = socket (AF_INET, SOCK_STREAM,0);
//dbgv(sd);
CHK_ERR(sd, "socket");

 memset(&sa, 0, sizeof(sa));
 sa.sin_family      = AF_INET;
 sa.sin_addr.s_addr =hosti;
 sa.sin_port        = htons     (porti);
 err = connect(sd, (struct sockaddr*) &sa,	sizeof(sa));
 CHK_ERR(err, "connect");

	SendData(sd,string("\r\n").c_str());
	ReceiveData(sd);
	SendData(sd,string("EHLO [127.0.0.1]\r\n").c_str());
	ReceiveData(sd);
	SendData(sd,string("STARTTLS\r\n").c_str());
	ReceiveData(sd);

	ssl = SSL_new (ctx);
	CHK_NULL(ssl);
	SSL_set_fd (ssl, sd);
	err = SSL_connect (ssl);
	CHK_SSL(err);
	time_t tod = time(NULL);
	string g;

	SendData(sd,string("EHLO [127.0.0.1]\r\n").c_str(),ssl);
	ReceiveData(sd,ssl);

	SendData(sd,string("AUTH LOGIN\r\n").c_str(),ssl);
	ReceiveData(sd,ssl);

	SendData(sd,string(base64_encode(sender)+"\r\n").c_str(),ssl);
	ReceiveData(sd,ssl);
	SendData(sd,string(base64_encode(pass)+"\r\n").c_str(),ssl);
	ReceiveData(sd,ssl);

	lop(i,0,to.size()){
	SendData(sd,string("MAIL FROM:<"+sender+">\r\n").c_str(),ssl);
	ReceiveData(sd,ssl);

	SendData(sd,string("RCPT TO:<"+to[i]+">\r\n").c_str(),ssl);
	ReceiveData(sd,ssl);

	SendData(sd,"DATA\r\n",ssl);
	ReceiveData(sd,ssl);


	g=string("From: "+sender+"\nTo: "+to[i]+"\nDate: "+string(ctime(&tod))+"Subject: "+subj+"\nContent-Type: text/html; charset=\"UTF-8\"\n\n");
	SendData(sd,g.c_str(),ssl);

	SendData(sd,string(msg+"\r\n.\r\n").c_str(),ssl);
	dbgv(to[i]);
	//sleepms(3000);
	}



	SendData(sd,"QUIT\r\n",ssl);
	dbgv(0,ReceiveData(sd,ssl));
}



















///decod ignores version
string string_dencrypt(string text,int enc1dec0,int version){
	if(enc1dec0==1 && version==0){
			text.push_back(0);
			return text;
	}
  unsigned char *key = (unsigned char *)"{å¦U$\v×-:¨D\rW/þñå¹ïÀ\tð]ÎJ¢O¸Àhá¸¯@^\ní×Ö\"Ji¿Çµ»úÙ¾×%\a\?JM´;ôFÔxßCefa\\êho-qHätÓù³99oHU¨C\\î\"í\'Gà\"_aqð¨\vÙv!¶Ì9þ¹þ`ò¹TËµoÖÌq>óÚúÝ2¨¾SgK_%9òx\vk² N\vyAÝ\nÁßBÛê\"¶UÝ/@¹Ð\a\f³Ä}TÁâô¹i4ÆÈ\aÙt6$Î¥\\¨¶¾ß®_Pì9w~{-{X\'á¶\fR\vùü º´%Çwÿy$î¶»Tëj®=©°¥ðAò¢Ê±FµÜ¤4A­)å]vÝCâs4å^\v`3ÕJÚ3%ðS´þ5á±;s,ó<Yj²¡±XfÒnz¬óýí¡oÓúÉ¸äõçî¶7¤qcûüµ¯k¯Þl²6®ýÑoÇÜ[7¼\'½#Vá;Ð¨(shxeÔ1Í[z¿&eÿ\'>Ø»³7hBRh+ZH\"p·ø8P¨mP¹ÏÍÊ c·v!ó3«w\f,+É®c¢þºÿY";
  unsigned char *iv = (unsigned char *)"i¬ÈéÉo*áÓíÑÃcî¤fÁ6hZ{½yÐ3)ÙIÉ\000¬d½Êt¨3bfå/³¿Eÿªk¨î¢´Ê_e>õx,\aéæj1YCPö§ù9Ñ¼0);e6½j\bð§.\n·¯Z±#\a{¬XhxÆ";
  ERR_load_crypto_strings();
	//OpenSSL_add_all_algorithms();
	OPENSSL_config(NULL);
	if(enc1dec0==1){
		text=string_compresslzma(text,1);
		unsigned char ciphertext[text.size()*2];
//		unsigned char *plaintext =(unsigned char *)text.c_str();
		unsigned char plaintext[text.size()];

		unsigned char v=1;
    memcpy(plaintext,text.c_str(),text.size());
		int ciphertext_len;
		ciphertext_len = encrypt (plaintext, text.size(), key, iv, ciphertext);
		///v= version
		ciphertext[ciphertext_len]=v;
		return string(reinterpret_cast< char const* >(ciphertext),ciphertext_len+1);
	}

	///unecrypt só vais buscar versao ao ficheiro
	if(enc1dec0==0){
  	///ver versao
  	unsigned char v=(unsigned char)text.back();
  	text.pop_back();
  	if(v==0)return text;
		unsigned char decryptedtext[text.size()*2];
//  	dbgv((int)v);
		unsigned char *plaintext =(unsigned char *)text.c_str();
  	int decryptedtext_len ;
		decryptedtext_len = decrypt(plaintext, text.size(), key, iv, decryptedtext);

	text=string(reinterpret_cast< char const* >(decryptedtext),decryptedtext_len);
		text=string_compresslzma(text,0);

		return text;
	}
}


#endif


