#include "bwt_helper.h"

#define READ_SIZE 2000

int getNumMatch(FILE *in, rank *r, char *block, int *c, int cur);

int main(int argc, char **argv) {
  FILE *in = fopen(argv[1], "r");
  FILE *out = fopen(argv[2], "w");

  char block[BLOCK_SIZE];

  char *block_f = malloc(BLOCK_SIZE);

  // ===== preprocessing started ===== // takes ~0.9s for 15MB
  c_table *ct = init_c_table();
  rank *r = init_rank();
  int *c = malloc(sizeof(int));
  int cur = 0;
  int next_pos;

  int numRead;
  while ((numRead = fread(block, 1, BLOCK_SIZE, in)) != 0) {
    for (int i = 0; i < numRead; i++) {
      if (block[i] == '\n') {
        update_rank(r, block[i], cur);
	cur++;
	continue;
      }
      update_c_table(ct, block[i]);
      update_rank(r, block[i], cur);
      cur++;
    }
  }
  // ===== preprocessing done ===== //
  
  int block_index = BLOCK_SIZE - 1;
  next_pos = 0;

  // i = cur - 1 to avoid seeking \n
  for (int i = cur-2; i >= 0; i--) {
    // ------------------------- 
    // computation heavy part, other part of codes only nd ~0.28s for 15MB, most of them usr time.

    int count = getNumMatch(in, r, block_f, c, next_pos);
    next_pos = ct->count[to_index(*c)] + count;

    block[block_index] = *c; // this line costs ~0.02s for 15MB
    // -------------------------
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

int getNumMatch(FILE *in, rank *r, char *block, int *c, int cur) {
  int block_id = cur / BLOCK_SIZE;
  int offset = cur % BLOCK_SIZE;

  int ch;
  int result;
// ---------------------- this is the computational heavy part,
// other parts in this func costs almost nothing.
  if (offset < BLOCK_SIZE - offset || block_id == r->numBlock - 1) {
    fseek(in, cur-offset, SEEK_SET);
    fread(block, offset+1, 1, in);

    *c = block[offset];
    ch = *c;

    result = r->match[to_index(ch)][block_id];

    for (int i = 0; i < offset; i++) {
      if (block[i] == ch) result++;
    }

  } else {
    fseek(in, cur, SEEK_SET);
    fread(block, BLOCK_SIZE-offset, 1, in);

    *c = block[0];
    ch = *c;

    result = r->match[to_index(ch)][block_id+1];


    for (int i = 0; i < BLOCK_SIZE - offset; i++) {
      if (block[i] == ch) result--;
    }
  }
  // -----------------------------
  return result;
}