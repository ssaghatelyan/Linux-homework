TARGET = Complex
CC = g++
CXXFLAGS = -std=c++11 -Wall -O2

all: $(TARGET)

main.o: main.cpp Complex.h sort_complex.h
	$(CC) $(CXXFLAGS) -c main.cpp -o main.o

Complex.o: Complex.cpp Complex.h
	$(CC) $(CXXFLAGS) -c Complex.cpp -o Complex.o

sort_complex.o: sort_complex.cpp sort_complex.h Complex.h
	$(CC) $(CXXFLAGS) -c sort_complex.cpp -o sort_complex.o

$(TARGET): main.o Complex.o sort_complex.o
	$(CC) main.o Complex.o sort_complex.o -o $(TARGET)

clean:
	rm -f *.o $(TARGET)
