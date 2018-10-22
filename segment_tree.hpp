#ifndef SEGMENTTREE__H
#define SEGMENTTREE__H

#include <iostream>
#include <cmath>
#include "vector.hpp"

typedef double (* Mode_t)(const double & x, const double & y);


template <typename T>
class Segment_tree{
  private:
	Vector<T> tree;
	size_t orig_arr_size;
	Mode_t segment_mode;

  public:
  	Segment_tree(){
  		orig_arr_size = 0;
  		segment_mode = 0;
  	};

  	~Segment_tree(){};

  	Segment_tree(const Vector<T> &arr){ //vol size set as default
  		size_t size = pow(2, ceil(log(arr.getSize())/log(2))); //nearest pow 2
  		orig_arr_size = size;


  		for (size_t i = 0; i < (2*size); i++){
  				tree.append(0);// sets half of the tree with empty data
  				if(i >= (2*size-1) - arr.getSize()){
  					if(arr[i].isEmpty())
  						tree.append(0);
  					else
  						tree.append(1); //concatenates arr and resizes to 2^n-1
  				}
  		}

  		for (size_t i = tree.getSize()-1; i > 0 ; i-=2) 
  			tree[(i-2)/2] = tree[i] + tree[i-1];
	}

  	Segment_tree(const Vector<T> &arr, Mode_t mode){
  		size_t size = pow(2, ceil(log(arr.getSize())/log(2))); //nearest pow 2
  		orig_arr_size = size;


  		for (size_t i = 0; i < (2*size-1) - arr.getSize(); i++)
  				tree.append(0);// sets half of the tree with empty data
  		tree += arr; //concatenates arr and resizes to 2^n-1

  		fillTree(mode);
  		segment_mode = mode;
  	}

  	void fillTree(const Mode_t& mode){
  		for (size_t i = tree.getSize()-1; i > 0 ; i-=2) 
  			tree[(i-2)/2] = (*mode)(tree[i], tree[i-1]);
  	}

	T getSegment(size_t t0, size_t tf){
		t0+=orig_arr_size-1;
		tf+=orig_arr_size-1;
		T aux;
		size_t i = 0;

		while(t0 < tf)
		{
			if(t0%2!=0){
				if(i == 0){
					aux = tree[t0];
					i++;
				}
				else{
					aux = segment_mode(aux,tree[t0]);
					t0++;
				}
			}
			if(tf%2!=0){
				if(i == 0){
					aux = tree[tf];
					i++;
				}
				else{	
					tf--;
					aux = segment_mode(aux,tree[tf]);
				}
			}
			t0/=2;
			tf/=2;
		}
		return aux;
	}

  	size_t getSize(){ return tree.getSize(); }

  	size_t getOrigSize(){ return orig_arr_size; } //tecnically it returns nearest pow2 of n

  	friend ostream& operator<<(ostream& os, const Segment_tree& t) {
        os << t.tree;
        return os;
    }

};