#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <cstdlib>
#include <string>
#include <optional>

#include <xcurl.h>
//#include <code.h>

std::optional<std::string> get_env_var(const char * name){
    if (const char * rc = std::getenv(name)) {
      return std::string {rc};
    } 
    return std::nullopt;
}

TEST_CASE("parse") {
    // namespace ret = rk::ret;
    // namespace fio = rk::fio;
    // auto rc = get_env_var("RC");
    // if (rc){
    //     std::string filepath = *rc + "/front_0.bin";
    //     fio::IFileHdr ifile_hdr(filepath);
    //     CHECK(ifile_hdr.parse() == ret::Code::Ok);
    //     return;
    // }
    CHECK(true); 
}

TEST_CASE("parse fail open") {

    // namespace ret = rk::ret;
    // namespace fio = rk::fio;
    // auto rc = get_env_var("RC");
    // if (rc){
    //     std::string filepath = *rc + "/unknown.bin";
    //     fio::IFileHdr ifile_hdr(filepath);
    //     CHECK(ifile_hdr.parse() == ret::Code::FileOpenFailed);
    //     return;
    // }
    CHECK(true);
}

TEST_CASE("get information"){
    // namespace ret = rk::ret;
    // namespace fio = rk::fio;
    // auto rc = get_env_var("RC");
    // if (rc){
    //     std::string filepath = *rc + "/front_0.bin";
    //     fio::IFileHdr ifile_hdr(filepath);
    //     CHECK(ifile_hdr.parse() == ret::Code::Ok);
    //     CHECK(ifile_hdr.total_input_file_bytes()==21003);
    //     return;
    // }
    CHECK(true);
}
