
#ifndef ENV_MGR_H
#define ENV_MGR_H

#include <optional>
#include <string>
#include <cstdlib>
#include <ncnm.h>

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

private:
  EnvMgr() = default;
};

} // namespace platform

#endif
