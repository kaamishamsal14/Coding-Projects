#include "TemperatureDatabase.h"

#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

// Default constructor/destructor. Modify them if you need to.
TemperatureDatabase::TemperatureDatabase() {}
TemperatureDatabase::~TemperatureDatabase() {}

void TemperatureDatabase::loadData(const string& filename) {
	// Implement this function for part 1
	/*
	std::ifstream file(filename);
	if (! file.is_open())
	{
		cout << "Error: Unable to open " << filename;
	}

	std::string id;
	int year;
	int month;
	double temp;
	while ( file >> id >> year >> month >> temp )
	{
		if ( temp < -50 || temp > 50)
		{
			cout << "Error: Invalid temperature " << temp;
		}
		else if (year < 1800  || year > 2022)
		{
			cout << "Error: Invalid year " << year;
		}
		else if (month < 1 || month > 12)
		{
			cout << "Error: Invalid month " << month;
		}
		// records.insert(id, year, month, temp);
	}
	*/
	string id="";
	string line="";
	int year = -1;
	double month = -1; //
	double temp = -1;
	ifstream file(filename);
	if(!file.is_open()){
		cout << "Error: Unable to open input.dat"<<endl;
	}
	else{
		while(!file.eof()){
			getline(file, line);
			istringstream sin(line);
			if(line==""){
				break;
			}
			sin >> id;
			if(!sin.good()){
				cout << "Error: Invalid location " << id << endl;
				continue;
			}
			if(id==""){
				cout<<"Error: Invalid location "<< id << endl;
				continue;
			}
			sin >> year;
			if(!sin.good()){
				cout << "Error: Invalid year " << year << endl;
				continue;
			}
			else if(year>=2022 || year<1800){
				cout << "Error: Invalid year " << year << endl;
				continue;
			}
			sin>>month;
			if(month==0.2){
				cout << "Error: Other invalid input " << endl;
				continue;
			}
			else if(month<1.0 || month>12.0){
				cout << "Error: Invalid month " << int(month) << endl;
				continue;
			}
			if(sin.eof()){
				cout << "Error: Other invalid input " << endl;
				continue;
			}
			sin >> temp;
			if(!(temp >= -50.0 && temp<= 50.0) && temp!= -99.99){
				cout << "Error: Invalid temperature " << temp << endl;
				continue;
			}
			LinkedList ll;
			ll.insert(id,year,month,temp);
			cout << ll.print();
			id="";
			line="";
		}
	}
}

// Do not modify
void TemperatureDatabase::outputData(const string& filename) {
	ofstream dataout("sorted." + filename);
	
	if (!dataout.is_open()) {
		cout << "Error: Unable to open " << filename << endl;
		exit(1);
	}
	dataout << records.print();
}

//void TemperatureDatabase::performQuery(const string& filename) {
	// Implement this function for part 2
	//  Leave it blank for part 1
//}