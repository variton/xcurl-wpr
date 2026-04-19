
#ifndef RESPONSE_HDR_H
#define RESPONSE_HDR_H

#include <ncnm.h>
#include <string_view>

// todo add the needed concepts for the class topology
// todo implement the test for coverage

/**
 * @namespace ret
 * @brief Provides response-parsing utilities and response wrapper types.
 */
namespace ret
{

/**
 * @brief Alias representing a generic response payload.
 *
 * This type stores a textual response together with a network port number.
 *
 * @details
 * - The first element (@c std::string) represents the response body or message.
 * - The second element (@c int) represents the associated port number.
 *
 */
using UResponse = std::tuple<std::string, int>;

/**
 * @brief Alias for a non-copyable, non-movable CRTP base class.
 *
 * This alias applies the @c utils::NCNM utility to the given type in order
 * to prevent copy and move construction/assignment.
 *
 * @tparam T The derived type using the CRTP pattern.
 */
template <typename T>
using Default = utils::NCNM<T>;

/**
 * @brief Generic response header parser and converter.
 *
 * The @c ResponseHdr class is responsible for extracting typed response data
 * from a JSON object representation.
 *
 * @details
 * The class uses:
 * - @p Jhdr to parse or represent the JSON header
 * - @p JhdrError to represent parsing or conversion errors
 * - @p Response as the final output type
 *
 * The class inherits from @c Default to disable copy and move semantics.
 *
 * @tparam Jhdr Type used internally to parse or represent the JSON header.
 * @tparam JhdrError Error type returned when parsing or conversion fails.
 * @tparam Response Final typed response object produced on success.
 */
template <typename Jhdr, typename JhdrError, typename Response>
class ResponseHdr : public Default<ResponseHdr<Jhdr, JhdrError, Response>>
{
public:
  /**
   * @brief Default constructor.
   *
   * Constructs an empty @c ResponseHdr object.
   *
   * @note This constructor does not throw exceptions.
   */
  ResponseHdr() noexcept;

  /**
   * @brief Parses and extracts response data from a JSON object string.
   *
   * Attempts to interpret the supplied JSON text and convert it into a
   * value of type @p Response.
   *
   * @param json_obj A string view containing the JSON object to parse.
   *
   * @return tl::expected<Response, JhdrError>
   *         - On success: a populated @p Response object
   *         - On failure: a @p JhdrError describing the issue
   *
   * @note This function does not throw exceptions.
   */
  tl::expected<Response, JhdrError>
  get_data(std::string_view json_obj) noexcept;

private:
  /**
   * @brief Internal header parser or representation.
   *
   * This object is responsible for handling the JSON header portion
   * during parsing and conversion.
   */
  Jhdr jhdr_;
};

} // namespace ret

#include "response_hdr.tpp"

#endif
