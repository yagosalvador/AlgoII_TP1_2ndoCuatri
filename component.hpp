#ifndef COMPONENTS__H
#define COMPONENTS__H

#include <iostream>
#include <string>

#include "vector.hpp"
#include "Tree.hpp"

class Component{
  private:
    std::string id;
    Vector<double> data;
    SegmentTree<double>* minTree;
    SegmentTree<double>* maxTree;
    SegmentTree<double>* avgTree;

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
	t0+=data.getSize();
	tf+=data.getSize();
	double aux = 1e20;
	while(t0<tf)
	{
		cout<<"t0 = "<<t0<<"tf = "<<tf<<endl;
		if(t0%2!=0){
			aux = min(aux,minTree->getData(t0));
			t0++;
		}
		if(tf%2!=0){
			tf--;
			aux = min(aux,minTree->getData(tf));
		}
		t0/=2;
		tf/=2;
	}
	cout<<"devuelvo min: "<<aux<<endl;
	return aux;
    }

    size_t getDataVol(size_t t0, size_t tf){return tf-t0;}

    size_t getSize(){return data.getSize();}

    void buildTree()
    {
        minTree = new SegmentTree<double>(data,MIN);
        maxTree = new SegmentTree<double>(data,MAX);
        avgTree = new SegmentTree<double>(data,AVG);
	//cout<<*minTree<<endl;
//	cout<<*maxTree<<endl;
//	cout<<*avgTree<<endl;
    }

};

#endif
