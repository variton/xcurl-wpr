
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <string>

#include <xcurl.h>
#include <xcurl_ctx.h>
#include <xcurl_global.h>

TEST_CASE("XCurlCtx")
{
  using namespace xcwpr;
  xcgen::XcurlCtx<Xcurl, std::string, XcurlGlobal>{"https://httpbin.org/get"};
  CHECK(true);
}
