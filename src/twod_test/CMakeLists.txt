
set(APP_NAME test_twod)
set(APP_VERSION "0.1")
set(APP_COPYRIGHT "Copyright 2016 Bill Quith")

set(PROJECT_SOURCES
    main.cpp
    )

find_package(SFML 2.3 COMPONENTS system window graphics REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/src ${SFML_INCLUDE_DIR})

set(APP_BUILD_TYPE )
set(APP_RESOURCE_DIR "res")

# add_definitions("-DRESOURCE_DIR=\"${APP_RESOURCE_DIR}\"")

add_executable(${APP_NAME} ${APP_BUILD_TYPE} ${PROJECT_SOURCES})

target_link_libraries(${APP_NAME} twod ${SFML_LIBRARIES})

# add_custom_command(TARGET ${APP_NAME} POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#         ${CMAKE_SOURCE_DIR}/src/app/res
#         $<TARGET_FILE_DIR:${APP_NAME}>/${APP_RESOURCE_DIR})

