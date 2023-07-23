#include <drogon/drogon.h>
#include <mysql.h>
#include <cstdlib>

#include "controllers/v1/users/v1_User.h"

void setCustom404() {
    Json::Value result;
    result["status"] = 404;
    result["message"] = "Not Found";
    drogon::app().setCustom404Page(drogon::HttpResponse::newHttpJsonResponse(result));
}

int main() {
    LOG_INFO << "Initializing...";
    drogon::app().loadConfigFile("../config.json");
  
    const char *portStr = std::getenv("PORT");
    int port = portStr == nullptr ? 1477 : atoi(portStr) == 0 ? 1477 : atoi(portStr);
    setCustom404();
    LOG_INFO << "Listening at 0.0.0.0:" << port;
    //Set HTTP listener address and port
    drogon::app().addListener("0.0.0.0", port);
    //Load config file
    //Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();
    return 0;
}
