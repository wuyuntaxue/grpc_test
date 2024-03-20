cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME "grpc_sample")

project(${PROJECT_NAME} VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

link_directories("${PROJECT_SOURCE_DIR}/3rdparty/grpc-1.62.1/lib/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -Werror=return-type -Wl,--copy-dt-needed-entries")


add_subdirectory(${PROJECT_SOURCE_DIR}/example/server)

add_subdirectory(${PROJECT_SOURCE_DIR}/example/client)

add_subdirectory(${PROJECT_SOURCE_DIR}/server)

add_subdirectory(${PROJECT_SOURCE_DIR}/client)