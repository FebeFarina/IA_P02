CC = g++
CFLAGS = -Wall

astar: main.cc grid.o node.o
	$(CC) $(CFLAGS) -o astar main.cc grid.o node.o

grid.o: grid.cc grid.h
	$(CC) $(CFLAGS) -c grid.cc grid.h function.h

node.o: node.cc node.h
	$(CC) $(CFLAGS) -c node.cc node.h

clean:
	rm -rf *.o
	rm -rf salida.txt
	rm -rf astar
	rm -rf *.gch