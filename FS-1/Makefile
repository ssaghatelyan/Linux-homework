CXX = g++
CXXFLAGS = -Wall -Wextra -o2 -std=c++17

TARGET = read-file

all: $(TARGET)

$(TARGET): read-file.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) read-file.cpp

clean:
	rm -f $(TARGET)
