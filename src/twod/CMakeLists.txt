
set(LIB_NAME twod) # 2D

set(PROJECT_SOURCES
    config.hpp
    vector.hpp
    vector.cpp    
    # imgui/imconfig.h
    # imgui/imgui.h
    # imgui/imgui_internal.h
    # imgui/imgui.cpp
    # imgui/imgui_demo.cpp
    # imgui/imgui_draw.cpp
    # imgui/imgui_impl_a5.cpp
    # imgui/imgui_impl_a5.h
    # imgui/stb_rect_pack.h
    # imgui/stb_textedit.h
    # imgui/stb_truetype.h
    )

# source_group("ImGui"
#              REGULAR_EXPRESSION "imgui/.*")

include_directories(${PROJECT_SOURCE_DIR}/src)

add_library(${LIB_NAME} STATIC ${PROJECT_SOURCES})

