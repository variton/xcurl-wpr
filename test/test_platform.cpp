
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <env_mgr.h>
#include <cache.h>

TEST_CASE("EnvMgr get_env_var")
{
  auto rc = platform::EnvMgr::get_instance().get_env_var("RC");
  if (rc) {
    CHECK(*rc == "/home/cxx-core/rc");
  }
}

TEST_CASE("EnvMgr get_env_var fail")
{
  auto rc = platform::EnvMgr::get_instance().get_env_var("X");
  if (!rc) {
    CHECK(true);
  }
}

TEST_CASE("EnvMgr get_envv")
{
  auto &local = platform::EnvMgr::get_instance();
  auto rc = local.get_envv("RC");
  if (rc) {
    CHECK(rc.value() == "/home/cxx-core/rc");
  }
}

TEST_CASE("EnvMgr get_envv fail")
{
  auto &local = platform::EnvMgr::get_instance();
  auto rc = local.get_envv("XY");
  if (!rc) {
    CHECK(rc.error().type == platform::EnvMgrError::NoEnvVar);
    CHECK(rc.error().message == "No env var found\n");
  }
}

TEST_CASE("Cache add")
{
  auto &local = platform::EnvMgr::get_instance();
  auto rc = local.get_envv("RC");
  if (rc) {
    platform::Cache local_cache{};
    CHECK(local_cache.size() == 0);
    local_cache.add("RC", rc.value());
    CHECK(local_cache.size() == 1);
  }
}

TEST_CASE("Cache get")
{
  auto &local = platform::EnvMgr::get_instance();
  auto rc = local.get_envv("RC");
  if (rc) {
    platform::Cache local_cache{};
    local_cache.add("RC", rc.value());
    auto rc_val = local_cache.get("RC");
    CHECK(rc_val == "/home/cxx-core/rc");
    CHECK(local_cache.size() == 1);
  }
}

TEST_CASE("Cache get fail")
{
  platform::Cache local_cache{};
  auto rc_val = local_cache.get("RC");
  CHECK(rc_val == "");
  CHECK(local_cache.size() == 0);
}

TEST_CASE("Cache update")
{
  auto &local = platform::EnvMgr::get_instance();
  auto rc = local.get_envv("RC");
  if (rc) {
    platform::Cache local_cache{};
    local_cache.add("RC", rc.value());
    auto rc_val = local_cache.get("RC");
    CHECK(rc_val == "/home/cxx-core/rc");
    CHECK(local_cache.size() == 1);
    local_cache.add("RC", "/home/spectrum");
    CHECK(local_cache.size() == 1);
    rc_val = local_cache.get("RC");
    CHECK(rc_val == "/home/spectrum");
  }
}
