#ifndef OUTPUT_GREP_H
#define OUTPUT_GREP_H

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/errors.h"
#define GREP
#include "../common/flags.h"

typedef long int l_int;
typedef struct {
  int files_count;
  char *f_name;
} file_comp;

void output_grep(char **argv, int *index, int argc, flags_setup *f_setup,
                 int *error);
void get_next_symb(l_int *next_f_symb, FILE *fpp);
void get_str(FILE *fpp, l_int *str_st, l_int *str_len, char *cur_str);
void get_lines(FILE *fpp, int *error, flags_setup *f_setup, file_comp *f_comp);
void get_str_len(l_int *str_length, l_int *f_length, l_int *str_start,
                 FILE *fpp);
l_int get_length(FILE *fpp);
void show_match_count(flags_setup *f_setup, file_comp *f_comp,
                      int match_counter);
void process_line_enum(int *l_n, flags_setup *f_setup);
void process_match_count(int *match_c, flags_setup *f_setup, int *match_res);
void process_line_output(int *line_number, flags_setup *f_setup, int *match_res,
                         char *cur_str, file_comp *f_comp);
void add_or_ignore_filename(flags_setup *f_setup, file_comp *f_comp);
#endif
