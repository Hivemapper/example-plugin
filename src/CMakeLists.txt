# add Eigen3 dependency
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

# add libcurl dependency
find_package(CURL REQUIRED)

if(NOT CMAKE_SYSROOT OR CMAKE_SYSROOT STREQUAL "")
    set(CMAKE_SYSROOT "")
    message(STATUS "CMAKE_SYSROOT was empty, defaulting to root: ${CMAKE_SYSROOT}")
else()
    message(STATUS "CMAKE_SYSROOT is: ${CMAKE_SYSROOT}")
endif()

# Set the expected include and lib paths
set(HIVECPP_LIB_PATH "${CMAKE_SYSROOT}/opt/dashcam/bin/hivecpp/lib")
set(HIVECPP_INCLUDE_DIR "${CMAKE_SYSROOT}/opt/dashcam/bin/hivecpp/include")

# Look for the hivecpp static library
find_library(HIVECPP_LIBRARY
    NAMES hivecpp
    PATHS "${HIVECPP_LIB_PATH}"
    NO_DEFAULT_PATH
)

# Check if everything was found
if(NOT HIVECPP_LIBRARY OR NOT HIVECPP_INCLUDE_DIR)
    message(FATAL_ERROR "Could not find the hivecpp library or includes.")
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
    ${HIVECPP_INCLUDE_DIR}
)

target_link_libraries(ExamplePlugin
    ${HIVECPP_LIBRARY}
    CURL::libcurl
)