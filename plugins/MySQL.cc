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
        "aws.connect.psdb.cloud",     //host
        "3yws8udxs91piue9x0qi",     //user
        "pscale_pw_zPQ3pA6wt4YYO6K7hnGKVULtSDCpCTSYJezhvDprV0O", //pw
        "millie",     //name
        3306, 
        nullptr,
        0
    );
    if(connection == nullptr) 
    {
        LOG_ERROR << "Unable to create a database connection";
        exit(1);
    }
    LOG_INFO << "Successfully created a database connection";
}

bool MySQL::validate_uuid(const std::string& s)
{
    static const std::regex e("^[0-9a-f]{8}-[0-9a-f]{4}-[0-5][0-9a-f]{3}-[089ab][0-9a-f]{3}-[0-9a-f]{12}$", std::regex_constants::icase);
    return std::regex_match(s, e);
}

bool MySQL::validate_name(const std::string& s)
{
    static const  std::regex e("^[ㄱ-ㅎ|가-힣|a-z|A-Z|0-9|]+$", std::regex_constants::icase);
    return std::regex_match(s, e);
}

Json::Value MySQL::runQuery(const std::string& query)
{
    if(mysql_query(connection, query.c_str()))
    {
        LOG_DEBUG << "쿼리 실행 실패";
    }
    LOG_ERROR << "에러라인 1";
    MYSQL_RES* response = mysql_store_result(connection);
    MYSQL_ROW row;
    MYSQL_FIELD* fields = mysql_fetch_fields(response);
    if (response == nullptr)
    {
        LOG_ERROR << "결과 가져오기 실패 : " << mysql_error(connection);
    }

    
    int field_num = mysql_num_fields(response);
    
    Json::Value result;    
    Json::Value field_arr;
    while(row = mysql_fetch_row(response))
    {
        if (row == nullptr)
        {
            break;
        }
        for (int i = 0; i < field_num; ++i) 
        {
            if (row[i] != nullptr)
            {
                field_arr[fields[i].name] = row[i];
            }
            else
            {
                field_arr[fields[i].name] = "null";
            }
        }
        result.append(field_arr);
    }

    LOG_DEBUG << result.toStyledString();

    return result;
}

void MySQL::shutdown() {}
