set(SOURCE_FILES
    dpd.c)

set(CMAKE_C_FLAGS_DEBUG_INIT
    "-g"
    "-ggdb3"
    "-O1"
    "-fsanitize=address"
    "-fno-omit-frame-pointer")

if(STB_IMAGE_IMPLEMENTATION)
    add_definitions(-DSTB_IMAGE_IMPLEMENTATION)
endif()


# We didn't write stb_image.h, include as "system" header to surpress warnings about code we don't
# control.

include_directories(SYSTEM "stb/")
set(STB_LIB_FILES "stb/stb_image.h")
add_library(stb_static STATIC ${STB_LIB_FILES})
target_link_libraries(stb_static m)
target_compile_definitions(stb_static PUBLIC LIBRARY_HEADER_ONLY)
set_target_properties(stb_static PROPERTIES LINKER_LANGUAGE C)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(
        -Wall
        -Wpedantic
        -Werror
        -Wextra
        -Wunused-function
        -Wredundant-decls)
endif()

include_directories("lib/")
set(LIB_FILES "lib/image.c" "lib/image.h" "lib/common.c" "lib/common.h")
add_library(lib STATIC ${LIB_FILES})
set_property(TARGET lib PROPERTY C_STANDARD 11)
target_link_libraries(lib m)
target_compile_definitions(lib PUBLIC LIBRARY_HEADER_ONLY)
set_target_properties(lib PROPERTIES LINKER_LANGUAGE C C_STANDARD 11)

add_executable("dpd" ${SOURCE_FILES})
set_property(TARGET dpd PROPERTY C_STANDARD 11)
target_link_libraries(dpd lib stb_static m)
