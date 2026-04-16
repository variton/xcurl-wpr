#ifndef CACHE_H
#define CACHE_H

#include <map>
#include <string>
#include <ncnm.h>

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
 * @brief Simple key-value cache for string data.
 *
 * Cache provides a lightweight wrapper around an associative container
 * (`std::map`) for storing and retrieving string-based key-value pairs.
 *
 * The class is non-copyable and non-movable.
 *
 * @note This implementation is not thread-safe.
 */
class Cache : public Default<Cache>
{

public:
  /**
   * @brief Default constructor.
   */
  Cache() = default;

  /**
   * @brief Default destructor.
   */
  ~Cache() = default;

  /**
   * @brief Adds or updates a key-value pair in the cache.
   *
   * If the key already exists, its associated value is overwritten.
   * Otherwise, a new key-value pair is inserted.
   *
   * @param key The key to insert or update.
   * @param value The value associated with the key.
   */
  void add(const std::string &key, const std::string &value)
  {
    cache_[key] = value;
  }

  /**
   * @brief Retrieves the value associated with a key.
   *
   * @param key The key to look up.
   * @return std::string
   *         - The associated value if the key exists.
   *         - An empty string if the key is not found.
   *
   * @note An empty string return value may indicate either:
   *       - the key does not exist, or
   *       - the stored value is actually an empty string.
   *       Callers should account for this ambiguity if it matters.
   */
  std::string get(const std::string &key) const
  {
    auto it = cache_.find(key);
    if (it != cache_.end()) {
      return it->second;
    }
    return ""; // return empty string if key not found
  }

  /**
   * @brief Returns the number of entries in the cache.
   *
   * @return size_t Number of stored key-value pairs.
   *
   * @note This function never throws.
   */
  size_t size() const noexcept
  {
    return cache_.size();
  }

private:
  /**
   * @brief Internal storage for key-value pairs.
   *
   * Uses `std::map` to maintain ordered key storage.
   */
  std::map<std::string, std::string> cache_;
};

} // namespace platform

#endif
