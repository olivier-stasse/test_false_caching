cmake_minimum_required(VERSION 3.12)
project(openmptest CXX)

SET(CMAKE_CXX_STANDARD 14)
add_executable(test_false_caching test_false_caching.cpp)

find_package(OpenMP REQUIRED)
find_package(Boost REQUIRED timer)
target_link_libraries(test_false_caching PRIVATE
  OpenMP::OpenMP_CXX
  ${Boost_LIBRARIES})
