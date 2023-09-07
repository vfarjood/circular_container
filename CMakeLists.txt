cmake_minimum_required(VERSION 3.16)

project(circular_container VERSION 1.0)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)

