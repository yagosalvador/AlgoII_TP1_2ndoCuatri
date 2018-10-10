#include <iostream>
#include "vector.hpp"

using namespace std;

template <class T>
class SegmentTree
{
	private:
	Vector<T> v;
	size_t n;

	public:
	SegmentTree(const Vector<T>& arr);
};

template <class T>
SegmentTree<T>::SegmentTree(const Vector<T>& arr)
{
	size_t k;
	v.setSize(2*arr.getSize());
	for(k=0;k<arr.getSize();k++){
		v[arr.getSize()+k]=arr[k];
	}
	//k = n
	while(k>0){
		T a = 2*k-1;
		T b = 2*k-2;
		v[k-1]=min(v[a],v[b]);
		k--;
	}
	v.remove(0);
	cout<<v<<endl;
}
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
