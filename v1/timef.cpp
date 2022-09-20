#include "timef.hpp"
#include <chrono>
#include <boost/thread/thread.hpp>


time_t dateconstuct(int year,int month,int day,int hour,int minutes,int seconds){
	struct tm time;
	memset(&time, 0, sizeof(time));
	time.tm_sec=seconds;
	time.tm_min=minutes;
	time.tm_hour=hour;
	time.tm_mday = day;
	time.tm_mon = month;
	time.tm_year = year-1900; 
	return mktime(&time); 
}

int hourofdayms(time_t date){
	time_t datet=(time_t)date/1000+1;
	const std::tm * time_out = std::localtime(&datet);
	return time_out->tm_hour;
}
int dayofmonthms(time_t date){
	time_t datet=(time_t)date/1000+1;
	const std::tm * time_out = std::localtime(&datet);
	return time_out->tm_mday;
}
int dayofweekms(time_t date){
	time_t datet=(time_t)date/1000+1;
	const std::tm * time_out = std::localtime(&datet);
	return time_out->tm_wday;
}

//time_t strtimeToTimet(string str){
//	struct std::tm tm;
//	std::istringstream ss("16:35:12");
//	ss >> std::get_time(&tm, "%H:%M:%S"); // or just %T in this case
//	std::time_t time = mktime(&tm);
//}

void sleepms(int milisecs){
//#ifdef __linux__
boost::this_thread::sleep_for(boost::chrono::milliseconds(milisecs));
//#endif // LINUX
}

//http://www.cplusplus.com/reference/ctime/strftime/
string intToTimeStr(int inp,const char* format="%c"){
    time_t rawtime=(time_t)inp;
    struct tm * timeinfo;
    char buffer [255];
    //time (&rawtime);
    timeinfo = gmtime (&rawtime);
    strftime (buffer,80,format,timeinfo);
    string tim=buffer;
    return tim;
}

int now(){
	time_t no;
	time (&no);
	return no;
}


performance perf;
performance::performance(char*  name){pname=name;pclock=clock();}
void performance::p(char* prefix){
	if(prefix==0){
		pclock=clock();
		printf("\nbenchmark\n");
		return;
	}
	printf("\n%s %s %f sec ",pname,prefix,((float)clock()-pclock)/CLOCKS_PER_SEC);
	fflush(stdout);
	pclock=clock();
}



/*
pauserc::pauserc(){ini_=clock();}
pauserc::pauserc(int minutes,int secondsToPause){ini_=clock();minutestomilisecs=minutes*60000;milisecondsToPause=secondsToPause*1000;}
void pauserc::se(){if(clock()-ini_>minutestomilisecs){pause(milisecondsToPause);ini_=clock();}}

*/

///estranho aqui devia funcionar
#if 0
//#ifdef __linux__

#define ReverseEndianInt(x) ((x) = \
    ((x)&0xff000000) >> 24 |\
    ((x)&0x00ff0000) >> 8 |\
    ((x)&0x0000ff00) << 8 |\
    ((x)&0x000000ff) << 24)

/**
 * NTP Fixed-Point Timestamp Format.
 * From [RFC 5905](http://tools.ietf.org/html/rfc5905).
 */
struct Timestamp
{
    unsigned int seconds; /**< Seconds since Jan 1, 1900. */
    unsigned int fraction; /**< Fractional part of seconds. Integer number of 2^-32 seconds. */

    /**
     * Reverses the Endianness of the timestamp.
     * Network byte order is big endian, so it needs to be switched before
     * sending or reading.
     */
    void ReverseEndian() {
        ReverseEndianInt(seconds);
        ReverseEndianInt(fraction);
    }

    /**
     * Convert to time_t.
     * Returns the integer part of the timestamp in unix time_t format,
     * which is seconds since Jan 1, 1970.
     */
    time_t to_time_t()
    {
        return (seconds - ((70 * 365 + 17) * 86400))&0x7fffffff;
    }
};

