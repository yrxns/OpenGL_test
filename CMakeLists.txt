cmake_minimum_required(VERSION 3.10)
project(demo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options($<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/utf-8$<SEMICOLON>/DNOMINMAX$<SEMICOLON>/D_USE_MATH_DEFINES>)
    add_compile_options($<$<COMPILE_LANG_AND_ID:C,MSVC>:/utf-8$<SEMICOLON>/DNOMINMAX$<SEMICOLON>/D_USE_MATH_DEFINES>)
elseif (CMAKE_COMPILER_IS_GNUCXX)
    if (CMAKE_BUILD_TYPE MATCHES "[Dd][Ee][Bb][Uu][Gg]")
        add_compile_options($<$<COMPILE_LANG_AND_ID:CXX,GNU>:-Wall$<SEMICOLON>-Wextra>)
        add_compile_options($<$<COMPILE_LANG_AND_ID:CXX,GNU>:-ftrapv$<SEMICOLON>-fbounds-check$<SEMICOLON>-fsanitize-trap>)
    endif()
endif()

#指定编译类型
set(CMAKE_BUILD_TYPE Debug)      #Debug

# Debug版本，开启调试信息，不进行代码优化
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")

set(INCDIRS include imgui .)

foreach(incdir ${INCDIRS})
    include_directories(${incdir})
endforeach()

add_subdirectory(glm)
add_subdirectory(glfw)
add_subdirectory(glad)


# aux_source_directory(./src DIR_SRCS)
# aux_source_directory(./imgui DIR_SRCS)
# add_executable (main ${DIR_SRCS})
# target_link_libraries(main PUBLIC glm)
# target_link_libraries(main PUBLIC glfw)
# target_link_libraries(main PUBLIC glad)

# target_link_libraries(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/libassimp.a)
# target_link_libraries(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/libzlibstatic.a)

# examples

## hello_window
set(DIR_SRCS "")
aux_source_directory(./src DIR_SRCS)
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/01_hello_window DIR_SRCS)
list(REMOVE_ITEM DIR_SRCS ./src/main.cpp)
message("..." ${DIR_SRCS})
add_executable (hello_window ${DIR_SRCS})
target_link_libraries(hello_window PUBLIC glm)
target_link_libraries(hello_window PUBLIC glfw)
target_link_libraries(hello_window PUBLIC glad)

## hello_triangle_1
set(DIR_SRCS "")
aux_source_directory(./src DIR_SRCS)
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/02_hello_triangle_1 DIR_SRCS)
list(REMOVE_ITEM DIR_SRCS ./src/main.cpp)
message("..." ${DIR_SRCS})
add_executable (hello_triangle_1 ${DIR_SRCS})
target_link_libraries(hello_triangle_1 PUBLIC glm)
target_link_libraries(hello_triangle_1 PUBLIC glfw)
target_link_libraries(hello_triangle_1 PUBLIC glad)