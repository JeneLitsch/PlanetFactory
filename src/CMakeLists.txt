cmake_minimum_required (VERSION 3.8)

add_compile_options("-std=c++20" "-g")

add_executable(app main.cxx App.cxx)
add_subdirectory(core)
add_subdirectory(level)
target_link_libraries(app core level)
target_link_libraries(app "pthread" "sfml-graphics" "sfml-audio" "sfml-network" "sfml-system" "sfml-window" imgui)