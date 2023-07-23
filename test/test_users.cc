#include <drogon/drogon.h>
#include <drogon/drogon_test.h>
#include <drogon/HttpClient.h>
#include <drogon/HttpRequest.h>

using namespace drogon;

DROGON_TEST(UsersAPITest)
{
  auto fn1 = async_func([TEST_CTX]() -> drogon::Task<void> {
    auto client = HttpClient::newHttpClient("http://127.0.0.1:8848");
    auto req = HttpRequest::newHttpRequest();
    req->setPath("/users");

    auto res = co_await client->sendRequestCoro(req);
    CO_REQUIRE(res != nullptr);
    CHECK(res->getStatusCode() == k200OK);
    CHECK(res->contentType() == CT_APPLICATION_JSON);
  });
  // auto fn = [TEST_CTX]() -> Task<void> {
  //   auto client = HttpClient::newHttpClient("http://localhost:8848");
  //   auto req = HttpRequest::newHttpRequest();
  //   req->setPath("/users");

  //   auto res = co_await client->sendRequestCoro(req);
  //   CO_REQUIRE(res != nullptr);
  //   CHECK(res->getStatusCode() == k200OK);
  //   CHECK(res->contentType() == CT_APPLICATION_JSON);
  // };

  fn1();
}
