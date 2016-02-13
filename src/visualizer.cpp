/**
* @file
* @brief Contains main method for the visualizer.
*/

#include <ncurses.h>
#include <iostream>
#include "vis/OutputVisualizer.h"
#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif //WIN32

/**
 * @brief Visualizer main method
 *
 * Initializes console output and contains main display loop
 * @param argc number of arguments
 * @param argv array of arguments
 */
int main(int argc, char **argv) {
    taylortrack::utils::Options options = taylortrack::utils::Options();
    taylortrack::vis::OutputVisualizer *out = new taylortrack::vis::OutputVisualizer(options);

    // Generate vector with sample data
    std::vector<double> sampleVector;

    int i = 0;
    if(out->term_supports_color()) {
        while(!out->has_failed() && !out->user_has_quit()) {
            if(i % 15 == 14) {
                sampleVector.clear();
                for (int j = 0; j < 360; ++j) {
                    sampleVector.push_back(((double) rand()) / ((double) RAND_MAX));
                }
                out->set_diagram_data(sampleVector);
            }


            out->draw_frame();

            // Obviously Windows and Unix systems use different sleep functions...
            int milliseconds = 100;
            #ifdef WIN32
                Sleep(milliseconds);
            #else
                #ifdef __useconds_t_defined
                    usleep((__useconds_t) (milliseconds * 1000));
                #else
                    usleep(milliseconds * 1000);
                #endif // __useconds_t_defined
            #endif // win32
            ++i;
        }

        // Leave ncurses terminal mode
        delete(out);
    } else {
        delete(out);
        std::cout << "Your terminal doesn't support colors, aborting..." << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}