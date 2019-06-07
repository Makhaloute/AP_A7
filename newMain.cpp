#include "handlers.hpp"
#include "my_server.hpp"

#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  try {
    MyServer server(argc > 1 ? atoi(argv[1]) : 5000);
    server.setNotFoundErrPage("static/404.html");
 
    server.get("/login", new ShowPage("static/logincss.html"));
    server.post("/login", new LoginHandler());

    server.get("/signup", new ShowPage("static/logincss.html"));
    server.post("/signup", new signupHandler());

    server.get("/addfilm", new ShowPage("static/logincss.html"));
    server.post("/addfilm", new addfilmHandler());

    server.get("/userhome", new ShowPage("static/logincss.html"));
    server.post("/userhome", new userHomeHandler());


    server.get("/profile", new ShowPage("static/logincss.html"));
    server.post("/profile", new profileHandler());

    server.get("/filmdetail", new ShowPage("static/logincss.html"));
    server.post("/filmdetail", new filmDetailHandler());


     server.get("/logout", new logoutHandler());



   // server.get("/up", new ShowPage("static/upload_form.html"));
    //server.post("/up", new UploadHandler());
    
 
   
   // server.get("/home.png", new ShowImage("static/home.png"));
   
  //  server.get("/", new ShowPage("static/home.html"));
   
   // server.get("/colors", new ColorHandler("template/colors.html"));
   

    server.run();
  } catch (Server::Exception e) {
    cerr << e.getMessage() << endl;
  }
}
