#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <xcurl_global.h>

TEST_CASE("XcurlGlobal") {
  xcwpr::XcurlGlobal xcurl_global{};;
  CHECK(xcurl_global.status());
}
