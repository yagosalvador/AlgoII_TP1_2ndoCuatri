#ifndef SEGMENTTREE__H
#define SEGMENTTREE__H

#include <iostream>
#include <cmath>
#include "vector.hpp"
#include "utils.hpp"

typedef Sensor_data (* Mode_t)(const Sensor_data & x, const Sensor_data & y);


class Segment_tree{
  private:
	Vector<Sensor_data> tree;
	size_t orig_arr_size;
	Mode_t segment_mode;

  public:
  	Segment_tree(){
  		orig_arr_size = 0;
  		segment_mode = 0;
  	}

  	~Segment_tree(){};

  	Segment_tree(const Vector<Sensor_data> &arr){ //vol size set as default
  		size_t size = pow(2, ceil(log(arr.getSize())/log(2))); //nearest pow 2
  		orig_arr_size = size;
  		Sensor_data t;
  		double zero = 0;
  		segment_mode = sum;

  		for (size_t i = 0, j=0; i < (2*size-1); i++){ 
  				if(i >= size && i < (size + arr.getSize()) ){// sets half of the tree with empty data
                    if(!arr[j] && (double)arr[j] != zero){
                        t = 0;
                        tree.append(t);
                        j++;
                    }
                    else{
  						t = 1;
  						tree.append(t); //concatenates arr and resizes to 2^n-1
                        j++;
                    }
  				}
  				else{
  					t = 0;
  					tree.append(t);
  				}

  		}

  		fillTree(segment_mode);
	}

  	Segment_tree(const Vector<Sensor_data> &arr, Mode_t mode){
  		size_t size = pow(2, ceil(log(arr.getSize())/log(2))); //nearest pow 2
  		orig_arr_size = size;
  		Sensor_data t;
  		size_t i,j;

  		for (i = 0, j = 0; i < 2*size-1; i++){
  				if(i >= size && i < (size + arr.getSize()-1) ){
  					tree.append(arr[j]); //concatenates arr and resizes to 2^n-1
   					j++;
  				}
  				else
  					tree.append(t);// sets half of the tree with empty data
  		}
  		

  		fillTree(mode);
  		segment_mode = mode;
  	}

  	void fillTree(const Mode_t& mode){
  		int i;

  		for (i = tree.getSize()-1; ((i-2)/2) >= 0 ; i-=2){
  			tree[(i-2)/2] = (*mode)(tree[i-1], tree[i]);
        }
  	}

	Sensor_data getSegment(size_t t0, size_t tf){
		t0+=orig_arr_size+1;
		tf+=orig_arr_size+1;
		Sensor_data aux;
		size_t i = 0;

		while(t0 < tf)
		{
			if(t0%2==0){
				if(i == 0){
					aux = tree[t0];
                         i++;
				}
				else{
					aux = segment_mode(aux,tree[t0]);
					t0++;
				}
			}
			if(tf%2==0){
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

#endif