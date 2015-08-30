CC=g++
CFLAGS=-c -Wall -pg -std=c++0x
LDFLAGS= -pg
SOURCES=main.cpp checkers.cpp TwofoldStarter.cpp tests.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=modStarter_2

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o starters
