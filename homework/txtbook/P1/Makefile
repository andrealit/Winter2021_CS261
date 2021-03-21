CC = g++
exe_file = test

$(exe_file): hello.o
	$(CC) hello.o -o $(exe_file)

hello.o: hello.c
	$(CC) -std=c++11 -c hello.c

clean:
	rm -f *.out *.o $(exe_file)