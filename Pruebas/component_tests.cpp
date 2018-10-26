#include <gtest/gtest.h>
#include "component.hpp"
#include <string>
#include "vector.hpp"
#include "sensor_data.hpp"

namespace {
	TEST(Component, Constructor){
		Component a;
		EXPECT_EQ(a.showId(),"");
		EXPECT_EQ(a.getSize(),0);
	}

	TEST(Component, Copy_Constructor){
		std::string str = "Sensor1";
		Component a(str),b;
		double x=20;

		for (size_t i=0; i < 30; i++)
			a.append(x+i);

		b = a;
		EXPECT_EQ(a.getSize(),b.getSize() );
		EXPECT_EQ(a.showId(),b.showId() );

		for (size_t i=0; i < 30; i++ )
			EXPECT_EQ(a[i],b[i]);
	}

	TEST(Component,Constructor_String){
		std::string str = "Sensor";
		Component a(str);
		EXPECT_EQ(a.showId(),str);

	}

	TEST(Component,Constructor_Str_Arr){
		std::string str = "Sensor";
		Vector<Sensor_data> arr1;
		double x = 10;

		for (size_t i=0; i < 30; i++ ){
				arr1.append(x+i);
		}
		Component a(str,arr1);
		EXPECT_EQ(a.showId(),str);
		EXPECT_EQ(a.getSize(),arr1.getSize());
		for (size_t i = 0; i < arr1.getSize();i++)
			EXPECT_EQ(a[i],arr1[i]);
	}

	TEST(Component,SetId){
		std::string str = "Sensor";
		Component a;

		a.setId(str);
		EXPECT_EQ(a.showId(),str);
	}

	TEST(Component,Append){
		Component a("Sensor");
		double x;
		size_t old_size = a.getSize();

		a.append(x);
		EXPECT_EQ(a[a.getSize()-1],x);
		EXPECT_GT(a.getSize(),old_size);
	}

	TEST(Component,GetMax){
		Component a("Sensor");
		Sensor_data x;
		size_t t0,tf;

		tf = (rand() % 10) * (rand() % 10);

		for (size_t i=0; i < tf; i++ ){
			x = rand();
			a.append(x);
		}


		x = a.getMax(0, a.getSize());
		for(size_t i = 0; i < a.getSize(); i++){
			EXPECT_GE(x,a[i]);
		}
	}

	TEST(Component,GetMin){
		Component a("Sensor");
		Sensor_data x;
		size_t tf;

		tf = (rand() % 10) * (rand() % 10);

		for (size_t i=0; i < tf; i++ ){
			x = rand();
			a.append(x);
		}


		x = a.getMin(0, a.getSize());
		for(size_t i = 0; i < a.getSize(); i++){
			EXPECT_LE(x,a[i]);
		}
	}

	TEST(Component,GetAvg){
		Component a("Sensor");
		Sensor_data x,result;
		size_t tf,i;

		tf = (rand() % 10) * (rand() % 10);

		for (size_t i=0; i < tf; i++ ){
			x = rand();
			a.append(x);
		}


		x = a.getAvg(0, a.getSize());
		for(i = 0; i < a.getSize(); i++)
			result = result + a[i];
		EXPECT_EQ(result,x);
	}

}
