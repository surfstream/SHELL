CC= gcc
CFLAGS= -Wall -std=c99 -pedantic
project1:project1.c
	$(CC) $(CFLAGS) project1.c -o project1
myls:myls.c
	$(CC) $(CFLAGS) myls.c -o myls
execute:
	./project1
	  
clean:
	rm -rf project1 myls
