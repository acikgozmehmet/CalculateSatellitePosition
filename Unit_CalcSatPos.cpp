#include<iostream>
#include "./BrdcEph/BrdcEph.h"

using namespace std;

int main() {
		
	{ // test -1
		cout << endl << "===============Test-1 started=======================" << endl;
		BrdcEph brdc237("brdc2370.05n");
		Epoch t;
		t.date = { 2005, 8, 25 };
		t.time = { 12, 10 ,0 };
		Car satPos;
		int svprn = 11;
		if (brdc237.calcSatPos(11, t, satPos)) {
			cout << endl << "ECEF Cartesian Coordinates of the Satellite #"; cout << svprn << endl;
			cout << "Epoch                                  X(m)         Y(m)         Z(m)" << endl;
			t.print(); cout << "\t\t";   satPos.print();
		}
		cout << endl << "=============== Test-1 done =======================" << endl;
		cout << endl;
	}
	

	{ // test -2
		cout << endl << "===============Test-2 started=======================" << endl;
		BrdcEph brdc("brdc2330.05n");
		Epoch t;
		t.date = { 2005, 8, 21 };
		t.time = { 4, 5 ,0 };
		Car satPos;
		int svprn = 11;
		if (brdc.calcSatPos(11, t, satPos)) {
			cout << endl << "ECEF Cartesian Coordinates of the Satellite #"; cout << svprn << endl;
			cout << "Epoch                                  X(m)         Y(m)         Z(m)" << endl;
			t.print(); cout << "\t\t";   satPos.print();
		}
		cout << endl << "=============== Test-2 done =======================" << endl;
		cout << endl;
	}


	{ // test-3
		cout <<endl << "===============Test-3 started======================="<< endl;
		BrdcEph brdceph("epgg0100.02n");
		Epoch t;
		t.date = { 2002, 1, 10 };
		t.time = { 0, 15 ,0 };
		Car satPos;
		int svprn = 31;
		if (brdceph.calcSatPos(svprn, t, satPos)){
			cout << endl << "ECEF Cartesian Coordinates of the Satellite #"; cout << svprn << endl;
			cout << "Epoch                                  X(m)         Y(m)         Z(m)" << endl;
			t.print(); cout << "\t\t";   satPos.print();
		}
		cout <<endl<<"=============== Test-3 done =======================" << endl;
		cout << endl << endl;
		
	}



	{ // test -4
		cout << endl << "===============Test-4 started=======================" << endl;
		BrdcEph brdc("auto0010.01n");
		Epoch t;
		t.date = { 2001, 1, 1 };
		t.time = { 0, 0 ,0 };
		int svprn = 24;
		Car satPos;
		if (brdc.calcSatPos(svprn, t, satPos)) {
			cout << endl << "ECEF Cartesian Coordinates of the Satellite #"; cout << svprn << endl;
			cout << "Epoch                                  X(m)         Y(m)         Z(m)" << endl;
			t.print(); cout << "\t\t";   satPos.print();
		}
		cout << endl << "=============== Test-4 done =======================" << endl;
		cout << endl;

	}


	{ // test -5
	  // Kai Borre solution with 'pta.96n' ==
		cout << endl << "===============Test-5 started=======================" << endl;
		BrdcEph brdc("PTA02530.96N");
		Epoch t;
		t.date = { 1996, 9, 9 };
		t.time = { 22, 0 ,0 };
		Car satPos;
		if (brdc.calcSatPos(1, t, satPos)) {
			cout <<endl << "ECEF Cartesian Coordinates of the Satellite #1: " << endl;
			cout << "Epoch                                  X(m)         Y(m)         Z(m)" << endl;
			t.print(); cout << "\t\t";   satPos.print();
		}
		cout << endl << "=============== Test-5 done =======================" << endl;
		cout << endl;
	}


	cin.get();

	return 0;
}