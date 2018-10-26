#ifndef UTILS__H
#define UTILS__H

#include <iostream>
#include "sensor_data.hpp"
using namespace std;

Sensor_data min(const Sensor_data & x, const Sensor_data & y){
	if(x < y){
		return x;
	}
	else
		return y;
}

Sensor_data max(const Sensor_data & x,const Sensor_data & y){
	if(x > y)
		return x;
	else
		return y;
}

Sensor_data sum(const Sensor_data & x, const Sensor_data & y){ return (x+y); }

#endif