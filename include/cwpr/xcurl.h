/**
 * @file xcurl.h
 * @brief Curl wrapper class.
 */

#ifndef XCURL_H
#define XCURL_H

#include <string>
#include <memory>
#include <string_view>
#include <ncnm.h>

#include <curl/curl.h>

#define HTTP_NOT_SET -1
#define CURLE_NO_REQ 10000

namespace cwpr{

/**
 * @brief Non-copyable, non-movable base alias.
 *
 * Prevents copying and moving of derived types.
 */
template <typename T>
using Default = utils::NCNM<T>;

/**
 * @brief Lightweight URL request/response wrapper.
 *
 * Handles fetching data from a given URL and storing the result
 * in an internal buffer. The class owns internal resources and
 * is non-copyable and non-movable.
 */
class Xcurl:public Default<Xcurl>{

public:
    /**
     * @brief Construct with target URL.
     *
     * @param url Target URL (must remain valid for lifetime of object).
     */
    explicit Xcurl(std::string_view url) noexcept;

    /**
     * @brief default desctructor. 
     *
     */
     ~Xcurl();

    /**
     * @brief Access the internal response buffer.
     *
     * Shorthand for read_buffer().
     *
     * @return Mutable reference to stored response data.
     */
    std::string_view operator()() noexcept;

    /**
     * @brief Check if network/backend is available.
     *
     * @return true if ready for requests.
     */
    bool has_network() noexcept;

    /**
     * @brief Perform the request and fill the buffer.
     *
     * @return true on success, false otherwise.
     */
    bool fetch_data() noexcept;

    /**
     * @brief Get the response buffer.
     *
     * @return Mutable reference to internal buffer.
     */
    std::string_view read_buffer() noexcept;

    /**
     * @brief Get request status code.
     *
     * Typically represents HTTP or internal status.
     */
    CURLcode status() const noexcept;

    /**
     * @brief Get HTTP code.
     *
     * Typically represents HTTP or internal status.
     */
    std::int16_t http_code() const noexcept;

private:
    /**
     * @brief Initialize internal resources.
     */
    void init() noexcept;

    /// Target URL (non-owning reference)
    std::string_view url_;

    /// Buffer holding fetched data
    std::string read_buffer_;

    /// Opaque internal implementation/cache
    struct cache;

    /// Pointer to internal state
    std::unique_ptr<cache> cache_;
};

}

#endif
