#ifndef __trie_list_h__
#define __trie_list_h__

#include "header.h"

typedef struct TTrieStruct {
	struct TTrieStruct* child;
	struct TTrieStruct* next;
	char ch;
} TTrie;

int    trie_load(const char* fname, TTrie** ptrie);
void   trie_delete(TTrie* root);
TTrie* trie_find(TTrie* root, const char* str);
void   trie_insert(TTrie* root, const char* str);

#endif
