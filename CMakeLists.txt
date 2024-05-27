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


aux_source_directory(./src DIR_SRCS)
aux_source_directory(./imgui DIR_SRCS)
add_executable (main ${DIR_SRCS})
target_link_libraries(main PUBLIC glm)
target_link_libraries(main PUBLIC glfw)
target_link_libraries(main PUBLIC glad)

target_link_libraries(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/libassimp.a)
target_link_libraries(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/libzlibstatic.a)

# examples

## hello_window
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/01_hello_window DIR_SRCS)
add_executable (hello_window ${DIR_SRCS})
target_link_libraries(hello_window PUBLIC glm)
target_link_libraries(hello_window PUBLIC glfw)
target_link_libraries(hello_window PUBLIC glad)

## hello_triangle_1
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/02_hello_triangle_1 DIR_SRCS)
add_executable (hello_triangle_1 ${DIR_SRCS})
target_link_libraries(hello_triangle_1 PUBLIC glm)
target_link_libraries(hello_triangle_1 PUBLIC glfw)
target_link_libraries(hello_triangle_1 PUBLIC glad)

## hello_triangle_2
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/02_hello_triangle_2 DIR_SRCS)
add_executable (hello_triangle_2 ${DIR_SRCS})
target_link_libraries(hello_triangle_2 PUBLIC glm)
target_link_libraries(hello_triangle_2 PUBLIC glfw)
target_link_libraries(hello_triangle_2 PUBLIC glad)

## hello_triangle_exercise_1
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/03_hello_triangle_exercise_1 DIR_SRCS)
add_executable (hello_triangle_exercise_1 ${DIR_SRCS})
target_link_libraries(hello_triangle_exercise_1 PUBLIC glm)
target_link_libraries(hello_triangle_exercise_1 PUBLIC glfw)
target_link_libraries(hello_triangle_exercise_1 PUBLIC glad)

## hello_triangle_exercise_2
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/03_hello_triangle_exercise_2 DIR_SRCS)
add_executable (hello_triangle_exercise_2 ${DIR_SRCS})
target_link_libraries(hello_triangle_exercise_2 PUBLIC glm)
target_link_libraries(hello_triangle_exercise_2 PUBLIC glfw)
target_link_libraries(hello_triangle_exercise_2 PUBLIC glad)

## shader_glsl
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/04_shader_glsl DIR_SRCS)
add_executable (shader_glsl ${DIR_SRCS})
target_link_libraries(shader_glsl PUBLIC glm)
target_link_libraries(shader_glsl PUBLIC glfw)
target_link_libraries(shader_glsl PUBLIC glad)

## shader_glsl_2
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/04_shader_glsl_2 DIR_SRCS)
add_executable (shader_glsl_2 ${DIR_SRCS})
target_link_libraries(shader_glsl_2 PUBLIC glm)
target_link_libraries(shader_glsl_2 PUBLIC glfw)
target_link_libraries(shader_glsl_2 PUBLIC glad)

## shader_glsl_2
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/05_shader_class DIR_SRCS)
add_executable (shader_class ${DIR_SRCS})
target_link_libraries(shader_class PUBLIC glm)
target_link_libraries(shader_class PUBLIC glfw)
target_link_libraries(shader_class PUBLIC glad)

## glsl_exercise
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/06_glsl_exercise DIR_SRCS)
add_executable (glsl_exercise ${DIR_SRCS})
target_link_libraries(glsl_exercise PUBLIC glm)
target_link_libraries(glsl_exercise PUBLIC glfw)
target_link_libraries(glsl_exercise PUBLIC glad)

## glsl_exercise_1
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/06_glsl_exercise_1 DIR_SRCS)
add_executable (glsl_exercise_1 ${DIR_SRCS})
target_link_libraries(glsl_exercise_1 PUBLIC glm)
target_link_libraries(glsl_exercise_1 PUBLIC glfw)
target_link_libraries(glsl_exercise_1 PUBLIC glad)

## glsl_exercise_2
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/06_glsl_exercise_2 DIR_SRCS)
add_executable (glsl_exercise_2 ${DIR_SRCS})
target_link_libraries(glsl_exercise_2 PUBLIC glm)
target_link_libraries(glsl_exercise_2 PUBLIC glfw)
target_link_libraries(glsl_exercise_2 PUBLIC glad)

## glsl_exercise_3
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/06_glsl_exercise_3 DIR_SRCS)
add_executable (glsl_exercise_3 ${DIR_SRCS})
target_link_libraries(glsl_exercise_3 PUBLIC glm)
target_link_libraries(glsl_exercise_3 PUBLIC glfw)
target_link_libraries(glsl_exercise_3 PUBLIC glad)

