
#include <json_hdr.h>
#include <tuple>
#include <string>

using UResponse = std::tuple<std::string,std::string>;

template <typename Jhdr,typename JhdrError>
ResponseHdr<Jhdr,JhdrError>::ResponseHdr() noexcept
  :jhdr_{}{
  }
 
template <>
template <>
tl::expected<UResponse,JsonHdrError>
ResponseHdr<JsonHdr, JsonHdrError>::get_data<UResponse>(std::string_view json_obj) noexcept {
  auto res = jhdr_.parse(json_obj);
  if(!res) return tl::unexpected(res.error());
  auto host = (*res.value())["headers"]["Host"].GetString();
  auto origin = (*res.value())["origin"].GetString();
  return UResponse{host,origin};
}
