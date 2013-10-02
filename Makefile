CC=gcc
CFLAGS=-Wall -Wextra
BINDIR=/usr/bin

dns-disovery: narc4_test.c narc4.h
	$(CC) $(CFLAGS) -c *.c 
	$(CC) $(CFLAGS) -o narc4_test *.o -O3 
	rm *.o

clean:
	rm narc4_test
