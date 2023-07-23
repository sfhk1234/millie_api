/**
 *
 *  MySQL.cc
 *
 */

#include "MySQL.h"

using namespace drogon;

void MySQL::initAndStart(const Json::Value &config)
{
    LOG_INFO << "Creating a database connection";
    mysql_init(&this->mysql);
    this->connection = mysql_real_connect(
        &mysql, 
        std::getenv("DB_HOST"),
        std::getenv("DB_USER"),
        std::getenv("DB_PASSWORD"),
        std::getenv("DB_NAME"),
        3306, 
        nullptr,
        0
    );
    if(connection == nullptr) {
        LOG_ERROR << "Unable to create a database connection";
        exit(1);
    }
    LOG_INFO << "Successfully created a database connection";
}

void MySQL::shutdown() {}
