#include "BrdcEph.h"

const double BrdcEph::PI = atan(1.0) * 4;

BrdcEph::BrdcEph():m_filename("") {}
BrdcEph::BrdcEph(string filename) : m_filename(filename) { 
	cout << "Loading :" << m_filename << endl;
	readFromFile(m_filename);
}
BrdcEph::~BrdcEph() {}

void BrdcEph::setFilename(string filename) { m_filename = filename; }
string BrdcEph::getFilename(void) { return m_filename; }

void BrdcEph::load() { 
	cout << "Loading :" << m_filename << endl;
	readFromFile(m_filename); 
}

void BrdcEph::readFromFile(const string& filename) {
	ifstream inFile;
	string line;

	try {
		inFile.open(filename);
		if (!inFile)
			throw runtime_error(filename + " does not exist !");
	}
	catch (runtime_error& ex) {
		cout << endl << "Error ! : " << ex.what() << endl;
		cin.get();
		exit(1);
	}

	// For the default summary file...
	string outFilename = filename.substr(0, filename.find(".")) + ".sum";
	ofstream outFile;
	outFile.open(outFilename);

	// Getting the name of the brdc file and writing it to outFile
	string stationName = filename.substr(0, 4);
	for (unsigned int i = 0; i < stationName.length(); i++)
		stationName.at(i) = toupper(stationName.at(i));

	outFile << "\t\t\t" << stationName << endl;

	// this part of code is to skip the header part of the input file
	do {
		getline(inFile, line);
	} while (line.substr(60, 13) != "END OF HEADER");

	// the main part of the input file
	int counter = 0;
	while (getline(inFile, line) && line.size() > 0) {

		changeSciNotation(line); // to get rid of the fortran style double sign D+2 -> E+2

		Ephemeris eph;

		// first line of the nav. message : prn, epoch, satclk
		eph.svID = atoi(line.substr(0, 2).c_str());
		eph.toc.date.year  = atoi(line.substr(3, 2).c_str());
		eph.toc.date.month = atoi(line.substr(6, 2).c_str());
		eph.toc.date.day   = atoi(line.substr(9, 2).c_str());
		eph.toc.time.hour  = atoi(line.substr(12, 2).c_str());
		eph.toc.time.min   = atoi(line.substr(15, 2).c_str());
		eph.toc.time.sec   = atof(line.substr(17, 5).c_str());
		eph.af0 = atof(line.substr(22, 19).c_str());
		eph.af1 = atof(line.substr(41, 19).c_str());
		eph.af2 = atof(line.substr(60, 19).c_str());
		
		convertYYToYYYY(eph.toc.date.year);

		// broadcast orbit 1 - //    double IODE, crs, deltan, M0;
		getline(inFile, line);
		changeSciNotation(line);				
		//eph.IODE = atof(line.substr(3,22).c_str());
		eph.crs = atof(line.substr(22, 19).c_str());
		eph.deltan = atof(line.substr(41, 19).c_str());
		eph.M0 = atof(line.substr(60, 19).c_str());

		// broadcast orbit 2 - 		//    cuc, ecc, cus, roota;
		getline(inFile, line);
		changeSciNotation(line);
		eph.cuc = atof(line.substr(3, 19).c_str());
		eph.ecc = atof(line.substr(22, 19).c_str());
		eph.cus = atof(line.substr(41, 19).c_str());
		eph.roota = atof(line.substr(60, 19).c_str());

		// broadcast orbit 3 - 		//    toe, cic, Omega0, cis;
		getline(inFile, line);
		changeSciNotation(line);
		eph.toe = atof(line.substr(3, 19).c_str());
		eph.cic = atof(line.substr(22, 19).c_str());
		eph.Omega0 = atof(line.substr(41, 19).c_str());
		eph.cis = atof(line.substr(60, 19).c_str());

		// broadcast orbit 4 - 		//    i0, crc, omega, Omegadot;
		getline(inFile, line);
		changeSciNotation(line);
		eph.i0 = atof(line.substr(3, 19).c_str());
		eph.crc = atof(line.substr(22, 19).c_str());
		eph.omega = atof(line.substr(41, 19).c_str());
		eph.Omegadot = atof(line.substr(60, 19).c_str());


		// broadcast orbit 5 - 		//   idot, codes, weekno, L2flag;
		getline(inFile, line);
		changeSciNotation(line);
		eph.idot = atof(line.substr(3, 19).c_str());
		//eph.codes = atof(line.substr(22,41).c_str());
		eph.weekno = atof(line.substr(41,60).c_str());
		//eph.L2flag = atof(line.substr(60,79).c_str());

		// broadcast orbit 6 - 		//   svaccur, svhealth, tgd, iodc;
		getline(inFile, line);
		changeSciNotation(line);
		/*   eph.svaccur = atof(line.substr(3,22).c_str());
		eph.svhealth = atof(line.substr(22,41).c_str());
		eph.tgd = atof(line.substr(41,60).c_str());
		eph.iodc = atof(line.substr(60,79).c_str());
		*/

		// broadcast orbit 7 - 		//   tom, spare, spare, spare;
		getline(inFile, line);
		changeSciNotation(line);
		eph.tom = atof(line.substr(3, 19).c_str());
		//eph.spare1 = atof(line.substr(22,41).c_str());
		//eph.spare2 = atof(line.substr(41,60).c_str());
		//eph.spare3 = atof(line.substr(60,79).c_str());

		eph.hasData = true;
		// This is just a test: cross-check
		Epoch t;
		TimeSystems::GPSTimeToDate(eph.weekno, eph.toe, t.date.year, t.date.month, t.date.day, t.time.hour, t.time.min, t.time.sec);
		
		//cout << "date and time from gpsweek and toe :"; t.print(); cout << endl;
		//cout << "date and time from toc             :"; eph.toc.print(); cout << endl;
		//cin.get();
		
		/*
		eph.toc.print();
		cout << "  " <<hashFunction(eph.toc);
		cout << endl;
		*/
		int index = hashFunction(eph.toc);
		//eph.toc.date.print(); cout << endl;
		
		if (!m_data[eph.svID][index].hasData) {
			m_data[eph.svID][index] = eph;
		}
		else {
			//outFile << "\t*Collision for the SV # " << setw(2) << m_data[eph.svID][index].svID << " and epoch : " << m_data[eph.svID][index].toe << endl;
			outFile << "\t*Collision for the SV # " << setw(2) << m_data[eph.svID][index].svID << " and epoch : "; m_data[eph.svID][index].toc.print(outFile); outFile << endl;
			//outFile << "\t*Epoch of previous data and new data respectivley : " << m_data[prn][index].toe << "  " <<eph.toe << endl;
			if (eph.toe > m_data[eph.svID][index].toe) {
				m_data[eph.svID][index] = eph;
				outFile << "  Indexing updated with the most recent one" << endl;
			}
		}

		// Reporting the status
		counter++;
		printLoadingBar(counter);
	} // end of reading main part
	//cout << "PI : " << PI << endl;
	cout << " 100 %" << endl;  // for printLoadingBar to display that all the data is loaded...
	printGraphics(outFile);
	inFile.close();
	outFile.close();
}