## load_texture
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/07_load_texture DIR_SRCS)
add_executable (load_texture ${DIR_SRCS})
target_link_libraries(load_texture PUBLIC glm)
target_link_libraries(load_texture PUBLIC glfw)
target_link_libraries(load_texture PUBLIC glad)

## load_texture_exercise
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/08_load_texture_exercise DIR_SRCS)
add_executable (load_texture_exercise ${DIR_SRCS})
target_link_libraries(load_texture_exercise PUBLIC glm)
target_link_libraries(load_texture_exercise PUBLIC glfw)
target_link_libraries(load_texture_exercise PUBLIC glad)

## load_texture_exercise_1
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/08_load_texture_exercise_1 DIR_SRCS)
add_executable (load_texture_exercise_1 ${DIR_SRCS})
target_link_libraries(load_texture_exercise_1 PUBLIC glm)
target_link_libraries(load_texture_exercise_1 PUBLIC glfw)
target_link_libraries(load_texture_exercise_1 PUBLIC glad)

## load_texture_exercise_2
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/08_load_texture_exercise_2 DIR_SRCS)
add_executable (load_texture_exercise_2 ${DIR_SRCS})
target_link_libraries(load_texture_exercise_2 PUBLIC glm)
target_link_libraries(load_texture_exercise_2 PUBLIC glfw)
target_link_libraries(load_texture_exercise_2 PUBLIC glad)

## load_texture_exercise_3
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/08_load_texture_exercise_3 DIR_SRCS)
add_executable (load_texture_exercise_3 ${DIR_SRCS})
target_link_libraries(load_texture_exercise_3 PUBLIC glm)
target_link_libraries(load_texture_exercise_3 PUBLIC glfw)
target_link_libraries(load_texture_exercise_3 PUBLIC glad)

## transform
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/09_transform DIR_SRCS)
add_executable (transform ${DIR_SRCS})
target_link_libraries(transform PUBLIC glm)
target_link_libraries(transform PUBLIC glfw)
target_link_libraries(transform PUBLIC glad)

## transform_1
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/09_transform_1 DIR_SRCS)
add_executable (transform_1 ${DIR_SRCS})
target_link_libraries(transform_1 PUBLIC glm)
target_link_libraries(transform_1 PUBLIC glfw)
target_link_libraries(transform_1 PUBLIC glad)

## use_plane_geometry
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/10_use_plane_geometry DIR_SRCS)
add_executable (use_plane_geometry ${DIR_SRCS})
target_link_libraries(use_plane_geometry PUBLIC glm)
target_link_libraries(use_plane_geometry PUBLIC glfw)
target_link_libraries(use_plane_geometry PUBLIC glad)

## use_sphere_geometry
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/11_use_sphere_geometry DIR_SRCS)
add_executable (use_sphere_geometry ${DIR_SRCS})
target_link_libraries(use_sphere_geometry PUBLIC glm)
target_link_libraries(use_sphere_geometry PUBLIC glfw)
target_link_libraries(use_sphere_geometry PUBLIC glad)

## use_box_geometry
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/12_use_box_geometry DIR_SRCS)
add_executable (use_box_geometry ${DIR_SRCS})
target_link_libraries(use_box_geometry PUBLIC glm)
target_link_libraries(use_box_geometry PUBLIC glfw)
target_link_libraries(use_box_geometry PUBLIC glad)

## model_view_projection
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/13_model_view_projection DIR_SRCS)
add_executable (model_view_projection ${DIR_SRCS})
target_link_libraries(model_view_projection PUBLIC glm)
target_link_libraries(model_view_projection PUBLIC glfw)
target_link_libraries(model_view_projection PUBLIC glad)

## use_image_ui
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/14_use_image_ui DIR_SRCS)
add_executable (use_image_ui ${DIR_SRCS})
target_link_libraries(use_image_ui PUBLIC glm)
target_link_libraries(use_image_ui PUBLIC glfw)
target_link_libraries(use_image_ui PUBLIC glad)

## mvp_matrix_exercise
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/15_mvp_matrix_exercise DIR_SRCS)
add_executable (mvp_matrix_exercise ${DIR_SRCS})
target_link_libraries(mvp_matrix_exercise PUBLIC glm)
target_link_libraries(mvp_matrix_exercise PUBLIC glfw)
target_link_libraries(mvp_matrix_exercise PUBLIC glad)

