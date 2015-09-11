#include "header.h"

int trie_load(const char* fname, TTrie** ptrie) {

	FILE* fd;
	char* str = 0;
	size_t len = 0;
	ssize_t read;

	fd = fopen(fname, "r");
	if(fd == 0) return 1;

	(*ptrie) = trie_allocate();

	while((read = getline(&str, &len, fd)) != -1) {
		if(str[strlen(str)-1] == 10) str[strlen(str)-1] = 0;

		trie_insert(*ptrie, str);
		free(str);
		str = 0;
	}

	fclose(fd);
	return 0;
}

void trie_delete(TTrie* root) {

	TTrie *cur, *next;
	for(cur = root->child; cur != 0; cur = next) {
		next = cur->next;
		trie_delete(cur);
	}
	free(root);
}

int trie_find(TTrie* root, const char* str) {

	size_t sz = strlen(str), i;
	TTrie* cur = root;

	for(i=0; i<=sz; ++i) {
		for(cur = cur->child; cur != 0 && str[i] != cur->ch; cur = cur->next);
		if(cur == 0) return 0;
	}
	return 1;
}

TTrie* trie_allocate() {

	TTrie* node = malloc(sizeof(TTrie));
	node->ch = 0;
	node->child = 0;
	node->next = 0;

	return node;
}

TTrie* trie_insert_node(TTrie* parent, TTrie* prev, char ch) {

	TTrie* node = trie_allocate();
	node->ch = ch;
	if(prev != 0) prev->next = node;
	if(parent != 0) parent->child = node;

	return node;
}

void trie_insert(TTrie* root, const char* str) {

	size_t sz = strlen(str), i;
	TTrie *cur = root, *parent = 0;

	for(i=0; i<=sz; ++i){
		TTrie* prev = 0;
		parent = cur;
		for(cur = cur->child; cur != 0 && str[i] != cur->ch; cur = cur->next)
			prev = cur;

		if(cur == 0)
			if(prev == 0)
				cur = trie_insert_node(parent, 0, str[i]);
			else
				cur = trie_insert_node(0, prev, str[i]);
	}
}
