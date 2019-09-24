/*
William Moore
1061752
wmoore02@uoguelph.ca
*/
#include"ds_memory.h"
#include<stdio.h>
#include<stdlib.h>

struct ds_list_item_struct{
	int item;
	long next;
};

int ds_create_list();

int ds_init_list();

int ds_replace(int value, long index);

int ds_insert(int value, long index);

int ds_delete(long index);

int ds_swap(long index1, long index2);

int ds_find(int target);

int ds_read_elements(char* filename);

int ds_finish_list();

struct ds_list_item_struct* ds_read_list(struct ds_list_item_struct* ptr, int index, long* prev);