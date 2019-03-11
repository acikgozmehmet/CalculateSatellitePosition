#include<iostream>

using namespace std;

class TimeSystems {
public:

	/**
	* Returns  Julian Day given calendar date and time ,
	* @param year (4 digit), month (1-12), day (1-31), hour(0-23) , minute(0-59) and second (0-59)
	* @return juliaa day number
	* - Valid for Gregorian dates from 17-Nov-1858.
	* - Adapted from sci.astro FAQ.
	* - Adapted for hour, minute and second
	*/
	static double DateToJd(int year, int month, int day, int hour = 0, int minute = 0, double second = 0);

	/**
	Returns the Modified Julian Day
	@param year (yyyy), month(1-12), day(1-31), hour(0-23), minute(0-59), second(0-59)
	@return MJD
	*/
	static double DateToMjd(int year, int month, int day, int hour = 0, int minute = 0, double second = 0);

	/**
	Returns the Julian Day
	@param Modified Julian Day
	@return Julian Day
	*/
	static double MjdToJd(double mjd);

	/**
	Returns the Modified Julian Day
	@param Julian Day
	@return  Modified Julian Day
	*/
	static double JdToMjd(double jd);

	/**
	Returns the Gregorian Calendar Date and time
	@param, jd Julian Day
	@return, year (yyyy), month(1-12), day(1-31), hour(0-23), minute(0-59), second(0-59)
	*/
	static void JdToDate(double jd, int& year, int& month, int& day, int& hour, int& minute, double& second);

	/**
	Returns the day of the year
	@param, year (yyyy), month(1-12), day(1-31), hour(0-23), minute(0-59), second(0-59)
	@return, the number of the day in the year
	*/
	static int DateToDoy(int year, int month, int day, int hour = 0, int minute = 0, double second = 0);

	/**
	Returns the Gregorian Calendar Date
	@param, year (4 digit) and  day of year (3 digit)
	@return, year (yyyy), month(1-12), day(1-31), hour(0-23), minute(0-59), second(0-59)
	*/
	static void DoyToDate(int& year, int doy, int& month, int& day, int& hour, int& minute, double& second);

	/**
	Returns the GPS Time
	@param, year (yyyy), month(1-12), day(1-31), hour(0-23), minute(0-59), second(0-59)
	@return, second of Week - secofWeek, GPSWeek, dayofWeek
	*/
	static void DateToGPSTime(int year, int month, int day, int hour, int minute, double second, double& secOfWeek, int& GPSWeek, int& dayOfWeek);

	/**
	Returns the GPS Time
	@param, jd (julian day number)
	@return, second of Week - secofWeek, GPSWeek, dayofWeek
	*/
	static void JdToGPSTime(double jd, int& GPSWeek, int& dayOfWeek, double& secOfWeek);

	/**
	Returns the Modified Julian Day
	@param, GPSCycle, GPSWeek, GPSSeconds
	@return, MJD
	*/
	static double GPSTimeToMjd(int GPSCycle, int GPSWeek, double GPSSeconds);

	/**
	Returns the GPSCycle by mode (1024)
	@param GPSWeek (not mode by 1024)
	#return GPSCycle (0,1,...)
	*/
	static int GPSWeekToGPSCycle(int GPSWeek);


	/**
	Returns the Modified Julian Day
	@param, GPSWeek, GPSSeconds
	@return, MJD
	*/

	static double GPSTimeToMjd(int GPSWeek, double GPSSeconds);


	/**
	Returns the Gregorian Calendar Date
	@param, GPSCycle, GPSWeek, dayOfWeek
	@return, year (yyyy), month(1-12), day(1-31), hour(0-23), minute(0-59), second(0-59)
	*/
	static void GPSTimeToDate(int GPSCycle, int GPSWeek, double GPSSeconds, int& year, int& month, int& day, int& hour, int& minute, double& second);

	/**
	Returns the Gregorian Calendar Date
	@param, GPSWeek (not modulus by 1024), dayOfWeek
	@return, year (yyyy), month(1-12), day(1-31), hour(0-23), minute(0-59), second(0-59)
	*/
	static void GPSTimeToDate(int GPSWeek, double GPSSeconds, int& year, int& month, int& day, int& hour, int& minute, double& second);


};
