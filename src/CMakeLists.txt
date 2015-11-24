# Add Datastreamer executable
add_executable(sim_datastreamer sim_datastreamer.cpp)

# Add Datareceiver executable
add_executable(sim_datareceiver sim_datareceiver.cpp)

# link Yarp libraries
target_link_libraries(sim_datastreamer ${YARP_LIBRARIES})
target_link_libraries(sim_datareceiver ${YARP_LIBRARIES})

