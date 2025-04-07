# add Eigen3 dependency
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

# add HerePlugin executable
add_executable(HerePlugin
    HivemapperApi.cpp
    HerePlugin.cpp
)

# add include directory
target_include_directories(HerePlugin PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/lib
    ${EIGEN3_INCLUDE_DIR}
)