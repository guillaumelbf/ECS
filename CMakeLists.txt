cmake_minimum_required(VERSION 3.17)

project(ECS)

set(CMAKE_CXX_STANDARD 20)

include_directories(Include)

# Add source files
file(GLOB_RECURSE SOURCE_FILES
        Src/*.c
        Src/*.cpp)

#### Lib


add_executable(ECS ${SOURCE_FILES})