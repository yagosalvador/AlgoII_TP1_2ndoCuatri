#ifndef SENSORDATA_HPP__
#define SENSORDATA_HPP__

#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

class Sensor_data{
  private:
  	double value;
  	bool is_empty;

  public:
  	Sensor_data(){}
  	~Sensor_data(){}
  	Sensor_data(const Sensor_data& d){
  		value = d.value;
  		is_empty = d.is_empty;
  	}

  	Sensor_data(const double& v, const bool & b){
  		value = v;
  		is_empty = b;
  	}

  	double getData(){return value;}

  	bool isEmpty(){return is_empty;}

  	friend ostream& operator<<(ostream& os, const Sensor_data & d){
  		if(d.is_empty == false)
  			os << d.value;
  		else
  			os << "NO DATA";
  		return os;
  	}

  	friend istream& operator>>(istream& is, Sensor_data& d){
  		char ch;
  		double aux;
  		bool good;
  		std::string str;

  		d.is_empty = false;
  		if(is >> ch){
  			is.putback(ch);
			is >> aux;

  			if(is.fail()){
  				d.is_empty = true;
  				good = true;
  				is.clear(std::ios::goodbit);
  			}

  			else if(is.peek()!=','){
  				is.clear(std::ios::goodbit); // if input is sth like 123asd, it will read 123
  				good = true;
  				d.is_empty = true;
  			}

  			else{
  				d.is_empty = false;
  				good = true;
  			}
  		}
  		else if(is.good()){
  			is.putback(ch);
  			good = getline(is,str);
  		}
  		if(good == true){
  			if(d.is_empty == false)
	  			d.value = aux;
	  		else{
	  			d.value = std::numeric_limits<double>::quiet_NaN();
	  		}
  		} else {
            is.clear(std::ios::badbit);
            std::cerr << "ERROR_MSG_CORRUPTED_DATA" << std::endl;
        }
        return is;
	}

};




#endif