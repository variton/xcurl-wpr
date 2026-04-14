
#ifndef ENV_MGR_H
#define ENV_MGR_H

#include <optional>
#include <string>
#include <cstdlib>
#include <ncnm.h>
#include <tl/expected.hpp>

namespace platform
{

/**
 * @brief Alias for a non-copyable, non-movable base class.
 *
 * Prevents copying and moving of derived types via CRTP.
 *
 * @tparam T Derived type.
 */
template <typename T>
using Default = utils::NCNM<T>;

enum class EnvMgrError
{
  NoEnvVar,
  InvalidEnvVarType,
};

struct EnvMgrErrorInfo
{
  EnvMgrError type;
  std::string message;
};

// todo change optional with expected & add documentation
class EnvMgr : public Default<EnvMgr>
{
public:
  static EnvMgr &get_instance() noexcept
  {
    static EnvMgr instance;
    return instance;
  }

  std::optional<std::string> get_env_var(const char *name)
  {
    if (const char *rc = std::getenv(name)) {
      return std::string{rc};
    }
    return std::nullopt;
  }

  tl::expected<std::string, EnvMgrErrorInfo> get_envv(const char *name)
  {
    if (const char *rc = std::getenv(name)) {
      return std::string{rc};
    }
    return tl::unexpected(
      EnvMgrErrorInfo{EnvMgrError::NoEnvVar, "No env var found\n"}
    );
  }

private:
  EnvMgr() = default;
};

} // namespace platform

#endif
