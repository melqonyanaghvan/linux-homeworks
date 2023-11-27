all: array-summary

array-summary: array-summary.o
	g++ array-summary.o -o array-summary

array-summary.o: array-summary.cpp
	g++ -c array-summary.cpp -o array-summary.o

clear:
	rm *.array-summary
