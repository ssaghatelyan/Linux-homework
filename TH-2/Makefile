CXX=g++
CXXFLAGS=-O2 -Wall -pthread
TARGET=demo-application
LIB=libparallel_scheduler.so

all: $(LIB) $(TARGET)

$(LIB): parallel_scheduler.cpp parallel_scheduler.h
	$(CXX) $(CXXFLAGS) -fPIC -shared -o $(LIB) parallel_scheduler.cpp

$(TARGET): demo-application.cpp $(LIB)
	$(CXX) $(CXXFLAGS) demo-application.cpp -L. -lparallel_scheduler -Wl,-rpath=. -o $(TARGET)

run: all
	LD_LIBRARY_PATH=.:$$LD_LIBRARY_PATH ./$(TARGET)

clean:
	rm -f $(TARGET) $(LIB)
