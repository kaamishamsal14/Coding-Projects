/*
 * TemperatureData.cpp
 *
 *  Created on: Jul 16, 2018
 *      Author: student
 */
#include <string>
#include "TemperatureData.h"
using namespace std;

TemperatureData::TemperatureData() {
	id ="";
	year = 0; //invalid
	month = 0; //invalid
	temperature = 0.0; //invalid
} //initialize everything(done)

TemperatureData::TemperatureData(std::string id, int year, int month, double temperature) {
	this->id = id;
	this->year = year;
	this->month = month;
	this->temperature = temperature;
} //initialize everything(done)


TemperatureData::~TemperatureData() {} // You should not need to implement this

bool TemperatureData::operator<(const TemperatureData& b) {
	// Implement this(done)
	if(this->id < b.id){
		return true;
	} else if(this->year < b.year && this->id==b.id)
	{
		return true;
	} else if (this->month < b.month && this->year==b.year && this->id==b.id)
	{
		return true;
	} 
	return false;
}

