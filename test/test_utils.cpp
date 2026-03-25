
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <ncnm.h>

template <typename T>
using Default = utils::NCNM<T>;

struct Sample : public Default<Sample>
{
};

TEST_CASE("Non copyble non moveable class")
{
  static_assert(utils::NonCopyableNonMovable<Sample>);
  CHECK(true);
}
