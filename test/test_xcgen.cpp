
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <string>

#include <xcurl>
#include <curl/curl.h>

using Xcurl_ctx =
  xcgen::XcurlCtx<xcwpr::Xcurl, std::string, xcwpr::XcurlGlobal>;

TEST_CASE("XCurlCtx")
{
  Xcurl_ctx cctx{"https://httpbin.org/get"};
  CHECK(cctx.ctx_status());
  CHECK(cctx->http_code() == HTTP_NOT_SET);
  CHECK(cctx->status() == CURLE_OK);
}

TEST_CASE("read_buffer empty")
{
  Xcurl_ctx cctx{"https://httpbin.org/get"};
  CHECK(cctx.ctx_status());
  CHECK(cctx->read_buffer().empty());
  CHECK(cctx->status() == CURLE_OK);
  CHECK(cctx->http_code() == HTTP_NOT_SET);
  CHECK(cctx.ctx_status());
}

TEST_CASE("functor [read_buffer empty]")
{
  Xcurl_ctx cctx{"https://httpbin.org/get"};
  CHECK(cctx.ctx_status());
  CHECK(cctx->read_buffer().empty());
  CHECK(cctx->status() == CURLE_OK);
  CHECK(cctx->http_code() == HTTP_NOT_SET);
}

TEST_CASE("read_buffer with real url")
{
  Xcurl_ctx cctx{"https://httpbin.org/get"};
  CHECK(cctx.ctx_status());
  auto ret = cctx->fetch_data();
  CHECK(ret);
  CHECK(!cctx->read_buffer().empty());
  CHECK(cctx->status() == CURLE_OK);
  CHECK(cctx->http_code() == 200);
}

TEST_CASE("read_buffer with fake url")
{
  Xcurl_ctx cctx{"https://xspectrum/get"};
  CHECK(cctx.ctx_status());
  auto ret = cctx->fetch_data();
  CHECK(!ret);
  CHECK(cctx->read_buffer().empty());
  CHECK(cctx->http_code() == HTTP_NOT_SET);
}

TEST_CASE("read_buffer with malformat url")
{
  Xcurl_ctx cctx{"1Z%"};
  CHECK(cctx.ctx_status());
  auto ret = cctx->fetch_data();
  CHECK(!ret);
  CHECK(cctx->read_buffer().empty());
  CHECK(cctx->status() == CURLE_URL_MALFORMAT);
  CHECK(cctx->http_code() == HTTP_NOT_SET);
}