## use_camera
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/16_use_camera DIR_SRCS)
add_executable (use_camera ${DIR_SRCS})
target_link_libraries(use_camera PUBLIC glm)
target_link_libraries(use_camera PUBLIC glfw)
target_link_libraries(use_camera PUBLIC glad)

## use_camera_class
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/17_use_camera_class DIR_SRCS)
add_executable (use_camera_class ${DIR_SRCS})
target_link_libraries(use_camera_class PUBLIC glm)
target_link_libraries(use_camera_class PUBLIC glfw)
target_link_libraries(use_camera_class PUBLIC glad)

## light_scene
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/18_light_scene DIR_SRCS)
add_executable (light_scene ${DIR_SRCS})
target_link_libraries(light_scene PUBLIC glm)
target_link_libraries(light_scene PUBLIC glfw)
target_link_libraries(light_scene PUBLIC glad)

## basic_lighting
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/19_basic_lighting DIR_SRCS)
add_executable (basic_lighting ${DIR_SRCS})
target_link_libraries(basic_lighting PUBLIC glm)
target_link_libraries(basic_lighting PUBLIC glfw)
target_link_libraries(basic_lighting PUBLIC glad)

## light_material
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/20_light_material DIR_SRCS)
add_executable (light_material ${DIR_SRCS})
target_link_libraries(light_material PUBLIC glm)
target_link_libraries(light_material PUBLIC glfw)
target_link_libraries(light_material PUBLIC glad)

## light_map
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/21_light_map DIR_SRCS)
add_executable (light_map ${DIR_SRCS})
target_link_libraries(light_map PUBLIC glm)
target_link_libraries(light_map PUBLIC glfw)
target_link_libraries(light_map PUBLIC glad)

## light_map_exercise
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/22_light_map_exercise DIR_SRCS)
add_executable (light_map_exercise ${DIR_SRCS})
target_link_libraries(light_map_exercise PUBLIC glm)
target_link_libraries(light_map_exercise PUBLIC glfw)
target_link_libraries(light_map_exercise PUBLIC glad)

## light_map_exercise_1
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/22_light_map_exercise_1 DIR_SRCS)
add_executable (light_map_exercise_1 ${DIR_SRCS})
target_link_libraries(light_map_exercise_1 PUBLIC glm)
target_link_libraries(light_map_exercise_1 PUBLIC glfw)
target_link_libraries(light_map_exercise_1 PUBLIC glad)

## light_map_exercise_2
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/22_light_map_exercise_2 DIR_SRCS)
add_executable (light_map_exercise_2 ${DIR_SRCS})
target_link_libraries(light_map_exercise_2 PUBLIC glm)
target_link_libraries(light_map_exercise_2 PUBLIC glfw)
target_link_libraries(light_map_exercise_2 PUBLIC glad)

## light_map_exercise_3
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/22_light_map_exercise_3 DIR_SRCS)
add_executable (light_map_exercise_3 ${DIR_SRCS})
target_link_libraries(light_map_exercise_3 PUBLIC glm)
target_link_libraries(light_map_exercise_3 PUBLIC glfw)
target_link_libraries(light_map_exercise_3 PUBLIC glad)

## direction_light
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/23_direction_light DIR_SRCS)
add_executable (direction_light ${DIR_SRCS})
target_link_libraries(direction_light PUBLIC glm)
target_link_libraries(direction_light PUBLIC glfw)
target_link_libraries(direction_light PUBLIC glad)

## point_light
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/24_point_light DIR_SRCS)
add_executable (point_light ${DIR_SRCS})
target_link_libraries(point_light PUBLIC glm)
target_link_libraries(point_light PUBLIC glfw)
target_link_libraries(point_light PUBLIC glad)

## spot_light
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/25_spot_light DIR_SRCS)
add_executable (spot_light ${DIR_SRCS})
target_link_libraries(spot_light PUBLIC glm)
target_link_libraries(spot_light PUBLIC glfw)
target_link_libraries(spot_light PUBLIC glad)

## spot_light_1
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/25_spot_light_1 DIR_SRCS)
add_executable (spot_light_1 ${DIR_SRCS})
target_link_libraries(spot_light_1 PUBLIC glm)
target_link_libraries(spot_light_1 PUBLIC glfw)
target_link_libraries(spot_light_1 PUBLIC glad)

## multiple_lights
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/26_multiple_lights DIR_SRCS)
add_executable (multiple_lights ${DIR_SRCS})
target_link_libraries(multiple_lights PUBLIC glm)
target_link_libraries(multiple_lights PUBLIC glfw)
target_link_libraries(multiple_lights PUBLIC glad)

