# Add current directory to include path
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Set up dummy input target
if(COMPILE_INPUT_DUMMY)
    add_executable(dummy_input sim_datastreamer.cpp input/dummy_input_strategy.cpp sim/streamer.cpp utils/parameter_parser.cpp utils/config_parser.cpp)
    target_compile_definitions(dummy_input PUBLIC INPUT_DUMMY)
    target_link_libraries(dummy_input ${YARP_LIBRARIES})
endif()

# Set up file input target
if(COMPILE_INPUT_READFILE)
    add_executable(read_file_input sim_datastreamer.cpp input/read_file_input_strategy.cpp sim/streamer.cpp utils/parameter_parser.cpp utils/config_parser.cpp)
    target_compile_definitions(read_file_input PUBLIC INPUT_READ_FILE)
    target_link_libraries(read_file_input ${YARP_LIBRARIES})
endif()

# Set up wave file input target
if(COMPILE_INPUT_WAVE)
    add_executable(wave_file_input sim_datastreamer.cpp utils/wave_parser.cpp input/wave_input_strategy.cpp sim/streamer.cpp utils/parameter_parser.cpp utils/config_parser.cpp)
    target_compile_definitions(wave_file_input PUBLIC INPUT_WAVE_FILE)
    target_link_libraries(wave_file_input ${YARP_LIBRARIES})
endif()

# Set up openCV input target
if(COMPILE_INPUT_OPENCV)
    add_executable(open_cv_input sim_datastreamer.cpp sim/streamer.cpp utils/parameter_parser.cpp utils/config_parser.cpp input/opencv_input_strategy.cpp)
    target_compile_definitions(open_cv_input PUBLIC INPUT_OPENCV)
    target_link_libraries(open_cv_input ${YARP_LIBRARIES})
    target_link_libraries(open_cv_input ${OpenCV_LIBS})
endif()

# Set up microphone input target
if(COMPILE_INPUT_MICROPHONE)
    add_executable(microphone_input sim_datastreamer.cpp sim/streamer.cpp utils/parameter_parser.cpp utils/config_parser.cpp input/microphone_input_strategy.cpp input/microphone_input_strategy.h)
    target_compile_definitions(microphone_input PUBLIC INPUT_MICROPHONE)
    target_link_libraries(microphone_input ${YARP_LIBRARIES})
    target_link_libraries(microphone_input ${PORTAUDIO_LIBRARIES})
endif()

# Add Datareceiver executable
if(COMPILE_TRACKER_AUDIO)
    add_executable(sim_datareceiver sim_datareceiver.cpp utils/parameter_parser.cpp utils/config_parser.cpp localization/srp_phat.cpp utils/fft_lib.cpp utils/fft_strategy.cpp utils/vad_simple.cpp)
    target_link_libraries(sim_datareceiver ${YARP_LIBRARIES})
endif()

# Add OpenCv Datareceiver executeable
if(COMPILE_TRACKER_VIDEO)
    add_executable(opencv_datareceiver opencv_datareceiver.cpp utils/parameter_parser.cpp utils/config_parser.cpp localization/vision_tracker.cpp)
    target_link_libraries(opencv_datareceiver ${YARP_LIBRARIES})
    target_link_libraries(opencv_datareceiver ${OpenCV_LIBS})
endif()

# Add test executable
if(COMPILE_TESTUNIT)
    add_executable(testunit input/dummy_input_strategy.cpp sim/streamer.cpp tests/testinit.cpp tests/simulation_test.cpp tests/streamer_test.cpp utils/parameter_parser.cpp utils/fft_lib.cpp localization/srp_phat.cpp tests/parser_test.cpp tests/read_input_file_test.cpp input/read_file_input_strategy.cpp tests/fft_test.cpp utils/wave_parser.cpp tests/wave_parser_test.cpp input/wave_input_strategy.cpp tests/wave_input_test.cpp utils/config_parser.cpp tests/config_parser_test.cpp tests/srp_phat_test.cpp utils/fft_strategy.cpp utils/vad_strategy.h utils/vad_simple.cpp utils/vad_simple.h tests/vad_simple_test.cpp)
    target_link_libraries(testunit ${YARP_LIBRARIES})
    target_link_libraries(testunit ${ZLIB_LIBRARIES})
    target_link_libraries(testunit ${GTEST_LIBRARIES} -lpthread -lm)
    if(COMPILE_TESTCOVERAGE)
        SETUP_TARGET_FOR_COVERAGE(testunit_coverage testunit coverage)
    endif()
endif()

# Result Visualizer
if(COMPILE_VISUALIZER)
    add_executable(visualizer visualizer.cpp vis/output_visualizer.cpp utils/config_parser.cpp)
    target_link_libraries(visualizer ${YARP_LIBRARIES})
    target_link_libraries(visualizer ${CURSES_LIBRARIES})
endif()
