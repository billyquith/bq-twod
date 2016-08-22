###############################
# Lib Twod
###############################

set(LIB_NAME twod) # 2D

set(PROJECT_SOURCES
    config.hpp
    
    # types
    types/rect.hpp
    types/rect.cpp    
    types/vector.hpp
    types/vector.cpp
    
    # physics/Chipmunk
    physics/physics.hpp
    physics/physics.cpp
)

source_group("Twod" REGULAR_EXPRESSION ".*")
source_group("Types" REGULAR_EXPRESSION "types/.*")
source_group("Physics" REGULAR_EXPRESSION "physics/.*")

include_directories(${PROJECT_SOURCE_DIR}/src
                    ${BQTWOD_EXTERNAL_DIR}/chipmunk/include)

add_library(${LIB_NAME} STATIC ${PROJECT_SOURCES})

###############################
# installing
###############################

install(CODE "MESSAGE(\"Installing ${LIB_NAME} to ${CMAKE_INSTALL_PREFIX}.\")")

install(DIRECTORY DESTINATION "${CMAKE_INSTALL_PREFIX}/include")
install(DIRECTORY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
install(DIRECTORY DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")

install(DIRECTORY . DESTINATION include COMPONENT dev
        FILES_MATCHING PATTERN "*.hpp")

install(TARGETS twod
        RUNTIME DESTINATION bin COMPONENT bin
        LIBRARY DESTINATION lib COMPONENT bin
        ARCHIVE DESTINATION lib COMPONENT dev)

