
#include <iostream>
#include "Tree.hpp"
#include "vector.hpp"
using namespace std;
int main()
{
	Vector<int> a;
	a.append(1);
	a.append(2);
	a.append(3);
	a.append(4);
	a.append(5);
	a.append(6);
	SegmentTree<int> s(a,MIN);
}
