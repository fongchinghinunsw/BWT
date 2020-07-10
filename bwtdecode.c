#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 247920

typedef struct c_table {
  int count[4];
} c_table;

typedef struct rank {
  // current # character.
  int cur;
  // current # occurance of each character.
  int count[5];
  int chars[MAX_SIZE];
  int match[MAX_SIZE];
} rank;

c_table *init_c_table();
rank *init_rank();
int to_index(int c);
void update_c_table(c_table *ct, int ch);
void update_rank(rank *r, int ch);
void print_c_table(c_table *ct);
void print_rank(rank *r);

int main(int argc, char **argv) {
  FILE *in = fopen(argv[1], "r");
  FILE *out = fopen(argv[2], "w");

  char buffer[MAX_SIZE];

  c_table *ct = init_c_table();
  rank *r = init_rank();
  int c;
  int next_pos;
  while ((c = fgetc(in)) != EOF) {
    if (c == '\n') next_pos = r->cur;
    update_c_table(ct, c);
    update_rank(r, c);
  }
  print_c_table(ct);
  print_rank(r);

  for (int i = 0; i < r->cur+1; i++) {
    buffer[i] = r->chars[next_pos];
    //printf("%d %c %d %d...\n", next_pos, r->chars[next_pos], ct->count[to_index(r->chars[next_pos])], r->match[next_pos]);
    next_pos = ct->count[to_index(r->chars[next_pos])] + r->match[next_pos];
  }

  for (int i = r->cur-1; 1; i--) {
    fputc(buffer[i], out);
    if (buffer[i] == '\n') {
      break;
    }
  }

  return 0;
}

c_table *init_c_table() {
  c_table *new = calloc(1, sizeof(*new));
  return new;
}

rank *init_rank() {
  rank *new = calloc(1, sizeof(*new));
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