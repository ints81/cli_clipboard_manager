cmake_minimum_required(VERSION 3.14.0)
project(cli_clipboard_manager VERSION 0.1.0)

include(CTest)
enable_testing()

add_subdirectory(third_party/leveldb)
add_subdirectory(third_party/clip)

add_executable(cli_clipboard_manager main.cpp)

target_link_libraries(cli_clipboard_manager leveldb)

target_include_directories(cli_clipboard_manager PUBLIC ${CMAKE_SOURCE_DIR}/third_party/clip/)
target_link_libraries(cli_clipboard_manager clip)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
