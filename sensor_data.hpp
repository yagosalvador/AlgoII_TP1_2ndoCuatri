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
  	Sensor_data(){
  		is_empty = true;
  		value = 0;
  	}
  	~Sensor_data(){}

  	Sensor_data(const Sensor_data& d){
  		value = d.value;
  		is_empty = d.is_empty;
  	}

  	Sensor_data(const double& d){
  		value = d;
  		is_empty = false;
  	}

  	Sensor_data(const double& v, const bool & b){
  		value = v;
  		is_empty = b;
  	}

  	double getValue(){return value;}

  	bool isEmpty(){return is_empty;}

	operator bool(){
  		return !is_empty;
  	}

  	bool operator!(){
  		return is_empty;
  	}

  	friend ostream& operator<<(ostream& os, const Sensor_data & d){
  		if(d.is_empty == false)
  			os << d.value;
  		else
  			os << "NO DATA";
  		return os;
  	}

  	bool operator==(const Sensor_data& b)const{
  		if(is_empty == b.is_empty)
  			return true;
  		if(value == b.value)
  			return true;
  		return false;
  	}

  	bool operator<(const Sensor_data& b)const{
  		if(is_empty == true && b.is_empty == true)
  			return true;
  		if(is_empty == true && b.is_empty == false)
  			return false;
  		if(is_empty == false && b.is_empty == true)
  			return true;
  		
  		return value < b.value;
  	}

    bool operator<=(const Sensor_data& b)const{
        if(is_empty == true && b.is_empty == true)
            return true;
        if(is_empty == true && b.is_empty == false)
            return false;
        if(is_empty == false && b.is_empty == true)
            return true;
        
        return value <= b.value;
    }

  	bool operator>(const Sensor_data& b)const{
  		if(is_empty == true && b.is_empty == true)
  			return true;
  		if(is_empty == true && b.is_empty == false)
  			return false;
  		if(is_empty == false && b.is_empty == true)
  			return true;

  		return value > b.value;
  	}

    bool operator>=(const Sensor_data& b)const{
        if(is_empty == true && b.is_empty == true)
            return true;
        if(is_empty == true && b.is_empty == false)
            return false;
        if(is_empty == false && b.is_empty == true)
            return true;

        return value >= b.value;
    }

  	Sensor_data& operator+=(const Sensor_data& b){
		if(is_empty == false && b.is_empty == false){
			value += b.value;
			return *this;
		}

  		if(is_empty == true && b.is_empty == false){
  			value = b.value;
            is_empty = false;
  			return *this;
  		}

  		if(is_empty == false && b.is_empty == true)
  			return *this;
		
		return *this;
  	}

  	Sensor_data operator+(const double& b)const{
		if(is_empty == true)
  			return Sensor_data(b,false);
		return Sensor_data(value + b,true);
  	}

  	Sensor_data operator/(const Sensor_data& b)const{
		if(is_empty == true && b.is_empty == false)
  			return Sensor_data(0,false);
  		if(is_empty == false && b.is_empty == true)
  			return Sensor_data(0, true);
  		if(is_empty == false && b.is_empty == false)
  			return Sensor_data(value/b.value, false);
		return Sensor_data(0,true);
  	}

  	Sensor_data operator+(const Sensor_data& b)const{
  		if(is_empty == false && b.is_empty == false)
  			return Sensor_data(value + b.value,false);

  		if(is_empty == true && b.is_empty == false)
  			return Sensor_data(b.value,false);

  		if(is_empty == false && b.is_empty == true)
  			return Sensor_data(value,false);
		
		return Sensor_data(value,true);
  	}

  	Sensor_data& operator=(const Sensor_data& b){
  		is_empty = b.is_empty;
  		value = b.value;
  		return *this;
  	}  	

  	Sensor_data& operator=(const double& b){
  		is_empty = false;
  		value = b;
  		return *this;
  	}


  	operator double(){
  		return value;
  	}

  	operator size_t(){
  		return (size_t) value;
  	}

  	friend istream& operator>>(istream& is, Sensor_data& d){
  		char ch;
  		double aux = 0;
  		bool good;
  		std::string str;

        if( (ch = is.get()) ){
            while (isspace(ch))
                ch = is.get();
            is.putback(ch);;
			is >> aux;

  			if(is.fail()){
  				d.is_empty = true;
  				good = true;
  				is.clear(std::ios::goodbit);
  			}
  			else if(isalpha( is.peek() )){
  				is.clear(std::ios::goodbit); // if input is sth like 123asd, it will read 123
  				good = true;
  				d.is_empty = true;
  			}

  			else{
  				d.is_empty = false;
  				good = true;
  			}
  		}
        else if(is.eof())
            return is;

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