void BrdcEph::convertYYToYYYY(int & yy) {
	if (yy < 100) {
		if (yy < 80) {
			yy += 2000;
		}
		else
			yy += 1900;
	}
}

void BrdcEph::changeSciNotation(string& text) {
	for (unsigned int i = 0; i < text.length(); i++) {
		if (toupper(text.at(i) == 'D'))
			text.at(i) = 'E';
	}
}


int BrdcEph::hashFunction(Epoch t) {
	//cout << endl;  t.print(); cout << endl;
	int key = (t.time.hour + (t.time.min + ceil(t.time.sec / 60)) / 60); // it is ok to have the data within 1 minute latency
	//key %= 24;
	//cout << key << endl;
	//cin.get();

	int doy = atoi(m_filename.substr(4, 3).c_str());
	int doyFromEpoch = TimeSystems::DateToDoy(t.date.year, t.date.month, t.date.day, t.time.hour, t.time.min, t.time.sec);
	//cout << doy << " " << doyFromEpoch << endl;

	if (doyFromEpoch - doy == -1) { // one day before
		key = 0;
	}
	else if (doyFromEpoch - doy == 1) { // one day later
		key = 24;
	}
	
	//cout << "key: " << key << endl;



	if (key % 2 == 0) { // even
		return (key % MAX_EPOCH);
	}
	else { // odd
		return ( (key - 1) % MAX_EPOCH );
	}


}


