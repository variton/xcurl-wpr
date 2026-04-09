#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <string>
#include <json_hdr.h>

TEST_CASE("JsonHdr") {
  std::string jsonstr = R"({
    "name": "Alice",
    "age": 25,
    "isStudent": false
  })";

  xjson::JsonHdr jhdr{};
  auto ret = jhdr.parse(jsonstr); 

  if (ret){
    CHECK(ret.value()->HasMember("name"));
    CHECK(ret.value()->HasMember("age"));
    CHECK(ret.value()->HasMember("isStudent"));
    return;
  }
  CHECK(false);
}
