#include "bwt_helper.h"

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
    fseek(in, next_pos, SEEK_SET);
    buffer[i] = fgetc(in);
    //printf("%d %c %d %d...\n", next_pos, r->chars[next_pos], ct->count[to_index(r->chars[next_pos])], r->match[next_pos]);
    next_pos = ct->count[to_index(buffer[i])] + r->match[next_pos];
  }

  for (int i = r->cur-1; 1; i--) {
    fputc(buffer[i], out);
    if (buffer[i] == '\n') {
      break;
    }
  }

  return 0;
}