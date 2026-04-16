#ifndef ENV_MGR_H
#define ENV_MGR_H

#include <optional>
#include <string>
#include <cstdlib>
#include <ncnm.h>
#include <tl/expected.hpp>
#include <cache.h>

namespace platform
{

/**
 * @brief Alias for a non-copyable, non-movable base class.
 *
 * This alias uses the CRTP pattern to inherit from a utility type that
 * disables copy construction, copy assignment, move construction, and
 * move assignment for the derived type.
 *
 * @tparam T Derived type that should be made non-copyable and non-movable.
 */
template <typename T>
using Default = utils::NCNM<T>;

/**
 * @brief Error codes used by EnvMgr operations.
 */
enum class EnvMgrError
{
  /**
   * @brief The requested environment variable does not exist.
   */
  NoEnvVar,

  /**
   * @brief The environment variable exists but cannot be converted or
   * interpreted as the expected type.
   *
   * @note This error code is defined for future extensibility. It is not
   * currently produced by the functions in this header.
   */
  InvalidEnvVarType,
};

/**
 * @brief Detailed error information returned by EnvMgr.
 */
struct EnvMgrErrorInfo
{
  /**
   * @brief High-level error category.
   */
  EnvMgrError type;

  /**
   * @brief Human-readable description of the error.
   */
  std::string message;
};

/**
 * @brief Singleton manager for reading and caching environment variables.
 *
 * EnvMgr provides helper functions for accessing process environment variables.
 * It exposes:
 * - an optional-based API via get_env_var() for simple presence checks
 * - an expected-based API via get_envv() for explicit error reporting
 *
 * Values retrieved through get_envv() are cached internally to avoid repeated
 * calls to `std::getenv` for the same key.
 *
 * This class is intentionally non-copyable and non-movable.
 *
 * @note Use get_instance() to access the single global instance.
 */
class EnvMgr : public Default<EnvMgr>
{
public:
  /**
   * @brief Returns the singleton instance of EnvMgr.
   *
   * The instance is initialized on first use and lives until program
   * termination.
   *
   * @return Reference to the global EnvMgr instance.
   *
   * @note This function is thread-safe as of C++11 due to guaranteed
   * thread-safe initialization of function-local statics.
   * @note This function never throws.
   */
  static EnvMgr &get_instance() noexcept
  {
    static EnvMgr instance;
    return instance;
  }

  /**
   * @brief Retrieves an environment variable by name.
   *
   * This function looks up the specified environment variable using
   * `std::getenv`.
   *
   * @param name Null-terminated name of the environment variable.
   * @return std::optional<std::string>
   *         - Contains the environment variable value if it exists.
   *         - `std::nullopt` if the variable is not defined.
   *
   * @warning Passing a null pointer for @p name results in undefined behavior.
   * @note This overload does not use the internal cache.
   */
  std::optional<std::string> get_env_var(const char *name)
  {
    if (const char *rc = std::getenv(name)) {
      return std::string{rc};
    }
    return std::nullopt;
  }

  /**
   * @brief Retrieves an environment variable by name with explicit error
   * reporting.
   *
   * This function first checks the internal cache for a previously retrieved
   * value. If the value is not cached, it queries the process environment
   * using `std::getenv`, stores the result in the cache, and returns it.
   *
   * @param name Null-terminated name of the environment variable.
   * @return tl::expected<std::string, EnvMgrErrorInfo>
   *         - On success: contains the environment variable value.
   *         - On failure: contains an @ref EnvMgrErrorInfo describing the
   *           reason for failure.
   *
   * @retval EnvMgrError::NoEnvVar The requested environment variable was not
   * found.
   *
   * @warning Passing a null pointer for @p name results in undefined behavior.
   * @note Cached values are returned directly without re-reading the process
   * environment.
   */
  tl::expected<std::string, EnvMgrErrorInfo> get_envv(const char *name)
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

private:
  /**
   * @brief Constructs the environment manager.
   *
   * The constructor is private to enforce singleton usage through
   * get_instance().
   */
  EnvMgr() : cache_{}
  {
  }

  /**
   * @brief Internal cache for environment variable values.
   *
   * Used by get_envv() to store previously resolved environment variables.
   */
  Cache cache_;
};

} // namespace platform

#endif
