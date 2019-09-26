all: myTestCaesar.o
	g++ caesar.o myTestCaesar.o -o test

myTestCaesar.o: caesar.o myTestCaesar.cpp
	g++ -c myTestCaesar.cpp

caesar.o: caesar.cpp caesar.h
	g++ -c caesar.cpp

clean: 
	rm -rf *.o
