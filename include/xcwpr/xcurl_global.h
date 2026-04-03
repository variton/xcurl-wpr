/**
 * @file xcurl_global.h
 * @brief Curl global context class.
 */

#ifndef XCURL_GLOBAL_H
#define XCURL_GLOBAL_H

#include <ncnm.h>
#include <xcwpr>

namespace xcwpr
{

/**
 * @brief Alias for a non-copyable, non-movable base class.
 *
 * This alias ensures that derived classes cannot be copied or moved.
 *
 * @tparam T Derived type using CRTP.
 */
template <typename T>
using Default = utils::NCNM<T>;

/**
 * @brief RAII wrapper for global cURL initialization and cleanup.
 *
 * This class manages the lifetime of the global cURL state.
 * Initialization is performed in the constructor and cleanup
 * in the destructor.
 *
 * Copy and move operations are disabled via Default.
 */
class XcurlGlobal : public Default<XcurlGlobal>
{
public:
  /**
   * @brief Constructs the global cURL handler.
   *
   * Initializes the cURL global environment.
   */
  XcurlGlobal() noexcept;

  /**
   * @brief Destroys the global cURL handler.
   *
   * Cleans up the cURL global environment if initialization succeeded.
   */
  ~XcurlGlobal();

  /**
   * @brief Checks whether initialization was successful.
   *
   * @return true if cURL was successfully initialized, false otherwise.
   */
  bool status() const noexcept;

private:
  /**
   * @brief Initialization status flag.
   *
   * Indicates whether cURL global initialization succeeded.
   */
  bool status_;
};

static_assert(
  topology::xcwpr::HasBoolStatus<XcurlGlobal>,
  "XcurlGlobal must provide bool status() const noexcept"
);

} // namespace xcwpr

#endif // XCURL_GLOBAL_H
