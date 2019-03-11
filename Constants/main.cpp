#include<iostream>

#include "constants.h"





using namespace std;
int main(){

	//double M_PI = (4 * atan(1.0));
	double radius = 2.0;
	double circumference = 2 * radius * constants::C;
	cout << circumference << endl;
	cout << "C: " << constants::C << endl;
	cout << "GM: " << constants::GM << endl;

	cin.get();

	return 0;

}
