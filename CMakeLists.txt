cmake_minimum_required(VERSION 3.17)

project(ECS)

set(CMAKE_CXX_STANDARD 20)

include_directories(Include)

# Add source files
file(GLOB_RECURSE SOURCE_FILES
        Src/*.c
        Src/*.cpp)

#### Lib

#GLFW
set(GLFW_DIR ThirdParty/glfw)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${GLFW_DIR})
include_directories(${GLFW_DIR}/include)

#glad
file(GLOB_RECURSE GLAD_FILES
        ThirdParty/glad/Src/*.c)

include_directories(ThirdParty/glad/Include)

#OpenGL
find_package(OpenGL REQUIRED)

set(LIB OpenGL::GL glfw)

add_executable(ECS ${SOURCE_FILES} ${GLAD_FILES})
target_link_libraries(ECS ${LIB})