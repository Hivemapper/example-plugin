# add Eigen3 dependency
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

# add libcurl dependency
find_package(CURL REQUIRED)

# add HerePlugin executable
add_executable(HerePlugin
    LandmarksApi.cpp
    HerePlugin.cpp
)

# add include directory
target_include_directories(HerePlugin PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/lib
    ${EIGEN3_INCLUDE_DIR}
)

target_link_libraries(HerePlugin
    PRIVATE CURL::libcurl
)