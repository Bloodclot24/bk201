SOURCES=

TESTSOURCES=Gates/testGates.cpp \
	Circuito/testCircuito.cpp \
	Circuito/testCircuitoCompuesto.cpp

MAIN=AlgunNombre.cpp

CFLAGS=-g -Wall
LDFLAGS=
CC=g++
EXECUTABLE=AlgunNombre

OBJECTS=$(SOURCES:.cpp=.o)
TESTOBJECTS=$(TESTSOURCES:.cpp=.o)
MAINSOURCES=$(SOURCES) $(MAIN)
MAINOBJECTS=$(MAIN:.cpp=.o) $(OBJECTS)
ALLOBJECTS=$(MAINOBJECTS) $(TESTOBJECTS)
TESTEXEC=$(TESTSOURCES:.cpp=)

all: $(MAINSOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(MAINOBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(MAINOBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TESTSOURCES) $(TESTEXEC)

$(TESTEXEC): $(TESTOBJECTS) $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) $@.o -o $@

clean:
	rm -f $(ALLOBJECTS) $(EXECUTABLE) $(TESTEXEC)