/*
William Moore
1061752
wmoore02@uoguelph.ca
*/

#include "ds_array.h"

long elements = 0;

// int main(){
// 	int i = 0, temp = 0;
// 	ds_create("array.bin", sizeof(int) * MAX_ELEMENTS + sizeof(long));
// 	ds_create_array();
// 	ds_init_array();
// 	ds_read_elements("bin/temp.txt");
// 	ds_swap(0, 1);
// 	printf("%ld\n", ds_find(7));
// 	printf("%d\n", ds_delete(0));
// 	for (i = 0; i < elements; ++i) {	
// 		printf("%d\n", ds_read_array(&temp, i));
// 	}
// 	ds_finish_array();
// 	return 0;
// }

int ds_create_array(){
	/*initiates a file of the proper size*/
	if(ds_init("array.bin") != 0)
		return -1;
	/*Allocate space for the long*/
	ds_malloc(sizeof(long));
	/*Writes initial array size to start of file*/
	if(ds_write(0, &elements, sizeof(long)) != 0)
		return -1;
	/*Allocate data for the rest of the array*/
	ds_malloc(sizeof(int) * (MAX_ELEMENTS));
	ds_finish();
	return 0;
}

int ds_init_array(){
	if(ds_init("array.bin") != 0)
		return -1;
	/*Read in first entry in the file, the number of elements in the array*/
	if((ds_read(&elements, 0, sizeof(long))) != &elements)
		return -2;
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
	if(index >= MAX_ELEMENTS || index < 0 || elements == MAX_ELEMENTS - 1 || index > elements)
		return -1;
	if(index != elements){
		/*Read/write value and recurse*/
		/*Read in value stored at index*/
		if(ds_read_array(&temp, index) != temp)
			return -1;
		/*Write value*/
		if(ds_replace(value, index) != 0)
			return -1;

		return ds_insert(temp, index++);
		
	} else {
		/*Final read/write and exit here*/
		if(ds_replace(value, index) != 0)
			return -1;

		elements++;
	}
	return 0;
}

int ds_delete(long index){
	int temp = 0;
	/*Checks for index being out of bounds*/
	if(index >= MAX_ELEMENTS || index < 0 || index >= elements)
		return -2;
	/*Checks for edge case of having one element and being on the final element*/
	if(index == (elements - 1)){
		elements--;
		return 0;
	} else {
		/*Read in value to be written to earlier index*/
		if(ds_read_array(&temp, index + 1) != temp)
			return -1;
		/*Write value read in above*/
		if(ds_replace(temp, index) != 0)
			return -1;
		/*Recurse*/
		return ds_delete(index + 1);
	}
}

int ds_swap(long index1, long index2){
	int temp1, temp2;
	/*Read in first index*/
	if(ds_read_array(&temp1, index1) != temp1)
		return -1;
	/*Read in second index*/
	if(ds_read_array(&temp2, index2) != temp2)
		return -1;
	/*Write first number in second index*/
	if(ds_replace(temp1, index2) != 0)
		return -1;
	/*Write second number in first index*/
	if(ds_replace(temp2, index1) != 0)
		return -1;
	return 0;
}

long ds_find(int target){
	int i, temp;
	for(i = 0; i < elements; i++){
		/*Read in ith element*/
		if(ds_read_array(&temp, i) != temp)
			return -1;
		/*Check if its equal to target, return index if it is*/
		if(temp == target)
			return i;
	}
	return -1;
}

int ds_read_elements(char *filename){
	int index = elements, temp = 0;
	FILE *fp;
	if((fp = fopen(filename, "r")) == NULL){
		return -1;
	}
	/*Loops through entire file*/
	while(fscanf(fp, "%d", &temp) != EOF){
		/*Inserts read in character into array*/
		if(ds_insert(temp, index) != 0)
			return -1;
		index++;
		if(index == MAX_ELEMENTS)
			return -1;
	}
	fclose(fp);
	return 0;
}

int ds_finish_array(){
	/*Writes final size of array to file*/
	if(ds_write(0, &elements, sizeof(long)) != 0)
		return -1;
	if(ds_finish() != 0)
		return -1;
	return 0;
}

int ds_read_array(int* ptr, int index){
	/*Reads in from file, returns something that isnt *ptr when something goes wrong*/
	if(*(int*)(ds_read(ptr, index * sizeof(int) + sizeof(long), sizeof(int))) != *ptr)
		return !*ptr;
	return *ptr;
}