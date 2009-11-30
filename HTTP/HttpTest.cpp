#include "HttpRequest.h"
#include "HttpResponse.h"

int main(int argc, char** argv){

  /* Creo un nuevo request */
  HttpRequest req("192.168.0.10:8080/algo");

  req.setContentLength(100);
  /* Obtengo el request completo y lo muestro */
  const std::string &request = req.getRequest();
  std::cout << request;

  HttpRequest decode(request,1);

  HttpResponse res(200);

  res.setContentLength(50);

  std::string &response = res.getResponse();
  std::cout << "\n"<<response;

  HttpResponse resDeco(response);
   
  return 0;
}

