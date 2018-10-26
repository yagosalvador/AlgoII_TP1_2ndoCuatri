#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cfloat>
#include <string>

#include <ctime>  // for timing purposes
#include <vector>
#include <complex>

#include "cmdline.hpp"
#include "utils.hpp"
#include "component.hpp"
#include "vector.hpp"
#include "sensor_data.hpp"
#include "errors.hpp"
#include "segment_tree.hpp"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::fstream;
using std::ios;
using std::istringstream;
using std::string;

// syntax: {needs argument,
//          short name,
//          long name,
//          default value,
//          parser,
//          flag}
static option_t options[] = {
    {0, },
};

static ostream *Arbol_oss = 0;
static fstream Arbol_ofs;
static ostream *Orig_oss = 0;
static fstream Orig_ofs;
static const char *Orig_filename = "datosOrig.txt";
static const char *Arbol_filename = "datosArbol.txt";


int main(int argc, char * const argv[]) {
    cmdline cmdl(options);
    cmdl.parse(argc, argv);
    Component sensor1;
    Vector<Sensor_data> v;

    Arbol_ofs.open(Arbol_filename, ios::out);
    Arbol_oss = &Arbol_ofs;
    if (!Arbol_oss->good()) {
        cerr << ERROR_MSG_CANT_OPEN_FILE
             << Arbol_filename
             << "."
             << endl;
        exit(1);
    }
    Orig_ofs.open(Orig_filename, ios::out);
    Orig_oss = &Orig_ofs;
    if (!Orig_oss->good()) {
        cerr << ERROR_MSG_CANT_OPEN_FILE
             << Orig_filename
             << "."
             << endl;
        exit(1);
    }

    int max_size = 1000;
    float division_constant = 7;
    for (size_t i = 1; i < 8388608; i *= 2) {
        for (size_t j = 0, r = 1; j < i; j++) {
            srand((j+i+r)*(j+i+r));
            r = rand();
            srand((j+i-r)*(j+i-r));
            sensor1.append((r%max_size)/division_constant);
        }
        clock_t begin = clock();
        cout<< sensor1.getSize()-1 <<endl;
        sensor1.getMax(0,sensor1.getSize()-1);
        clock_t end = clock();
        double elapsed_secs = double(end - begin)/CLOCKS_PER_SEC;
        *Orig_oss << i << " " << elapsed_secs << std::endl;

        Segment_tree tree(sensor1.getData(), max );
        begin = clock();
        tree.getSegment(0,sensor1.getSize()-1);
        end = clock();
        elapsed_secs = double(end - begin)/CLOCKS_PER_SEC;
        *Arbol_oss << i << " " << elapsed_secs << std::endl;
    }

    return 0;
}
