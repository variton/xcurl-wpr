#ifndef FILE_MGR_H
#define FILE_MGR_H

#include <string>
#include <cstdlib>
#include <ncnm.h>
#include <tl/expected.hpp>

namespace fio
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
 * @brief Error codes used by FileMgr operations.
 */
enum class FileMgrError
{
  NoFile,
  InvalidFile,
};

/**
 * @brief Detailed error information returned by FileMgr.
 */
struct FileMgrErrorInfo
{
  /**
   * @brief High-level error category.
   */
  FileMgrError type;

  /**
   * @brief Human-readable description of the error.
   */
  std::string message;
};

class FileMgr : public Default<FileMgr>
{
public:
  /**
   * @brief Returns the singleton instance of FileMgr.
   *
   * The instance is initialized on first use and lives until program
   * termination.
   *
   * @return Reference to the global FileMgr instance.
   *
   * @note This function is thread-safe as of C++11 due to guaranteed
   * thread-safe initialization of function-local statics.
   * @note This function never throws.
   */
  static FileMgr &get_instance() noexcept
  {
    static FileMgr instance;
    return instance;
  }

  tl::expected<std::string, FileMgrErrorInfo>
  read(const std::string &path) noexcept
  {
    std::ifstream file(path);
    if (!file.is_open())
      return tl::unexpected(
        FileMgrErrorInfo{FileMgrError::NoFile, "Could not open file\n"}
      );

    std::ostringstream ss;
    ss << file.rdbuf(); // dump entire file buffer into stream
    return ss.str();
  }

private:
  /**
   * @brief Constructs the file manager.
   *
   * The constructor is private to enforce singleton usage through
   * get_instance().
   */
  FileMgr() = default;
};

} // namespace fio

#endif
