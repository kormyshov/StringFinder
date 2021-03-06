#include "header.h"

int main(int argc, const char** argv) {

	if (argc != 2) {
		printf("Invalid args\n");
		exit(EXIT_FAILURE);
	}

	TTrie* trie;

	if(trie_load(argv[1], &trie) != 0) {
		printf("Unable to create trie from file\n");
		exit(EXIT_FAILURE);
	}

	char* str = 0;
	size_t len = 0;
	ssize_t read;

	while((read = getline(&str, &len, stdin)) != -1) {
		if(str[strlen(str)-1] == 10) str[strlen(str)-1] = 0;
		if(strcmp(str, "exit") == 0) {
			free(str);
			break;
		}
		printf("%s\n", (trie_find(trie, str) ? "YES" : "NO"));

		free(str);
		str = 0;
	}

	trie_delete(trie);

	return 0;
}
