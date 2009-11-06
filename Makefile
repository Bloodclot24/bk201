SOURCES=Controlador/controlador.cpp \
	Vista/ventanaTrabajo.cpp \
	Red/Socket.cpp \
	HTTP/HttpRequest.cpp \
	HTTP/HttpResponse.cpp \
	XML/Xml.cpp \
	XML/Soap.cpp \
	Util/Util.cpp \
	Vista/areaDibujo.cpp \
	Red/Mensajero.cpp

TESTSOURCES=Gates/testGates.cpp \
	Circuito/testCircuito.cpp \
	Circuito/testCircuitoCompuesto.cpp \
	HTTP/HttpTest.cpp \
	HTTP/HttpSoapTest.cpp \
	XML/testSoap.cpp \
	main.cpp \
	Server/Server.cpp\
	Server/testCliente.cpp

MAIN=AlgunNombre.cpp

CFLAGS=-g -Wall `pkg-config --cflags gtkmm-2.4 gthread-2.0 libxml-2.0`
LDFLAGS=`pkg-config --libs gtkmm-2.4 gthread-2.0 libxml-2.0`
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