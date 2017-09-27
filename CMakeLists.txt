cmake_minimum_required(VERSION 3.5)
project(omxcam)

file(GLOB SRC "src/*.c")

include_directories(
    include
    /opt/vc/include
)

link_directories(/opt/vc/lib)

add_definitions(-DOMX_SKIP64BIT)

add_library(omxcam ${SRC})
target_link_libraries(omxcam openmaxil bcm_host)

add_subdirectory(examples)

# install library and headers
install(TARGETS omxcam
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)
install(DIRECTORY include/ DESTINATION include)

# install cmake configuration file
set(CONF_INCLUDE_DIRS /opt/vc/include ${CMAKE_INSTALL_PREFIX}/include)
set(CONF_LIBRARY_DIRS /opt/vc/lib ${CMAKE_INSTALL_PREFIX}/lib)
configure_file(omxcamConfig.cmake.in "${PROJECT_BINARY_DIR}/omxcamConfig.cmake" @ONLY)
install(FILES "${PROJECT_BINARY_DIR}/omxcamConfig.cmake" DESTINATION "share/omxcam/cmake/" COMPONENT dev)