/**
 * A Network Time Protocol Message.
 * From [RFC 5905](http://tools.ietf.org/html/rfc5905).
 */
struct NTPMessage
{
    unsigned int mode :3; /**< Mode of the message sender. 3 = Client, 4 = Server */
    unsigned int version :2; /**< Protocol version. Should be set to 3. */
    unsigned int leap :2; /**< Leap seconds warning. See the [RFC](http://tools.ietf.org/html/rfc5905#section-7.3) */
    unsigned char stratum; /**< Servers between client and physical timekeeper. 1 = Server is Connected to Physical Source. 0 = Unknown. */
    unsigned char poll; /**< Max Poll Rate. In log2 seconds. */
    unsigned char precision; /**< Precision of the clock. In log2 seconds. */
    unsigned int sync_distance; /**< Round-trip to reference clock. NTP Short Format. */
    unsigned int drift_rate; /**< Dispersion to reference clock. NTP Short Format. */
    unsigned char ref_clock_id[4]; /**< Reference ID. For Stratum 1 devices, a 4-byte string. For other devices, 4-byte IP address. */
    Timestamp ref; /**< Reference Timestamp. The time when the system clock was last updated. */
    Timestamp orig; /**< Origin Timestamp. Send time of the request. Copied from the request. */
    Timestamp rx; /**< Recieve Timestamp. Reciept time of the request. */
    Timestamp tx; /**< Transmit Timestamp. Send time of the response. If only a single time is needed, use this one. */


    /**
     * Reverses the Endianness of all the timestamps.
     * Network byte order is big endian, so they need to be switched before
     * sending and after reading.
     *
     * Maintaining them in little endian makes them easier to work with
     * locally, though.
     */
    void ReverseEndian() {
        ref.ReverseEndian();
        orig.ReverseEndian();
        rx.ReverseEndian();
        tx.ReverseEndian();
    }

    /**
     * Recieve an NTPMessage.
     * Overwrites this object with values from the recieved packet.
     */
    int recv(int sock)
    {
        int ret = ::recv(sock, (char*)this, sizeof(*this), 0);
        ReverseEndian();
        return ret;
    }

    /**
     * Send an NTPMessage.
     */
    int sendto(int sock, struct sockaddr_in* srv_addr)
    {
        ReverseEndian();
        int ret = ::sendto(sock, (const char*)this, sizeof(*this), 0, (sockaddr*)srv_addr, sizeof(*srv_addr));
        ReverseEndian();
        return ret;
    }

    /**
     * Zero all the values.
     */
    void clear()
    {
        memset(this, 0, sizeof(*this));
    }
};
#endif
#ifdef LINUX
#include "ssl.hpp";
#include <netdb.h>

int dns_lookup(const char *host, sockaddr_in *out)
{
    struct addrinfo *result;
    int ret = getaddrinfo(host, "ntp", NULL, &result);
    for (struct addrinfo *p = result; p; p = p->ai_next)
    {
        if (p->ai_family != AF_INET)
            continue;

        memcpy(out, p->ai_addr, sizeof(*out));
    }
    freeaddrinfo(result);
}

time_t getntptimestamp(){


//char *host = "pool.ntp.org"; /* Don't distribute stuff pointing here, it's not polite. */
char *host = "time.nist.gov"; /* This one's probably ok, but can get grumpy about request rates during debugging. */

NTPMessage msg;
/* Important, if you don't set the version/mode, the server will ignore you. */
msg.clear();
msg.version = 3;
msg.mode = 3 /* client */;

NTPMessage response;
response.clear();

int sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
sockaddr_in srv_addr;
memset(&srv_addr, 0, sizeof(srv_addr));
dns_lookup(host, &srv_addr); /* Helper function defined below. */

msg.sendto(sock, &srv_addr);
response.recv(sock);

time_t t = response.tx.to_time_t();
char *s = ctime(&t);
printf("The time is %s.", s);

close(sock);


return t;


}
#endif // LINUX
