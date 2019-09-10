#include"ds_memory.h"

struct ds_file_struct ds_file;
struct ds_counts_struct ds_counts;

int ds_create(char *filename, long size){
	return 0;
}

int ds_init(char *filename){
	return 0;
}

long ds_malloc(long amount){
	return 0;
}

void ds_free(long start){
	return;
}

void *ds_read(void *ptr, long start, long bytes){
	return;
}

long ds_write(long start, void *ptr, long bytes){
	return 0;
}

int ds_finish(){
	return 0;
}