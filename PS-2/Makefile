CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
TARGET = interactive-shell
SOURCES = shell.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

all: $(TARGET)

clean:
	rm -f $(TARGET) *.log

.PHONY: all clean
