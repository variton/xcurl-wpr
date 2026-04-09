
#ifndef JSON_HDR_H
#define JSON_HDR_H

#include <ncnm.h>
#include <rapidjson/document.h>
#include <tl/expected.hpp>
#include <string>
#include <string_view>

namespace xjson {

/**
 * @brief Alias for a non-copyable, non-movable base class.
 *
 * This alias uses CRTP (Curiously Recurring Template Pattern) to prevent
 * copying and moving of derived types.
 *
 * @tparam T The derived type.
 */
template <typename T>
using Default = utils::NCNM<T>;

/**
 * @enum JsonHdrError
 * @brief Enumerates possible errors during JSON parsing.
 */
enum class JsonHdrError {
    ParseError  ///< Indicates a JSON parsing failure.
};

/**
 * @struct JsonErrorInfo
 * @brief Contains detailed information about a JSON parsing error.
 */
struct JsonErrorInfo {
    JsonHdrError type;   ///< Type of error.
    std::string message; ///< Human-readable error message.
};

/**
 * @class JsonHdr
 * @brief Lightweight JSON parser wrapper using RapidJSON.
 *
 * This class provides a simple interface to parse JSON strings into a
 * RapidJSON document while returning errors using `tl::expected`.
 *
 * @note This class is non-copyable and non-movable.
 */
class JsonHdr : public Default<JsonHdr> {
public:

    /**
     * @brief Default constructor.
     */
    JsonHdr();

    /**
     * @brief Default destructor.
     */
    ~JsonHdr();

    /**
     * @brief Parses a JSON string into a RapidJSON document.
     *
     * @param json_obj A string view containing the JSON text.
     *
     * @return tl::expected containing:
     * - Pointer to the parsed `rapidjson::Document` on success
     * - `JsonErrorInfo` on failure
     *
     * @retval success Returns pointer to internal document.
     * @retval failure Returns error info with type `JsonHdrError::ParseError`.
     *
     * @note The returned pointer is valid as long as the `JsonHdr` instance exists.
     * @warning The input must be valid JSON; otherwise parsing will fail.
     */
    tl::expected<rapidjson::Document*, JsonErrorInfo>
    parse(std::string_view json_obj) noexcept; 

private:
    rapidjson::Document doc_; ///< Internal RapidJSON document storage.
};

} // namespace xjson

#endif
