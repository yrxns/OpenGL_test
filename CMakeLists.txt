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

set(INCDIRS include)

foreach(incdir ${INCDIRS})
    include_directories(${incdir})
endforeach()


add_subdirectory(glm)
add_subdirectory(glfw)
add_subdirectory(glad)

# 01_hello_window
# aux_source_directory(./examples/01_hello_window DIR_SRCS)
# add_executable (01_hello_window ${DIR_SRCS})
# target_link_libraries(01_hello_window PUBLIC glm)
# target_link_libraries(01_hello_window PUBLIC glfw)
# target_link_libraries(01_hello_window PUBLIC glad)


# 02_hello_triangle
# aux_source_directory(./examples/02_hello_triangle DIR_SRCS)
# add_executable (02_hello_triangle ${DIR_SRCS})
# target_link_libraries(02_hello_triangle PUBLIC glm)
# target_link_libraries(02_hello_triangle PUBLIC glfw)
# target_link_libraries(02_hello_triangle PUBLIC glad)

# 03_shader_class
aux_source_directory(./examples/03_shader_class DIR_SRCS)
add_executable (03_shader_class ${DIR_SRCS})
target_link_libraries(03_shader_class PUBLIC glm)
target_link_libraries(03_shader_class PUBLIC glfw)
target_link_libraries(03_shader_class PUBLIC glad)

# 
# aux_source_directory(./src DIR_SRCS)
# add_executable (test ${DIR_SRCS})
# target_link_libraries(test PUBLIC glm)
# target_link_libraries(test PUBLIC glfw)
# target_link_libraries(test PUBLIC glad)

# target_compile_definitions(${PROJECT_NAME} PUBLIC -DOPENGLTUTOR_HOME=\"${CMAKE_CURRENT_SOURCE_DIR}/\")
