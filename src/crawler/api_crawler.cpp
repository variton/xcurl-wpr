
#include <cstdlib>
#include <string>
#include <fmt/core.h>

#include <curl/curl.h>
#include <xcurl>

using Xcurl_ctx =
  xcgen::XcurlCtx<xcwpr::Xcurl, std::string, xcwpr::XcurlGlobal>;

// todo replace fmt with spdlog to log the events of the api_crawler
namespace
{
int helper(char **argv)
{
  fmt::print("Usage: {} {}", argv[0], "./api_crawler <url>\n");
  fmt::print("example:\n");
  fmt::print("./api_crawler https://httpbin.org/get\n");
  return EXIT_FAILURE;
}
} // namespace

int main(int argc, char **argv)
{
  if (argc < 2)
    return helper(argv);
  std::string url{argv[1]};

  Xcurl_ctx cctx{url};
  if (cctx.ctx_status() && cctx->status() == CURLE_OK) {
    auto ret = cctx->fetch_data();
    if (!ret) {
      fmt::print(
        "failed to fetch data with code error {}",
        std::to_string(cctx->status())
      );
      return EXIT_FAILURE;
    }

    auto response = cctx->read_buffer();
    fmt::print("{}\n", response);
    // todo add parsing of the reponse with a json parser
  }
  return EXIT_SUCCESS;
}
