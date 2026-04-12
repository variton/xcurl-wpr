
#include <json_hdr.h>
#include <tuple>
#include <string>

namespace ret{

template <typename Jhdr,typename JhdrError,typename Response>
ResponseHdr<Jhdr,JhdrError,Response>::ResponseHdr() noexcept
  :jhdr_{}{
  }
 
template <>
tl::expected<UResponse,xjson::JsonErrorInfo>
ResponseHdr<xjson::JsonHdr,xjson::JsonErrorInfo,UResponse>::get_data(std::string_view json_obj) noexcept {
  auto res = jhdr_.parse(json_obj);
  if(!res) return tl::unexpected(res.error());
  const auto & doc = res.value().get();
  auto host = doc["oblivion"]["host"].GetString();
  auto port = doc["oblivion"]["port"].GetInt();
  return std::make_tuple(host,port);
}

}
