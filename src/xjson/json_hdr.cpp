#include <json_hdr.h>

namespace xjson
{

JsonHdr::JsonHdr() = default;

JsonHdr::~JsonHdr() = default;

tl::expected<rapidjson::Document *, JsonErrorInfo>
JsonHdr::parse(std::string_view json_obj) noexcept
{
  doc_.Parse(json_obj.data());

  if (doc_.HasParseError()) {
    return tl::unexpected(
      JsonErrorInfo{JsonHdrError::ParseError, "Parse error\n"}
    );
  }

  return &doc_;
}

} // namespace xjson
