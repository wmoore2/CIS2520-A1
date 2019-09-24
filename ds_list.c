/*
William Moore
1061752
wmoore02@uoguelph.ca
*/

#include"ds_list.h"

int main(){
    struct ds_list_item_struct temp = {};
    long pos, elem = 0;
    int i = 0;
    ds_create("list.bin", sizeof(struct ds_list_item_struct) * MAX_BLOCKS);
    printf("Create List: %d\n", ds_create_list());
    printf("Init List: %d\n", ds_init_list());
    //printf("Malloc: %ld\n", ds_malloc(sizeof(long)));
    //printf("Insert: %d\n", ds_insert(120, 0));
    //printf("Insert: %d\n", ds_insert(143, 1));
    //ds_read(&temp, sizeof(long), sizeof(struct ds_list_item_struct));
    //ds_read(&elem, 0, sizeof(long));
    //ds_read_list(&temp, 0, &pos);
    //printf("Item: %d  Next: %ld  Pos: %ld\n", temp.item, temp.next, ds_malloc(sizeof(long)));
    printf("Read_elements: %d\n", ds_read_elements("bin/temp.txt"));
    while(1){

    }
    ds_finish_list();
    return 0;
}

int ds_create_list(){
    long toWrite = -1;
    /*Initialize the file*/
    if(ds_init("list.bin") != 0)
        return -1;
    /*Malloc a long and write -1 to it*/
    if(ds_malloc(sizeof(long)) == -1)
        return -1;

    if(ds_write(0, &toWrite, sizeof(long)) != 0)
        return -1;
    /*Closes file and prints reads/writes*/
    if(ds_finish() != 0)
        return -1;
    return 0;
}

int ds_init_list(){
    /*Open file*/
    if(ds_init("list.bin") != 0)
        return -1;
	return 0;
}

int ds_replace(int value, long index){
    long firstElement, elemPos;
    struct ds_list_item_struct temp;
    /*Read first long to see filesize*/
    if(*(int*)ds_read(&firstElement, 0, sizeof(long)) != firstElement)
        return -1;
    /*Check for invalid index*/
    if(firstElement == -1)
        return -1;
    /*Reads in element to be replaced*/
    if(ds_read_list(&temp, index, &elemPos) == NULL)
        return -1;
    /*Sets new value*/
    temp.item = value;
    /*Writes entire element*/
    if(ds_write(elemPos + sizeof(long), &temp, sizeof(struct ds_list_item_struct)) != 0)
        return -1;

	return 0;
}

int ds_insert(int value, long index){
    long firstElement, next, elemPos;
    struct ds_list_item_struct tempIn, tempOut;
    if(index < 0)
        return -1;
    /*index = 0 case*/
    if(index == 0){
        /*Read first long to see first entry location*/
        if(*(int*)ds_read(&firstElement, 0, sizeof(long)) != firstElement)
            return -2;
        /*builds struct to write*/
        tempOut.item = value;
        tempOut.next = firstElement;
        /*allocating space for new entry*/
        firstElement = ds_malloc(sizeof(struct ds_list_item_struct));
        if(firstElement == -1)
            return -3;
        /*Write new first element position*/
        if(ds_write(0, &firstElement, sizeof(long)) != 0)
            return -4;
        /*write inserted entry*/
        if(ds_write(firstElement, &tempOut, sizeof(struct ds_list_item_struct)) != 0)
            return -5;
    } else {
        /*reads in entry before the entry to be inserted*/
        if(ds_read_list(&tempIn, index - 1, &elemPos) == NULL)
            return -6;
        /*building the struct to write*/
        tempOut.item = value;
        tempOut.next = tempIn.next;
        /*Allocating space for new entry*/
        next = ds_malloc(sizeof(struct ds_list_item_struct));
        if(next == -1)
            return -7;
        /*altering the previous struct before writing it*/
        tempIn.next = next;
        if(ds_write(elemPos, &tempIn, sizeof(struct ds_list_item_struct)) != 0)
            return -8;
        /*write inserted entry*/
        if(ds_write(next, &tempOut, sizeof(struct ds_list_item_struct)) != 0)
            return -9;
    }
	return 0;
}

