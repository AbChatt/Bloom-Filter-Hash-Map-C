CC = gcc
CFLAGS = -Wall -Werror -g
DEPS = Hash.h HashMap.h BloomFilter.h
OBJ = Hash.o HashMap.o BloomFilter.o TestHashMap.o TestBloomFilter.o

all: TestHashMap TestBloomFilter

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

TestHashMap: Hash.o HashMap.o TestHashMap.o
	$(CC) -o $@ $^ $(CFLAGS)

TestBloomFilter: Hash.o BloomFilter.o TestBloomFilter.o
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ) ./TestHashMap ./TestBloomFilter

