
#ifndef JSON_HDR_H
#define JSON_HDR_H

#include <ncnm.h>
#include <rapidjson/document.h>
#include <tl/expected.hpp>
#include <string>
#include <string_view>

//todo needs to be documented

namespace json{
/**
 * @brief Alias for a non-copyable, non-movable base class.
 *
 * Prevents copying and moving of derived types via CRTP.
 *
 * @tparam T Derived type.
 */
template <typename T>
using Default = utils::NCNM<T>;

enum class JsonHdrError{
  ParseError
};


struct JsonErrorInfo {
    JsonHdrError type;
    std::string message; // or extra data
};

class JsonHdr:public Default<JsonHdr>{
  public:
    JsonHdr() = default;

    ~JsonHdr() = default;

  tl::expected<rapidjson::Document*, JsonErrorInfo> parse(std::string_view json_obj) noexcept{
    doc_.Parse(json_obj.data());

    if (doc_.HasParseError()) {
      return tl::unexpected(JsonErrorInfo{JsonHdrError::ParseError, "Parse error\n"});
    }
    return &doc_; 
  }

  private:
  rapidjson::Document doc_;

};

}

#endif
