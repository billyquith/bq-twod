
set(BQTWOD_EXTERNAL_DIR "${CMAKE_CURRENT_LIST_DIR}/external")

add_subdirectory(twod)

##################################################
# handy

add_subdirectory(external/handy)

target_include_directories(twod PUBLIC external/handy/src)

##################################################
# chipmunk

set(BUILD_SHARED OFF)  # for Chipmunk only
add_subdirectory(external/chipmunk)

#source_group(chipmunk REGULAR_EXPRESSION chipmunk/.*)

set(BQTWOD_CHIPMUNK_LIB chipmunk_static)

target_compile_definitions(${BQTWOD_CHIPMUNK_LIB} PUBLIC
    "CP_BOOL_TYPE=bool" "cpTrue=true" "cpFalse=false"
    "CP_USE_DOUBLES=1"
    )
    
target_include_directories(${BQTWOD_CHIPMUNK_LIB}
                           PUBLIC ${BQTWOD_EXTERNAL_DIR}/chipmunk/include/chipmunk)    

unset(BUILD_SHARED)

##################################################
# bq-twod

# Link to this for automatic dependencies
add_library(bqtwod INTERFACE)
target_link_libraries(bqtwod INTERFACE twod chipmunk_static)

