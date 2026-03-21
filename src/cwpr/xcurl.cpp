
#include <utility>

#include <netdb.h>
#include <xcurl.h>
//#include <fmt/core.h>

namespace{
// usefull static function use by curl lib 
  static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    const auto total = size * nmemb;
    auto * buffer = reinterpret_cast<std::string *>(userp);
    buffer->append(reinterpret_cast<const char *>(contents), size * nmemb);
    return total;
  }

  template <typename Func, typename... Args>
  CURLcode call_curl(Func func, Args&&... args) noexcept {
    return func(std::forward<Args>(args)...);
  }

}

namespace cwpr{

////start of cache implementation-------------------------------------------------------------
struct Xcurl::cache{

    cache():curl_(curl_easy_init()),
            res_(CURLE_FAILED_INIT),
            http_code_{HTTP_NOT_SET} {}

    ~cache(){
      if(curl_){
        curl_easy_cleanup(curl_);
        curl_ = nullptr;
      }
    }

    CURL * curl_;
    CURLcode res_;
    long http_code_;
};
//end of cache implementation---------------------------------------------------------------

void Xcurl::init() noexcept{
  if(cache_ && cache_->curl_) {
    cache_->res_=curl_easy_setopt(cache_->curl_,
                                  CURLOPT_URL,
                                  url_.c_str());
  }
}

Xcurl::Xcurl(const std::string & url) noexcept
    : url_(url),
      read_buffer_{},
      cache_(std::make_unique<cache>())
{
  init();
}

Xcurl::~Xcurl() = default;

std::string_view Xcurl::operator()() noexcept{
    return read_buffer();
}

bool Xcurl::has_network() noexcept{
    return true; // temp cache_ ? cache_->network_available : false;
}

bool Xcurl::fetch_data() noexcept {
  if(!cache_ || !cache_->curl_) return false;

  cache_->res_ = ::call_curl(curl_easy_setopt,cache_->curl_,CURLOPT_WRITEFUNCTION,::WriteCallback);
  if (cache_->res_ != CURLE_OK) return false;

  cache_->res_ = ::call_curl(curl_easy_setopt,cache_->curl_,CURLOPT_WRITEDATA, &read_buffer_);
  if (cache_->res_ != CURLE_OK) return false;

  cache_->res_ = ::call_curl(curl_easy_perform,cache_->curl_);
  if (cache_->res_ != CURLE_OK) return false;

  cache_->res_ = ::call_curl(curl_easy_getinfo,
                             cache_->curl_,
                             CURLINFO_RESPONSE_CODE,
                             & cache_->http_code_);
  if (cache_->res_ != CURLE_OK) return false;

  return cache_->http_code_ >= 200 && cache_->http_code_ < 300;
}

std::string_view Xcurl::read_buffer() noexcept{
    return read_buffer_;
}

CURLcode Xcurl::status() const noexcept{
  return cache_->res_;
}

long Xcurl::http_code() const noexcept{
  return cache_->http_code_;
}

}
