###############################
# BQ-Twod (2D utilities)
###############################

cmake_minimum_required(VERSION 3.1)

set(PROJECT_NAME bqtwod)
set(${PROJECT_NAME}_VERSION_MAJOR 0)
set(${PROJECT_NAME}_VERSION_MINOR 2)
set(${PROJECT_NAME}_VERSION_PATCH 0)

project(${PROJECT_NAME})

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

add_subdirectory(src)
add_subdirectory(test)


