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
    
    Component(std::string str){
        id = str;
    }

    Component(std::string str, Vector<Sensor_data> d){
        id = str;
        data = d;
    }

    Sensor_data operator[](size_t n){return data[n];}


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

    Sensor_data getAvg(size_t t0, size_t tf){
        size_t i, j;
        Sensor_data sum;

        for(i = t0, j = 0; i < tf ; j++, i++){
            if(data[i].isEmpty()){
                j--;
            }
            else{
                sum += data[i];
            }
        }

        if(sum.isEmpty()){
            return sum;
        }
        else{
            sum = sum.getValue()/j;
            return sum;
        }
    }

    Sensor_data getMax(size_t t0, size_t tf){
        size_t i = t0;
        Sensor_data aux;

        while(data[i].isEmpty()) //check until finding a value that is valid
            i++;

        for(aux = data[i]; i < tf ;i++){
            if(!data[i].isEmpty()){
                if(aux < data[i])
                    aux = data[i];
            }
        }

        return aux;
    }

    Sensor_data getMin(size_t t0, size_t tf){
        size_t i = t0;
        Sensor_data aux;

        while(data[i].isEmpty()) //check until finding a value that is valid
            i++;

        for(aux = data[i]; i < tf ; i++){
            if(!data[i].isEmpty()){
                if(aux > data[i])
                    aux = data[i];
            }
        }
    
        return aux;
    }

    Vector<Sensor_data> getData(){ return data ;}

    size_t getDataVol(size_t t0, size_t tf){return tf-t0;}

    size_t getSize(){return data.getSize();}

};

#endif
