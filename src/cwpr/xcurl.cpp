
#include <netdb.h>

#include <curl/curl.h>
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
            res_(std::move(CURLE_FAILED_INIT)),
            is_freed_(false) {}

    void manage_result(CURLcode & _code){
      #pragma GCC diagnostic push
      #pragma GCC diagnostic ignored "-Wswitch"
      if (_code == CURLE_COULDNT_RESOLVE_HOST ||
          _code == CURLE_URL_MALFORMAT){
          curl_easy_cleanup(curl_);
          is_freed_=true;
          return; //temporary until all edges cases are handled
      }


      switch(_code){
        case CURLE_FAILED_INIT:{throw std::runtime_error("couldn't create curl object");}
        case CURLE_UNSUPPORTED_PROTOCOL:{throw std::runtime_error("curl unsupported protocol");}
        case CURLE_OK:{break;}
      }
      #pragma GCC diagnostic pop
    }

    CURL * curl_;
    CURLcode res_;
    bool is_freed_;
};
//end of cache implementation---------------------------------------------------------------

void Xcurl::init() noexcept{
  if(cache_->curl_) {
    curl_easy_setopt(cache_->curl_, CURLOPT_URL,url_.data());
    cache_->res_ = CURLE_OK;
  }
  cache_->manage_result(cache_->res_);
}

void Xcurl::Deleter::operator()(cache * p) noexcept {
  if (!p->is_freed_){ 
    curl_easy_cleanup(p->curl_);
  }  
}

Xcurl::Xcurl(std::string_view url) noexcept
    : url_(url),
      read_buffer_{},
      cache_(new cache)
{
    init();
}

Xcurl::~Xcurl() = default;

std::string & Xcurl::operator()() const noexcept{
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
  }
  cache_->manage_result(cache_->res_);
  return cache_->res_ == CURLE_OK;
}

std::string & Xcurl::read_buffer() const noexcept{
    if (read_buffer_.empty()){
      if (cache_->res_ == CURLE_OK ) cache_->res_ = CURLE_READ_ERROR;
    }
    return const_cast<std::string&>(read_buffer_);
}

int Xcurl::status() noexcept{
    return cache_->res_;
}

}
