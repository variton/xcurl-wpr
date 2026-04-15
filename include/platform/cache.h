
#ifndef CACHE_H
#define CACHE_H

#include <map>
#include <string>

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

class Cache : public Default<Cache>
{

public:
  Cache() = default;
  ~Cache() = default;

  // Add or update a key-value pair
  void add(const std::string &key, const std::string &value)
  {
    cache_[key] = value;
  }

  // Retrieve value by key
  std::string get(const std::string &key) const
  {
    auto it = cache_.find(key);
    if (it != cache_.end()) {
      return it->second;
    }
    return ""; // return empty string if key not found
  }

  size_t size() const noexcept
  {
    return cache_.size();
  }

private:
  std::map<std::string, std::string> cache_;
};

} // namespace platform

#endif
