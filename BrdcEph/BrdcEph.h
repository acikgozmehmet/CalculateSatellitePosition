/**
BrdcEph.cpp
@author : Mehmet Acikgoz

Purpose: Calculating the position and clock of any GPS satellite at a given time by using GNSS Rinex Navigation File.

*/
#ifndef BRDCEPH_H
#define BRDCEPH_H

#include<iostream>
#include<string>
#include<fstream>
#include<stdexcept>
#include<iomanip>
#include<cmath>

#include "..\Constants\Constants.h"
#include "..\TimeSystems\TimeSystems.h"

using namespace std;

struct Ephemeris {
	int svID;
	Epoch toc;
	double af0, af1, af2;
	double crs, deltan, M0;                          // orbit 1      double IODE, crs, deltan, M0;    // orbit 1
	double cuc, ecc, cus, roota;	                // orbit 2
	double toe, cic, Omega0, cis;                  // orbit 3
	double i0, crc, omega, Omegadot;              // orbit 4
	double idot, weekno;                         // orbit 5     double idot, codes, weekno, L2flag;  // orbit 5
	// double svaccur, svhealth, tgd, iodc;     // orbit 6
	double tom;                                // orbit 7     double tom, spare1, spare2, spare3;  // orbit 7

	bool hasData;

	Ephemeris() {
		hasData = false;
	}
};

// Maximum number of Satellite Vehicles (SV) + 1
const int MAX_SV = 32 + 1;
// Maximum number of epochs for each SV in the file. 
const int MAX_EPOCH = 13; // max number of epochs 


class BrdcEph {
public:
	BrdcEph();
	BrdcEph(string filename);
	~BrdcEph();

	void setFilename(string filename);
	string getFilename(void);
/**
    Loads the input file to the memory
	@param none.
	@return none.
*/
	void load();

/**
    Returns true if the Satellite Coordinate is calculated at any given time, otherwise returns false
    @param svID is the Satellite #
    @param t  is the Epoch of the observation at which satellite coordinate is to be estimated.
    @param satPos is the coordinate of the Satellite to be calculated.

	Source: 
	GPS data processing: code and phase
	Algorithms, Techniques and Recipes
	Research group of Astronomy and GEomatics (gAGE/UPC)
*/
	bool calcSatPos(int svID, Epoch t, Car& satPos);

/**
   Overloading function
*/
	bool calcSatPos(int svID, int GPSweek, double tGPSsec, Car& satPos);

/**
	Returns the Satellite clock bias
	param svID is the Satellite #
	param t is the Epoch of the observation  which satellite clock bias are to be estimated.
*/
	double calcSatClkBias(int svID, Epoch t);

	double calcSatClkBias(int svID, int GPSweek, double tGPSsec);



private:
	string m_filename;
	Ephemeris m_data[MAX_SV][MAX_EPOCH];
	static const double PI;

/**
   Reads the input broadcast ephemeris file and creates a summary file with the extension of ".sum"

   @param filename is the name of the input file.
   @return None.
*/
	void readFromFile(const string& filename);

/**
	Changes the Fortran Scientific notation for double/float numbers (D-, D+) to
	C++ notation (E-, E+)
	@param text is the line of string which contains only numbers
*/
	void changeSciNotation(string& text);


/** Converts  the 2 digit year to 4 digit year format.
	@param yy is the 2 digit year.
	@return None.
*/
	void convertYYToYYYY(int & yy);

/**
    Returns the index when key is given.
	@param t is the epoch of observation. 
	@return index
*/
	int hashFunction(Epoch t);

/**
     Creates an summary table when loads the file to the memory.
	 @param w is the ostream object either to print the file to the screen ot outfile
	 @return  None.
*/
	void printGraphics(ostream& w);

/** 
    Prints the loading bar to the screen.
	@param counter is the number of the lines read from input file each time.
	@return None.
*/
	void printLoadingBar(int counter);

/**
    Returns the index when the epoch of observation is given.
	@param t is the epoch of the obervation
	@return index
*/
	int getIndex(Epoch t);

/**
   Returns the ephemeris data when svID and index of the observation are given.
   @param  svID is the satellite number/ID.
   @param ephIndex is the index of the ephemeris which associates with the observation time.
*/
	Ephemeris getEphData(int svID, int ephIndex);

	bool isEphDataAvailable(int svID, int& ephIndex);

/**
    Checks the time of the obervation whether it is in the same week.
	@param tk is the time in seconds from the beginning of GPS week. in GPSTime
	@return None.
*/
	void checkTk(double& tk);

/** 
    Returns the arctan value of trigonometric function. 
	It is good for the region problem of the angle.
	@param x is the value 
	@param y is the value
	@return atan trigonometric value.
*/
	double ArcTan(double x, double y);


};

#endif