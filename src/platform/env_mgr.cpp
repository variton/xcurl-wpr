#include <env_mgr.h>

namespace platform
{

EnvMgr &EnvMgr::get_instance() noexcept
{
  static EnvMgr instance;
  return instance;
}

tl::expected<std::string, EnvMgrErrorInfo> EnvMgr::get_env_var(const char *name)
{
  auto key = std::string{name};
  auto val = cache_.get(key);

  if (val.empty()) {
    if (const char *envvar = std::getenv(name)) {
      auto value = std::string{envvar};
      cache_.add(key, value);
      return value;
    }

    return tl::unexpected(
      EnvMgrErrorInfo{EnvMgrError::NoEnvVar, "No env var found\n"}
    );
  }
  else {
    return val;
  }
}

EnvMgr::EnvMgr() : cache_{}
{
}

} // namespace platform
