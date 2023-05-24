#include <iostream>
#include <iomanip>
#include <string>
#include "parallel_tracks.h"
#include <sstream>
#include <fstream>


using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::istringstream;
using std::ifstream;

//-------------------------------------------------------
// Name: get_runner_data
// PreCondition:  the prepped parallel arrays , and a legit filename is pass
// PostCondition: all arrays contain data from the text file given
//---------------------------------------------------------
void get_runner_data( const std::string& file, double(&timeArray)[SIZE], std::string(&countryArray)[SIZE],
                      unsigned int(&numberArray)[SIZE], std::string(&lastnameArray)[SIZE])
{
	ifstream fin(file);
	uint g = 0;
	string line = "";
	double time = 0.0;
	string country = "";
	unsigned int number = 0;
	string name = "";
	unsigned int rankArray[SIZE];
	prep_unsigned_int_array(rankArray);
	int name_len = 0;
	string name_2 = "";
	string n = "";

	if (!fin.is_open()) {
		throw std::runtime_error("Cannot open file");
	}
	else {
		while (!fin.eof()) {
			getline(fin, line);
			//cout << line << endl;
			if (fin.eof() && line == "") {
				break;
			}
			istringstream sin(line);
			sin >> time;
			if (!sin.good() || time <= 0.0) {
				throw std::domain_error("File contains invalid data (time)");
			}
			else {
				timeArray[g] = time;
			}
			sin >> country;
			if (country.length() != 3) {
				throw std::domain_error("File contains invalid data (country)");
			}
			else if ((country.at(0) < 65 || country.at(0) > 90) || (country.at(1) < 65 || country.at(1) > 90) || (country.at(2) < 65 || country.at(2) > 90)) {
				throw std::domain_error("File contains invalid data (country)");
			}
			else {
				countryArray[g] = country;
			}
			sin >> number;
			if (!sin.good() || number > 99) {
				throw std::domain_error("File contains invalid data (number)");
			}
			else {
				numberArray[g] = number;
			}
			sin >> name;
			name_len = name.length();
			if (name_len > 1 && name != "") {
				for (int i = 0; i < name_len; i++) {
					if ((name.at(i) >= 65 && name.at(i) <= 90) || (name.at(i) >= 97 && name.at(i) <= 122)) {
						n = name;
					}
					else {
						throw std::domain_error("File contains invalid data (name)");
					}
				}
			}
			else {
				throw std::domain_error("File contains invalid data (name)");
			}
			sin >> name_2;
			if (name_2 == "") {
				lastnameArray[g] = n;

				//continue;
			}
			else {
				name_len = name_2.length();
				if (name_len > 1 && name_2 != "") {
					for (int i = 0; i < name_len; i++) {
						if ((name_2.at(i) >= 65 && name_2.at(i) <= 90) || (name_2.at(i) >= 97 && name_2.at(i) <= 122)) {
							n += name_2;
							lastnameArray[g] = n;
						}
						else {
							throw std::domain_error("File contains invalid data (name)");
						}
					}
				}
			}

			g+=1;
		}
	}
	if (!fin.eof() && line == "") {
		throw std::domain_error("File missing data");
	}
	get_ranking(timeArray, rankArray);
	print_results(timeArray, countryArray, lastnameArray, rankArray);
}

//-------------------------------------------------------
// Name: prep_double_array
// PreCondition:  a double arrays is passed in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_double_array(double(&ary)[SIZE])
// making sure all values within the array are set to 0.0;
{
	//const unsigned int SIZE = 9;
	double g = 0.0;
	for (unsigned int i = 0; i < SIZE; i++) {
		ary[i] = g;
	}
}

//-------------------------------------------------------
// Name: prep_double_array
// PreCondition:  an unsigned int arrays is passed in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_unsigned_int_array(unsigned int(&ary)[SIZE])
// making sure all values within the array are set to 0;
{
	//const unsigned int SIZE = 9;
	for (unsigned int i = 0; i < SIZE; i++) {
		ary[i] = 0;
	}
}

//-------------------------------------------------------
// Name: prep_string_array
// PreCondition:  a string arrays is pass in
// PostCondition: data in the array is "N/A" out to determine if
// a value has changed
//---------------------------------------------------------
void prep_string_array(std::string(&ary)[SIZE])
// making sure all values within the array are set to "N/A";
{
	for (unsigned int i = 0; i < SIZE; i++) {
		ary[i] = "N/A";
	}
}

//-------------------------------------------------------
// Name: get_ranking
// PreCondition:  just the time array is passed in, and has valid data
// PostCondition: after a very inefficient nested loop to determine the placements
// and places the ranks in a new array. That new array is returned
//---------------------------------------------------------
void get_ranking(const double(&timeArray)[SIZE], unsigned int(&rankArray)[SIZE])
{
	double temptimeArray[SIZE];
	for (unsigned int i = 0; i < SIZE; i++) {
		temptimeArray[i] = timeArray[i];
	}
	int ranking = SIZE;
	while (ranking != 0) {
		double max = 0;
		uint arr_max = 0;
		for (unsigned int i = 0; i < SIZE; i++) {
			if (temptimeArray[i] > max) {
				max = temptimeArray[i];
				arr_max = i;
			}
		}
		temptimeArray[arr_max] = 0.0;
		rankArray[arr_max] = ranking;
		ranking -= 1;
	}
}



//-------------------------------------------------------
// Name: print_results
// PreCondition:  almost all parallel arrays are passed in and have valid data
// PostCondition: after a very inefficient nested loop to determine the ranks
// it then displays then along with a delta in time from the start
//---------------------------------------------------------
void print_results(const double(&timeArray)[SIZE], const std::string(&countryArray)[SIZE],
                   const std::string(&lastnameArray)[SIZE], const unsigned int(&rankArray)[SIZE])
{

	std::cout << "Final results!!";
	std::cout << std::setprecision(2) << std::showpoint << std::fixed << std::endl;
	double best_time = 0.0;

	// print the results, based on rank, but measure the time difference_type
	for (unsigned int j = 1; j <= SIZE; j++)
	{

		// go thru each array, find who places in "i" spot
		for (unsigned int i = 0; i < SIZE; i++)
		{
			if (rankArray[i] == 1) // has to be a better way, but need the starting time
			{
				best_time = timeArray[i];
			}


			if (rankArray[i] == j) // then display this person's data
			{
				// this needs precision display
				std::cout << "[" << j << "]  " << timeArray[i] << " " << std::setw(15) << std::left << lastnameArray[i] << "\t" << "(" << countryArray[i] << ")  +" << (timeArray[i] - best_time) << std::endl;
			}

		}
	}
}

std::string trim(std::string ret) {
	// remove whitespace from the beginning
	while (!ret.empty() && isspace(ret.at(0))) {
		ret.erase(0, 1);
	}

	// remove whitespace from the end
	//  Note: last index is (.size() - 1) due to 0 based indexing
	while (!ret.empty() && isspace(ret.at(ret.size() - 1))) {
		ret.erase(ret.size() - 1, 1);
	}

	return ret;
}