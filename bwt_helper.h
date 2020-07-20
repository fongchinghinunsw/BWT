#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 247920
#define BLOCK_SIZE 5

typedef struct c_table {
  int count[4];
} c_table;

typedef struct rank {
  // current # occurance of each character.
  int count[4];
  // # time that character occurs so far.
  int match[MAX_SIZE];
} rank;

typedef struct bs_rank {
  int count[4];
  int match[4][MAX_SIZE];
} bs_rank;

c_table *init_c_table();

rank *init_rank();

bs_rank *init_bs_rank();

int to_index(int);

void update_c_table(c_table *, int);

void update_rank(rank *, int, int);

void update_bs_rank(bs_rank *, int, int);

void print_c_table(c_table *);

void print_rank(rank *, int);

void print_bs_rank(bs_rank *, int);
