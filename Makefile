server: server.o dijkstra.o digraph.o
	g++ server.o dijkstra.o digraph.o -o server

dijkstra.o: dijkstra.h dijkstra.cpp
	g++ -c dijkstra.cpp -o dijkstra.o

digraph.o: digraph.cpp digraph.h
	g++ -c digraph.cpp -o digraph.o

server.o: server.cpp wdigraph.h
	g++ -c server.cpp -o server.o

clean:
	rm *.o server
