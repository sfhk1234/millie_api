#include <drogon/drogon.h>
#include <drogon/drogon_test.h>
#include <drogon/HttpClient.h>
#include <drogon/HttpRequest.h>
#include <future>
#include <iostream>

using namespace drogon;

DROGON_TEST(UsersAPITest)
{
  auto fn = async_func([TEST_CTX]() -> drogon::Task<void> {
    auto client = HttpClient::newHttpClient("http://127.0.0.1:1477");
    auto req = HttpRequest::newHttpRequest();
    req->setPath("/v1/users/00000000-0000-0000-0000-000000000000");

    auto res = co_await client->sendRequestCoro(req);
    CO_REQUIRE(res != nullptr);
    CHECK(res->getStatusCode() == k200OK);
    CHECK(res->contentType() == CT_APPLICATION_JSON);
    CO_REQUIRE(res->contentType() == CT_APPLICATION_JSON);
    CHECK(!res->getJsonObject()->isNull());
    CHECK(res->getJsonObject()->isMember("data"));
    CHECK((*res->getJsonObject())["data"].isNull());
  });
  fn();
}
