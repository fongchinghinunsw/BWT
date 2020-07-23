#include "bwt_helper.h"

int getNumMatch(FILE *in, rank *r, int c, int cur);

int main(int argc, char **argv) {
  FILE *in = fopen(argv[1], "r");
  FILE *out = fopen(argv[2], "w");

  char block[BLOCK_SIZE];

  // ===== preprocessing started ===== //
  c_table *ct = init_c_table();
  rank *r = init_rank();
  int c;
  int cur = 0;
  int next_pos;

  int numRead;
  while ((numRead = fread(block, 1, BLOCK_SIZE, in)) != 0) {
    for (int i = 0; i < numRead; i++) {
      if (block[i] == '\n') {
	cur++;
	continue;
      }
      update_c_table(ct, block[i]);
      update_rank(r, block[i], cur);
      cur++;
    }
  }
  // ===== preprocessing done ===== //
  
  // used to store the character temporary in block.
  int block_index = BLOCK_SIZE - 1;
  next_pos = 0;
  // i = cur - 1 to avoid seeking \n
  for (int i = cur-2; i >= 0; i--) {

    fseek(in, next_pos, SEEK_SET);
    int c = fgetc(in);
    next_pos = ct->count[to_index(c)] + getNumMatch(in, r, c, next_pos);

    block[block_index] = c;
    block_index--;
    if (block_index < 0) {
      fseek(out, i, SEEK_SET);
      fwrite(block, 1, BLOCK_SIZE, out);
      block_index = BLOCK_SIZE - 1;
    }
  }

  if (block_index != BLOCK_SIZE - 1) {
    fseek(out, 0, SEEK_SET);
    fwrite(block+block_index+1, 1, BLOCK_SIZE-block_index-1, out);
  }
  fseek(out, cur-1, SEEK_SET);
  fwrite("\n", 1, 1, out);

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
  return result;
}