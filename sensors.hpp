#ifndef SENSORES_HPP__
#define SENSORES_HPP__

#include <sstream>
#include <string>

#include "errors.hpp"
#include "vector.hpp"
#include "component.hpp"
#include "sensor_data.hpp"

class Sensores{
  private:
    Vector<Component> v;

  public:
    Sensores(){};

    Sensores(const Sensores& a){
        v = a.v;
    }

    Sensores(Vector<std::string> ids){
        size_t i;

        for(i=0; i < v.getSize(); i++)
            v[i].setId(ids[i]);

    }

    friend istream& operator>> (istream& is, Sensores& s){
        std::string str;
        std::stringstream iss;
        Component obj;
        Sensor_data x,empty_data;
        size_t i;
        char ch;

        getline(is,str);
        if(str[str.length()-1] == 0x0d)
        	str.resize(str.length()-1);//to eliminate carriage return
        iss << str;
        while(getline(iss,str,',')){
            if(str.length() == 1){ //in case empty str
                std::cerr << ERROR_DATABASE << std::endl;
                exit(1);
            }
            obj.setId(str);
            s.v.append(obj);
        }
        iss.clear();

        ch = is.get();
        if(!is.eof())
            is.putback(ch);
        while(!is.eof()){
                getline(is,str);
                x = empty_data;
                if(is.fail()){
                	std::cerr << ERROR_DATABASE << std::endl;
                	exit(1);
                }
                iss << str;
                for(i = 0; i < s.v.getSize(); i++){
                    iss >> x;
                    if(is.fail())
                        x = empty_data;
                    iss.ignore(1,',');
                    s.v[i].append(x);
                    if(i == s.v.getSize()-1)
                        getline(iss,str);//in case there are extra columns
                }
                iss.clear();
        }
        return is;
    }

    friend ostream& operator<< (ostream& os, const Sensores& s){
        size_t i;

        for(i=0; i < s.v.getSize(); i++){
            os << s.v[i];             
        }

        return os;
    }

	Component operator[](size_t n){return v[n];}

    void append(const Component &c){v.append(c);}

	size_t getSize(){return v.getSize();}

    ~Sensores(){};

};

#endif
