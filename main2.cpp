#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cstdlib>

#include "sensor_data.hpp"
#include "errors.hpp"
#include "cmdline.hpp"
#include "component.hpp"
#include "vector.hpp"
#include "query_tree.hpp"
#include "sensors.hpp"


static void opt_input(string const &);
static void opt_output(string const &);
static void opt_data(string const &);
static void opt_help(string const &);



static std::fstream dfs;
static std::istream *iss = 0;
static std::fstream ifs;
static std::ostream *oss = 0;
static std::fstream ofs;

using namespace std;


// syntax: {needs argument,
//          short name,
//          long name,
//          default value,
//          parser,
//          flag}
static option_t options[] = {
    {1, "d", "data", "", opt_data, OPT_DEFAULT},
    {1, "i", "input", "-", opt_input, OPT_DEFAULT},
    {1, "o", "output", "-", opt_output, OPT_DEFAULT},
    {0, "h", "help", NULL, opt_help, OPT_DEFAULT},
    {0, },
};

static void opt_input(string const &arg) {
    if (arg == "-") {
        iss = &std::cin;
    } else {
        ifs.open(arg.c_str(), std::ios::in);
        iss = &ifs;
    }

    if (!iss->good()) {
        cerr << ERROR_MSG_CANT_OPEN_FILE
             << arg
             << "."
             << endl;
        exit(1);
    }
}

static void opt_output(string const &arg) {
    if (arg == "-") {
        oss = &std::cout;
    } else {
        ofs.open(arg.c_str(), std::ios::out);
        oss = &ofs;
    }

    if (!oss->good()) {
        cerr << ERROR_MSG_CANT_OPEN_FILE
             << arg
             << "."
             << endl;
        exit(1);
    }
}

static void opt_data(string const &arg) {
    if (arg != "") {
        dfs.open(arg.c_str(), std::ios::in);
    }
    else {
        cerr << ERROR_MSG_MANDATORY_OPT
             << "-d"
             << endl;
        exit(1);
    }

    if (!dfs.good()) {
        cerr << ERROR_MSG_CANT_OPEN_FILE
             << arg
             << "."
             << endl;
        exit(1);
    }
}

static void opt_help(string const &arg) {
    cout << HELP_MSG
         << endl;
    exit(0);
}


using namespace std;

int main(int argc, char * const argv[]) {
    cmdline cmdl(options);
    cmdl.parse(argc, argv);

    Sensores obj;
    Query q;

    dfs >> obj;

    while(*iss >> q)
        *oss << q.resolve(obj) << std::endl;
        
	return 0;
}
