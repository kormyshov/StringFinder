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

	size_t i;
	for(i=0; i<MAX_EDGES; ++i)
		if(root->child[i] != NULL)
			trie_delete(root->child[i]);
	free(root);
}

int trie_find(TTrie* root, const char* str) {

	size_t sz = strlen(str), i;
	TTrie* cur = root;

	for(i=0; i<sz; ++i) {
		char ch = str[i] - 32;
		if(cur->child[ch] == NULL) return 0;
		cur = cur->child[ch];
	}
	return cur->data;
}

TTrie* trie_allocate() {

	TTrie* node = malloc(sizeof(TTrie));
	node->data = 0;
	memset(node->child, 0, sizeof(node->child));
	return node;
}

void trie_insert(TTrie* root, const char* str) {

	size_t sz = strlen(str), i;
	TTrie* cur = root;

	for(i=0; i<sz; ++i){
		char ch = str[i] - 32;
		if(cur->child[ch] == NULL)
			cur->child[ch] = trie_allocate();
		cur = cur->child[ch];
	}
	cur->data = 1;
}
