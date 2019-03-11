#ifndef CONSTANTS_H
#define CONSTANTS_H
#include<iostream>
#include<iomanip>

using namespace std;

struct Date {
	int year, month, day;

	void print(ostream& w = cout) {
	w << year << " " << month << " " << day << " ";
	}
};

struct Time {
	int hour, min;
	double sec;

	void print(ostream& w = cout) {
		w << hour << " " << min << " " << sec << " ";
	}

};

struct Epoch {
	Date date;
	Time time;

	void print(ostream& w = cout) {
		date.print( w );
		time.print( w );
	}
};

struct Car {
	double x, y, z;

	void print(ostream& w = cout) {
		w << fixed << setprecision(4);
		w << x << " " << y << " " << z << " ";
	}
};

struct Geo {
	double lat, lon, hgt;

	void print(ostream& w = cout) {
		w << fixed << setprecision(8);
		w << lat << " " << lon << " " << setprecision(3) <<  hgt << " ";
	}
};

struct Coord {
	//string name;
	Car car;
	Geo geo;

	void print(ostream& w = cout) {
		car.print(w);
		geo.print(w);
	}
};


// define your own namespace to hold constants
namespace constants
{
	constexpr double C(0.299792458e9);                 //    VELOCITY OF LIGHT                  M / SEC
    constexpr double FREQ1(1575420000);               //    L1 - CARRIER FREQUENCY   GPS       1 / SEC
    constexpr double FREQ2(1227600000);              //    L2 - CARRIER FREQUENCY   GPS       1 / SEC
    constexpr double GM(3.986004418e14);            //    GRAVITY CONSTANT*EARTH MASS      M**3 / SEC * *2    
	constexpr double OMEGAE_DOT(7.2921151467e-5);  //    ANGULAR VELOCITY OF EARTH        RAD / SEC  
  
}
#endif