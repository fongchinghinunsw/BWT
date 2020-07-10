default: bwtdecode bwtsearch

aencode: bwtdecode.c
	gcc -o bwtdecode bwtdecode.c
adecode: bwtsearch.c
	gcc -o bwtsearch bwtsearch.c