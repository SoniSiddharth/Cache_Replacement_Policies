#include "definitions.h"
#include "policy.c"
#include "workload.c"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{	char* w_type = malloc(sizeof(char*)*10);
	strcpy(w_type, argv[1]);
	int pages = atoi(argv[2]);
	int size = atoi(argv[3]);

	// generating workload according to the input
	struct workload *current_load = (struct workload *)malloc(sizeof(struct workload));
	if(strcmp(w_type, "loop")==0){
		current_load = generate_workload(LOOP, pages, size);
	}
	else if(strcmp(w_type, "local")==0){
		current_load = generate_workload(LOCAL, pages, size);
	}
	else{
		current_load = generate_workload(RANDOM, pages, size);
	}

	// variables to store the returned values
	float ans_lru, ans_approx, ans_random, ans_fifo;
	int cache_size;
	int i = 0;

	char f_name[100] = "plots";

	// creating csv file to store hit rate for each policy
	char *file_name = f_name;
	FILE *fd;
	file_name = strcat(file_name, ".csv");
	fd = fopen(file_name,"w+");
	fprintf(fd,"cache size, LRU, LRU Approx, Random, FIFO");

	// varying cache size from 10 to 100
	for(i=10;i<101;i++){
		cache_size = i;
		ans_lru = 100*policy_LRU(current_load, cache_size);
		ans_approx = 100*policy_LRUapprox(current_load, cache_size);
		ans_random = 100*policy_RANDOM(current_load, cache_size);
		ans_fifo = 100*policy_FIFO(current_load, cache_size);
		// printf("%f\n", ans);
		fprintf(fd, "\n%d, %f, %f, %f, %f", cache_size, ans_lru, ans_approx, ans_random, ans_fifo);
	}
	fclose(fd);
	return 0;
}