#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <cstdlib>
#include <string>
#include <optional>

#include <xcurl.h>
#include <curl/curl.h>

#include <fmt/core.h>

std::optional<std::string> get_env_var(const char * name){
  if (const char * rc = std::getenv(name)) {
    return std::string {rc};
  } 
  return std::nullopt;
}

TEST_CASE("Xcurl") {
  cwpr::Xcurl xcurl{"https://httpbin.org/get"};
  // fmt::print("xcurl status -> {}\n",xcurl.status());
  CHECK(xcurl.status()==CURLE_OK);
  //should be an enum with a mapped value with CURlCode : uint8_t
}

//TEST_CASE("Xcurl with init KO") {
//    cwpr::Xcurl xcurl{""};
//    CHECK(xcurl.status()==CURLE_FAILED_INIT);
//    //need to create the context to generate the condition for curl to fail
//    //when initialized
//}

TEST_CASE("read_buffer empty") {
  cwpr::Xcurl xcurl{"https://httpbin.org/get"};
  CHECK(xcurl.read_buffer().empty());
  CHECK(xcurl.status() == CURLE_READ_ERROR);
}

TEST_CASE("functor [read_buffer empty]"){
  cwpr::Xcurl xcurl{"https://httpbin.org/get"};
  CHECK(xcurl().empty());
  CHECK(xcurl.status() == CURLE_READ_ERROR);
}

TEST_CASE("read_buffer with real url") {
  cwpr::Xcurl xcurl{"https://httpbin.org/get"};
  auto ret = xcurl.fetch_data();
  CHECK(ret); 
  CHECK(!xcurl.read_buffer().empty());
  CHECK(xcurl.status() == CURLE_OK);
}

TEST_CASE("read_buffer with fake url") {
  cwpr::Xcurl xcurl{"https://xspectrum/get"};
  auto ret = xcurl.fetch_data();
  CHECK(!ret); 
  CHECK(xcurl.read_buffer().empty());
  CHECK(xcurl.status() == CURLE_COULDNT_RESOLVE_HOST);
}

TEST_CASE("read_buffer with malformat url") {
  cwpr::Xcurl xcurl{"1Z%"};
  auto ret = xcurl.fetch_data();
  CHECK(!ret); 
  CHECK(xcurl.read_buffer().empty());
  CHECK(xcurl.status() == CURLE_URL_MALFORMAT);
}
