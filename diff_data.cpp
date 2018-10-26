#include <iostream>
#include <iomanip>  // for std::setprecision
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cfloat>
#include <string>

#include "cmdline.hpp"
#include "vector.hpp"
#include "errors.hpp"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::fstream;
using std::ios;
using std::stringstream;
using std::string;

static void opt_input1(string const &);
static void opt_input2(string const &);
static void opt_verbose(string const &);

// syntax: {needs argument,
//          short name,
//          long name,
//          default value,
//          parser,
//          flag}
static option_t options[] = {
    {1, "i1", "input1", "-", opt_input1, OPT_DEFAULT},
    {1, "i2", "input2", "-", opt_input2, OPT_DEFAULT},
    {0, "v", "verbose", NULL, opt_verbose, OPT_DEFAULT},
    {0, },
};

static std::istream *iss1 = 0;
static std::istream *iss2 = 0;
static fstream ifs1;
static fstream ifs2;
static bool verbose = false;


static void opt_input1(string const &arg) {
    if (arg == "-") {
        iss1 = &cin;
    } else {
        ifs1.open(arg.c_str(), ios::in);
        iss1 = &ifs1;
    }

    if (!iss1->good()) {
        cerr << ERROR_MSG_CANT_OPEN_FILE
             << arg
             << "."
             << endl;
        exit(1);
    }
}

static void opt_input2(string const &arg) {
    if (arg == "-") {
        iss2 = &cin;
    } else {
        ifs2.open(arg.c_str(), ios::in);
        iss2 = &ifs2;
    }

    if (!iss2->good()) {
        cerr << ERROR_MSG_CANT_OPEN_FILE
             << arg
             << "."
             << endl;
        exit(1);
    }
}

static void opt_verbose(string const &arg) {
    verbose = true;
}

int main(int argc, char * const argv[]) {
    cmdline cmdl(options);
    cmdl.parse(argc, argv);
    std::string str1,str2;
    Vector<double> v1, v2;
    double x, y, diff = 0, treshold = 0.1;
    stringstream ss1,ss2;

    while(getline(*iss1,str1) && getline(*iss2,str2)){
        if(str1 != str2){
            if(isalpha(str1[0]) && isalpha(str2[0])){}//if there is text in string
            if(isspace(str1[0]) && isspace(str2[0])){}//if there are spaces in string
            else { 
                ss1 << str1;
                ss2 << str2;
                while( (ss1 >> x) && (ss2 >> y) ){
                    ss1.get();
                    ss2.get();
                    v1.append(x);
                    v2.append(y);
                }
                for (size_t i = 0; i < v1.getSize(); i++)
                    diff += abs((v1[i]-v2[i]));
                if(diff/v1.getSize() > treshold){
                    cout << "In first file: " << str1 << endl;
                    exit(0);
                }
                ss1.clear();//in order to write again in ss
                ss2.clear();
            }
        }
    }
    cout<< "No Errors" <<endl;
    return 0;
}
