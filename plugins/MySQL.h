/**
 *
 *  MySQL.h
 *
 */

#pragma once

#include <drogon/plugins/Plugin.h>
#include <mysql.h>


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
};

