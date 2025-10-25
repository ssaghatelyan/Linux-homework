CXX = g++
CXXFLAGS = -O2 -Wall -pthread
TARGET = array-summary

all: $(TARGET)

$(TARGET): array-summary.cpp
	$(CXX) $(CXXFLAGS) array-summary.cpp -o $(TARGET)

clean:
	rm -f $(TARGET)
