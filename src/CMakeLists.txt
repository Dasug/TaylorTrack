# Add Datastreamer executable

add_executable(sim_datastreamer sim_datastreamer.cpp input/dummy_input_strategy.cpp sim/streamer.cpp input/read_file_input_strategy.cpp utils/parameter_parser.cpp)

# Add Datareceiver executable
add_executable(sim_datareceiver sim_datareceiver.cpp utils/parameter_parser.cpp )

# Add test executable
add_executable(testunit input/dummy_input_strategy.cpp sim/streamer.cpp tests/testinit.cpp tests/simtest.cpp tests/streamertest.cpp utils/parameter_parser.cpp utils/fft_lib.cpp localization/srpphat.cpp tests/parserTest.cpp tests/readInputFileTest.cpp input/read_file_input_strategy.cpp tests/fftTest.cpp tests/srpphatTest.cpp utils/fft_strategy.cpp)

SETUP_TARGET_FOR_COVERAGE(testunit_coverage testunit coverage)

# link Yarp libraries
target_link_libraries(sim_datastreamer ${YARP_LIBRARIES})
target_link_libraries(sim_datareceiver ${YARP_LIBRARIES})
target_link_libraries(testunit ${YARP_LIBRARIES})


# link google libraries
target_link_libraries(testunit ${GTEST_LIBRARIES} -lpthread -lm)

# link zlib
target_link_libraries(testunit ${ZLIB_LIBRARIES})

