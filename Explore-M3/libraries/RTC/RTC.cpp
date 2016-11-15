// Code by JeeLabs http://news.jeelabs.org/code/
// Released to the public domain! Enjoy!



#include "RTC.h"





#define SBIT_CLKEN   	  0		/* RTC Clock Enable*/
#define SBIT_CTCRST	      1		/* RTC Clock Reset */
#define SBIT_CCALEN	      4		/* RTC Calibration counter enable */

#define SBIT_CALDIR    	 17
#define SBIT_PCRTC        9


////////////////////////////////////////////////////////////////////////////////
// utility code, some of this could be exposed in the DateTime API if needed

const uint8_t daysInMonth [] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

// number of days since 2000/01/01, valid for 2001..2099
static uint16_t date2days(uint16_t y, uint8_t m, uint8_t d) {
    if (y >= 2000)
        y -= 2000;
    uint16_t days = d;
    for (uint8_t i = 1; i < m; ++i)
        days += (daysInMonth[i - 1]);
    if (m > 2 && y % 4 == 0)
        ++days;
    return days + 365 * y + (y + 3) / 4 - 1;
}

static long time2long(uint16_t days, uint8_t h, uint8_t m, uint8_t s) {
    return ((days * 24L + h) * 60 + m) * 60 + s;
}

////////////////////////////////////////////////////////////////////////////////
// DateTime implementation - ignores time zones and DST changes
// NOTE: also ignores leap seconds, see http://en.wikipedia.org/wiki/Leap_second

DateTime::DateTime (uint32_t t) {
  t -= SECONDS_FROM_1970_TO_2000;    // bring to 2000 timestamp from 1970

    ss = t % 60;
    t /= 60;
    mm = t % 60;
    t /= 60;
    hh = t % 24;
    uint16_t days = t / 24;
    uint8_t leap;
    for (yOff = 0; ; ++yOff) {
        leap = yOff % 4 == 0;
        if (days < 365 + leap)
            break;
        days -= 365 + leap;
    }
    for (m = 1; ; ++m) {
        uint8_t daysPerMonth = daysInMonth[m - 1];
        if (leap && m == 2)
            ++daysPerMonth;
        if (days < daysPerMonth)
            break;
        days -= daysPerMonth;
    }
    d = days + 1;
}

DateTime::DateTime (uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec) {
    if (year >= 2000)
        year -= 2000;
    yOff = year;
    m = month;
    d = day;
    hh = hour;
    mm = min;
    ss = sec;
}

DateTime::DateTime (const DateTime& copy):
  yOff(copy.yOff),
  m(copy.m),
  d(copy.d),
  hh(copy.hh),
  mm(copy.mm),
  ss(copy.ss)
{}

static uint8_t conv2d(const char* p) {
    uint8_t v = 0;
    if ('0' <= *p && *p <= '9')
        v = *p - '0';
    return 10 * v + *++p - '0';
}

// A convenient constructor for using "the compiler's time":
//   DateTime now (__DATE__, __TIME__);
// NOTE: using F() would further reduce the RAM footprint, see below.
DateTime::DateTime (const char* date, const char* time) {
    // sample input: date = "Dec 26 2009", time = "12:34:56"
    yOff = conv2d(date + 9);
    // Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec 
    switch (date[0]) {
        case 'J': m = date[1] == 'a' ? 1 : m = date[2] == 'n' ? 6 : 7; break;
        case 'F': m = 2; break;
        case 'A': m = date[2] == 'r' ? 4 : 8; break;
        case 'M': m = date[2] == 'r' ? 3 : 5; break;
        case 'S': m = 9; break;
        case 'O': m = 10; break;
        case 'N': m = 11; break;
        case 'D': m = 12; break;
    }
    d = conv2d(date + 4);
    hh = conv2d(time);
    mm = conv2d(time + 3);
    ss = conv2d(time + 6);
}



