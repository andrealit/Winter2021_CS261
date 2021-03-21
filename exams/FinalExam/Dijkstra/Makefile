default: prog 

dijkstra.o: sinisa_dijkstra.c sinisa_dijkstra.h 
	gcc -Wall -ansi -c sinisa_dijkstra.c

prog: dijkstra.o main.c
	gcc -Wall -ansi -o prog sinisa_dijkstra.o  main.c

clean:
	rm dijkstra.o	

cleanall: clean
	rm prog