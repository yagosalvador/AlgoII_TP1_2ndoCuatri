#ifndef COMPONENTS__H
#define COMPONENTS__H

#include <iostream>
#include <string>
#include "sensor_data.hpp"

#include "vector.hpp"

using namespace std;

class Component{
  private:
    std::string id;
    Vector<Sensor_data> data;

  public:
    Component(){
        id = "";
    };

    ~Component(){};

    Component(const Component& c){
        id = c.id;
        data = c.data;
    }

    Component(std::string str, Vector<Sensor_data> d){
        id = str;
        data = d;
    }

    void setId(std::string str){
        id = str;
    }

    std::string showId() const{return id;}

    void append(Sensor_data x){
        data.append(x);
        return;
    }

    friend ostream& operator<< (ostream& os, const Component& c){
        os << c.showId() << std::endl;
        os << c.data << std::endl;
        return os;
    }

    Component& operator= (const Component& c){
        (*this).id = c.id;
        (*this).data = c.data;
        return *this;
    }

    double getAvg(size_t t0, size_t tf){
        size_t i, j;
        double sum = 0;

        if(t0 == tf){
            if(data[tf].isEmpty())
                return std::numeric_limits<double>::quiet_NaN();//REVISAAAAAAAAAAAAAAAAAAAAR
            return data[tf].getData();
        }
        for(i = t0, j = 0; i < tf ; j++, i++)
            if(data[i].isEmpty())
                j--;
            else
                sum += data[i].getData();

        return sum/j; 
    }

    double getMax(size_t t0, size_t tf){
        size_t i = t0;
        double aux = 0;


        while(data[i].isEmpty()) //check until finding a value that is valid
            i++;

        for(aux = data[i].getData(); i < tf ;i++){
            if(!data[i].isEmpty()){
                if(aux < data[i].getData())
                    aux = data[i].getData();
            }
        }

        return aux;
    }

    double getMin(size_t t0, size_t tf){
        size_t i = t0;
        double aux = 0;

        while(data[i].isEmpty()) //check until finding a value that is valid
            i++;

        for(aux = data[i].getData(); i < tf ; i++){
            if(!data[i].isEmpty()){
                if(aux > data[i].getData())
                    aux = data[i].getData();
            }
        }

        return aux;
    }

    size_t getDataVol(size_t t0, size_t tf){return tf-t0;}

    size_t getSize(){return data.getSize();}

};

#endif
