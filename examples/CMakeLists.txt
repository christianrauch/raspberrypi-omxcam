cmake_minimum_required(VERSION 3.5)
project(examples)

find_package(Threads REQUIRED)

include_directories( ../include )

# still
set(STI_EXP jpeg rgb yuv)
foreach(still_example ${STI_EXP})
    add_executable(${still_example} still/${still_example}/${still_example}.c)
    target_link_libraries(${still_example} omxcam)
endforeach()

# video
#set(VID_EXMP h264 h264-motion h264-motion-nopthread h264-nopthread h264-stdout h264-update h264-update-timer rgb yuv)
set(VID_EXP h264 h264-motion h264-motion-nopthread h264-nopthread h264-stdout h264-update h264-update-timer)
foreach(vid_example ${VID_EXP})
    add_executable(${vid_example} video/${vid_example}/${vid_example}.c)
    target_link_libraries(${vid_example} omxcam Threads::Threads)
endforeach()

# video examples rgb and yuv are conflicting with still examples
add_executable(vid_rgb video/rgb/rgb.c)
target_link_libraries(vid_rgb omxcam Threads::Threads)

add_executable(vid_yuv video/yuv/yuv.c)
target_link_libraries(vid_yuv omxcam Threads::Threads)
