# makefile
# code compiler to use for compilation
CC=g++
main: main.o
	$(CC) $(CFLAGS) main.o -o run
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp
memtest: main
	valgrind --leak-check=yes ./run
clean:
	rm -f *.o
	rm -f *.out
	rm -f run
run: main
	./run
