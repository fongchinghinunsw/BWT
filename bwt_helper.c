#include "bwt_helper.h"

c_table *init_c_table() {
  c_table *new = calloc(1, sizeof(*new));
  new->count[0] = new->count[1] = new->count[2] = new->count[3] = 1;
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
    case 'A': return 0;
    case 'C': return 1;
    case 'G': return 2;
    case 'T': return 3;
  }
}

void update_c_table(c_table *ct, int ch) {
  for (int i = to_index(ch) + 1; i < 4; i++) {
    ct->count[i]++;
  }
}

void update_rank(rank *r, int ch, int cur) {
  r->match[cur] = r->count[to_index(ch)];
  r->count[to_index(ch)]++;
}

void update_bs_rank(bs_rank *r, int ch, int cur) {
  r->count[to_index(ch)]++;
  for (int i = 0; i < 4; i++) {
    if (to_index(ch) != i) {
      r->match[i][cur] = r->count[i];
    } else {
      r->match[i][cur] = r->count[to_index(ch)];
    }
  }
}

void print_c_table(c_table *ct) {
  printf("A %d\n", ct->count[0]);
  printf("C %d\n", ct->count[1]);
  printf("G %d\n", ct->count[2]);
  printf("T %d\n", ct->count[3]);
}

void print_rank(rank *r, int cur) {
  printf("Position #Matching\n");
  for (int i = 0; i < cur; i++) {
    printf("%8d%10d\n", i, r->match[i]);
  }
}

void print_bs_rank(bs_rank *r, int cur) {
  printf("A C G T\n");
  for (int i = 0; i < cur; i++) {
    for (int j = 0; j < 4; j++) {
      printf("%d ", r->match[j][i]);
    }
    printf("\n");
  }
}
