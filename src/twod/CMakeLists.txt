
set(LIB_NAME twod) # 2D

set(PROJECT_SOURCES
    config.hpp
    
    # types
    types/rect.hpp
    types/rect.cpp    
    types/vector.hpp
    types/vector.cpp
    
    # chipmunk++
    chipmunk.hpp
    chipmunk.cpp
    chipmunkpp/arbiter.cpp
    chipmunkpp/arbiter.hpp
    chipmunkpp/bb.cpp
    chipmunkpp/bb.hpp
    chipmunkpp/body.cpp
    chipmunkpp/body.hpp
    chipmunkpp/circleshape.cpp
    chipmunkpp/circleshape.hpp
    chipmunkpp/polyshape.cpp
    chipmunkpp/polyshape.hpp
    chipmunkpp/segmentqueryinfo.hpp
    chipmunkpp/segmentshape.cpp
    chipmunkpp/segmentshape.hpp
    chipmunkpp/shape.cpp
    chipmunkpp/shape.hpp
    chipmunkpp/space.cpp
    chipmunkpp/space.hpp
    chipmunkpp/types.cpp
    chipmunkpp/types.hpp
    chipmunkpp/vect.cpp
    chipmunkpp/vect.hpp
    )

source_group("Twod" REGULAR_EXPRESSION ".*")
source_group("Types" REGULAR_EXPRESSION "types/.*")
source_group("Chipmunk" REGULAR_EXPRESSION "chipmunkpp/.*")

include_directories(${PROJECT_SOURCE_DIR}/src
                    ${BQTWOD_EXTERNAL_DIR}/chipmunk/include)

add_definitions(-std=c++11)

add_library(${LIB_NAME} STATIC ${PROJECT_SOURCES})

