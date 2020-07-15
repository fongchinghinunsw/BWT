#include "bwt_helper.h"

int main(int argc, char **argv) {
  FILE *in = fopen(argv[1], "r");
  FILE *out = fopen(argv[2], "w");

  char buffer[MAX_SIZE];

  c_table *ct = init_c_table();
  rank *r = init_rank();
  int c;
  int cur = 0;
  int next_pos;
  while ((c = fgetc(in)) != EOF) {
    if (c == '\n') {
      next_pos = cur;
      cur++;
      continue;
    }
    update_c_table(ct, c);
    update_rank(r, c, cur);
    cur++;
  }
  print_c_table(ct);
  print_rank(r, cur);

  next_pos = r->match[next_pos];
  for (int i = 0; i < cur; i++) {
    fseek(in, next_pos, SEEK_SET);
    buffer[i] = fgetc(in);
    //printf("%c %d\n", buffer[i], next_pos);
    next_pos = ct->count[to_index(buffer[i])] + r->match[next_pos];
  }

  for (int i = cur-2; i >= 0; i--) {
    fputc(buffer[i], out);
    putchar(buffer[i]);
  }
  printf("\n");

  fclose(in);
  fclose(out);

  return 0;
}