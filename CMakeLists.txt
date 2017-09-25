cmake_minimum_required(VERSION 3.5)
project(omxcam)

file(GLOB SRC "src/*.c")

include_directories(
    include
    /opt/vc/include
)

link_directories(/opt/vc/lib)

add_definitions(
    -DSTANDALONE -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS 
    -DTARGET_POSIX -D_LINUX -DPIC -D_REENTRANT -D_LARGEFILE64_SOURCE 
    -D_FILE_OFFSET_BITS=64 -U_FORTIFY_SOURCE -DHAVE_LIBOPENMAX=2 -DOMX 
    -DOMX_SKIP64BIT -DUSE_EXTERNAL_OMX -DHAVE_LIBBCM_HOST 
    -DUSE_EXTERNAL_LIBBCM_HOST -DUSE_VCHIQ_ARM -fPIC -ftree-vectorize -pipe 
    -Werror -g -Wall -O2 -fvisibility=hidden -DOMXCAM_DEBUG
)

add_library(omxcam ${SRC})
target_link_libraries(omxcam openmaxil bcm_host)

add_subdirectory(examples)

install(TARGETS omxcam
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)
install(DIRECTORY include/ DESTINATION include)
