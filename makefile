#William Moore
#1061752
#wmoore02@uoguelph.ca

CC = gcc
CFLAGS = -Wall -pedantic -ansi

ds_array.o: ds_array.c ds_array.h ds_memory.h
	$(CC) $(CLFAGS) ds_array.c -o bin/ds_array.o

ds_list.o: ds_list.c ds_list.h ds_memory.h
	$(CC) $(CLFAGS) ds_list.c -o bin/ds_list.o

ds_memory.o: ds_memory.c ds_memory.h
	$(CC) $(CLFAGS) ds_memory.c -o bin/ds_memory.o

clean:
	rm bin/*