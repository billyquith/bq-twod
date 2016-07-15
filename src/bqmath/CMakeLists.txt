
set(LIB_NAME bqmath) # misc

set(PROJECT_SOURCES
    config.hpp
    bqmath.hpp
    bqmath.cpp
    )

#source_group("Twod" REGULAR_EXPRESSION ".*")

include_directories(${PROJECT_SOURCE_DIR}/src
                    ${BQMATH_EXTERNAL_DIR}/chipmunk/include)

add_definitions(-std=c++11)

add_library(${LIB_NAME} STATIC ${PROJECT_SOURCES})

