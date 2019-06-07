#include "handlers.hpp"

using namespace std;

Response *LoginHandler()::callback(Request *req , Imain* mainInterface){
  if(mainInterface->login(req->getQueryParam("name"),req->getQueryParam("password"))){
    Response *res = Response::redirect("/userhome");
    string id = stoi(mainInterface->returnId());
    res->setSessionId(id);
    return res;
  }
  throw Server::Exception();
} 

Response *signupHandler()::callback(Request *req , Imain* mainInterface){
  int type = 0;
  if (req->getQueryParam("type") == "publisher"){
    type = 1;
  }
  std::map<string, string> characteristics;
  characteristics.insert ( std::pair<string,string>("name",req->getQueryParam("name")) );
  characteristics.insert ( std::pair<string,string>("age",req->getQueryParam("age")) );
  characteristics.insert ( std::pair<string,string>("password",req->getQueryParam("password")) );
  characteristics.insert ( std::pair<string,string>("mail",req->getQueryParam("mail")) );
  characteristics.insert ( std::pair<string,string>("type",req->getQueryParam("type")) );
  if(mainInterface->signup(req->getQueryParam("name"),characteristics,Type)){
    Response *res = Response::redirect("/userhome");
    string id = stoi(mainInterface->returnId());
    res->setSessionId(id);
    return res;
  }
  else{
    throw Server::Exception();
  }
}


Response *addfilmHandler()::callback(Request *req , Imain* mainInterface){
  std::map<string, string> details;
  details.insert ( std::pair<string,string>("name",req->getQueryParam("name")) );
  details.insert ( std::pair<string,string>("price",req->getQueryParam("price")) );
  details.insert ( std::pair<string,string>("director",req->getQueryParam("director")) );
  details.insert ( std::pair<string,string>("length",req->getQueryParam("length")) );
  details.insert ( std::pair<string,string>("year",req->getQueryParam("year")) );
  details.insert ( std::pair<string,string>("summery",req->getQueryParam("summery")) );
  if(mainInterface->addFilm(stoi(req->getSessionId()),details)){
    Response *res = Response::redirect("/userhome");
    return res;
  }
  else{
    throw Server::Exception();
  }
}


