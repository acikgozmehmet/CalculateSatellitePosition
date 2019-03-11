#include "TimeSystems.h"

double TimeSystems::DateToMjd(int year, int month, int day, int hour, int minute, double second ) {
	return JdToMjd( DateToJd(year, month, day, hour, minute, second) );
}

double TimeSystems::MjdToJd(double mjd) {
	return mjd + 2400000.5;
}

double TimeSystems::JdToMjd(double jd) {
	return (jd - 2400000.5);
}


double TimeSystems::DateToJd(int year, int month, int day, int hour, int minute, double second) {	
	double ans = 367 * year
		- 7 * (year + (month + 9) / 12) / 4
		- 3 * ((year + (month - 9) / 7) / 100 + 1) / 4
		+ 275 * month / 9
		+ day
		+ 1721028
		+ 0.5
        + double(hour) / 24 + double(minute) / 60 / 24 + second / 3600 / 24; // to convert them all to a unit of a day
	return ans;
}



/**
C---COMPUTES THE GREGORIAN CALENDAR DATE (YEAR,MONTH,DAY)
C   GIVEN THE JULIAN DATE (JD).
*/
void TimeSystems::JdToDate(double jd, int& year, int& month, int& day, int& hour, int& minute, double& second) {

	int JD, I, J, K;

	//JD = int(jd);
	JD = round(jd);
	int L = JD + 68569;
	int N = 4 * L / 146097;
	L = L - (146097 * N + 3) / 4;
	I = 4000 * (L + 1) / 1461001;
	L = L - 1461 * I / 4 + 31;
	J = 80 * L / 2447;
	K = L - 2447 * J / 80;
	L = J / 11;
	J = J + 2 - 12 * L;
	I = 100 * (N - 49) + I + L;

	year = I;
	month = J;
	day = K;

	double tempjd = DateToJd(year, month, day);
	double diff = jd - tempjd;

	hour = int(diff * 24);
	minute = (diff * 24 - hour) * 60;
	second = ( ( (diff *24 - hour) * 60) - minute) * 60;


}

int TimeSystems::DateToDoy(int year, int month, int day, int hour, int minute, double second) {
	
	return DateToJd(year, month, day, hour, minute, second) - DateToJd(year, 1, 1, 0, 0, 0) + 1;

}

void TimeSystems::DoyToDate(int& year, int doy, int& month, int& day, int& hour, int& minute, double& second) {
	//double jd = DateToJd(year, 1, 1) + doy - 1 + double( hour + double(minute)/60 + second/3600 ) / 24;
	double jd = DateToJd(year, 1, 1, hour, minute, second) + doy - 1;
	JdToDate(jd, year, month, day, hour, minute, second);
}



void TimeSystems::DateToGPSTime(int year, int month, int day, int hour, int minute, double second, double& secOfWeek, int& GPSWeek, int& dayOfWeek) {
	double jd = DateToJd(year, month, day, hour, minute, second);
	JdToGPSTime(jd, GPSWeek, dayOfWeek, secOfWeek);
}

void TimeSystems::JdToGPSTime(double jd, int& GPSWeek, int& dayOfWeek, double& secOfWeek) {
	const double JAN061980 = DateToJd(1980, 1, 6, 0, 0, 0);  // start of gpstime in terms of jd
	const double SEC_PER_DAY = 86400.0;
	GPSWeek = int((jd - JAN061980) / 7);
	dayOfWeek = int(jd - JAN061980) % 7;
	secOfWeek = ((jd - JAN061980) - GPSWeek * 7) * SEC_PER_DAY;
}

/*
* Convert GPS Week and Seconds to Modified Julian Day.
* - Ignores UTC leap seconds.
* GPSWeek is mod(1024)
* 
*/
double TimeSystems::GPSTimeToMjd(int GPSCycle, int GPSWeek, double GPSSeconds) {
	int GPSDays = ((GPSCycle * 1024) + GPSWeek) * 7 + ( int(GPSSeconds) / 86400);
	return DateToMjd(1980, 1, 6) + GPSDays;
}

int TimeSystems::GPSWeekToGPSCycle(int GPSWeek) {
	return GPSWeek / 1024;
}

double TimeSystems::GPSTimeToMjd(int GPSWeek, double GPSSeconds) {
	//int GPSDays =  GPSWeek * 7 + ( int( GPSSeconds / 86400) );
	double GPSDays = GPSWeek * 7 + (GPSSeconds / 86400);
	return DateToMjd(1980, 1, 6) + GPSDays;
}


void TimeSystems::GPSTimeToDate(int GPSCycle, int GPSWeek, double GPSSeconds, int& year, int& month, int& day, int& hour, int& minute, double& second) {
	double mjd = GPSTimeToMjd(GPSCycle, GPSWeek, GPSSeconds);
	double jd = MjdToJd(mjd);
	JdToDate(jd, year, month, day, hour, minute, second);
}


void TimeSystems::GPSTimeToDate(int GPSWeek, double GPSSeconds, int& year, int& month, int& day, int& hour, int& minute, double& second) {
	double mjd = GPSTimeToMjd(GPSWeek, GPSSeconds);
	double jd = MjdToJd(mjd);
	JdToDate(jd, year, month, day, hour, minute, second);
}