uint8_t DateTime::dayOfTheWeek() const {    
    uint16_t day = date2days(yOff, m, d);
    return (day + 6) % 7; // Jan 1, 2000 is a Saturday, i.e. returns 6
}

uint32_t DateTime::unixtime(void) const {
  uint32_t t;
  uint16_t days = date2days(yOff, m, d);
  t = time2long(days, hh, mm, ss);
  t += SECONDS_FROM_1970_TO_2000;  // seconds from 1970 to 2000

  return t;
}

long DateTime::secondstime(void) const {
  long t;
  uint16_t days = date2days(yOff, m, d);
  t = time2long(days, hh, mm, ss);
  return t;
}

DateTime DateTime::operator+(const TimeSpan& span) {
  return DateTime(unixtime()+span.totalseconds());
}

DateTime DateTime::operator-(const TimeSpan& span) {
  return DateTime(unixtime()-span.totalseconds());
}

TimeSpan DateTime::operator-(const DateTime& right) {
  return TimeSpan(unixtime()-right.unixtime());
}

////////////////////////////////////////////////////////////////////////////////
// TimeSpan implementation

TimeSpan::TimeSpan (int32_t seconds):
  _seconds(seconds)
{}

TimeSpan::TimeSpan (int16_t days, int8_t hours, int8_t minutes, int8_t seconds):
  _seconds((int32_t)days*86400L + (int32_t)hours*3600 + (int32_t)minutes*60 + seconds)
{}

TimeSpan::TimeSpan (const TimeSpan& copy):
  _seconds(copy._seconds)
{}

TimeSpan TimeSpan::operator+(const TimeSpan& right) {
  return TimeSpan(_seconds+right._seconds);
}

TimeSpan TimeSpan::operator-(const TimeSpan& right) {
  return TimeSpan(_seconds-right._seconds);
}

////////////////////////////////////////////////////////////////////////////////
// RTC implementation

static uint8_t bcd2bin (uint8_t val) { return val - 6 * (val >> 4); }
static uint8_t bin2bcd (uint8_t val) { return val + 6 * (val / 10); }
static uint8_t rtc_start=0;

boolean RTC::begin(void) {
    LPC_SC->PCONP |=(1<<9); // Enable the power to RTC module 
	/* Disable RTC clock, reset clock, Enable RTC calibration */
	LPC_RTC->CCR = ((1<<SBIT_CTCRST) | (1<<SBIT_CCALEN));
	LPC_RTC->CALIBRATION = 0x00;
    LPC_RTC->CCR = (1<<SBIT_CLKEN); /* Enable the clock for RTC */
    rtc_start = 0;
  return true;
}

uint8_t RTC::isrunning(void) {
 
  return rtc_start; // flag to check if RTC is enabled and return the same
}

void RTC::adjust(const DateTime& dt) {
  
     LPC_RTC->SEC   =  dt.second();       // Update sec value
	 LPC_RTC->MIN   =  dt.minute();	   // Update min value
     LPC_RTC->HOUR	=  dt.hour();	   // Update hour value  
	 LPC_RTC->DOM	=  dt.day();	   // Update date value 
	 LPC_RTC->MONTH =  dt.month();	   // Update month value
	 LPC_RTC->YEAR  =  dt.year();	   // Update year value
}

DateTime RTC::now() {     
  uint8_t ss = LPC_RTC->SEC;
  uint8_t mm = LPC_RTC->MIN;
  uint8_t hh = LPC_RTC->HOUR;
  uint8_t d = LPC_RTC->DOM;
  uint8_t m = LPC_RTC->MONTH;
  uint16_t y = LPC_RTC->YEAR;
  
  return DateTime (y, m, d, hh, mm, ss);
}



////////////////////////////////////////////////////////////////////////////////
// RTC_Millis implementation

long RTC_Millis::offset = 0;

void RTC_Millis::adjust(const DateTime& dt) {
    offset = dt.unixtime() - millis() / 1000;
}

DateTime RTC_Millis::now() {
  return (uint32_t)(offset + millis() / 1000);
}

