
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
add_definitions()
include_directories()
link_directories()
add_executable(rtclock rtclock.c)
target_link_libraries(rtclock "rt" )

