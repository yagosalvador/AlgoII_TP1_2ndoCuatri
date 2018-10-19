#ifndef SENSORES_HPP__
#define SENSORES_HPP__

#include <sstream>
#include <string>

#include "errors.hpp"
#include "vector.hpp"
#include "component.hpp"

using namespace std;

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
        double x;
        size_t i;

        getline(is,str);
        str.resize(str.length()-1);//to eliminate last null char, and avoid having two of them with next getline
        iss << str;
        while(getline(iss,str,',')){
            if(str.length() == 1){ //in case empty str
                std::cerr << ERROR_DATABASE << std::endl;
                exit(1);
            }
            obj.setId(str);
            s.v.append(obj);
        }


        while(!is.eof()){
            for(i=0; i < s.v.getSize() && !is.eof(); i++){
                if(is.fail()){
                	std::cerr << ERROR_DATABASE << std::endl; //if empty, complete with 0, last value or what?
                	exit(1);
                }
                is >> x;
                if(is.eof())
                    break;
                is.ignore(1,',');
                s.v[i].append(x);
            }
        }
	for(i=0;i<s.v.getSize();i++)
		s.v[i].buildTree();

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

	size_t getSize(){return v.getSize();}

    ~Sensores(){};

};

#endif
