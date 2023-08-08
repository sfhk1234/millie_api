#pragma once

#include <drogon/HttpController.h>
#include <cctype>
#include <iostream>

using namespace drogon;

namespace v1
{
  struct UserModel
  {
    std::string name;
    std::string id;
  };

class User : public drogon::HttpController<User>
{
  public:
    METHOD_LIST_BEGIN
    // use METHOD_ADD to add your custom processing function here;
    // METHOD_ADD(User::get, "/{2}/{1}", Get); // path is /v1/User/{arg2}/{arg1}
    // METHOD_ADD(User::your_method_name, "/{1}/{2}/list", Get); // path is /v1/User/{arg1}/{arg2}/list
      ADD_METHOD_TO(User::getUser, "/v1/users/{1}", Get); // path is /absolute/path/{arg1}/{arg2}/list
      ADD_METHOD_TO(User::getUsers, "/v1/users", Get);
      ADD_METHOD_TO(User::createUser, "/v1/users", Post);
      //ADD_METHOD_TO();
    METHOD_LIST_END

    void getUser(const HttpRequestPtr& req, 
                 std::function<void (const HttpResponsePtr &)> 
                 &&callback, std::string user_id); 
    
    void getUsers(const HttpRequestPtr& req, 
                 std::function<void (const HttpResponsePtr &)> 
                 &&callback);

    void createUser(const HttpRequestPtr &req,
                std::function<void (const HttpResponsePtr &)> &&callback,
                UserModel &&newUser);
    // your declaration of processing function maybe like this:
    // void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int p1, std::string p2);
    // void your_method_name(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, double p1, int p2) const;
    
};
}
namespace drogon
{
  template <>
  inline v1::UserModel fromRequest(const HttpRequest &req)
  {
    auto json = req.getJsonObject();
    v1::UserModel user;
    LOG_DEBUG << json->toStyledString();
    if(json)
    {
      user.name = (*json)["name"].asString();
      user.id = (*json)["id"].asString();
    }
    return user; 
  }
}
