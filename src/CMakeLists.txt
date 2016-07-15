
set(BQMATH_EXTERNAL_DIR "${CMAKE_CURRENT_LIST_DIR}/external")

add_subdirectory(twod)

# chipmunk
set(BUILD_SHARED OFF)
add_subdirectory(external/chipmunk)
#source_group(chipmunk REGULAR_EXPRESSION chipmunk/.*)
