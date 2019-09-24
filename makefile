#William Moore
#1061752
#wmoore02@uoguelph.ca

CC = gcc
CFLAGS = -Wall -pedantic -ansi -Ia1

ds_array.o: ds_array.c ds_array.h ds_memory.h
	$(CC) $(CFLAGS) -c ds_array.c -o bin/ds_array.o

ds_list.o: ds_list.c ds_list.h ds_memory.h
	$(CC) $(CFLAGS) -c ds_list.c -o bin/ds_list.o

ds_memory.o: ds_memory.c ds_memory.h
	$(CC) $(CFLAGS) -c ds_memory.c -o bin/ds_memory.o

clean:
	rm bin/*

listMain.o: listMain.c ds_list.h ds_memory.h
	$(CC) $(CFLAGS) -c listMain.c -o bin/listMain.o

arrayMain.o: arrayMain.c ds_array.h ds_memory.h
	$(CC) $(CFLAGS) -c arrayMain.c -o bin/arrayMain.o

testArray: ds_memory.o ds_array.o ds_memory.h ds_array.h arrayMain.o
	$(CC) $(CFLAGS) bin/ds_memory.o bin/ds_array.o bin/arrayMain.o -o bin/array

testList: ds_memory.o ds_list.o ds_memory.h ds_list.h listMain.o
	$(CC) $(CFLAGS) bin/ds_memory.o bin/ds_list.o bin/listMain.o -o bin/list

list: testList
	./bin/list

array: testArray
	./bin/array