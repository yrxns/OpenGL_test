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

set(INCDIRS include)

foreach(incdir ${INCDIRS})
    include_directories(${incdir})
endforeach()


add_subdirectory(glm)
add_subdirectory(glfw)
add_subdirectory(glad)


aux_source_directory(./src DIR_SRCS)
add_executable (main ${DIR_SRCS})
target_link_libraries(main PUBLIC glm)
target_link_libraries(main PUBLIC glfw)
target_link_libraries(main PUBLIC glad)

# examples

### texture
set(DIR_SRCS "")
aux_source_directory(./src DIR_SRCS)
aux_source_directory(./examples/texture DIR_SRCS)
list(REMOVE_ITEM DIR_SRCS ./src/main.cpp)
message("..." ${DIR_SRCS})
add_executable (texture ${DIR_SRCS})
target_link_libraries(texture PUBLIC glm)
target_link_libraries(texture PUBLIC glfw)
target_link_libraries(texture PUBLIC glad)

### transform
set(DIR_SRCS "")
aux_source_directory(./src DIR_SRCS)
aux_source_directory(./examples/transform DIR_SRCS)
list(REMOVE_ITEM DIR_SRCS ./src/main.cpp)
add_executable (transform ${DIR_SRCS})
target_link_libraries(transform PUBLIC glm)
target_link_libraries(transform PUBLIC glfw)
target_link_libraries(transform PUBLIC glad)

# target_compile_definitions(${PROJECT_NAME} PUBLIC -DOPENGLTUTOR_HOME=\"${CMAKE_CURRENT_SOURCE_DIR}/\")
