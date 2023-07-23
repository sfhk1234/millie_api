#include <drogon/drogon.h>
#include <mysql.h>
#include <cstdlib>

int main() {
    drogon::app().loadConfigFile("../config.json");
  
    int port = atoi(std::getenv("PORT"));
    port = port == 0 ? 1477 : port;

    LOG_INFO << "Listening at 0.0.0.0:" << port;
    //Set HTTP listener address and port
    drogon::app().addListener("0.0.0.0", port);
    //Load config file
    //Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();
    return 0;
}
