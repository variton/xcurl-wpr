
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <optional>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>

#include <json_hdr.h>
#include <response_hdr.h>

using Response =
  ret::ResponseHdr<xjson::JsonHdr, xjson::JsonErrorInfo, ret::UResponse>;

std::optional<std::string> get_env_var(const char *name)
{
  if (const char *rc = std::getenv(name)) {
    return std::string{rc};
  }
  return std::nullopt;
}

std::string read_file(const std::string &path)
{
  std::ifstream file(path);
  if (!file.is_open())
    throw std::runtime_error("Could not open file: " + path);

  std::ostringstream ss;
  ss << file.rdbuf(); // dump entire file buffer into stream
  return ss.str();
}

TEST_CASE("ResponseHdr")
{
  Response hdr{};
  CHECK(true);
}

TEST_CASE("ResponseHdr get_data")
{
  auto rc = get_env_var("RC");
  if (rc) {
    std::string filepath = *rc + "/sample.json";
    std::string json = read_file(filepath);

    Response hdr{};
    auto ret = hdr.get_data(json.c_str());

    if (ret) {
      auto [host, port] = ret.value();
      CHECK(host == std::string{"127.0.0.1"});
      CHECK(port == 35000);
    }
  }
}

TEST_CASE("ResponseHdr get_data fail")
{
  std::string json =
    R"({"spectrum":"test","value":42,"items":[1,2,3,],"active":tru})";

  Response hdr{};
  auto ret = hdr.get_data(json.c_str());
  if (!ret) {
    CHECK(ret.error().type == xjson::JsonHdrError::ParseError);
    CHECK(ret.error().message == "Parse error\n");
  }
}