## load_model
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/27_load_model DIR_SRCS)
add_executable (load_model ${DIR_SRCS})
target_link_libraries(load_model PUBLIC glm)
target_link_libraries(load_model PUBLIC glfw)
target_link_libraries(load_model PUBLIC glad)
target_link_libraries(load_model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/libassimp.a)
target_link_libraries(load_model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/libzlibstatic.a)

## depth_testing
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/28_depth_testing DIR_SRCS)
add_executable (depth_testing ${DIR_SRCS})
target_link_libraries(depth_testing PUBLIC glm)
target_link_libraries(depth_testing PUBLIC glfw)
target_link_libraries(depth_testing PUBLIC glad)

## stencil_testing
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/29_stencil_testing DIR_SRCS)
add_executable (stencil_testing ${DIR_SRCS})
target_link_libraries(stencil_testing PUBLIC glm)
target_link_libraries(stencil_testing PUBLIC glfw)
target_link_libraries(stencil_testing PUBLIC glad)

## blending
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/30_blending DIR_SRCS)
add_executable (blending ${DIR_SRCS})
target_link_libraries(blending PUBLIC glm)
target_link_libraries(blending PUBLIC glfw)
target_link_libraries(blending PUBLIC glad)

## blending_1
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/30_blending_1 DIR_SRCS)
add_executable (blending_1 ${DIR_SRCS})
target_link_libraries(blending_1 PUBLIC glm)
target_link_libraries(blending_1 PUBLIC glfw)
target_link_libraries(blending_1 PUBLIC glad)

## face_culling
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/31_face_culling DIR_SRCS)
add_executable (face_culling ${DIR_SRCS})
target_link_libraries(face_culling PUBLIC glm)
target_link_libraries(face_culling PUBLIC glfw)
target_link_libraries(face_culling PUBLIC glad)

## frame_buffers
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/32_frame_buffers DIR_SRCS)
add_executable (frame_buffers ${DIR_SRCS})
target_link_libraries(frame_buffers PUBLIC glm)
target_link_libraries(frame_buffers PUBLIC glfw)
target_link_libraries(frame_buffers PUBLIC glad)

## frame_buffers_1
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/32_frame_buffers_1 DIR_SRCS)
add_executable (frame_buffers_1 ${DIR_SRCS})
target_link_libraries(frame_buffers_1 PUBLIC glm)
target_link_libraries(frame_buffers_1 PUBLIC glfw)
target_link_libraries(frame_buffers_1 PUBLIC glad)

## frame_buffers_2
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/32_frame_buffers_2 DIR_SRCS)
add_executable (frame_buffers_2 ${DIR_SRCS})
target_link_libraries(frame_buffers_2 PUBLIC glm)
target_link_libraries(frame_buffers_2 PUBLIC glfw)
target_link_libraries(frame_buffers_2 PUBLIC glad)

## frame_buffers_3
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/32_frame_buffers_3 DIR_SRCS)
add_executable (frame_buffers_3 ${DIR_SRCS})
target_link_libraries(frame_buffers_3 PUBLIC glm)
target_link_libraries(frame_buffers_3 PUBLIC glfw)
target_link_libraries(frame_buffers_3 PUBLIC glad)

## frame_buffers_4
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/32_frame_buffers_4 DIR_SRCS)
add_executable (frame_buffers_4 ${DIR_SRCS})
target_link_libraries(frame_buffers_4 PUBLIC glm)
target_link_libraries(frame_buffers_4 PUBLIC glfw)
target_link_libraries(frame_buffers_4 PUBLIC glad)

## frame_buffers_5
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/32_frame_buffers_5 DIR_SRCS)
add_executable (frame_buffers_5 ${DIR_SRCS})
target_link_libraries(frame_buffers_5 PUBLIC glm)
target_link_libraries(frame_buffers_5 PUBLIC glfw)
target_link_libraries(frame_buffers_5 PUBLIC glad)

## frame_buffers_6
set(DIR_SRCS "")
aux_source_directory(./imgui DIR_SRCS)
aux_source_directory(./examples/32_frame_buffers_6 DIR_SRCS)
add_executable (frame_buffers_6 ${DIR_SRCS})
target_link_libraries(frame_buffers_6 PUBLIC glm)
target_link_libraries(frame_buffers_6 PUBLIC glfw)
target_link_libraries(frame_buffers_6 PUBLIC glad)