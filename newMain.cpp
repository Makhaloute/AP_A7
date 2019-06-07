#include "handlers.hpp"
#include "my_server.hpp"

#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  try {
    Imain* mainInterface;
    MyServer server(argc > 1 ? atoi(argv[1]) : 5000);
    server.setNotFoundErrPage("static/404.html");
 
    server.get("/login", new ShowPage("static/logincss.html"));
    server.post("/login", new LoginHandler(mainInterface));

    server.get("/signup", new ShowPage("static/logincss.html"));
    server.post("/signup", new signupHandler(mainInterface));

    server.get("/addfilm", new ShowPage("static/logincss.html"));
    server.post("/addfilm", new addfilmHandler(mainInterface));

    server.get("/userhome", new ShowPage("static/logincss.html"));
    server.post("/userhome", new userHomeHandler(mainInterface));


    server.get("/profile", new ShowPage("static/logincss.html"));
    server.post("/profile", new profileHandler(mainInterface));

    server.get("/filmdetail", new ShowPage("static/logincss.html"));
    server.post("/filmdetail", new filmDetailHandler(mainInterface));
     server.get("/logout", new logoutHandler());
    server.run();
  } catch (Server::Exception e) {
    cerr << e.getMessage() << endl;
  }
}
