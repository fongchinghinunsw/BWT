default: bwtdecode bwtsearch

bwtdecode: bwtdecode.c
	gcc -O3 -o bwtdecode bwtdecode.c bwt_helper.c
bwtsearch: bwtsearch.c
	gcc -O3 -o bwtsearch bwtsearch.c bwt_helper.c