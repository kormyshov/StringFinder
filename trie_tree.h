#ifndef __trie_tree_h__
#define __trie_tree_h__

#include "header.h"

#define LinkChild 1
#define LinkRight 2
#define LinkLeft  3

typedef struct TTrieStruct {
	struct TTrieStruct* child;
	struct TTrieStruct* left;
	struct TTrieStruct* right;
	char ch;
} TTrie;

void   trie_balance(TTrie* root, int type);
int    trie_load(const char* fname, TTrie** ptrie);
void   trie_delete(TTrie* root);
int    trie_find(TTrie* root, const char* str);
TTrie* trie_allocate();
void   trie_insert(TTrie* root, const char* str);

#endif
