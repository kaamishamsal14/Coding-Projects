#ifndef PARALLEL_TRACKS_H
#define PARALLEL_TRACKS_H

#include <string>

const unsigned int SIZE = 9; // lines in the data


//-------------------------------------------------------
// Name: get_runner_data
// PreCondition:  the prepped parallel arrays , and a legit filename is pass
// PostCondition: all arrays contain data from the text file given
//---------------------------------------------------------
void get_runner_data( const std::string& file, double(&timeArray)[SIZE], std::string(&countryArray)[SIZE], 
		unsigned int(&numberArray)[SIZE], std::string(&lastnameArray)[SIZE]);

//-------------------------------------------------------
// Name: prep_double_array
// PreCondition:  a double arrays is pass in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_double_array(double(&ary)[SIZE]);

//-------------------------------------------------------
// Name: prep_double_array
// PreCondition:  a double arrays is pass in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_unsigned_int_array(unsigned int(&ary)[SIZE]);

//-------------------------------------------------------
// Name: prep_string_array
// PreCondition:  a string arrays is pass in
// PostCondition: data in the array is "N/A" out to determine if
// a value has changed
//---------------------------------------------------------
void prep_string_array(std::string(&ary)[SIZE]);

//-------------------------------------------------------
// Name: get_ranking
// PreCondition:  just the time array is passed in, and has valid data
// PostCondition: after a very inefficient nested loop to determine the placements 
// and places the ranks in a new array. That new array is returned
//---------------------------------------------------------
void get_ranking(const double(&timeArray)[SIZE], unsigned int(&rankArray)[SIZE]);

//-------------------------------------------------------
// Name: print_results
// PreCondition:  almost all parallel arrays are passed in and have valid data
// PostCondition: after a very inefficient nested loop to determine the ranks
// it then displays then along with a delta in time from the start
//---------------------------------------------------------
void print_results(const double(&timeArray)[SIZE], const std::string(&countryArray)[SIZE],
		const std::string(&lastnameArray)[SIZE], const unsigned int(&rankArray)[SIZE]);

//-------------------------------------------------------
// Name: trim
// PreCondition:  string
// PostCondition: returns string with whitespace removed from beginning and end
//---------------------------------------------------------
std::string trim(std::string);

#endif