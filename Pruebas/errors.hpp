#ifndef ERRORS_HPP__
#define ERRORS_HPP__

#define ERROR_MSG_CANT_OPEN_FILE    "While opening stream: "
#define ERROR_MSG_UNKNOWN_METHOD    "Unknown method."
#define ERROR_MSG_CORRUPTED_DATA    "Input data was corrupt."
#define ERROR_MSG_INVALID_ARG       "Invalid non-option argument: "
#define ERROR_MSG_OPT_REQ_ARG       "Option requires argument: "
#define ERROR_MSG_UNKNOWN_OPT       "Unknown option: "
#define ERROR_MSG_MANDATORY_OPT     "Option is mandatory."
#define HELP_MSG                    "cmdline [-d data] [-i file] [-o file]"
#define ERROR_DATABASE				"Error Database"
#define STATUS_SIZE 5

std::string status_dict[STATUS_SIZE] = {
    "OK",
    "UNKNOWN ID",
    "BAD QUERY",
    "NO DATA",
    ""
};

#endif