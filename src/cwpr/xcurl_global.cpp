
#include <curl/curl.h>
#include <xcurl_global.h>

namespace cwpr {

XcurlGlobal::XcurlGlobal() noexcept : status_{false} {
  status_ = curl_global_init(CURL_GLOBAL_DEFAULT) == CURLE_OK;
}

XcurlGlobal::~XcurlGlobal() {
  if (status_) {
    curl_global_cleanup();
  }
}

bool XcurlGlobal::status() const noexcept { return status_; }

} // namespace cwpr
