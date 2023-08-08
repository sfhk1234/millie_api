#include <drogon/drogon.h>
#include <mysql/mysql.h>
#include <cstdlib>

#include "controllers/v1/users/v1_User.h"

#define PORT 1477

void setCustom404() {
    Json::Value result;
    result["status"] = 404;
    result["message"] = "Not Found";
    drogon::app().setCustom404Page(drogon::HttpResponse::newHttpJsonResponse(result));
}

int getPort() {
    const char *portStr = std::getenv("PORT");
    if(portStr == nullptr) return PORT;
    const int port = atoi(portStr);
    if(port == 0) return PORT;
    return port;
}

int main() {
    LOG_INFO << "Initializing...";
    drogon::app().loadConfigFile("../config.json");
  
    int port = getPort();
    setCustom404();
    LOG_INFO << "Listening at 0.0.0.0:" << port;
    //Set HTTP listener address and port
    drogon::app().addListener("0.0.0.0", port);
    //Load config file
    //Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();
    return 0;
}
