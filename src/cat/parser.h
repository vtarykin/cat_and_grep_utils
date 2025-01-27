#ifndef CAT_PARSER_H_
#define CAT_PARSER_H_
#define _GNU_SOURCE

#include <getopt.h>
#include <stdlib.h>
#include <string.h>

#define CAT
#include "../common/flags.h"

int parse_args(int argc, char **argv, char *short_options,
               struct option long_options[], flags_setup *f_setup, int *ind);

#endif
