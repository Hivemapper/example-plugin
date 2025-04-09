# add Eigen3 dependency
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

# add libcurl dependency
find_package(CURL REQUIRED)

# add hivecpp library
add_library(hivecpp STATIC
    src/PositionApi.cpp
    src/LandmarksApi.cpp
    src/FileApi.cpp
    src/Utils.cpp
)

# add include directory
target_include_directories(hivecpp PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/lib
    ${EIGEN3_INCLUDE_DIR}
)

target_link_libraries(hivecpp
    PRIVATE CURL::libcurl
)