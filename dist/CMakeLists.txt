set(build_static_lib TRUE)
add_subdirectory("easyloggingpp")
target_include_directories(easyloggingpp INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/easyloggingpp/src")
