cmake_minimum_required(VERSION 3.13)
project(symulacja_sieci)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors)

include_directories(
        include
)

set(SOURCE_FILES
        src/package.cpp
        src/storage_types.cpp
        src/nodes.cpp
        src/helpers.cpp
	src/factory.cpp
        )


add_executable(main__debug ${SOURCE_FILES} main.cpp)

