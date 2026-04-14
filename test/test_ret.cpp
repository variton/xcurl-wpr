
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <string>
#include <fstream>
#include <sstream>

#include <env_mgr.h>
#include <json_hdr.h>
#include <response_hdr.h>

using Response =
  ret::ResponseHdr<xjson::JsonHdr, xjson::JsonErrorInfo, ret::UResponse>;

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
  auto &local = platform::EnvMgr::get_instance();
  auto rc = local.get_env_var("RC");
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
