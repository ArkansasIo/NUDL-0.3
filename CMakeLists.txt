cmake_minimum_required(VERSION 3.20)
project(nudl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(nudl_frontend
  03-compiler/src/lexer.cpp
  03-compiler/src/parser.cpp
  03-compiler/src/diagnostics.cpp
)
target_include_directories(nudl_frontend PUBLIC 03-compiler/include)

add_executable(nudlc 03-compiler/src/main.cpp)
target_link_libraries(nudlc PRIVATE nudl_frontend)

enable_testing()
add_executable(nudl_smoke_test 07-tests/cpp/smoke_test.cpp)
target_link_libraries(nudl_smoke_test PRIVATE nudl_frontend)
add_test(NAME nudl_smoke_test COMMAND nudl_smoke_test)
