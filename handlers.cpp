#include "handlers.hpp"

using namespace std;

Response *LoginHandler()::callback(Request *req , Imain mainInterface){
  if(mainInterface->login(req->getQueryParam("name"),req->getQueryParam("password"))){
    Response *res = Response::redirect("/userhome");
    string id = stoi(mainInterface->returnId());
    res->setSessionId(id);
    return res;
  }
  throw Server::Exception();
} 


Response *signupHandler()::callback(Request *req , Imain mainInterface){
  int type = 0;
  if (req->getQueryParam("type") == "publisher"){
    type = 1;
  }


 std::map<string, string> map = {{"age",req->getQueryParam("age")} }


  if(mainInterface->signup(req->getQueryParam("name"), map <string,string> carectristics,Type)){

  }



  req->getQueryParam("password")
req->getQueryParam("mail")
req->getQueryParam("type")




  req->getBodyParam("file_name")
req->getBodyParam("file")

}




Response *addfilmHandler()::callback(Request *req , Imain mainInterface){}
Response *userHomeHandler()::callback(Request *req , Imain mainInterface){}
Response *profileHandler()::callback(Request *req , Imain mainInterface){}
Response *filmDetailHandler()::callback(Request *req , Imain mainInterface){}
Response *logoutHandler()::callback(Request *req , Imain mainInterface){}















Response *RandomNumberHandler::callback(Request *req) {
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1>AP HTTP</h1>";
  body += "<p>";
  body += "a random number in [1, 10] is: ";
  body += to_string(rand() % 10 + 1);
  body += "</p>";
  body += "<p>";
  body += "SeddionId: ";
  body += req->getSessionId();
  body += "</p>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *LoginHandler::callback(Request *req) {
  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");
  if (username == "root")
    throw Server::Exception("Remote root access has been disabled.");
  cout << "username: " << username << ",\tpassword: " << password << endl;
  Response *res = Response::redirect("/rand");
  res->setSessionId("SID");
  return res;
}

Response *UploadHandler::callback(Request *req) {
  string name = req->getBodyParam("file_name");
  string file = req->getBodyParam("file");
  cout << name << " (" << file.size() << "B):\n" << file << endl;
  Response *res = Response::redirect("/");
  return res;
}

LoginHandler::LoginHandler(string filePath) : TemplateHandler(filePath) {}

map<string, string> LoginHandler::handle(Request *req) {
  map<string, string> context;
  string newName = "I am " + req->getQueryParam("name");
  context["name"] = newName;
  context["color"] = req->getQueryParam("color");
  return context;
}
