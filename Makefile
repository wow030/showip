showip: main.o
	g++ -o showip main.o
main.o: main.cpp
	g++ -c main.cpp
clean:
	rm -rf *.o