#include <gtest/gtest.h>
#include "vector.hpp"
#include "component_tests.cpp"
#include "query_tests.cpp"

namespace {
		TEST(Vector,Constructor){
			Vector<double> arr;
			EXPECT_EQ(0,arr.getSize());

		}

		TEST(Vector,CopyConstructor){
			Vector<double> arr1;
			double x = 1;
			arr1.append(x);
			arr1.append(x);

			Vector<double> arr2(arr1);
			EXPECT_EQ(arr1,arr2);
		}

		TEST(Vector, Append){
    		Vector<double> arr;
    		double y = 10;
    		EXPECT_EQ(0,arr.getSize());

    		arr.append(y);
    		EXPECT_GT(arr.getSize(),0);
    		EXPECT_EQ(y,arr[arr.getSize()-1]);
		}

		TEST(Vector, Asign){
			Vector<double> arr1,arr2;
			double x;

			for (size_t i=0; i < 30; i++ ){
				arr1.append(x+i);
			}
			arr2 = arr1;
			EXPECT_EQ(arr1.getSize(),arr2.getSize());
			for (size_t i = 0; i < arr1.getSize();i++)
				EXPECT_EQ(arr1[i],arr2[i]);
		}

		TEST(Vector, OperatorPlus){
			Vector<double> arr1,arr2,result;
			double x=2,y=3;

			arr1.append(x);
			arr2.append(y);

			result = arr1 + arr2;
			for(size_t i=0; i < result.getSize(); i++){
				if (i < arr1.getSize())
					EXPECT_EQ(x,result[arr1.getSize()-1]);
				else
					EXPECT_EQ(y,result[arr1.getSize()+arr2.getSize()-1]);
			}
		}

		TEST(Vector,Remove){
			Vector<double> arr;
			double x;
			size_t old_size;

			for (size_t i=0; i < 30; i++ ){
				arr.append(x+i);
			}
			x = arr[25];
			arr.remove(25);
			EXPECT_GT(arr.getSize()-1,old_size);
			EXPECT_NE(arr[25],x);

		}

		TEST(Vector,Empty){
			Vector<double> arr;
			double x = 20;

			arr.append(x);

			arr.empty();
			EXPECT_EQ(arr.getSize(),0);
		}

		
}
