
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
    demo/physics.hpp
    demo/physics.cpp
    
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

if(APPLE)
    set(APP_BUILD_TYPE MACOSX_BUNDLE)
    set(APP_RESOURCE_PATH "$<TARGET_FILE_DIR:${APP_NAME}>/../Resources")
else()
    set(APP_BUILD_TYPE )
    set(APP_RESOURCE_PATH "$<TARGET_FILE_DIR:${APP_NAME}>/res")
endif()

# add_definitions("-DRESOURCE_DIR=\"${APP_RESOURCE_DIR}\"")
add_definitions(-std=c++11)

add_executable(${APP_NAME} ${APP_BUILD_TYPE} ${PROJECT_SOURCES})

target_link_libraries(${APP_NAME} bqtwod ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

# add_custom_command(TARGET ${APP_NAME} POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#         ${CMAKE_SOURCE_DIR}/src/app/res
#         $<TARGET_FILE_DIR:${APP_NAME}>/${APP_RESOURCE_DIR})

if(APPLE)
    # Mac OS X bundle support.
    set_target_properties(${APP_NAME} PROPERTIES
        MACOSX_BUNDLE_COPYRIGHT "${APP_COPYRIGHT}"
        # MACOSX_BUNDLE_ICON_FILE "Icon.icns"
        MACOSX_BUNDLE_INFO_STRING "${APP_VERSION}, ${APP_COPYRIGHT}"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "${APP_VERSION}"
        MACOSX_BUNDLE_LONG_VERSION_STRING "${PROJECT_NAME} app v${APP_VERSION}"
        MACOSX_BUNDLE_GUI_IDENTIFIER "org.quith.${PROJECT_NAME}.app"
        )
endif()
