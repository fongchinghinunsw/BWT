default: bwtdecode bwtsearch

bwtdecode: bwtdecode.c
	gcc -o bwtdecode bwtdecode.c bwt_helper.c
bwtsearch: bwtsearch.c
	gcc -o bwtsearch bwtsearch.c bwt_helper.c