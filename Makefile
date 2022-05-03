stack.exe: main.o
	g++ -std=c++0x main.o -o stack.exe

main.o: main.cpp
	g++ -std=c++0x -c main.cpp -o main.o

.PHONY: clean
clean:
	rm *.exe *.o
