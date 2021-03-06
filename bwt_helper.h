#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 700
#define MAX_SIZE (104857600/BLOCK_SIZE)+2

typedef struct c_table {
  int count[4];
} c_table;

typedef struct rank {
  int numBlock;
  // current # occurance of each character.
  int count[4];
  // # time that character occurs so far.
  //int match[MAX_SIZE];
  int match[4][MAX_SIZE];
} rank;

c_table *init_c_table();

rank *init_rank();

int to_index(int);

void update_c_table(c_table *, int);

void update_rank(rank *, int, int);

void update_bs_rank(rank *, int, int);

void print_c_table(c_table *);

void print_rank(rank *, int);
