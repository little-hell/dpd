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

# stb_image.h
include_directories(SYSTEM "stb/")

# lib/
include_directories("lib/")
set(LIB_FILES "lib/image.c" "lib/image.h" "lib/common.c" "lib/common.h")
add_library(lib STATIC ${LIB_FILES})
target_link_libraries(lib m)

# dpd
add_executable("dpd" ${SOURCE_FILES})
set_property(TARGET dpd PROPERTY C_STANDARD 11)
target_link_libraries(dpd lib m)
