#ifndef UTILS__H
#define UTILS__H


double min(const double & x, const double & y){
	cout<< "hola" <<endl;
	if(x > y)
		return y;
	else
		return x;
}

double max(const double & x,const double & y){
	if(x < y)
		return y;
	else
		return x;
}

double sum(const double & x, const double & y){ return (x+y); }

#endif