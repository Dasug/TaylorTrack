# Set up dummy input tagert
add_executable(dummy_input sim_datastreamer.cpp input/dummy_input_strategy.cpp sim/streamer.cpp utils/parameter_parser.cpp utils/config_parser.cpp)
target_compile_definitions(dummy_input PUBLIC INPUT_DUMMY)
target_link_libraries(dummy_input ${YARP_LIBRARIES})

# Set up file input target
add_executable(read_file_input sim_datastreamer.cpp input/read_file_input_strategy.cpp sim/streamer.cpp utils/parameter_parser.cpp utils/config_parser.cpp)
target_compile_definitions(read_file_input PUBLIC INPUT_READ_FILE)
target_link_libraries(read_file_input ${YARP_LIBRARIES})

# Set up file input target
add_executable(wave_file_input sim_datastreamer.cpp utils/wave_parser.cpp input/wave_input_strategy.cpp sim/streamer.cpp utils/parameter_parser.cpp utils/config_parser.cpp)
target_compile_definitions(wave_file_input PUBLIC INPUT_WAVE_FILE)
target_link_libraries(wave_file_input ${YARP_LIBRARIES})

# Set up file input target
add_executable(open_cv_input sim_datastreamer.cpp sim/streamer.cpp utils/parameter_parser.cpp utils/config_parser.cpp input/opencv_input_strategy.cpp)
target_compile_definitions(open_cv_input PUBLIC INPUT_OPENCV)
target_link_libraries(open_cv_input ${YARP_LIBRARIES})
target_link_libraries(open_cv_input ${OpenCV_LIBS})

# Add Datareceiver executable
add_executable(sim_datareceiver sim_datareceiver.cpp utils/parameter_parser.cpp sim/data_receiver.cpp utils/config_parser.cpp localization/vision_tracker.cpp)

# Add test executable
add_executable(testunit input/dummy_input_strategy.cpp sim/streamer.cpp tests/testinit.cpp tests/simtest.cpp tests/streamertest.cpp utils/parameter_parser.cpp utils/fft_lib.cpp localization/srpphat.cpp tests/parsertest.cpp tests/read_input_file_test.cpp input/read_file_input_strategy.cpp tests/ffttest.cpp utils/wave_parser.cpp tests/wave_parser_test.cpp input/wave_input_strategy.cpp tests/wave_input_test.cpp utils/config_parser.cpp tests/config_parser_test.cpp tests/srpphatTest.cpp utils/fft_strategy.cpp sim/data_receiver.cpp)

# Result Visualizer
add_executable(visualizer visualizer.cpp vis/OutputVisualizer.cpp sim/data_receiver.cpp utils/config_parser.cpp)

SETUP_TARGET_FOR_COVERAGE(testunit_coverage testunit coverage)

# link Yarp libraries
target_link_libraries(sim_datareceiver ${YARP_LIBRARIES})
target_link_libraries(testunit ${YARP_LIBRARIES})
target_link_libraries(visualizer ${YARP_LIBRARIES})
target_link_libraries(sim_datareceiver ${OpenCV_LIBS})


# link google libraries
target_link_libraries(testunit ${GTEST_LIBRARIES} -lpthread -lm)

# link zlib
target_link_libraries(testunit ${ZLIB_LIBRARIES})

# link
target_link_libraries(visualizer ${CURSES_LIBRARIES})
