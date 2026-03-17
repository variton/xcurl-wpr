
find_package(CURL)
if(NOT CURL_FOUND)
    message(FATAL_ERROR
        "libcurl not found.\n"
        "On Ubuntu, install it with:\n"
        "  sudo apt install libcurl4-openssl-dev"
    )
endif()

find_package(spdlog)
if(NOT spdlog_FOUND)
    message(FATAL_ERROR
        "libspdlog-dev not found.\n"
        "On Ubuntu, install it with:\n"
        "  sudo apt install libspdlog-dev"
    )
endif()

include(FetchContent)

FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.12
)

FetchContent_MakeAvailable(doctest)
