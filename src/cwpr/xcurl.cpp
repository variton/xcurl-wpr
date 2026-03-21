
#include <netdb.h>
#include <xcurl.h>

//#include <fmt/core.h>

namespace{
// usefull static function use by curl lib 
  static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    (reinterpret_cast<std::string *>(userp))->append(reinterpret_cast<char *>(contents), size * nmemb);
    return size * nmemb;
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
      curl_global_cleanup();
    }

    CURL * curl_;
    CURLcode res_;
    int16_t http_code_;
};
//end of cache implementation---------------------------------------------------------------

void Xcurl::init() noexcept{
  if(cache_ || cache_->curl_) {
    cache_->res_=curl_easy_setopt(cache_->curl_,
                                  CURLOPT_URL,
                                  url_.data());
  }
}

Xcurl::Xcurl(std::string_view url) noexcept
    : url_(url),
      read_buffer_{},
      cache_(std::make_unique<cache>())
{
  curl_global_init(CURL_GLOBAL_DEFAULT);
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
  if(cache_->curl_) {
    curl_easy_setopt(cache_->curl_, CURLOPT_WRITEFUNCTION, ::WriteCallback);
    curl_easy_setopt(cache_->curl_, CURLOPT_WRITEDATA, &read_buffer_);
    cache_->res_ = curl_easy_perform(cache_->curl_);

    if (cache_->res_ == CURLE_OK) {
        curl_easy_getinfo(cache_->curl_,
                          CURLINFO_RESPONSE_CODE,
                          & cache_->http_code_);
    }
  }
  return (cache_->res_ == CURLE_OK) &&
         (cache_->http_code_ >= 200 && cache_->http_code_ < 300);
}

std::string_view Xcurl::read_buffer() noexcept{
    if (read_buffer_.empty()){
      if (cache_->res_ == CURLE_OK ) cache_->res_ =(CURLcode) CURLE_NO_REQ;
    }
    return read_buffer_;
}

CURLcode Xcurl::status() const noexcept{
  return cache_->res_;
}

int16_t Xcurl::http_code() const noexcept{
  return cache_->http_code_;
}

}
