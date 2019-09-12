/*
William Moore
1061752
wmoore02@uoguelph.ca
*/

#include"ds_memory.h"

struct ds_file_struct ds_file;
struct ds_counts_struct ds_counts;

int ds_create(char *filename, long size){
	char buff = '\0';
	int i;
	if((ds_file->fp = fopen(filename, wb)) == NULL){
		/*error check when opening file*/
		return -1;
	}

	ds_file->block->start = 0;
	ds_file->block->length = size;
	ds_file->block->alloced = 0;
	/*may have to initialize entire ds_counts array to all 0*/

	if(fwrite(ds_file->block, sizeof(ds_blocks_struct), 1, ds_file->fp) != 1){
		fclose(ds_file->fp);
		return -1;
	}

	for(i = 0; i < size; i++){
		if(fwrite(&c, sizeof(char), 1, ds_file->fp) != 1){
			fclose(ds_file->fp);
			return -1;
		}
	}

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