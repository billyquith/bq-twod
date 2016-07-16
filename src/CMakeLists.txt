
set(BQTWOD_EXTERNAL_DIR "${CMAKE_CURRENT_LIST_DIR}/external")

add_subdirectory(bqmath)

add_subdirectory(twod)

# chipmunk tuning
set(BUILD_SHARED OFF)
add_subdirectory(external/chipmunk)
#source_group(chipmunk REGULAR_EXPRESSION chipmunk/.*)

set(BQTWOD_CHIPMUNK_LIB chipmunk_static)
target_compile_definitions(${BQTWOD_CHIPMUNK_LIB} PRIVATE
    "CP_BOOL_TYPE=bool" "cpTrue=true" "cpFalse=false"
    "CP_USE_DOUBLES=1"
    )
