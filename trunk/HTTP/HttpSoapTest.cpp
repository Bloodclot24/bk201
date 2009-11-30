#include "HttpRequest.h"
#include "HttpResponse.h"

#include "../XML/Soap.h"

int main(int argc, char** argv){

  std::cout << "Request:____________________________\n";

  /* Creo un nuevo request */
  HttpRequest req("192.168.0.10:8080/algo");

  Soap mensaje("Prueba1");
  mensaje.setParametro("Parametro1", "valor1");

  std::string *s = mensaje.toString();

  req.setContentLength(s->length());
  /* Obtengo el request completo y lo muestro */
  std::string &request = req.getRequest();
  std::cout << request;
  std::cout << *s << std::endl;

  std::cout << "Fin Request:________________________\n";

  HttpRequest deco(request,1);

  std::cout << "Fin decodificacion Request__________\n";

  HttpResponse res(200);

  res.setContentLength(s->length());

  std::string &response = res.getResponse();
  std::cout << "\n"<<response << *s << std::endl;

  HttpResponse resDeco(response);

  delete s;   

  return 0;
}

