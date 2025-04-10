# add Eigen3 dependency
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

# add libcurl dependency
find_package(CURL REQUIRED)

# find hivecpp library
list(APPEND CMAKE_PREFIX_PATH "/opt/dashcam")
find_library(HIVECPP_LIBRARY NAMES hivecpp PATHS /opt/dashcam/bin/hivecpp/lib)
if (NOT HIVECPP_LIBRARY)
    message(FATAL_ERROR "Could not find the hivecpp library.")
endif()

# add ExamplePlugin executable
add_executable(ExamplePlugin
    ExamplePlugin.cpp
)

# add include directory
target_include_directories(ExamplePlugin PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/lib
    ${EIGEN3_INCLUDE_DIR}
    /opt/dashcam/bin/hivecpp/include
)

target_link_libraries(ExamplePlugin
    ${HIVECPP_LIBRARY}
    CURL::libcurl
)