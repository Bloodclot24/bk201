#include "Socket.h"
#include <unistd.h>
#include <fcntl.h> 
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>


/* Crea un nuevo socket con la direccion de destino y puerto dados */
Socket::Socket(std::string direccion, int puerto){
  int puertoFinal=puerto;
  error = 0;
  timeout = 0;
  s=socket(AF_INET, SOCK_STREAM, 0);
  if(s == -1)
    error=errno;
  else{
    std::string hostName=direccion;
    size_t inicio=0,fin=0,limite=0;
    limite = direccion.find('.');
    inicio = direccion.find("://");
    fin = direccion.find_first_of(":/", limite);
	       
    if(inicio != std::string::npos && fin != std::string::npos){
      hostName= direccion.substr(inicio+3,fin-(inicio+3));
      if(direccion[fin] == ':'){
	puertoFinal = atoi(direccion.c_str()+fin+1);
      }
    }
    else{ 
      fin = direccion.find_first_of(":");
      hostName = direccion.substr(0,fin);
      if(direccion[fin] == ':'){
	puertoFinal = atoi(direccion.c_str()+fin+1);
      }
      else hostName = direccion;
    }
	  
    host=gethostbyname(hostName.c_str());
	       
    if(host == NULL){
      error = errno;
      return;
    }

    direccionDestino.sin_family = AF_INET; 
    /* usa host byte order */
	  
    direccionDestino.sin_port = htons(puertoFinal); 
    /* usa network byte order */
	  
    bzero(&(direccionDestino.sin_zero), 8); 
    /* pone en cero el resto */
  }
}

/* Hace que el socket escuche conexiones en su puerto */
bool Socket::enlazar(void){
  direccionDestino.sin_addr.s_addr = INADDR_ANY;
  int retorno = bind(s,					\
		     (struct sockaddr*)&direccionDestino,	\
		     sizeof(struct sockaddr));
  if (retorno != 0)
    error = errno;
  return esValido();
}

/* Acepta un socket que se quiere conectar */
Socket* Socket::aceptar(void){
  int sckfd = accept(s,NULL,0); 
  if (sckfd == -1) return NULL;
  return new Socket(sckfd);
}

/* Espera a que algun socket quiera conectarse a este */
bool Socket::escuchar(void){
  int retorno = listen(s, 20);
  if(retorno == -1)
    error = errno;
  return esValido();
}

/* Envia un buffer de una cierta longitud por el socket */
bool Socket::enviar(const void *buf, int longitud){
  int retorno = send(s,buf,longitud,MSG_NOSIGNAL);
  //MSG_NOSIGNAL, evita que se reciba SIGPIPE

  if(retorno == -1)
    error = errno;

     
  return esValido();
}
     
/* Recibe la cantidad de bytes pedidos en el buffer */
int Socket::recibir(void *buf, int cuanto){
  int recibido = recv(s, buf, cuanto, MSG_WAITALL);

  if(recibido < cuanto){
    invalidar();
  }
     
  return recibido;
}
     

/* Conecta al socket a la direccion y puerto dados en el constructor */
bool Socket::conectar(void){
  if(!esValido())
    return esValido();
  if(host == NULL){
    error = -1;
    return false;
  }
  direccionDestino.sin_addr = *((struct in_addr *)host->h_addr);

  int retorno=connect(s,(struct sockaddr*)&direccionDestino,sizeof(direccionDestino));

  if(retorno == -1)
    error = errno;
	  
  return esValido(); 
}

bool Socket::conectar(int timeout){
  setNoBloqueante();
  int estado = conectar();
  if(estado == EINPROGRESS || estado==0){
    error = 0;
    if(seleccionar(timeout)<=0){
      error = errno;
    }
  }
  else{
    error = errno;
  }
  setBloqueante();
  return esValido();
}

int Socket::seleccionar(int tiempo){
  struct timeval tv; 
  tv.tv_sec = tiempo;
  tv.tv_usec = 0;
  fd_set myset;
  FD_ZERO(&myset);
  FD_SET(s, &myset);
  return select(s+1, NULL, &myset, NULL, &tv);
}

bool Socket::setNoBloqueante(){
  // Set non-blocking 
  long arg = fcntl(s, F_GETFL, NULL); 
  arg |= O_NONBLOCK; 
  fcntl(s, F_SETFL, arg); 
  return true;
}

bool Socket::setBloqueante(){
  // Set blocking 
  long arg = fcntl(s, F_GETFL, NULL); 
  arg &= ~O_NONBLOCK; 
  fcntl(s, F_SETFL, arg); 
  return true;
}


/* Cierra el socket, lo desconecta */
bool Socket::cerrar(void){
  int retorno=0;
  if(s > 0 ){
    shutdown(s,SHUT_RDWR);
    retorno = close(s);
  }
  s=-1;
  if(retorno == -1)
    error = errno;
  return esValido();
}

/* Pone un timeout al socket tanto para recepcion de datos como
 * para emision de los mismos. */
void Socket::setTimeout(int seg, int useg){
  struct timeval tiempo;
  tiempo.tv_sec= seg;
  tiempo.tv_usec= useg;
  setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char*)&tiempo, sizeof(tiempo));
  setsockopt(s, SOL_SOCKET, SO_SNDTIMEO, (char*)&tiempo, sizeof(tiempo));
}

/* Indica si se produjo algun error durante la ultima operacion */
bool Socket::esValido(void){
  return (error==0);
}

/* resetea el estado del socket a valido */
void Socket::revalidar(void){
  error = 0;
}

/* setea el estado del socket a invalido */
void Socket::invalidar(void){
  error = -1;
}


/* Devuelve la descripcion del ultimo error */
const std::string& Socket::obtenerError(void){
  ultimoError.clear();
  ultimoError.insert(0, strerror(error));
  return ultimoError;
}


/* Cierra y libera el socket */
Socket::~Socket(){
  if(s > 0)
    cerrar();
}
