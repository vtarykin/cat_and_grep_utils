#include "../common/errors.h"
#include "output.h"
#include "parser.h"

int main(int argc, char **argv) {
  flags_setup flag_setup = {0};
  flags_setup *f_setup = &flag_setup;
  int index = 0;
  char *short_options = "+beEnstTv";
  struct option long_options[] = {{"number-nonblank", no_argument, NULL, 'b'},
                                  {"number", no_argument, NULL, 'n'},
                                  {"squeeze-blank", no_argument, NULL, 's'}};

  int error =
      parse_args(argc, argv, short_options, long_options, f_setup, &index);

  output(argv, index, argc, f_setup, &error);

  if (error) {
    error_dispatcher(error);
  }

  return 0;
}
