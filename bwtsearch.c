#include "bwt_helper.h"

void search(FILE *in, char *search_term, c_table *ct, rank *r);
int getNumMatch(FILE *in, rank *r, int c, int cur);

int main(int argc, char **argv) {
  FILE *in = fopen(argv[1], "r");
  char search_term[100];

  c_table *ct = init_c_table();
  rank *r = init_rank();

  int c;
  int cur = 0;
  while ((c = fgetc(in)) != EOF) {
    if (c == '\n') {
      cur++;
      continue;
    }
    update_c_table(ct, c);
    update_bs_rank(r, c, cur);
    cur++;
  }

  //print_rank(r, cur);

  while (scanf("%s", search_term) != EOF) {
    search(in, search_term, ct, r);
  }

  fclose(in);
}

void search(FILE *in, char *search_term, c_table *ct, rank *r) {
  int i = strlen(search_term) - 1; // last index of the pattern
  int c = search_term[i]; // start with last character of the pattern.
  int first = ct->count[to_index(c)];
  int last;
  if (to_index(c) == to_index('T')) {
    last = ct->count[to_index(c)] + r->count[to_index(c)] - 1;
  } else {
    last = ct->count[to_index(c)+1] - 1;
  }
  // stops when not found or reach the last character of the pattern.
  while ((first <= last) && (i >= 1)) {
    c = search_term[i-1];
    // bs_rank is to check "which" same character is that.
    first = ct->count[to_index(c)] + getNumMatch(in, r, c, first-1);
    last = ct->count[to_index(c)] + getNumMatch(in, r, c, last) - 1;
    //first = ct->count[to_index(c)] + r->match[to_index(c)][first-1];
    //last = ct->count[to_index(c)] + r->match[to_index(c)][last] - 1;
    i--;
  }
  if (last < first) {
    printf("0\n");
  } else {
    printf("%d\n", last - first + 1);
  }
}

int getNumMatch(FILE *in, rank *r, int c, int cur) {
  int block_id = cur / BLOCK_SIZE;
  int offset = cur % BLOCK_SIZE;

  int result = r->match[to_index(c)][block_id];
  for (int i = cur-offset+1; i <= cur; i++) {
    fseek(in, i, SEEK_SET);
    if (fgetc(in) == c) result++;
  }
  return result;
}