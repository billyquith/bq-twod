###############################
# Twod
###############################

cmake_minimum_required(VERSION 3.1)

set(PROJECT_NAME bqtwod)
set(${PROJECT_NAME}_VERSION_MAJOR 0)
set(${PROJECT_NAME}_VERSION_MINOR 2)
set(${PROJECT_NAME}_VERSION_PATCH 0)

project(${PROJECT_NAME})

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
# make_directory(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
# make_directory(${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_subdirectory(src)
add_subdirectory(test)


