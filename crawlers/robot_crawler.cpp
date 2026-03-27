
#include <xcurl>
#include <fmt/core.h>
#include <cstdlib>
#include <rapidjson/document.h>
#include <string>

using namespace xcwpr;

//todo replace fmt with spdlog to log the events of the api_crawler
namespace{
  int helper(char ** argv){
    fmt::print("Usage: {} {}",argv[0],"./api_crawler <url>\n");
    fmt::print("example:\n");
    fmt::print("./robot_crawler https://en.wikipedia.org/robots.txt\n");
    return EXIT_FAILURE;
  }
}

int main(int argc,char ** argv){
  if (argc < 2) return helper(argv);
  std::string url{argv[1]};
  
  XcurlGlobal ctx{}; //brings an overhead at runtime
  //it works without the global initialization
  if(!ctx.status()) return EXIT_FAILURE;
  
  Xcurl xcl_mgr{url};
  if (xcl_mgr.status() != CURLE_OK) return EXIT_FAILURE;
  
  auto ret = xcl_mgr.fetch_data();
  if(!ret){

    if(xcl_mgr.status() != CURLE_OK) {

      fmt::print("failed to fetch data with curl code {}\n",
                std::to_string(xcl_mgr.status()));
    }

    fmt::print("failed to fetch data with http code {}",
                std::to_string(xcl_mgr.http_code()));

    return EXIT_FAILURE;
  }

  auto response = xcl_mgr();
  fmt::print("{}\n",response);
  return EXIT_SUCCESS;
}
