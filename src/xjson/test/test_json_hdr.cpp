#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <optional>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>

#include <json_hdr.h>

//todo move get_env_var & read_file to specific libraries
//it affects the coverage percentage
std::optional<std::string> get_env_var(const char * name){
    if (const char * rc = std::getenv(name)) {
      return std::string {rc};
    }
    return std::nullopt;
}

std::string read_file(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("Could not open file: " + path);

    std::ostringstream ss;
    ss << file.rdbuf();       // dump entire file buffer into stream
    return ss.str();
}

TEST_CASE("JsonHdr parse") {
  auto rc = get_env_var("RC");
  if (rc){
    std::string filepath = *rc + "/sample.json";
    std::string json = read_file(filepath);

    xjson::JsonHdr jhdr{};
    auto ret = jhdr.parse(json.c_str());

    if(ret){
      const auto & doc = ret.value().get();
      auto host = doc["oblivion"]["host"].GetString();
      auto port = doc["oblivion"]["port"].GetInt();
      CHECK(host == std::string{"127.0.0.1"});
      CHECK(port == 35000);
    }
  }
}

TEST_CASE("JsonHdr parse error") {
  std::string corrupt_json = R"({"spectrum":"test","value":42,"items":[1,2,3,],"active":tru})";

  auto ret = xjson::JsonHdr{}.parse(corrupt_json);

  if (!ret){
    CHECK(ret.error().type == xjson::JsonHdrError::ParseError);
    CHECK(ret.error().message == "Parse error\n");
  }
}
