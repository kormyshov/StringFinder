#include "header.h"

#include <time.h>

int main(int argc, const char** argv) {

	if (argc != 3) {
		printf("Invalid args\n");
		exit(EXIT_FAILURE);
	}

	TTrie* trie;

	clock_t cl;
	cl = clock();
	if(trie_load(argv[1], &trie) != 0) {
		printf("Unable to create trie from file\n");
		exit(EXIT_FAILURE);
	}
	printf("Create : %.6lf\n", (clock()-cl)/(double)CLOCKS_PER_SEC);

	FILE* fd;
	char* str = 0;
	size_t len = 0;
	ssize_t read;

	fd = fopen(argv[2], "r");
	if(fd == 0) return 1;

	int res = 0;
	cl = clock();
	while((read = getline(&str, &len, fd)) != -1) {
		if(str[strlen(str)-1] == 10) str[strlen(str)-1] = 0;
		res += trie_find(trie, str);

		free(str);
		str = 0;
	}
	printf("Search : %.6lf, res = %d\n", (clock()-cl)/(double)CLOCKS_PER_SEC, res);

	fclose(fd);

	trie_delete(trie);

	return 0;
}
