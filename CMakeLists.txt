cmake_minimum_required(VERSION 3.14)
project(RMK LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")

include(FetchContent)
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.12.0
)
FetchContent_MakeAvailable(json)


FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.16.0
)

set(INSTALL_GTEST OFF)
FetchContent_MakeAvailable(googletest)

add_executable(rmk
  main.cpp
  rmk.cpp
  cashier.cpp
  receipt.cpp
  database.cpp
)

target_link_libraries(rmk PRIVATE nlohmann_json::nlohmann_json)

enable_testing()

file(GLOB TEST_SOURCES
  tests/test_*.cpp
)

add_executable(unit_tests
  ${TEST_SOURCES}
  receipt.cpp
  cashier.cpp
  database.cpp
  rmk.cpp
)

target_include_directories(unit_tests PRIVATE ${PROJECT_SOURCE_DIR})
target_link_libraries(unit_tests gtest_main nlohmann_json::nlohmann_json)