cmake_minimum_required(VERSION 3.23)

set(PROJECT_NAME IP_02_Demchenko_Oleksii)
set(CMAKE_CXX_STANDARD 20)
aux_source_directory(./src/ SOURCES)

project(${PROJECT_NAME})

file(GLOB HEADERS
        include/*.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

include_directories(./include/)