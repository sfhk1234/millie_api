/**
 *
 *  MySQL.h
 *
 */

#pragma once

#include <drogon/plugins/Plugin.h>
#include <mysql/mysql.h>
#include <regex>
#include <iostream>

class MySQL : public drogon::Plugin<MySQL>
{
  private:
    MYSQL mysql;
    MYSQL *connection;
  public:
    MySQL() {}
    /// This method must be called by drogon to initialize and start the plugin.
    /// It must be implemented by the user.
    void initAndStart(const Json::Value &config) override;
    /// This method must be called by drogon to shutdown the plugin.
    /// It must be implemented by the user.
    void shutdown() override;

    Json::Value runQuery(const std::string& query);
    bool validate_uuid(const std::string& s);
    bool validate_name(const std::string& s);

};

