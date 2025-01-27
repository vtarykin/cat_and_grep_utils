#ifndef PARSER_H
#define PARSER_H

#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#define GREP
#include "../common/flags.h"

int parse_args(int argc, char **argv, char *short_options,
               struct option long_options[], flags_setup *f_setup, int *ind);

#endif
