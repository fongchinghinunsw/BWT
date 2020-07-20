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

/*
  store rank every BLOCK_SIZE characters.
*/
void update_bs_rank(bs_rank *r, int ch, int cur) {
  r->count[to_index(ch)]++;
  if (cur % BLOCK_SIZE == 0) {
    printf("%d\n", cur);
    int index = cur / BLOCK_SIZE;
    for (int i = 0; i < 4; i++) {
      r->match[i][index] = r->count[i];
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
  printf("index    A    C    G    T\n");
  int index = cur / BLOCK_SIZE;
  for (int i = 0; i < index; i++) {
    printf("%5d", i);
    for (int j = 0; j < 4; j++) {
      printf("%5d", r->match[j][i]);
    }
    printf("\n");
  }
  printf("\nFinal count: %d %d %d %d\n\n", r->count[0], r->count[1], r->count[2], r->count[3]);
}
