/* INSTRUCTIONS:

This file contains all functions related with various policies.
Each policy returns the hit rate

*/

#include "definitions.h"
#include <stdio.h>
#include <stdlib.h>

// helper function to check a hit or miss
int hit(int page_no, int arr[], int n, int* index){
	int j = 0;
	// printf("%d\n", page_no);
	for(j=0;j<n;j++){
		if(arr[j]==page_no){
			*index = j;
			// it is a hit so return 1
			return 1;
		}
	}
	// It is a miss so return 0
	*index = 0;
	return 0;
}

// FIFO 
float policy_FIFO(struct workload * w, int cache_size)
{	
	float hit_rate;
	int i;
	// creating array for cache
	int cache[cache_size];

	// initializing all values in cache to -1
	for(i=0;i<cache_size;i++){
		cache[i] = -1;
	}
	int *p = w->work;
	float wsize = w->size;		// workload size
	i = 0;
	float faults = 0;			// number of faults
	int m;
	int available;				// variable to store a hit or miss 
	int index;

	// iterate over the workload
	while(i<wsize){
		// printf("%d\n", *p);
		available = hit(*p, cache, cache_size, &index);
		// if it is a miss
		if(available==0){
			// shift the pages in cache to append the latest page
			for(m=0; m<cache_size-1; m++){
				cache[m] = cache[m+1];
			}
			cache[m] = *p;
			// printf("%d\n",cache[m]);
			faults++;
		}
		i++;
		p++;	// increment the workload pointer
	}
	hit_rate = (wsize - faults)/wsize;
	// printf("%f\n", hit_rate);
	// printf("FIFO ended\n");
	return hit_rate;
}

float policy_LRU(struct workload * w, int cache_size)
{
	float hit_rate = 0;
	// creating array for cache
	int cache[cache_size];

	// initializing all values in cache to -1
	int i;
	for(i=0;i<cache_size;i++){
		cache[i] = -1;
	}
	int *p = w->work;
	float wsize = w->size;
	i = 0;
	float faults = 0;
	int n = cache_size;
	int j = 0;
	int index = 0;
	int available;
	int unique_pages = w->pages;

	// iterating over the workload
	while(i<wsize){
		// printf("%d\n", *p);
		available = hit(*p, cache, n, &index);
		// printf("%d\n", available);
		// it is a hit
		if (available==1){
			// just make the current page at the top of the queue
			for(j=index;j<n-1;j++){
				cache[j] = cache[j+1];
			}
			cache[j] = *p;
		}
		else{
			// it is a miss then pop the last one which was least frequent
			for(j=0;j<n-1;j++){
				cache[j] = cache[j+1];
			}
			cache[j] = *p;
			// printf("%d\n", cache[j]);
			faults++;
		}
		i++;
		p++;		// increment the workload pointer
	}
	// printf("%f\n", faults);
	// printf("%f\n", wsize);
	hit_rate = (wsize - faults)/wsize;
	return hit_rate;
}

// LRU Approx (second chance)
float policy_LRUapprox(struct workload * w, int cache_size)
{
	float hit_rate = 0;
	// creating array for cache
	int cache[cache_size];

	// initializing all values in cache to -1
	int i = 0;
	for(i=0;i<cache_size;i++){
		cache[i] = -1;
	}
	int *p = w->work;
	float wsize = w->size;
	float faults = 0;
	int n;
	int unique_pages = w->pages;
	n = cache_size;

	// define an array use_bits to keep track of which one was used
	int use_bits[w->pages];
	for(i=0; i<w->pages; i++){
        use_bits[i]=0;
	}
	i = 0;
	int index = 0;
	int available;
	int page_replc = 0;		// which page index will be replaced
	while(i<wsize){
		available = hit(*p, cache, n, &index);
		if (available==0){
			// it is a miss
			faults+=1;		// increment the fault count
			if(use_bits[page_replc]==1){
				// a do - while loop to check for the use_bit which is 0
				do{
					use_bits[page_replc] = 0;
					page_replc+=1;
					if(page_replc==n){
						page_replc = 0;
					}
				}
				while(use_bits[page_replc]!=0);
			}
			// after getting the index to be replace replace it in the cache
			if(use_bits[page_replc]==0){
				cache[page_replc] = *p;
				use_bits[page_replc] = 1;
				page_replc+=1;
			}
		}
		else{
			// it is a hit so make the use bit = 1
			if(use_bits[index]==0){
				use_bits[index] = 1;
			}
		}
		// if page_replc variable is at last of the array make it 0
		if(page_replc==n){
			page_replc = 0;
		}
		p++;		// increment the workload
		i++;
	}
	// printf("faults in approx %d\n",faults);
	// printf("faults in approx %d\n",wsize);
	hit_rate = (wsize - faults)/wsize;
	return hit_rate;
}

// Random policy
float policy_RANDOM(struct workload * w, int cache_size)
{
	float hit_rate = 0;
	// creating array for cache
	int cache[cache_size];

	// initializing all values in cache to -1
	int i = 0;
	for(i=0;i<cache_size;i++){
		cache[i] = -1;
	}
	int *p = w->work;
	float wsize = w->size;
	float faults = 0;
	int n;

	// iterate over the workload
	for(i=0;i<wsize;i++){
		n = cache_size;
		int j = 0;
		int index;
		int available;
		available = hit(*p, cache, n, &index);
		if(available==0){
			// it is a miss
			int index;
			// choose a random index and pop it out
			index = (rand() % (n-1 - 0 + 1)) + 0;
			for(j=index;j<n-1;j++){
				cache[j] = cache[j+1];
			}
			// put the current page at the top of the queue
			cache[j] = *p;
			faults++;
		}
		p++;		// increment the workload pointer
	}
	hit_rate = (wsize - faults)/wsize;
	return hit_rate;
}
