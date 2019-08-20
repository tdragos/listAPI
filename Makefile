list: main.c list.c
	gcc -pthread -g -Wall list.c main.c -o list

clean:
	rm list
