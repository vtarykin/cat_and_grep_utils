// this is stable and smooth version of get_lines() time: 03.12.2024 14:37

#include "output_grep.h"

void output_grep(char **argv, int *index, int argc, flags_setup *f_setup,
                 int *error) {
  file_comp f_comp = {0};
  f_comp.files_count = argc - *index;
  // printf("/n%d %d/n", argc, *index);
  for (; *index < argc; (*index)++) {
    FILE *fp = fopen(argv[*index], "r");

    if (fp != NULL) {
      f_comp.f_name = argv[*index];
      get_lines(fp, error, f_setup, &f_comp);
      fclose(fp);
    } else {
      *error = 2;
    }
  }
}

void get_lines(FILE *fpp, int *error, flags_setup *f_setup, file_comp *f_comp) {
  l_int f_length = get_length(fpp);
  l_int str_length = 0;
  l_int next_f_symb = 0;
  int line_number = 0;
  int match_counter = 0;
  // l_int str_start;
  regex_t reg;
  *error = f_setup->i ? regcomp(&reg, f_setup->pattern, REG_ICASE)
                      : regcomp(&reg, f_setup->pattern, 0);
  *error = *error != 0 ? 5 : *error;
  for (; (next_f_symb != EOF) && (*error == 0);) {
    l_int str_start = ftell(fpp);
    line_number++;

    get_str_len(&str_length, &f_length, &str_start, fpp);

    char *cur_str = calloc((str_length + 2), sizeof(char));
    if (cur_str == NULL) {
      *error = 3;
    } else {
      get_str(fpp, &str_start, &str_length, cur_str);
      int match_res = (regexec(&reg, cur_str, 0, NULL, 0));
      //*error = match_res ? 6 : *error;
      process_line_output(&line_number, f_setup, &match_res, cur_str, f_comp);

      process_match_count(&match_counter, f_setup, &match_res);

      if (cur_str != NULL) {
        free(cur_str);
      }
    }

    get_next_symb(&next_f_symb, fpp);
  }

  show_match_count(f_setup, f_comp, match_counter);
  f_setup->l && (match_counter > 0) ? printf("%s\n", f_comp->f_name)
                                    : line_number;

  regfree(&reg);
}

void add_or_ignore_filename(flags_setup *f_setup, file_comp *f_comp) {
  if ((f_comp->files_count > 1) && !(f_setup->h)) {
    printf("%s:", f_comp->f_name);
  }
}

void show_match_count(flags_setup *f_setup, file_comp *f_comp,
                      int match_counter) {
  if (f_setup->c && !(f_setup->l)) {
    add_or_ignore_filename(f_setup, f_comp);
    printf("%d\n", match_counter);
  }
}

void process_line_output(int *line_number, flags_setup *f_setup, int *match_res,
                         char *cur_str, file_comp *f_comp) {
  if (!(f_setup->v) && !(f_setup->c) && !(*match_res) && !(f_setup->l)) {
    add_or_ignore_filename(f_setup, f_comp);
    process_line_enum(line_number, f_setup);
    printf("%s\n", cur_str);
  } else if (f_setup->v && !(f_setup->c) && !(f_setup->l) && *match_res) {
    add_or_ignore_filename(f_setup, f_comp);
    process_line_enum(line_number, f_setup);
    printf("%s\n", cur_str);
  }
}

void process_match_count(int *match_c, flags_setup *f_setup, int *match_res) {
  if (!(f_setup->v) && !(*match_res)) {
    (*match_c)++;
  } else if (f_setup->v && (*match_res)) {
    (*match_c)++;
  }
}

void process_line_enum(int *l_n, flags_setup *f_setup) {
  if (f_setup->n) printf("%d:", *l_n);
}

void get_next_symb(l_int *next_f_symb, FILE *fpp) {
  fseek(fpp, 1, SEEK_CUR);
  *next_f_symb = fgetc(fpp);
  fseek(fpp, -1, SEEK_CUR);
}

void get_str(FILE *fpp, l_int *str_st, l_int *str_len, char *cur_str) {
  for (int i = *str_st + 1, j = 0; i < *str_len; i++, j++) {
    cur_str[j] = fgetc(fpp);
    fseek(fpp, i, *str_st);
  }
  cur_str[*str_len] = '\0';
}

l_int get_length(FILE *fpp) {
  fseek(fpp, 0, SEEK_END);
  l_int f_length = ftell(fpp);
  fseek(fpp, 0, SEEK_SET);
  return f_length;
}

void get_str_len(l_int *str_length, l_int *f_length, l_int *str_start,
                 FILE *fpp) {
  *str_length = 0;  // reset previous str_length
  int cur_symb;
  cur_symb = 0;
  for (int i = *str_start; (i < *f_length) && (cur_symb != '\n');
       ++i) {  // loop stops when it finds the first occurence of '\n'

    fseek(fpp, i, *str_start);
    *str_length = i;  // last loop will include '\n' into count
    cur_symb = fgetc(fpp);
  }
  (*str_length)++;
  fseek(fpp, *str_start, SEEK_SET);
}
