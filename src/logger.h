/**
 * @file logger.h
 * @brief реализация методы для логирования ошибок
 * @version 0.1
 * @date 2022-04-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef LOGGER_H
#define LOGGER_H

typedef unsigned int uint;
#include <assert.h>

enum class ERROR_CODE{

    OK,
    OWN,                    // недофолтная ошибка, которую юзер указывает сам
    ALLOC_MEM,
    CREATING_FILE,
    OPENING_FILE,
    EMPTY_INPUT_FILE,
    READ_BUFFER,
};

enum class CDUMP_OPTION{

    CONSOLE,
    FILE,
    BOTH    
};

struct log_location{

    const char*    file_name;
    const char*    func_name;
    uint           n_line;
};

enum LOG_TYPE{
    INFO,
    WARNING,
    ERROR
};

// TODO: replace to auxil file ??
#define ISNULL(obj) (obj == NULL)
#define CHECKALLOC(obj) if(obj == NULL) ESDLOG(ALLOC_MEM);
#define NASSERT(obj) assert(obj != NULL);

const uint UNRECOGNIZED_ERR_CODE = 0xDEADBEAF;

// for debugging errors
//struct derr{

//    ERROR_CODE num_of_val;
//    err_loc    location;
//};

const int  MAX_LOG_NAME_LEN  = 2 << 8;
const char LOG_LOCATION[32]  = "../logs/";  // TODO: make config for customise this option
const int  MAX_LOG_STR_LEN   = 2 << 10;

int  LogInit(/*CDUMP_OPTION mode*/ const char* path_to_clogs);
void LogClose();
void debug_log(log_location loc, LOG_TYPE type, const char* string, ...);
void debug_log_error(log_location loc, ERROR_CODE err_code, const char* string, ...);
void debug_log_error(log_location loc, ERROR_CODE err_code);
void debug_meta_log(log_location loc, const char* string, ...);

#define DLOG(type, string, ...)       debug_log({(__FILE__), (__FUNCTION__) , (__LINE__)}, (type), (string), ##__VA_ARGS__);
#define EDLOG(string, ...)            debug_log_error({(__FILE__), (__FUNCTION__) , (__LINE__)}, (ERROR_CODE::OWN), (string), ##__VA_ARGS__);
#define ESDLOG(err_code)              debug_log_error({(__FILE__), (__FUNCTION__) , (__LINE__)}, (err_code));
#define MDLOG(string, ...)            debug_meta_log({(__FILE__), (__FUNCTION__) , (__LINE__)}, (string), ##__VA_ARGS__);

#define PING DLOG(INFO, "meow")

#ifndef DLOG_MODE
#define DLOG_MODE 0 /**
					 * DLOG_MODE = CDUMP_OPTION::CONSOLE, - debug logging only to console
                     * DLOG_MODE = CDUMP_OPTION::FILE,    - debug logging only to file     
                     * DLOG_MODE = CDUMP_OPTION::BOTH,    - debug logging to file and console
					 */
#endif

#if DLOG_MODE == 0 || DLOG_MODE == 2
    #define DLOG_TO_CONSOLE_ENABLED 1
#else
    #define DLOG_TO_CONSOLE_ENABLED 0
#endif

#if DLOG_MODE == 1 || DLOG_MODE == 2
    #define DLOG_TO_FILE_ENABLED 1
#else
    #define DLOG_TO_FILE_ENABLED 0
#endif

#define TERM_RESET   	  "\033[0m"
#define ERROR_FONT        "\033[1;31m"
#define WARNING_FONT  	  "\033[1;33m"
#define INFO_FONT	      "\033[1;37m"
#define TERM_GREEN_FONT   "\033[1;32m"
#define INVALID_LOG_FONT  "\033[1;34m"

#define LOCATION       __LINE__, __FILE__, __FUNCTION__
#define DATE_OF_DEBUG  __DATE__, __TIME__

#define META_PARAMS char const * obj_name, int const n_line, char const * file_name, char const * func_name
#define LOC_PARAMS  int const n_line, char const * file_name, char const * func_name

#endif  // LOGGER_H
