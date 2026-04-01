

#ifndef XCGEN_CONCEPTS_H
#define XCGEN_CONCEPTS_H

namespace xcgen{

template <typename T>
concept client_arg_topology = requires(const T& t) {
  { t.data() } -> std::convertible_to<const char*>;
  { t.size() } -> std::convertible_to<std::size_t>;
};

template <typename T>
concept xcurl_topology = requires(const std::string& url) {
        T{url};
    } &&
    requires(T t) {
        { t() } noexcept -> std::same_as<std::string_view>;
        { t.has_network() } noexcept -> std::same_as<bool>;
        { t.fetch_data() } noexcept -> std::same_as<bool>;
        { t.read_buffer() } noexcept -> std::same_as<std::string_view>;
    } &&
    requires(const T t) {
        { t.status() } noexcept -> std::same_as<CURLcode>;
        { t.http_code() } noexcept -> std::same_as<long>;
    };

}

#endif
