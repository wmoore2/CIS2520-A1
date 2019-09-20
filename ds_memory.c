/*
William Moore
1061752
wmoore02@uoguelph.ca
*/

#include"ds_memory.h"

struct ds_file_struct ds_file;
struct ds_counts_struct ds_counts;

int ds_create(char *filename, long size){
	/*Used for filling file with null*/
	char buff = '\0';
	FILE *fp;
	int i;
	if((fp = fopen(filename, "wb")) == NULL){
		/*error check when opening file*/
		return -1;
	}

	ds_file.block[0].start = 0;
	ds_file.block[0].length = size;
	ds_file.block[0].alloced = 0;
	/*may have to initialize entire ds_counts array to all 0*/

	/*Write the header to the file (table of contents)*/
	if(fwrite(ds_file.block, sizeof(struct  ds_blocks_struct), 1, fp) != 1){
		fclose(fp);
		return -1;
	}

	/*Write null characters*/
	for(i = 0; i < size + sizeof(struct ds_blocks_struct); i++){
		if(fwrite(&buff, sizeof(char), 1, fp) != 1){
			fclose(fp);
			return -1;
		}
	}

	fclose(fp);

	return 0;
}

int ds_init(char *filename){
	/*Opens file into the global file pointer*/
	if((ds_file.fp = fopen(filename, "rb+")) == NULL){
		/*error check when opening file*/
		return -2;
	}
	/*Reads in the header or table of contents*/
	if(fread(ds_file.block, sizeof(struct ds_blocks_struct), 1, ds_file.fp) != 1){
		fclose(ds_file.fp);
		return -1;
	}
	/*Initializes reads and writes to 0*/
	ds_counts.reads = 0;
	ds_counts.writes = 0;

	return 0;
}

long ds_malloc(long amount){
	int i, blockFound = -1;
	struct ds_blocks_struct temp;
	/*Searches for next available block with enough space for amount*/
	for(i = 0; i < MAX_BLOCKS; i++){
		if(ds_file.block[i].alloced == 0){
			if(ds_file.block[i].length >= amount){
				/*Building temporary struct*/
				temp = ds_file.block[i];
				ds_file.block[i].alloced = 1;
				ds_file.block[i].length = amount;
				break;
			}
		}
	}
	/*Locates next available block and marks it as such*/
	for(i = 0; i < MAX_BLOCKS; i++){
		if(ds_file.block[i].length == 0){
			/*Setting up next block*/
			ds_file.block[i].start = temp.start + amount;
			ds_file.block[i].length = temp.length - amount;
			ds_file.block[i].alloced = 0;
			/*Sets return value*/
			blockFound = temp.start;
		}
	}
	return blockFound;
}

void ds_free(long start){
	int i;
	/*Searches for given start value*/
	for(i = 0; i < MAX_BLOCKS; i++){
		if(ds_file.block[i].start == start){
			ds_file.block[i].alloced = 0;
		}
	}
	return;
}

void *ds_read(void *ptr, long start, long bytes){
	/*Move file pointer to start position*/
	seekPos(start);
	/*Reads in specified bytes and stores it in given pointer*/
	if(fread(ptr, bytes, 1, ds_file.fp) != 1){
		return NULL;
	}
	ds_counts.reads++;
	return ptr;
}

long ds_write(long start, void *ptr, long bytes){
	/*Move file pointer to start position*/
	seekPos(start);
	/*Writes from the given pointer*/
	if(fwrite(ptr, bytes, 1, ds_file.fp) != 1){
		return -1;
	}
	ds_counts.writes++;
	return 0;
}

int ds_finish(){
	/*Write the header to the file (table of contents)*/
	if(fwrite(ds_file.block, sizeof(struct ds_blocks_struct), 1, ds_file.fp) != 1){
		fclose(ds_file.fp);
		return -1;
	}
	fclose(ds_file.fp);

	printf("reads: %d\nwrites: %d\n", ds_counts.reads, ds_counts.writes);

	return 0;
}

void seekPos(int pos){
	/*Moves the file pointer to the first position*/
	fseek(ds_file.fp, sizeof(struct ds_blocks_struct), SEEK_SET);
	/*Moves file pointer to position given*/
	fseek(ds_file.fp, pos, SEEK_CUR);
	return;
}