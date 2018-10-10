#ifndef TREE__H
#define TREE__H
#include <iostream>
#include "vector.hpp"

typedef enum
{
	MIN,
	MAX,
	AVG
}MODE_T;

template <class T>
T avg(T a,T b){return (a+b)/2;}

using namespace std;

template <class T>
class SegmentTree
{
	private:
	Vector<T> v;
	size_t n;

	public:
	SegmentTree(const Vector<T>& arr, MODE_T mode);
	template <class U>
	friend ostream& operator<<(ostream&, const SegmentTree<U>&);
};

template <class T>
SegmentTree<T>::SegmentTree(const Vector<T>& arr, MODE_T mode)
{
	size_t k;
	for(k=0;k<arr.getSize();k++)
		v.append(0);
	for(k=0;k<arr.getSize();k++)
		v.append(arr[k]);
	//k = n
	if(mode == MIN){
	while(k>0){
		T a = 2*k-1;
		T b = 2*k-2;
		v[k-1]=min(v[a],v[b]);
		k--;
	}
	v.remove(0);
	}
	else if(mode == MAX){
	while(k>0){
		T a = 2*k-1;
		T b = 2*k-2;
		v[k-1]=max(v[a],v[b]);
		k--;
	}
	v.remove(0);
	}
	else if(mode == AVG){
	while(k>0){
		T a = 2*k-1;
		T b = 2*k-2;
		v[k-1]=avg(v[a],v[b]);
		k--;
	}
	v.remove(0);
	}
	else cout<<"ERROR"<<endl;
	cout<<v<<endl;
}

template <class U>
ostream& operator<<(ostream& os, const SegmentTree<U>& tree)
{
	size_t i;
	for(i=0;i<tree.v.getSize();i++)
		os<<tree.v[i];
	return os;
}

#endif

/*
int main()
{
	Vector<int> a;
	a.append(1);
	a.append(2);
	a.append(3);
	a.append(4);
	a.append(5);
	a.append(6);
	a.append(7);
	a.append(8);
	cout<<a<<endl;
	SegmentTree<int> s(a);
}
*/
