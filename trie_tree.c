#include "header.h"

void trie_balance(TTrie* root, int type) {

	int cnt = 0;
	TTrie* cur;

	switch(type){
		case LinkChild : cur = root->child; break;
		case LinkRight : cur = root->right; break;
		default : cur = root->left;
	}

	if(cur == 0) return ;

	TTrie* first = cur;
	while(cur != 0) {
		cnt++;
		cur = cur->right;
	}

	if(cnt >= 3) {
		cur = first;
		cnt /= 2;

		while(cnt > 1) {
			cur = cur->right;
			cnt--;
		}

		switch(type){
			case LinkChild : root->child = cur->right; break;
			case LinkRight : root->right = cur->right; break;
			default : root->left = cur->right;
		}
		cur->right->left = first;
		cur->right = 0;
	}

	switch(type){
		case LinkChild : cur = root->child; break;
		case LinkRight : cur = root->right; break;
		default : cur = root->left;
	}

	trie_balance(cur, LinkChild);
	trie_balance(cur, LinkRight);
	trie_balance(cur, LinkLeft);
}

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

	trie_balance(*ptrie, LinkChild);

	return 0;
}

void trie_delete(TTrie* root) {

	if(root->child != 0) trie_delete(root->child);
	if(root->left != 0) trie_delete(root->left);
	if(root->right != 0) trie_delete(root->right);

	free(root);
}

int trie_find(TTrie* root, const char* str) {

	size_t sz = strlen(str), i;
	TTrie* cur = root;

	for(i=0; i<=sz; ++i) {
		for(cur = cur->child; cur != 0 && str[i] != cur->ch; cur = (str[i] > cur->ch ? cur->right : cur->left) );
		if(cur == 0) return 0;
	}
	return 1;
}

TTrie* trie_allocate() {

	TTrie* node = malloc(sizeof(TTrie));
	node->ch = 0;
	node->child = 0;
	node->left = 0;
	node->right = 0;

	return node;
}

TTrie* trie_insert_node(TTrie* parent, TTrie* prev, char ch) {

	TTrie* node = trie_allocate();
	node->ch = ch;
	if(prev != 0) {
		node->right = prev->right;
		prev->right = node;
	}
	if(parent != 0) {
		node->right = parent->child;
		parent->child = node;
	}

	return node;
}

void trie_insert(TTrie* root, const char* str) {

	size_t sz = strlen(str), i;
	TTrie *cur = root, *parent = 0;

	for(i=0; i<=sz; ++i){
		TTrie* prev = 0;
		parent = cur;
		for(cur = cur->child; cur != 0 && str[i] > cur->ch; cur = cur->right)
			prev = cur;

		if(cur == 0 || str[i] < cur->ch)
			if(prev == 0)
				cur = trie_insert_node(parent, 0, str[i]);
			else
				cur = trie_insert_node(0, prev, str[i]);
	}
}
