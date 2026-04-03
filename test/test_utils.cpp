
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <ncnm.h>
#include <nc.h>
#include <utils>

template <typename T>
using Default = utils::NCNM<T>;

template <typename T>
using Movable = utils::NC<T>;

struct Sample : public Default<Sample>
{
};

struct Decoy : public Movable<Decoy>
{
};

TEST_CASE("Non copyble non moveable class")
{
  static_assert(topology::utils::NonCopyableNonMovable<Sample>);
  CHECK(true);
}

TEST_CASE("Non copyble class")
{
  static_assert(topology::utils::NonCopyable<Decoy>);
  CHECK(true);
}
