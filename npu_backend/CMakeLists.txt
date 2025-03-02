cmake_minimum_required(VERSION 3.7)

project(npu_backend)

set(CMAKE_CXX_STANDARD 17)
set(THREADS_PREFER_PTHREAD ON)

find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package(Threads)

add_definitions(-DCROW_USE_BOOST)

include_directories(${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/npu_backend)
add_executable(npu_backend LoginController.cpp FanItem.cpp CreationController.cpp CreationItem.cpp main.cpp)
target_link_libraries(npu_backend ${Boost_LIBRARIES} Threads::Threads)
