#ifndef COMPONENTS__H
#define COMPONENTS__H

#include <iostream>
#include <string>

#include "vector.hpp"

class Component{
  private:
    std::string id;
    Vector<double> data;

  public:
    Component(){
        id = "";
    };

    ~Component(){};

    Component(const Component& c){
        id = c.id;
        data = c.data;
    }

    Component(std::string str, Vector<double> d){
        id = str;
        data = d;
    }

    void setId(std::string str){
        id = str;
    }

    std::string showId() const{return id;}

    void append(double x){
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

        for(i = t0, j = 0; i < tf ; j++, i++)
            sum += data[i];
            
        return sum/j; 
    }

    double getMax(size_t t0, size_t tf){
        size_t i;
        double aux = 0;

        for(i = t0, aux = data[i]; i < tf ;i++){
            if(aux < data[i])
                aux = data[i];
        }

        return aux;
    }

    double getMin(size_t t0, size_t tf){
        size_t i;
        double aux = 0;

        for(i = t0, aux = data[i]; i < tf ; i++){
            if(aux > data[i])
            aux = data[i];
        }

        return aux;
    }

    size_t getDataVol(size_t t0, size_t tf){return tf-t0;}

    size_t getSize(){return data.getSize();}

};

#endif
