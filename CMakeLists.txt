project(Winter2k23 CXX C)
cmake_minimum_required(VERSION 3.13)

add_executable(main main.cpp)

add_subdirectory(DB)
target_link_libraries(main mysqlcppconn DB)
