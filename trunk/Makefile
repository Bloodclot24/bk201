SOURCES=Controlador/controlador.cpp \
	Vista/VentanaTrabajo.cpp \
	Red/Socket.cpp \
	HTTP/HttpRequest.cpp \
	HTTP/HttpResponse.cpp \
	XML/Xml.cpp \
	XML/Soap.cpp \
	Util/Util.cpp \
	Vista/AreaDibujo.cpp \
	Vista/AreaDibujoGenerica.cpp \
	Red/Mensajero.cpp \
	Threads/ThreadAceptor.cpp \
	Server/Server.cpp \
	Vista/Dibujos/CompuertaBuffer.cpp \
	Vista/Dibujos/CompuertaXor.cpp \
	Vista/Dibujos/CompuertaAnd.cpp \
	Vista/Dibujos/CompuertaNot.cpp \
	Vista/Dibujos/CompuertaOr.cpp \
	Vista/Dibujos/Compuerta.cpp \
	Vista/Dibujos/EntradaSalida.cpp \
	Vista/Dibujos/Circuito.cpp \
	Vista/Dibujos/Conexion.cpp \
	Vista/Dibujos/Dibujo.cpp \
	Controlador/ControladorVentana.cpp \
	Vista/Tabla.cpp \
	Threads/ThreadListado.cpp \
	Vista/CircuitoRemoto.cpp \
	Threads/ThreadObtenerCircuito.cpp \
	Threads/ThreadLimpieza.cpp \
	Threads/ThreadSimulador.cpp \
	Vista/Impresion/VentanaImpresion.cpp \
	Vista/Impresion/Impresora.cpp \
	Circuito/CircuitoRemotoServidor.cpp

TESTSOURCES=Gates/testGates.cpp \
	Circuito/testCircuito.cpp \
	Circuito/testCircuitoCompuesto.cpp \
	HTTP/HttpTest.cpp \
	HTTP/HttpSoapTest.cpp \
	XML/testSoap.cpp \
	main.cpp \
	Server/testServer.cpp\
	Server/testCliente.cpp\
	Circuito/testCircuitoRemotoCl.cpp\
	Circuito/testCircuitoRemotoSr.cpp

MAIN=main.cpp
SERVIDOR=Server/testServer.cpp

CFLAGS+=-g3 -Wall -O0 `pkg-config --cflags gdkmm-2.4 gtkmm-2.4 gthread-2.0 libxml-2.0`
LDFLAGS=`pkg-config --libs gdkmm-2.4 gtkmm-2.4 gthread-2.0 libxml-2.0`
CC=g++
EXECUTABLE=bk201
EXECUTABLESERVIDOR=bk201_server

OBJECTS=$(SOURCES:.cpp=.o)
TESTOBJECTS=$(TESTSOURCES:.cpp=.o)
MAINSOURCES=$(SOURCES) $(MAIN)
MAINSERVIDOROBJECTS=$(SERVIDOR:.cpp=.o) $(OBJECTS)
MAINSERVIDORSOURCES=$(SOURCES) $(SERVIDOR)
MAINOBJECTS=$(MAIN:.cpp=.o) $(OBJECTS)
ALLOBJECTS=$(MAINOBJECTS) $(MAINSERVIDOROBJECTS) $(TESTOBJECTS)
TESTEXEC=$(TESTSOURCES:.cpp=)

PREFIX=~/
PROGNAME=Bk201
BASEDIR=$(PREFIX)/$(PROGNAME)

all: $(MAINSOURCES) $(EXECUTABLE) $(EXECUTABLESERVIDOR)

$(EXECUTABLE): $(MAINOBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(MAINOBJECTS) -o $@

$(EXECUTABLESERVIDOR): $(MAINSERVIDOROBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(MAINSERVIDOROBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TESTSOURCES) $(TESTEXEC)

$(TESTEXEC): $(TESTOBJECTS) $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) $@.o -o $@

clean:
	rm -f $(ALLOBJECTS) $(EXECUTABLE) $(TESTEXEC) 

prueba: $(MAINSOURCES) $(EXECUTABLE)
	$(CC) $(CFLAGS) $(LDFLAGS) $(SOURCES) $(MAIN) -o $(EXECUTABLE)

install: all
	mkdir -p $(BASEDIR)
	mkdir -p $(BASEDIR)/Vista
	cp -r -f Vista/Imagenes/ $(BASEDIR)/Vista
	cp Vista/interfaz.glade $(BASEDIR)/Vista
	cp $(EXECUTABLE) $(BASEDIR)
	cp $(EXECUTABLESERVIDOR) $(BASEDIR)
	strip $(BASEDIR)/$(EXECUTABLE)
	strip $(BASEDIR)/$(EXECUTABLESERVIDOR)

uninstall:
	rm -r -f $(BASEDIR)