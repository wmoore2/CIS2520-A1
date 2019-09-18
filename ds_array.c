/*
William Moore
1061752
wmoore02@uoguelph.ca
*/

#include "ds_array.h"

long elements = 0;

int ds_create_array(){
	/*Creates a file of the proper size*/
	if(ds_create("array.bin", sizeof(int) * (MAX_ELEMENTS) + sizeof(long)) != 0)
		return -1;
	if(ds_init("array.bin") != 0)
		return -1;
	/*Allocate space for the long*/
	ds_malloc(sizeof(long));
	/*Writes initial array size to start of file*/
	if(ds_write(0, &elements, sizeof(long)) != 0)
		return -1;
	/*Allocate data for the rest of the array*/
	ds_malloc(sizeof(int) * (MAX_ELEMENTS));
	return 0;
}

int ds_init_array(){
	if(ds_init("array.bin") != 0)
		return -1;
	/*Read in first entry in the file, the number of elements in the array*/
	if((ds_read(&elements, 0, sizeof(long))) != &elements)
		return -1;
	return 0;
}

int ds_replace(int value, long index){
	/*Checks for index out of bounds*/
	if(index >= MAX_ELEMENTS || index < 0)
		return -1;
	/*Replaces the element at index with value*/
	if(ds_write(index * sizeof(int) + sizeof(long), &value, sizeof(int)) != 0)
		return -1;
	return 0;
}

int ds_insert(int value, long index){
	int temp;
	if(index >= MAX_ELEMENTS || index < 0 || elements == MAX_ELEMENTS - 1)
		return -1;
	if(index != elements){
		/*Read/write value and recurse*/
		/*Read in value stored at index*/
		if(ds_read_array(&temp, index) != temp)
			return -1;
		/*Write value*/
		if(ds_replace(&value, index) != 0)
			return -1;

		return ds_insert(temp, index++);
		
	} else {
		/*Final read/write and exit here*/
		if(ds_replace(&value, index) != 0)
			return -1;

		elements++;
	}
	return 0;
}

int ds_delete(long index){
	return 0;
}

int ds_swap(long index1, long index2){
	return 0;
}

long ds_find(int target){
	return 0;
}

int ds_read_elements(char *filename){
	return 0;
}

int ds_finish_array(){
	return 0;
}

int ds_read_array(int index, int* ptr){
	/*Reads in from file, returns -1 when something goes wrong*/
	if(*(int*)(ds_read(ptr, index * sizeof(int) + sizeof(long), sizeof(int))) != *ptr)
		return -1;
	return *ptr;
}