int ds_delete(long index){
    long firstElement, elemPos;
    struct ds_list_item_struct temp1, temp2;
    if(index < 0)
        return -1;

    if(index == 0){
        /*Delete 0th element*/
        /*Read in 0th element*/
        if(ds_read_list(&temp1, index, &elemPos) == NULL)
            return -1;
        /*frees element*/
        ds_free(firstElement);
        firstElement = temp1.next;
        /*Write new first element into the first position*/
        if(ds_write(0, &firstElement, sizeof(long)) != 0)
            return -1;

    } else {
        /*Delete index element*/
        /*Read in element to be deleted*/
        if(ds_read_list(&temp1, index, &elemPos) == NULL)
            return -1;
        /*Read in prior element*/
        if(ds_read_list(&temp2, index - 1, &elemPos) == NULL)
            return -1;
        /*Freeing and removing temp1 from the list*/
        ds_free(temp2.next);
        temp2.next = temp1.next;
        /*Write out new prior entry, pointing past the deleted entry*/
        if(ds_write(elemPos, &temp2, sizeof(struct ds_list_item_struct)) != 0)
            return -1;
    }
	return 0;
}

int ds_swap(long index1, long index2){
    long elemPos1, elemPos2;
    int temp;
    struct ds_list_item_struct elem1, elem2;
    /*Check for proper indicies*/
    if(index1 < 0 || index2 < 0)
        return -1;
    /*Read in elements*/
    if(ds_read_list(&elem1, index1, &elemPos1) == NULL)
        return -1;
    if(ds_read_list(&elem2, index2, &elemPos2) == NULL)
        return -1;
    /*swap*/
    temp = elem1.item;
    elem1.item = elem2.item;
    elem2.item = temp;
    /*Write elements back into file*/
    if(ds_write(elemPos1, &elem1, sizeof(struct ds_list_item_struct)) != 0)
        return -1;
    if(ds_write(elemPos2, &elem2, sizeof(struct ds_list_item_struct)) != 0)
        return -1;
	return 0;
}

int ds_find(int target){
    long next;
    int index = 0;
    struct ds_list_item_struct elem;

    /*Read first long to see first entry location*/
    if(*(int*)ds_read(&next, 0, sizeof(long)) != next)
        return -1;

    while(1){
        /*Read in element*/
        if((struct ds_list_item_struct*)ds_read(&elem, next + sizeof(long), sizeof(struct ds_list_item_struct)) != &elem)
            return -1;
        /*Checks for correct value*/
        if(elem.item == target)
            return index;
        /*Check for end of file*/
        if(elem.next == -1 || elem.next == 0)
            return -1;
        /*run er again*/
        next = elem.next;
        index++;
    }
	return -1;
}

int ds_read_elements(char *filename){
    int index = 0, temp = 0;
    FILE *fp;
    if((fp = fopen(filename, "r")) == NULL){
        return -2;
    }
    /*Loops through entire file*/
    while(fscanf(fp, "%d", &temp) != EOF){
        /*Inserts read in character into array*/
        if(ds_insert(temp, index) != 0)
            return -1;
        index++;
    }
    fclose(fp);
    return 0;
}

int ds_finish_list(){
	return ds_finish();
}

struct ds_list_item_struct* ds_read_list(struct ds_list_item_struct* ptr, int index, long* prev){
    long next = 0;
    int i = 0;
    /*Gets first element location*/
    if(*(int*)ds_read(&next, 0, sizeof(long)) != next)
        return NULL;
    /*Set values for prev. This pointer stores the position of the struct being returned*/
    *prev = -1;
    /*Move through the list and find given index*/
    for(i = 0; i <= index; i++){
        /*Read in next item*/
        if((struct ds_list_item_struct*)ds_read(ptr, next, sizeof(struct ds_list_item_struct)) != ptr)
            return NULL;
        /*Change next position to check, set the prev value*/
        *prev = next;
        next = (*ptr).next;
        if((*ptr).next == 0)
            return NULL;
        /*Check if it is the correct item*/
        if(i == index)
            return ptr;
        /*Checks for index being out of bounds*/
        if((*ptr).next == -1)
            return NULL;
    }
    /*Returns NULL if nothing is found*/
    return NULL;
}