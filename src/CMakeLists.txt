set(SOURCE_FILES
    dpd.c)

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall" "-g")

#option(STB_IMAGE_IMPLEMENTATION "stb_image implementation" ON)

if(STB_IMAGE_IMPLEMENTATION)
    add_definitions(-DSTB_IMAGE_IMPLEMENTATION)
endif()

include_directories("lib/")
set(LIB_FILES "lib/stb_image.h" "lib/image.c" "lib/image.h" "lib/common.c" "lib/common.h")

add_library(stb_static STATIC ${LIB_FILES})
target_link_libraries(stb_static m)
target_compile_definitions(stb_static PUBLIC LIBRARY_HEADER_ONLY)
set_target_properties(stb_static PROPERTIES LINKER_LANGUAGE C)

add_executable("dpd" ${SOURCE_FILES})
target_link_libraries(dpd stb_static m)
