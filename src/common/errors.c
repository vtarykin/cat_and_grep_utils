#include "../common/errors.h"

void error_dispatcher(int error_number) {
  if (error_number > 4) {
    output_error_reg();
  } else if (error_number > 2) {
    output_error_mem_dir(error_number);
  } else {
    output_error_incorrect_flags(error_number);
  }
}

void output_error_incorrect_flags(int error_number) {
  if (error_number == 1) {
    printf(
        "Current utility does not support the one or a couple of options you "
        "have provided. "
        "Please make sure that each of your options correspond to any of the "
        "following: "
        "-b or --number-nonblank, -e, -n or --number, -s or --squeeze-blank, "
        "-t, -v\n");
  } else if (error_number == 2) {
    printf(
        "Current utility does not support the one or a couple of options you "
        "have provided. "
        "Please make sure that each of your options correspond to any of the "
        "following: "
        "-e or regexp, -i or --ignore-case, -v or --invert-match, -c or "
        "--count,"
        " -l or --files-with-matches, -n or --line-number, -h or no-filename,"
        " -s or --no-messages, -f or --file, -o or --only-matching.");
  }
}

void output_error_mem_dir(int error_number) {
  if (error_number == 3) {
    printf("Memory allocation failed.\n");
  } else if (error_number == 4) {
    printf(
        "A file or a directory you have prodided does not exist. Please "
        "provide ");
    printf("an existing file or a directory.\n");
  }
}

void output_error_reg() { printf("Regcomp() failed, returning nonzero.\n"); }
