#ifndef XCGEN_CONCEPTS_H
#define XCGEN_CONCEPTS_H

#include <concepts>
#include <cstddef>
#include <string>
#include <string_view>
#include <curl/curl.h>

/**
 * @file concepts.h
 * @brief Defines concept constraints for xcgen client types and client argument
 * types.
 */

namespace xcgen
{

/**
 * @concept client_arg_topology
 * @brief Concept for character-buffer argument types.
 *
 * Models a string-like or buffer-like object that exposes raw character data
 * and its size.
 *
 * A valid type must provide:
 * @code
 * t.data() -> convertible to const char*
 * t.size() -> convertible to std::size_t
 * @endcode
 *
 * @tparam T The type being constrained.
 */
template <typename T>
concept client_arg_topology = requires(const T &t) {
  { t.data() } -> std::convertible_to<const char *>;
  { t.size() } -> std::convertible_to<std::size_t>;
};

/**
 * @concept xcurl_topology
 * @brief Concept for xcgen-compatible client implementations.
 *
 * This concept describes the required interface for a client type used by
 * xcgen networking components.
 *
 * A valid type must:
 * - be constructible from a URL string
 * - expose a callable interface returning a `std::string_view`
 * - provide network availability and fetch operations
 * - expose CURL and HTTP status inspection
 *
 * Required expressions:
 * @code
 * T{url}
 * t()
 * t.has_network()
 * t.fetch_data()
 * t.read_buffer()
 * t.status()
 * t.http_code()
 * @endcode
 *
 * Return type requirements:
 * - `t()` -> `std::string_view`
 * - `t.has_network()` -> `bool`
 * - `t.fetch_data()` -> `bool`
 * - `t.read_buffer()` -> `std::string_view`
 * - `t.status()` -> `CURLcode`
 * - `t.http_code()` -> `long`
 *
 * All required member expressions must be `noexcept` where specified.
 *
 * @tparam T The type being constrained.
 */
template <typename T>
concept xcurl_topology =
  requires(const std::string &url) { T{url}; } && requires(T t) {
    { t() } noexcept -> std::same_as<std::string_view>;
    { t.has_network() } noexcept -> std::same_as<bool>;
    { t.fetch_data() } noexcept -> std::same_as<bool>;
    { t.read_buffer() } noexcept -> std::same_as<std::string_view>;
  } && requires(const T t) {
    { t.status() } noexcept -> std::same_as<CURLcode>;
    { t.http_code() } noexcept -> std::same_as<long>;
  };

} // namespace xcgen

#endif // XCGEN_CONCEPTS_H
