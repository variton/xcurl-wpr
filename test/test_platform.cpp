
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <env_mgr.h>

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
  auto rc = local.get_envv("RC");
  if (!rc) {
    CHECK(rc.error().type == platform::EnvMgrError::NoEnvVar);
    CHECK(rc.error().message == "No env var found\n");
  }
}
