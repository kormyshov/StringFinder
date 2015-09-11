#ifndef __trie_arr_h__
#define __trie_arr_h__

#include "header.h"

#define MAX_EDGES 96

typedef struct TTrieStruct {
	int data;
	struct TTrieStruct* child[MAX_EDGES];
} TTrie;

int    trie_load(const char* fname, TTrie** ptrie);
void   trie_delete(TTrie* root);
int    trie_find(TTrie* root, const char* str);
TTrie* trie_allocate();
void   trie_insert(TTrie* root, const char* str);

#endif
