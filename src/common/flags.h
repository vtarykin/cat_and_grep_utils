#ifndef SRC_COMMON_FLAGS_H_
#define SRC_COMMON_FLAGS_H_

typedef struct {
  int e;
  int n;
  int s;
  int v;
#ifdef CAT
  int b;
  int t;
#endif  // CAT
#ifdef GREP
  int o;
  int h;
  int i;
  int l;
  int c;
  int f;
  char *pattern;
#endif  // GREP
} flags_setup;

#endif  // SRC_COMMON_FLAGS_H_
