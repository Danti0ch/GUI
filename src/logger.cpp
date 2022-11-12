#include "logger.h"
#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

static FILE* dlog_file       = NULL;

//========================================================================================//

//                          LOCAL_FUNCTIONS_DECLARATION

//========================================================================================//

void get_log_name(char* str);
int dlog_init();
void dlog_close();

//========================================================================================//

//                          PUBLIC_FUNCTIONS_DEFINITION

//========================================================================================//

int LogInit(/*CDUMP_OPTION mode*/ const char* path_to_clogs){

    assert(path_to_clogs != NULL);

    int dlog_init_ret_code = dlog_init();

    if(dlog_init_ret_code == 1){
        return 1;
    }

	return 0; 
}
//----------------------------------------------------------------------------------------//

void LogClose(){

	dlog_close();
	
    return;
}
//----------------------------------------------------------------------------------------//

// больше выделения для ошибок и ворнингов в файле???
void debug_log(log_location loc, LOG_TYPE type, const char* string, ...){

    assert(string != NULL);
    
    time_t rawtime = time(NULL);
    struct tm *ptm = localtime(&rawtime);

    char time_str[20] = "";
    strftime(time_str, 16, "%H:%M:%S", ptm);

	va_list args;
	va_start(args, string);

    #if DLOG_TO_FILE_ENABLED
    switch(type){
        case INFO:{
            fprintf(dlog_file, "\n[INFO] %s--%s--%s<%u>:: \n\t",
                time_str, loc.file_name, loc.func_name, loc.n_line);
            break;
        }
        case WARNING:{
            fprintf(dlog_file, "\n[WARNING] <%s>--%s--%s<%u>:: \n\t",
                time_str, loc.file_name, loc.func_name, loc.n_line);
            break;
        }
        default:{
            fprintf(dlog_file, "\n[UNDEFINIED] %s--%s--%s<%u>:: \n\t",
                time_str, loc.file_name, loc.func_name, loc.n_line);
            break;
        }
    }
    
    vfprintf(dlog_file, string, args);
	fprintf(dlog_file, "\n");
	
    #endif  //DLOG_TO_FILE_ENABLED

    #if DLOG_TO_CONSOLE_ENABLED

    switch(type){
        case INFO:{
            printf("\n%s[INFO] %s--%s--%s<%u>:: \n\t",
                INFO_FONT, time_str, loc.file_name, loc.func_name, loc.n_line);
            break;
        }
        case WARNING:{
            printf("\n%s[WARNING] %s--%s--%s<%u>:: \n\t",
                WARNING_FONT, time_str, loc.file_name, loc.func_name, loc.n_line);
            break;
        }
        default:{
            printf("\n%s[UNDEFINIED] %s--%s--%s<%u>:: \n\t",
                INVALID_LOG_FONT, time_str, loc.file_name, loc.func_name, loc.n_line);
            break;
        }
    }
    
    vprintf(string, args);
	printf("%s\n", TERM_RESET);

    #endif  // DLOG_TO_CONSOLE_ENABLED

	va_end(args);

    return;
}
//----------------------------------------------------------------------------------------//

void debug_log_error(log_location loc, ERROR_CODE err_code, const char* string, ...){

    assert(string != NULL);
    
    time_t rawtime = time(NULL);
    struct tm *ptm = localtime(&rawtime);

    char time_str[20] = "";
    strftime(time_str, 16, "%H:%M:%S", ptm);

	va_list args;
	va_start(args, string);

    #if DLOG_TO_FILE_ENABLED

    fprintf(dlog_file, "\n[ERROR] %s--%s--%s<%u>:: \n\t",
        time_str, loc.file_name, loc.func_name, loc.n_line);

    vfprintf(dlog_file, string, args);
	fprintf(dlog_file, "\n");
	
    #endif  //DLOG_TO_FILE_ENABLED

    #if DLOG_TO_CONSOLE_ENABLED

    printf("\n%s[ERROR] %s--%s--%s<%u>:: \n\t",
        ERROR_FONT, time_str, loc.file_name, loc.func_name, loc.n_line);

    vprintf(string, args);
	printf("%s\n", TERM_RESET);

    #endif  // DLOG_TO_CONSOLE_ENABLED

	va_end(args);

    LogClose();
    exit((int)err_code);
    
    return;
}
//----------------------------------------------------------------------------------------//

void debug_log_error(log_location loc, ERROR_CODE err_code){
    
    time_t rawtime = time(NULL);
    struct tm *ptm = localtime(&rawtime);

    char time_str[20] = "";
    strftime(time_str, 16, "%H:%M:%S", ptm);

    #if DLOG_TO_FILE_ENABLED

    fprintf(dlog_file, "[ERROR] %s--%s--%s<%u>:: %u\n",
        time_str, loc.file_name, loc.func_name, loc.n_line, (uint)err_code);

    #endif  //DLOG_TO_FILE_ENABLED

    #if DLOG_TO_CONSOLE_ENABLED

    printf("%s[ERROR] %s--%s--%s<%u>:: %u\n",
        ERROR_FONT, time_str, loc.file_name, loc.func_name, loc.n_line, (uint)err_code);
	printf("%s\n\n", TERM_RESET);

    #endif  // DLOG_TO_CONSOLE_ENABLED

    LogClose();
    
    return;
}
//----------------------------------------------------------------------------------------//

void debug_meta_log(log_location loc, const char* string, ...){

    assert(string != NULL);
    
	va_list args;
	va_start(args, string);

    #if DLOG_TO_FILE_ENABLED
    
    vfprintf(dlog_file, string, args);
	fprintf(dlog_file, "\n");
	
    #endif  //DLOG_TO_FILE_ENABLED

    #if DLOG_TO_CONSOLE_ENABLED
    
    vprintf(string, args);
	printf("%s\n", TERM_RESET);

    #endif  // DLOG_TO_CONSOLE_ENABLED

	va_end(args);

    return;
}
//----------------------------------------------------------------------------------------//

//========================================================================================//

//                          LOCAL_FUNCTIONS_DEFINITION

//========================================================================================//

void get_log_name(char* buf, const char* log_location){

    assert(buf != NULL);

	strcpy(buf, log_location);

    time_t rawtime = time(NULL);
    struct tm *ptm = localtime(&rawtime);

    strftime(buf + strlen(buf), MAX_LOG_NAME_LEN, "%H-%M-%S(%d.%m.%Y)", ptm);

    return;
}
//----------------------------------------------------------------------------------------//

int dlog_init(){

    #if DLOG_TO_FILE_ENABLED
    
    char name[MAX_LOG_NAME_LEN] = "";
    get_log_name(name, LOG_LOCATION);
    dlog_file = fopen(name, "w");

    if(dlog_file == NULL){
        printf("Unable to create log file on way: %s%s\n", LOG_LOCATION, name);
        return 1;
    }
    #endif //DLOG_TO_FILE_ENABLED

    DLOG(INFO, "Logging initiated");

    return 0;
}
//----------------------------------------------------------------------------------------//

void dlog_close(){

    DLOG(INFO, "Logging closed");

    #if DLOG_TO_FILE_ENABLED
    fclose(dlog_file);
    #endif  // DLOG_TO_FILE_ENABLED

    return;
}
//----------------------------------------------------------------------------------------//
