# add Eigen3 dependency
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

# add ExamplePlugin executable
add_executable(ExamplePlugin
    ExamplePlugin.cpp
)

# add include directory
target_include_directories(ExamplePlugin PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/lib
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/hive-cpp/include
    ${EIGEN3_INCLUDE_DIR}
)

target_link_libraries(ExamplePlugin
    PRIVATE hivecpp
)