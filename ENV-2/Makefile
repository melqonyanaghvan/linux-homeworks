all: main.o complex.o sort.o end remove
	
main.o: main.cpp
	g++ -c  main.cpp
	
complex.o: complex.cpp
	g++ -c complex.cpp
sort.o: sort.cpp
	g++ -c sort.cpp
	
end:
	g++ main.o complex.o sort.o -o main

remove:
	rm -f *.o
