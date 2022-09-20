/*
tm_sec	int	seconds after the minute	0-61
tm_min	int	minutes after the hour	0-59
tm_hour	int	hours since midnight	0-23
tm_mday	int	day of the month	1-31
tm_mon	int	months since January	0-11
tm_year	int	years since 1900
tm_wday	int	days since Sunday	0-6
tm_yday	int	days since January 1	0-365
tm_isdst	int	Daylight Saving Time flag

//http://www.cplusplus.com/reference/ctime/strftime/
%a	Abbreviated weekday name *	Thu
%A	Full weekday name *	Thursday
%b	Abbreviated month name *	Aug
%B	Full month name *	August
%c	Date and time representation *	Thu Aug 23 14:55:02 2001
%C	Year divided by 100 and truncated to integer (00-99)	20
%d	Day of the month, zero-padded (01-31)	23
%D	Short MM/DD/YY date, equivalent to %m/%d/%y	08/23/01
%e	Day of the month, space-padded ( 1-31)	23
%F	Short YYYY-MM-DD date, equivalent to %Y-%m-%d	2001-08-23
%g	Week-based year, last two digits (00-99)	01
%G	Week-based year	2001
%h	Abbreviated month name * (same as %b)	Aug
%H	Hour in 24h format (00-23)	14
%I	Hour in 12h format (01-12)	02
%j	Day of the year (001-366)	235
%m	Month as a decimal number (01-12)	08
%M	Minute (00-59)	55
%n	New-line character ('\n')
%p	AM or PM designation	PM
%r	12-hour clock time *	02:55:02 pm
%R	24-hour HH:MM time, equivalent to %H:%M	14:55
%S	Second (00-61)	02
%t	Horizontal-tab character ('\t')
%T	ISO 8601 time format (HH:MM:SS), equivalent to %H:%M:%S	14:55:02
%u	ISO 8601 weekday as number with Monday as 1 (1-7)	4
%U	Week number with the first Sunday as the first day of week one (00-53)	33
%V	ISO 8601 week number (00-53)	34
%w	Weekday as a decimal number with Sunday as 0 (0-6)	4
%W	Week number with the first Monday as the first day of week one (00-53)	34
%x	Date representation *	08/23/01
%X	Time representation *	14:55:02
%y	Year, last two digits (00-99)	01
%Y	Year	2001
%z	ISO 8601 offset from UTC in timezone (1 minute=1, 1 hour=100)
If timezone cannot be determined, no characters	+100
%Z	Timezone name or abbreviation *
If timezone cannot be determined, no characters	CDT
%%	A % sign	%
*/


#ifndef TIMEF_HPP_INCLUDED
#define TIMEF_HPP_INCLUDED

#include "regular.hpp"
#include <ctime>

//#define pause(milisecs) boost::this_thread::sleep_for(boost::chrono::milliseconds(milisecs))


time_t dateconstuct(int year=2020,int month=0,int day=1,int hour=0,int minutes=0,int seconds=0);

//cot ( datetime(time)->tm_min);
// const std::tm* datetime(time_t date){
	// time_t datet=(time_t)date;
	// return std::localtime(&datet); 
// }
//cot ( datetimems(time)->tm_min);
// const std::tm* datetimems(time_t date){
	// time_t datet=(time_t)date/1000+1;
	// return std::localtime(&datet); 
// }

int hourofdayms(time_t date);

int dayofmonthms(time_t date);

int dayofweekms(time_t date);

void sleepms(int milisecs);

//intToTimeStr(1489886464,"%c");
string intToTimeStr(int inp,const char* format);
int now();


class performance{
    private:
    unsigned int pclock;
    char* pname;
    public:
    performance(char*  name=""); //
    void p(char* prefix=""); //
};
extern performance perf;

class pauserc{
    unsigned int ini_;
    unsigned int minutestomilisecs=600000;
    unsigned int milisecondsToPause=35000;
    public:
    pauserc();
    pauserc(int minutes,int secondsToPause);
    void se();
};
//pauserc pauser;

#endif // TIMEF_HPP_INCLUDED
