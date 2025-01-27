#ifndef SRC_COMMON_ERRORS_H_
#define SRC_COMMON_ERRORS_H_

#include <stdio.h>

// here I would like to place functions for error processing
void error_dispatcher(int error_number);
void output_error_incorrect_flags(int error_number);
void output_error_mem_dir(int error_number);
void output_error_reg();
#endif
