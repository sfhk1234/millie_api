#include "v1_User.h"
#include "plugins/MySQL.h"

using namespace v1;
using namespace drogon;



// Add definition of your processing function here
void User::getUser(
  const HttpRequestPtr& req, 
  std::function<void (const HttpResponsePtr &)> &&callback, 
  std::string user_id) 
  {
    //Authentication algorithm, read database, verify, identify, etc...
    auto *db = app().getPlugin<MySQL>();

    if(!db->validate_uuid(user_id)) 
    {
      Json::Value result;
      result["status"]=400;
      result["message"]="id is not a uuid";
      auto resp=HttpResponse::newHttpJsonResponse(result);
      resp->setStatusCode(k400BadRequest);
      return callback(resp);
    }
    
    // user_id uuid 무조건 맞음
    auto result = db->runQuery("SELECT * FROM users WHERE id = \"" + user_id + "\"");
    Json::Value ret;
    ret["status"]=200;
    ret["result"]=result;
    LOG_DEBUG << "CORRECT";
    auto resp=HttpResponse::newHttpJsonResponse(ret);
    resp->setStatusCode(k400BadRequest);
    callback(resp);
  }

void User::getUsers(
  const HttpRequestPtr& req, 
  std::function<void (const HttpResponsePtr &)> &&callback)
  {
    auto *db = app().getPlugin<MySQL>();

    // table_name users 맞음
    auto result = db->runQuery("SELECT * FROM users");
    Json::Value ret;
    ret["status"]=200;
    ret["result"]=result;
    LOG_DEBUG << "CORRECT";
    auto resp=HttpResponse::newHttpJsonResponse(ret);
    resp->setStatusCode(k400BadRequest);
    callback(resp);
  }


  void User::createUser(const HttpRequestPtr &req,
                std::function<void (const HttpResponsePtr &)> &&callback,
                UserModel &&newUser)
    {
      auto *db = app().getPlugin<MySQL>();

      if(!db->validate_name(newUser.name.c_str())) 
      {
        Json::Value result;
        result["status"]=400;
        result["message"]="Special characters are not allowed.";
        auto resp=HttpResponse::newHttpJsonResponse(result);
        resp->setStatusCode(k400BadRequest);
        return callback(resp);
      }

      auto result = db->runQuery(std::string("INSERT INTO users (name) VALUES") + " (\"" + newUser.name.c_str() + "\")");
      Json::Value ret;
      ret["status"]=200;
      ret["result"]=result;
      LOG_DEBUG << "CORRECT";
      auto resp=HttpResponse::newHttpJsonResponse(ret);
      resp->setStatusCode(k400BadRequest);
      callback(resp);
      LOG_DEBUG << newUser.name;
      return;
    }