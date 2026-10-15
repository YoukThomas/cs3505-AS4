inc = ./include
CC = g++

testTrie: testTrie.cpp
	g++ -Wall -o testTrie -I$(inc) Trie.cpp testTrie.cpp;
	./testTrie

TrieDictionary:	Trie.o TrieDictionary.cpp
	$(CC) -Wall -g -fsanitize=undefined -o TrieDictionary -I$(inc) Trie.o TrieDictionary.cpp

Trie.o: Trie.cpp
	$(CC) -c -I$(inc) Trie.cpp

.PHONY: clean

clean:
	rm testTrie;rm TrieDictionary;rm *.o