#ifndef CAT_OUTPUT_H_
#define CAT_OUTPUT_H_

#include <stdio.h>

#define _GNU_SOURCE_
#define CAT
#include "../common/flags.h"

typedef struct {
  int line_counter;
  int blank_line;
  int first_line_c;
  long int f_length;
  long int last_n_symb;
  int prec_prev_sym;
  int prev_sym;
  int cur_sym;

} file_parameters;

void output(char **argv, int ind, int argc, const flags_setup *f_setup,
            int *error);
void process_and_print_symbol(FILE *fpp, const flags_setup *f_setup,
                              file_parameters *cur_f_pars);
void get_file_length(FILE *fpp, file_parameters *cur_f_pars);
void enumerate_lines(file_parameters *cur_f_pars, flags_setup f_setup,
                     FILE *fpp);
int squeeze_lines(file_parameters *cur_f_pars, flags_setup f_setup, FILE *fpp);
void handle_non_printables(int *cur_s, flags_setup f_setup);

#endif
