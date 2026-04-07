
#ifndef RESPONSE_HDR_H
#define RESPONSE_HDR_H

#include <ncnm.h>
#include <string_view>

//todo add the needed concepts for the class topology
//todo implement the test for coverage
//todo add the doxygen documentation
namespace ret{

/**
 * @brief Alias for a non-copyable, non-movable base class.
 *
 * Prevents copying and moving of derived types via CRTP.
 *
 * @tparam T Derived type.
 */
template <typename T>
using Default = utils::NCNM<T>;

template <typename Jhdr,typename JhdrError>
class ResponseHdr: public Default<ResponseHdr<Jhdr,JhdrError>>{

public:
  
  ResponseHdr() noexcept;
 
  template <typename Response> 
  tl::expected<Response, JhdrError> get_data(std::string_view json_obj) noexcept;

private:
  Jhdr jhdr_;

};

#include "response_hdr.tpp"

#endif
