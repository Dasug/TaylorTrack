# Add Datastreamer executable

add_executable(sim_datastreamer sim_datastreamer.cpp input/dummy_input_strategy.cpp sim/streamer.cpp input/read_file_input_strategy.cpp)

# Add Datareceiver executable
add_executable(sim_datareceiver sim_datareceiver.cpp)

# Add test executable
add_executable(testunit input/dummy_input_strategy.cpp tests/testinit.cpp tests/simtest.cpp)

# link Yarp libraries
target_link_libraries(sim_datastreamer ${YARP_LIBRARIES})
target_link_libraries(sim_datareceiver ${YARP_LIBRARIES})

# link google libraries
target_link_libraries(testunit ${GTEST_LIBRARIES})