#include "bwt_helper.h"
int getNumMatch(FILE *in, rank *r, int c, int cur);

int main(int argc, char **argv) {
  FILE *in = fopen(argv[1], "r");
  FILE *out = fopen(argv[2], "w");

  //char buffer[TMP_MAX_SIZE];

  c_table *ct = init_c_table();
  rank *r = init_rank();
  int c;
  int cur = 0;
  int next_pos;
  while ((c = fgetc(in)) != EOF) {
    if (c == '\n') {
      //next_pos = cur;
      // cur will be one larger than current index.
      cur++;
      continue;
    }
    update_c_table(ct, c);
    update_rank(r, c, cur);
    cur++;
  }
  //print_c_table(ct);
  //print_rank(r, cur);

  next_pos = 0;
  // i < cur - 1 to avoid seeking \n
  for (int i = 0; i < cur-1; i++) {
    fseek(in, next_pos, SEEK_SET);
    int c = fgetc(in);
    fputc(c, out);
    //buffer[i] = fgetc(in);
    //printf("%c %d %d %d\n", buffer[i], ct->count[to_index(buffer[i])], getNumMatch(in, r, buffer[i], next_pos), next_pos);
    next_pos = ct->count[to_index(c)] + getNumMatch(in, r, c, next_pos);
  }
  fputc('\n', out);

  for (int i = cur-2; i >= 0; i--) {
    //fputc(buffer[i], out);
    //putchar(buffer[i]);
  }
  //printf("\n");

  fclose(in);
  fclose(out);

  return 0;
}

int getNumMatch(FILE *in, rank *r, int c, int cur) {
  int block_id = cur / BLOCK_SIZE;
  int offset = cur % BLOCK_SIZE;

  int result = r->match[to_index(c)][block_id];
  char block[offset];
  fseek(in, cur-offset, SEEK_SET);
  fread(block, 1, offset, in);
  for (int i = 0; i < offset; i++) {
    if (block[i] == c) result++;
  }
  /*
  for (int i = cur-offset; i < cur; i++) {
    fseek(in, i, SEEK_SET);
    if (fgetc(in) == c) result++;
  }
  */
  return result;
}