
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <ncnm.h>

TEST_CASE("Non copyble non moveable class") {
  CHECK(true);
}
