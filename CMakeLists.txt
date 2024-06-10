cmake_minimum_required(VERSION 3.16)
project(FJE_2)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

set(SOURCES
        main.cpp
        src/json.cpp
        src/icon.cpp
        src/style.cpp
        src/visualization.cpp
        src/JsonLoader.cpp
)

set(HEADERS
        include/json.h
        include/icon.h
        include/style.h
        include/visualization.h
        include/JsonLoader.h
)

add_executable(fje ${SOURCES} ${HEADERS})
