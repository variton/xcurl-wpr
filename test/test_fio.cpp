
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <file_mgr.h>

TEST_CASE("FileMgr read")
{
  auto filepath = "/home/cxx-core/rc/sample.json";
  //auto json_file = R"({"oblivion":{"host":"127.0.0.1","port":35000}})"; 
  auto & fmgr = fio::FileMgr::get_instance(); 
  auto ret = fmgr.read(filepath);
  CHECK(ret);
}

TEST_CASE("FileMgr read fail")
{
  auto & fmgr = fio::FileMgr::get_instance();
  auto ret = fmgr.read("$^ùu");
  if (!ret) {
    CHECK(ret.error().type == fio::FileMgrError::NoFile);
    CHECK(ret.error().message == "Could not open file\n");
  }
}
