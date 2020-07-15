#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 247920

typedef struct c_table {
  int count[5];
} c_table;

typedef struct rank {
  // current # character.
  int cur;
  // current # occurance of each character.
  int count[5];
  // # time that character occurs so far.
  int match[MAX_SIZE];
} rank;

typedef struct bs_rank {
  int cur;
  int count[5];
  int match[5][MAX_SIZE];
} bs_rank;

c_table *init_c_table();

rank *init_rank();

bs_rank *init_bs_rank();

int to_index(int c);

void update_c_table(c_table *ct, int ch);

void update_rank(rank *r, int ch);

void update_bs_rank(bs_rank *r, int ch);

void print_c_table(c_table *ct);

void print_rank(rank *r);

void print_bs_rank(bs_rank *r);
