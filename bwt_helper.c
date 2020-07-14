#include "bwt_helper.h"

c_table *init_c_table() {
  c_table *new = calloc(1, sizeof(*new));
  return new;
}

rank *init_rank() {
  rank *new = calloc(1, sizeof(*new));
  return new;
}

bs_rank *init_bs_rank() {
  bs_rank *new = calloc(1, sizeof(*new));
  return new;
}

int to_index(int c) {
  switch (c)
  {
    case '\n': return 0;
    case 'A': return 1;
    case 'C': return 2;
    case 'G': return 3;
    case 'T': return 4;
  }
}

void update_c_table(c_table *ct, int ch) {
  for (int i = to_index(ch) + 1; i < 5; i++) {
    ct->count[i]++;
  }
}

void update_rank(rank *r, int ch) {
  r->chars[r->cur] = ch;
  r->match[r->cur] = r->count[to_index(ch)];
  r->count[to_index(ch)]++;
  r->cur++;
}

void update_bs_rank(bs_rank *r, int ch) {
  r->chars[r->cur] = ch;
  r->count[to_index(ch)]++;
  for (int i = 0; i < 5; i++) {
    if (to_index(ch) != i) {
      r->match[i][r->cur] = r->count[i];
    } else {
      r->match[i][r->cur] = r->count[to_index(ch)];
    }
  }
  r->cur++;
}

void print_c_table(c_table *ct) {
  printf("\\n %d\n", ct->count[0]);
  printf("A %d\n", ct->count[1]);
  printf("C %d\n", ct->count[2]);
  printf("G %d\n", ct->count[3]);
  printf("T %d\n", ct->count[4]);
}

void print_rank(rank *r) {
  printf("Position Symbol #Matching\n");
  for (int i = 0; i < r->cur; i++) {
    printf("%8d%7c%10d\n", i, r->chars[i], r->match[i]);
  }
}

void print_bs_rank(bs_rank *r) {
  printf("\\n A C G T\n");
  for (int i = 0; i < r->cur; i++) {
    for (int j = 0; j < 5; j++) {
      printf("%d ", r->match[j][i]);
    }
    printf("\n");
  }
}
