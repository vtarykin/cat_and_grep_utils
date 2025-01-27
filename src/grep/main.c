#include "output_grep.h"
#include "parser_grep.h"

int main(int argc, char **argv) {
  flags_setup flag_setup = {0};
  flags_setup *f_setup = &flag_setup;
  int index = 0;
  char *short_options = "+eivclnhsfo";
  struct option long_options[] = {
      {"regexp", no_argument, NULL, 'e'},
      {"ignore-case", no_argument, NULL, 'i'},
      {"invert-match", no_argument, NULL, 'v'},
      {"count", no_argument, NULL, 'c'},
      {"files-with-matches", no_argument, NULL, 'l'},
      {"no-filename", no_argument, NULL, 'h'},
      {"line-number", no_argument, NULL, 'n'},
      {"no-messages", no_argument, NULL, 's'},
      {"file", no_argument, NULL, 'f'},
      {"only-matching", no_argument, NULL, 'o'}};

  int error =
      parse_args(argc, argv, short_options, long_options, f_setup, &index);

  output_grep(argv, &index, argc, f_setup, &error);

  if (error && !(f_setup->s)) {
    error_dispatcher(error);
  }

  return 0;
}
