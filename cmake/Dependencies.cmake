
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

find_package(fmt)
if(NOT fmt_FOUND)
    message(FATAL_ERROR
        "libspdlog-dev not found.\n"
        "On Ubuntu, install it with:\n"
        "  sudo apt install libfmt-dev"
    )
endif()

find_program(LCOV_EXECUTABLE lcov)
find_program(GENHTML_EXECUTABLE genhtml)

if(NOT LCOV_EXECUTABLE OR NOT GENHTML_EXECUTABLE)
    message(FATAL_ERROR
        "lcov/genhtml not found.\n"
        "On Ubuntu, install it with:\n"
        "  sudo apt install lcov"
    )
endif()

find_program(GCOV_EXECUTABLE gcov)

if(NOT GCOV_EXECUTABLE)
    message(FATAL_ERROR
        "lcov/genhtml not found.\n"
        "On Ubuntu, install it with:\n"
        "  sudo apt install gcov"
    )
endif()

include(FetchContent)

FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.12
)

FetchContent_MakeAvailable(doctest)
