#include "output.h"

void output(char **argv, int ind, int argc, const flags_setup *f_setup,
            int *error) {
  file_parameters cur_file_pars;
  cur_file_pars.line_counter = 1;

  for (; (ind < argc) && (*error == 0); ind++) {
    FILE *fp = fopen(argv[ind], "r");
    if (fp != NULL) {
      cur_file_pars.blank_line = 0;
      cur_file_pars.first_line_c = 0;
      cur_file_pars.prec_prev_sym = 0;
      cur_file_pars.prev_sym = 0;

      get_file_length(fp, &cur_file_pars);

      while (!feof(fp)) {
        cur_file_pars.cur_sym = fgetc(fp);
        process_and_print_symbol(fp, f_setup, &cur_file_pars);
        cur_file_pars.prec_prev_sym = cur_file_pars.prev_sym;
        cur_file_pars.prev_sym = cur_file_pars.cur_sym;
      }

      fclose(fp);
    } else {
      *error = 4;
    }
  }
}

void process_and_print_symbol(FILE *fpp, const flags_setup *f_setup,
                              file_parameters *cur_f_pars) {
  if (squeeze_lines(cur_f_pars, *f_setup, fpp) && cur_f_pars->cur_sym != -1) {
    if (f_setup->n || f_setup->b) {
      enumerate_lines(cur_f_pars, *f_setup, fpp);
    }

    if (f_setup->v || f_setup->t || f_setup->e) {
      handle_non_printables(&(cur_f_pars->cur_sym), *f_setup);
    }
    putchar(cur_f_pars->cur_sym);
  }
}

void get_file_length(FILE *fpp, file_parameters *cur_f_pars) {
  fseek(fpp, 0, SEEK_END);
  int cur_symb = fgetc(fpp);
  cur_f_pars->f_length = ftell(fpp);

  for (int i = 0; i < (cur_f_pars->f_length) && cur_symb != '\n'; i++) {
    cur_symb = fgetc(fpp);
    fseek(fpp, -i, SEEK_END);
    cur_f_pars->last_n_symb = i - 1;
  }

  cur_f_pars->last_n_symb = cur_f_pars->f_length - cur_f_pars->last_n_symb;

  fseek(fpp, 0, SEEK_SET);
}

void enumerate_lines(file_parameters *cur_f_pars, flags_setup f_setup,
                     FILE *fpp) {  // line_counter > 1
  if (f_setup.b) {
    (ftell(fpp) == 1) && (cur_f_pars->cur_sym == '\n')
        ? (cur_f_pars->first_line_c)++
        : cur_f_pars->first_line_c;
    if ((cur_f_pars->cur_sym != '\n') && (cur_f_pars->prev_sym != '\n') &&
        !(cur_f_pars->first_line_c)) {
      printf("%6d\t", cur_f_pars->line_counter++);
      ++cur_f_pars->first_line_c;
    } else if (cur_f_pars->cur_sym != '\n' && cur_f_pars->prev_sym == '\n' &&
               (ftell(fpp) <= cur_f_pars->f_length)) {
      printf("%6d\t", cur_f_pars->line_counter++);
    }
  }

  if (f_setup.n) {
    if (!(cur_f_pars->first_line_c)) {
      cur_f_pars->first_line_c++;
      printf("%6d\t", cur_f_pars->line_counter++);
    } else if (cur_f_pars->prev_sym == '\n' &&
               (ftell(fpp) <= cur_f_pars->f_length)) {
      printf("%6d\t", cur_f_pars->line_counter++);
    }
  }
}

int squeeze_lines(file_parameters *cur_f_pars, flags_setup f_setup, FILE *fpp) {
  int printable_symb = 1;
  int s = f_setup.s;
  int blank_start = (ftell(fpp) == 1) && (cur_f_pars->cur_sym == '\n');

  if ((cur_f_pars->blank_line == 1) && (cur_f_pars->cur_sym == '\n') && s) {
    printable_symb = 0;
  }

  if (s && blank_start && (cur_f_pars->cur_sym == '\n')) {
    cur_f_pars->blank_line = 1;
  }

  if (s && cur_f_pars->prev_sym == '\n' && cur_f_pars->cur_sym == '\n' &&
      cur_f_pars->blank_line == 0) {
    cur_f_pars->blank_line = 1;
  }

  if (cur_f_pars->prev_sym == '\n' && cur_f_pars->cur_sym != '\n') {
    cur_f_pars->blank_line = 0;
    printable_symb = 1;
  }

  return printable_symb;
}

void handle_non_printables(int *cur_s, flags_setup f_setup) {
  if (f_setup.v && (*cur_s != 9 && *cur_s != 10) &&
      (*cur_s > 126 || *cur_s < 32)) {
    if (*cur_s < 0) {
      putchar('M');
      putchar('-');
      // *cur_s += 128;
      *cur_s = (*cur_s) & 0x7F;
    } else if (*cur_s < 32) {
      putchar('^');
      *cur_s += 64;
    } else if (*cur_s == 127) {
      putchar('^');
      *cur_s = '?';
    } else if (*cur_s > 127) {
      putchar('M');
      putchar('-');
      *cur_s = '^';
    }
  }

  if (f_setup.t && *cur_s == '\t') {
    putchar('^');
    *cur_s = (int)('I');
  }

  if (f_setup.e && *cur_s == '\n') {
    putchar('$');
  }
}
