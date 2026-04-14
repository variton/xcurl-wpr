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
 * This alias uses CRTP to inherit from a utility type that disables
 * copy and move operations for the derived class.
 *
 * @tparam T The derived type.
 */
template <typename T>
using Default = utils::NCNM<T>;

/**
 * @brief Error codes returned by EnvMgr operations.
 */
enum class EnvMgrError
{
  /** Environment variable was not found. */
  NoEnvVar,

  /** Environment variable exists but could not be interpreted as the expected
   * type. */
  InvalidEnvVarType,
};

/**
 * @brief Detailed error information for EnvMgr failures.
 */
struct EnvMgrErrorInfo
{
  /** The error category. */
  EnvMgrError type;

  /** Human-readable description of the error. */
  std::string message;
};

/**
 * @brief Singleton manager for reading environment variables.
 *
 * EnvMgr provides utility functions for retrieving environment variables
 * from the process environment. It offers both an optional-based API and
 * an expected-based API for error-aware access.
 *
 * The class is non-copyable and non-movable.
 */
class EnvMgr : public Default<EnvMgr>
{
public:
  /**
   * @brief Returns the singleton instance of EnvMgr.
   *
   * @return Reference to the global EnvMgr instance.
   *
   * @note This function is noexcept and guarantees a single shared instance
   *       for the lifetime of the program.
   */
  static EnvMgr &get_instance() noexcept
  {
    static EnvMgr instance;
    return instance;
  }

  /**
   * @brief Retrieves the value of an environment variable.
   *
   * Looks up the specified environment variable using `std::getenv`.
   *
   * @param name Null-terminated name of the environment variable.
   * @return std::optional<std::string>
   *         - Contains the variable value if found.
   *         - `std::nullopt` if the variable does not exist.
   */
  std::optional<std::string> get_env_var(const char *name)
  {
    if (const char *rc = std::getenv(name)) {
      return std::string{rc};
    }
    return std::nullopt;
  }

  /**
   * @brief Retrieves the value of an environment variable with error reporting.
   *
   * Looks up the specified environment variable using `std::getenv`.
   *
   * @param name Null-terminated name of the environment variable.
   * @return tl::expected<std::string, EnvMgrErrorInfo>
   *         - On success: the environment variable value.
   *         - On failure: an @ref EnvMgrErrorInfo describing the error.
   *
   * @retval EnvMgrError::NoEnvVar The requested environment variable was not
   * found.
   */
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
  /**
   * @brief Constructs an EnvMgr.
   *
   * Private to enforce singleton usage through get_instance().
   */
  EnvMgr() = default;
};

} // namespace platform

#endif
