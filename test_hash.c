#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <set>

#define HS 9000000000000007
#define hs 101

long long hash(const char* str) {
	long long r = 0, i;
	for(i=0; str[i]; ++i) {
		r *= hs;
		r += str[i]-31;
		r %= HS;
	}
	return r;
}

int main(int argc, const char** argv) {

	if (argc != 3) {
		printf("Invalid args\n");
		exit(EXIT_FAILURE);
	}

	clock_t cl;
	cl = clock();

	FILE* fd;
	char* str = 0;
	size_t len = 0;
	ssize_t read;

	fd = fopen(argv[1], "r");
	if(fd == 0) return 1;

	std::set<long long> sh;

	while((read = getline(&str, &len, fd)) != -1) {
		if(str[strlen(str)-1] == 10) str[strlen(str)-1] = 0;

		sh.insert(hash(str));
		free(str);
		str = 0;
	}

	fclose(fd);
	printf("Create : %.6lf\n", (clock()-cl)/(double)CLOCKS_PER_SEC);

	fd = fopen(argv[2], "r");
	if(fd == 0) return 1;

	int res = 0;
	cl = clock();
	while((read = getline(&str, &len, fd)) != -1) {
		if(str[strlen(str)-1] == 10) str[strlen(str)-1] = 0;
		res += sh.count(hash(str));

		free(str);
		str = 0;
	}
	printf("Search : %.6lf, res = %d\n", (clock()-cl)/(double)CLOCKS_PER_SEC, res);

	fclose(fd);

	return 0;
}
