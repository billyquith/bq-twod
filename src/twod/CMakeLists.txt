
set(LIB_NAME twod) # 2D

set(PROJECT_SOURCES
    config.hpp
    vector.hpp
    vector.cpp    
    )

# source_group("ImGui"
#              REGULAR_EXPRESSION "imgui/.*")

include_directories(${PROJECT_SOURCE_DIR}/src)

add_library(${LIB_NAME} STATIC ${PROJECT_SOURCES})

