CC = g++
CFLAGS 	= -c -Wall -O3 -g  -I ./include/ 

#Include Libs
#include OpenCV
CFLAGS 		+= $(shell pkg-config opencv --cflags) -std=c++11
LDFLAGS 	+= $(shell pkg-config opencv --libs)

SOURCES		= $(wildcard ./src/*.cpp)

OBJECTS		= $(SOURCES:.cpp=.o)

EXECUTABLE 	= heli_detector

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(CURDIR)/$< -o $@

clean: 
	rm -rf ./src/*.o $(EXECUTABLE)

