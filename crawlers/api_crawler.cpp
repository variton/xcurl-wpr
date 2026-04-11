
#include <xcurl>
#include <fmt/core.h>
#include <cstdlib>
#include <rapidjson/document.h>
#include <string>
#include <json_hdr.h>

using Xcurl_ctx = xcgen::XcurlCtx<xcwpr::Xcurl, 
                                  std::string, 
                                  xcwpr::XcurlGlobal>;

//todo replace fmt with spdlog to log the events of the api_crawler
namespace{
  int helper(char ** argv){
    fmt::print("Usage: {} {}",argv[0],"./api_crawler <url>\n");
    fmt::print("example:\n");
    fmt::print("./api_crawler https://httpbin.org/get\n");
    return EXIT_FAILURE;
  }
}

int main(int argc,char ** argv){
  if (argc < 2) return helper(argv);
  std::string url{argv[1]};

  Xcurl_ctx cctx{url};
  if(cctx.ctx_status() && cctx->status() == CURLE_OK){
    auto ret = cctx->fetch_data();
    if(!ret){
      fmt::print("failed to fetch data with code error {}",
                 std::to_string(cctx->status())); 
      return EXIT_FAILURE;
    }

    auto response = cctx->read_buffer();
   
    auto res = xjson::JsonHdr{}.parse(response.data());

    //todo this part needs to be improved
    if (res){
      auto host = res.value().get()["headers"]["Host"].GetString();
      auto origin = res.value().get()["origin"].GetString();
      fmt::print("Host: {}\n",host);
      fmt::print("Origin: {}\n",origin);
    }
    else{
      fmt::print("{}",res.error().message);
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}