void BrdcEph::printGraphics(ostream& w) {
	w << endl << "\t\t\t\tRinex Navigation File Data Availibilty Graph" << endl << endl;
	w << "       ";

	for (int i = 1; i < MAX_SV; i++)
		w << setw(3) << i;// % 10;
	w << endl;

	for (int i = 0; i < MAX_EPOCH; i++) {
		w << setw(2) << (2 * i) % 24 << " - " << setw(2) << (2 * i + 2) % 24; // << "  ";
		for (int j = 1; j < MAX_SV; j++) {
			w << (m_data[j][i].hasData ? "  X" : "   ");
		}
		w << endl;
	}
}


void BrdcEph::printLoadingBar(int counter) {

	int refVal = round(double(MAX_EPOCH * (MAX_SV - 1)) / 100) * 2;

	if (counter == 0)
		cout << "Loading Navigation File...  " << m_filename << endl;
	else if (counter % refVal == 0)
		cout << "*";

}

int BrdcEph::getIndex(Epoch t) {
	return hashFunction(t);
}


// first check the availability of eph data
// then fetch it if it is present there
// else continue with the next obs. skip this one. just let it know that it is skipped...
// As in the following...
/*
   if (isEphDataAvailable(svID, ephIndex)){
         getEphData(svID, ephIndex));
   }
   else{
      continue;
   }
*/

Ephemeris BrdcEph::getEphData(int svID, int ephIndex) {
	return m_data[svID][ephIndex];

		//Ephemeris temp;
	/*
		if (isEphDataAvailable(svID, ephIndex))
			return m_data[svID][ephIndex];
		else {
			cout << "Error: No ephemeris data within the 4 hour of the observation time" << endl;
			exit(1);
		}

	*/
}

bool BrdcEph::isEphDataAvailable(int svID, int& ephIndex) {

	if ((ephIndex == 0) && (!m_data[svID][ephIndex].hasData)) { // if it is the first record and has no ephemeris data			
		m_data[svID][ephIndex + 1].hasData ? ephIndex++ : ephIndex = -1; // check the next record and if does not have data either, set -1
	}
	else if ((ephIndex == 11) && (!m_data[svID][ephIndex].hasData)) { // if it is the last record and has no ephemeris data			
		m_data[svID][ephIndex - 1].hasData ? ephIndex-- : ephIndex = -1; // so similar to the above...
	}
	else if (!m_data[svID][ephIndex].hasData) {  // if it is somewhere in the middle and has no ephemeris data
		if (m_data[svID][ephIndex - 1].hasData) // use the previous record as long as it has ephemeris data 
			ephIndex--;
		else if (m_data[svID][ephIndex + 1].hasData)   // othwerwise use the next record
			ephIndex++;
		else
			ephIndex = -1; // last case: no data within the 4 hour of the observation time
	}

	return (ephIndex == -1 ? false : true); // if no ephemeris data for the epoch return false otherwise true.
}


void BrdcEph::checkTk(double& tk) {
	if (tk > 302400)
		tk -= 604800;
	else if (tk < -302400)
		tk += 604800;
}

double BrdcEph::ArcTan(double x, double y) {
	const double PI = std::atan(1.0) * 4;
	const double RHO = 180.0 / PI;
	double teta;
	teta = atan2(x, y);
	teta < 0 ? teta = teta + 2 * PI : teta = teta;
	return teta;
}


