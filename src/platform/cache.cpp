#include "cache.h"

namespace platform
{

Cache::Cache()
{
}

Cache::~Cache()
{
}

void Cache::add(const std::string &key, const std::string &value)
{
  cache_[key] = value;
}

std::string Cache::get(const std::string &key) const
{
  auto it = cache_.find(key);
  if (it != cache_.end()) {
    return it->second;
  }
  return "";
}

size_t Cache::size() const noexcept
{
  return cache_.size();
}

} // namespace platform
