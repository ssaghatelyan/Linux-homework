CC = g++
CFLAGS = -std=c++17 -O2 -Wall
TARGET = hacker-rm
SRCS = hacker-rm.cpp

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)
