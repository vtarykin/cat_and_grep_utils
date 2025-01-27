#include "parser_grep.h"

int parse_args(int argc, char **argv, char *short_options,
               struct option long_options[], flags_setup *f_setup, int *ind) {
  int res;
  int error = 0;
  int idx = 0;

  while ((res = getopt_long(argc, argv, short_options, long_options, &idx)) !=
         -1) {
    switch (res) {
      case 'e':
        f_setup->e = 1;
        f_setup->pattern = optarg;
        break;
      case 'i':
        f_setup->i = 1;
        break;
      case 'n':
        f_setup->n = 1;
        break;
      case 'c':
        f_setup->c = 1;
        break;
      case 'l':
        f_setup->l = 1;
        break;
      case 'h':
        f_setup->h = 1;
        break;
      case 's':
        f_setup->s = 1;
        break;
      case 'v':
        f_setup->v = 1;
        break;
      case 'o':
        f_setup->o = 1;
        break;
      case 'f':
        f_setup->f = 1;
        break;
      case '?':
        error = 2;
        break;
      default:
        error = 2;
        break;
    }
  }

  *ind = optind;
  if (f_setup->pattern == NULL) {
    f_setup->pattern = argv[optind];
    (*ind)++;
  }

  return error;
}