bool BrdcEph::calcSatPos(int svID, Epoch t, Car& satPos) {

	satPos = { 0, 0, 0 }; // initial value for each run, just to be on the safe side. 
	const double  GM = constants::GM;
	const double  OMEGAE_DOT = constants::OMEGAE_DOT;

	// First step to get the ephemerides ...
	int ephIndex = getIndex(t);
	Ephemeris eph;
	
	if (isEphDataAvailable(svID, ephIndex))  // if ephemeris is available, get it. Otherwise return false
		eph = getEphData(svID, ephIndex);
	else
		return false;
	
	// incase of an error in indexing
	if (svID != eph.svID) { 
		cout << "There is an error in indexing the ephemeris" << endl;
		cin.get();
		return false;
	}
		
	// tk
	double secWeek;
	int gWeek, dWeek;
	TimeSystems::DateToGPSTime(t.date.year, t.date.month, t.date.day, t.time.hour, t.time.min, t.time.sec, secWeek, gWeek, dWeek);
	double tk = secWeek - eph.toe;
	checkTk(tk);

	// mean anomaly for tk
	double A = eph.roota * eph.roota;
	double M = eph.M0 + (sqrt(GM / pow(A, 3)) + eph.deltan) * tk;
	//cout <<" A= " << A << "  " << M<< endl;


	// Solving (iteratively) Kepler equation for the eccentricity anomaly Ek:
	double E, Eold, dE, v;
	E = M;
	do {
		Eold = E;
		E = M + eph.ecc * sin(E);
		dE = abs(Eold - E);
	} while (dE > 1e-12);

	//Calculation of real anomaly vk:
	double uu1 = sqrt(1 - pow(eph.ecc, 2)) * sin(E);
	double uu2 = (cos(E) - eph.ecc);
	v = ArcTan(uu1, uu2);

	// Calculation of the argument of latitude uk from the argument of
	// perigee ω, real anomaly vk and corrections cuc and cus:
	double phi = v + eph.omega;
	phi = fmod(phi, (2 * PI));
	double u = phi + eph.cuc*cos(2 * phi) + eph.cus*sin(2 * phi);

	//Calculation of the radial distance rk, considering corrections crc and crs:
	double r = A * (1 - eph.ecc*cos(E)) + eph.crc*cos(2 * phi) + eph.crs*sin(2 * phi);

	// Calculation of inclination ik of the orbital plane from the inclination
	// io at the reference time toe, and corrections cic and cis:
	double i = eph.i0 + eph.idot*tk + eph.cic*cos(2 * phi) + eph.cis*sin(2 * phi);

	/*Calculation of the longitude of the ascending node λk (referring
	to Greenwich), using its right ascension
	o at the beginning
	of the current week, corrected from the apparent sidereal time
	variation in Greenwich between the beginning of the week and
	reference time tk = t − toe, and the change in longitude of the
	ascending node from the reference time toe.
	*/
	double Omega = eph.Omega0 + (eph.Omegadot - OMEGAE_DOT)*tk - OMEGAE_DOT * eph.toe;
	Omega = fmod((Omega + 2 * PI), (2 * PI));
	
	// Position in orbital plane
	double x1, y1;
	x1 = cos(u) * r;
	y1 = sin(u) * r;

	/*
	Calculation of coordinates in CTS frame, by applying three rotations
	(about uk, ik, λk):
	*/
	satPos.x = x1 * cos(Omega) - y1 * cos(i)*sin(Omega);
	satPos.y = x1 * sin(Omega) + y1 * cos(i)*cos(Omega);
	satPos.z = y1 * sin(i);

	//cout << "secWeek : " << secWeek << endl;
	return true;
}


bool BrdcEph::calcSatPos(int svID, int GPSweek, double tGPSsec, Car& satPos) {

	Epoch t;
	TimeSystems::GPSTimeToDate(GPSweek, tGPSsec, t.date.year, t.date.month, t.date.day, t.time.hour, t.time.min, t.time.sec);
	return calcSatPos(svID, t, satPos);
	
}



double BrdcEph::calcSatClkBias(int svID, Epoch t) {
	double secWeek;
	int gWeek, dWeek;
	TimeSystems::DateToGPSTime(t.date.year, t.date.month, t.date.day, t.time.hour, t.time.min, t.time.sec, secWeek, gWeek, dWeek);

	// Let's get the ephemerides ...
	int index = getIndex(t);
	Ephemeris eph = getEphData(svID, index);
	double tk = secWeek - eph.toe; // time elapsed since toe
	checkTk(tk);
	        //af0+ af1*t + af2* t^2      t -> tk	
	double result = eph.af0 + (eph.af1 * tk) + (eph.af2 * pow(tk, 2));
	//cout << "Sat Clock Bias: " << fixed << setprecision (12) << result << endl;
	return result;
}

double BrdcEph::calcSatClkBias(int svID, int GPSweek, double tGPSsec) {
	Epoch t;
	TimeSystems::GPSTimeToDate(GPSweek, tGPSsec, t.date.year, t.date.month, t.date.day, t.time.hour, t.time.min, t.time.sec);

	return calcSatClkBias(svID, t);
}