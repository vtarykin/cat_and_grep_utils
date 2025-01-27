#include "parser.h"

int parse_args(int argc, char **argv, char *short_options,
               struct option long_options[], flags_setup *f_setup, int *ind) {
  int res;
  int error = 0;
  int idx = 0;

  while ((res = getopt_long(argc, argv, short_options, long_options, &idx)) !=
         -1) {
    switch (res) {
      case 'b':
        f_setup->b = 1;
        break;
      case 'e':
        f_setup->e = 1;
        f_setup->v = 1;
        break;
      case 'E':
        f_setup->e = 1;
        break;
      case 'n':
        f_setup->n = 1;
        break;
      case 's':
        f_setup->s = 1;
        break;
      case 't':
        f_setup->t = 1;
        f_setup->v = 1;
        break;
      case 'T':
        f_setup->t = 1;
        break;
      case 'v':
        f_setup->v = 1;
        break;
      case '?':
        error = 1;
        break;
      default:
        error = 1;
        break;
    }
  }

  *ind = optind;

  if (f_setup->b == 1) {
    f_setup->n = 0;
  }

  return error;
}
