#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <string>
#include "class_tests.cpp"
#include "query.hpp"
#include "sensors.hpp"
#include "errors.hpp"

#define MAX_FILES 4
static std::fstream ifs,ifs2,ifs3;
static std::fstream ofs1,ofs2;
std::string queryfiles[MAX_FILES] ={"Query1_soloNombres.csv","Query2_archivoDataVacio.csv","Query3_archivoDataVacio.csv","Query4_archivoDataVacio.csv"};
std::string datafiles[MAX_FILES]={"Data1_soloNombres.csv","Data2_archivoDataVacio.csv","Data3_archivoDataVacio.csv","Data4_archivoDataVacio.csv"};
std::string resultfiles[MAX_FILES]={"Result1_soloNombres","Result2_archivoDataVacio.csv","Result3_soloNombres","Result4_soloNombres"}, outputftiles = "Salida.txt";

namespace {
		TEST(Query,Files){
		for(size_t i=0 ; i < MAX_FILES ;i++){
			ifs.open(queryfiles[i].c_str());
			ifs2.open(datafiles[i].c_str());
			ifs3.open(resultfiles[i].c_str());	
			ofs1.open(outputftiles.c_str(),std::ios::out);
			Query q;
			Sensores sen;
			std::string str,str2;

			ifs2 >> sen;
			while(ifs >> q)
				ofs1 << q.resolve(sen) << endl;

			while(!ifs3.eof() && !ofs1.eof()){
				getline(ifs3,str);
				getline(ofs1,str2);
				EXPECT_EQ(str2,str);
			}
		}
	}

	TEST(Main,OutputFile){
		ofs1.open("hola.txt");
		ofs2.open("hola.txt");
		EXPECT_EQ(!ofs2.good(),1);
	}

}

GTEST_API_ int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}