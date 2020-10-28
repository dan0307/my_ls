# -*- Makefile -*-

#target: dependecies
#	action

all: my_ls

my_ls: my_ls.o options.o dirContents.o
	gcc -o my_ls my_ls.o options.o dirContents.o -Wall -Wextra -Werror -g3 -fsanitize=address

my_ls.o: my_ls.c 
	gcc -c my_ls.c 

options.o: options.c
	gcc -c options.c 

dirContents.o: dirContents.c
	gcc -c dirContents.c

clean: 
	rm *.o my_ls core.*