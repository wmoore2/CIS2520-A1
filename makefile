#William Moore
#1061752
#wmoore02@uoguelph.ca

CC = gcc
CFLAGS = -Wall -pedantic -ansi

ds_array.o: ds_array.c ds_array.h ds_memory.h
	$(CC) $(CLFAGS) -c ds_array.c -o bin/ds_array.o

ds_list.o: ds_list.c ds_list.h ds_memory.h
	$(CC) $(CLFAGS) -c ds_list.c -o bin/ds_list.o

ds_memory.o: ds_memory.c ds_memory.h
	$(CC) $(CLFAGS) -c ds_memory.c -o bin/ds_memory.o

clean:
	rm bin/*

testArray: ds_memory.o ds_array.o ds_memory.h ds_array.h
	$(CC) $(CFLAGS) bin/ds_memory.o bin/ds_array.o -o bin/array

testList: ds_memory.o ds_list.o ds_memory.h ds_list.h
	$(CC) $(CFLAGS) bin/ds_memory.o bin/ds_list.o -o bin/list

list: testList
	./bin/list

array: testArray
	./bin/array