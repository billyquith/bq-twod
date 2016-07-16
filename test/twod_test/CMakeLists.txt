
set(APP_NAME test_twod)
set(APP_VERSION "0.1")
set(APP_COPYRIGHT "Copyright 2016 Bill Quith")

set(PROJECT_SOURCES
    main.cpp
    
    # demos
    demo/demo.hpp
    demo/demo.cpp
    demo/intersect.hpp
    demo/intersect.cpp
    # demo/physics.hpp
    # demo/physics.cpp
    
    # ImGui
    imgui/imconfig.h
    imgui/imgui.h
    imgui/imgui_internal.h
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/stb_rect_pack.h
    imgui/stb_textedit.h
    imgui/stb_truetype.h
    imgui/imgui-SFML.cpp
    imgui/imgui-SFML.h
    )

source_group(ImGui REGULAR_EXPRESSION imgui/.*)
source_group(demo REGULAR_EXPRESSION demo/.*)

find_package(SFML 2.3 COMPONENTS system window graphics REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/src ${SFML_INCLUDE_DIR})

set(APP_BUILD_TYPE )
set(APP_RESOURCE_DIR "res")

# add_definitions("-DRESOURCE_DIR=\"${APP_RESOURCE_DIR}\"")

add_definitions(-std=c++11)

add_executable(${APP_NAME} ${APP_BUILD_TYPE} ${PROJECT_SOURCES})

target_link_libraries(${APP_NAME} twod ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

# add_custom_command(TARGET ${APP_NAME} POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#         ${CMAKE_SOURCE_DIR}/src/app/res
#         $<TARGET_FILE_DIR:${APP_NAME}>/${APP_RESOURCE_DIR})

