#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <string>
#include <json_hdr.h>

TEST_CASE("JsonHdr parse") {
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
  }
}

TEST_CASE("JsonHdr parse error") {
  std::string jsonstr_empty = R"({})";

  xjson::JsonHdr jhdr{};
  auto ret = jhdr.parse(jsonstr_empty); 

  if (!ret){
    CHECK(ret.error().type == xjson::JsonHdrError::ParseError);
    CHECK(ret.error().message == "Parse error\n");
  }
}
