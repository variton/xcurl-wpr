/**
 * @file xcurl.h
 * @brief Lightweight cURL wrapper for simple HTTP requests.
 */

#ifndef XCURL_H
#define XCURL_H

#include <curl/curl.h>
#include <memory>
#include <ncnm.h>
#include <string>
#include <string_view>

#define HTTP_NOT_SET -1

namespace xcwpr
{

/**
 * @brief Alias for a non-copyable, non-movable base class.
 *
 * Prevents copying and moving of derived types via CRTP.
 *
 * @tparam T Derived type.
 */
template <typename T>
using Default = utils::NCNM<T>;

/**
 * @brief Simple RAII wrapper for performing HTTP requests using cURL.
 *
 * Stores the response in an internal buffer and provides accessors
 * for request status and response data.
 *
 * @warning This class stores the URL as a non-owning std::string_view.
 * The caller must ensure that the referenced URL remains valid for the
 * entire lifetime of the object.
 *
 * @warning Instances of this class are not thread-safe. Concurrent access
 * to the same object must be externally synchronized.
 *
 * @note Using libcurl typically requires global initialization with
 * curl_global_init() before creating request handles.
 */
class Xcurl : public Default<Xcurl>
{
public:
  /**
   * @brief Construct a request for the given URL.
   *
   * @param url Target URL.
   *
   * @warning The provided URL is stored as a non-owning view and must
   * outlive this object.
   */
  explicit Xcurl(const std::string &url) noexcept;

  /**
   * @brief Destructor.
   *
   * Releases internal resources associated with the request.
   */
  ~Xcurl();

  /**
   * @brief Access the response buffer.
   *
   * Equivalent to read_buffer().
   *
   * @return Response data view.
   *
   * @warning The returned view becomes invalid if the internal buffer
   * is modified or destroyed.
   */
  std::string_view operator()() noexcept;

  /**
   * @brief Check whether networking is available.
   *
   * @return true if the object is ready to perform requests.
   *
   * @note This function does not guarantee that a remote endpoint is
   * reachable, only that the local request backend appears available.
   */
  bool has_network() noexcept;

  /**
   * @brief Execute the request.
   *
   * Fills the internal response buffer with fetched data.
   *
   * @return true on success, false otherwise.
   *
   * @warning This function modifies internal state and must not be called
   * concurrently with other member functions on the same instance unless
   * externally synchronized.
   */
  bool fetch_data() noexcept;

  /**
   * @brief Get the response buffer.
   *
   * @return Response data view.
   *
   * @warning The returned view refers to internal storage owned by this
   * object. It becomes invalid when the buffer is modified or when the
   * object is destroyed.
   */
  std::string_view read_buffer() noexcept;

  /**
   * @brief Get the cURL operation status.
   *
   * @return CURLcode result of the request operation.
   */
  CURLcode status() const noexcept;

  /**
   * @brief Get the HTTP response code.
   *
   * @return HTTP status code, or HTTP_NOT_SET if unavailable.
   */
  long http_code() const noexcept;

private:
  /**
   * @brief Initialize internal state.
   */
  void init() noexcept;

  /// Target URL stored as const string ref.
  const std::string &url_;

  /// Response buffer owned by this object.
  std::string read_buffer_;

  /// Internal implementation details.
  struct cache;

  /// Pointer to internal state.
  std::unique_ptr<cache> cache_;
};

} // namespace xcwpr

#endif // XCURL_H
