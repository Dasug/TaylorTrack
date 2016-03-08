/**
* @file
* @brief Header file for taylortrack::vis::OutputVisualizer class.
* @version 1
*/

#ifndef TAYLORTRACK_OUTPUTVISUALIZER_H
#define TAYLORTRACK_OUTPUTVISUALIZER_H

#include <vector>
#include <ncurses.h>
#include "../utils/config.h"

namespace taylortrack {
  namespace vis {
    /**
    * @class OutputVisualizer
    * @brief Visualizes data using a histogram
    *
    * Data supplied using set_diagram_data() will be displayed as a histogram in the console window every time the draw_frame() function is called
    * Automatically scales to the largest value and will pack several bars into one if console is not wide enough to display each value individually
    * Does not support negative values and at least one value must be larger than 0.
    */
    class OutputVisualizer {
     public:
      /**
       * @brief OutputVisualizer constructor
       *
       * Initializes console output and draws initial frame
       * @param general_options taylortrack::utils::GeneralOptions configuration object
       */
      OutputVisualizer(taylortrack::utils::GeneralOptions general_options);

      /**
       * @brief Checks whether the user requested to terminate the visualization.
       *
       * You should terminate the program once this returns true, unless you want to blatantly lie to your user ;-)
       * @return true if key to quit has been pressed by the user, otherwise false
       */
      bool user_has_quit() const;


      /**
       * @brief Checks whether something failed while trying to display the visualization.
       *
       * You should terminate the program once this returns true, since the state of the class might be corrupted
       * @return true if something went wrong during execution or initialization, otherwise false
       */
      bool has_failed() const;

      /**
       * @brief Draws a single frame of the visualizer
       *
       * Need to be called in order to react to console window resizing and to display changed data
       * @pre has_failed() returns false
       */
      void draw_frame();

      /**
       * @brief Checks whether the terminal this program is being called in supports color.
       *
       * Since this visualizer relies on colors, you should terminate the program and inform the user if it doesn't support them.
       * Proceeding anyways might result in the program failing.
       * @return true if the terminal this program is being called on supports colors, otherwise false
       */
      bool term_supports_color();

      /**
       * @brief Sets diagram data to be displayed
       * @param diagram_data Diagram data to be displayed when drawing the next frame. The data may not consist of negative values and at least one value needs to be positive.
       * @pre has_failed() returns false
       * @note Please note that the diagram data will not be displayed until the next frame is drawn.
       * @sa draw_frame()
       */
      void set_diagram_data(const std::vector<double> &diagram_data);

      /**
       * @brief OutputVisualizer destructor
       *
       * Releases console display mode
       * @warning Absolutely needs to be invoked before terminating the program. Failure to do so will mess up your console!
       */
      virtual ~OutputVisualizer();

     private:
      taylortrack::utils::GeneralOptions general_options_;
      int rows_, cols_;
      WINDOW *top_window_;
      WINDOW *main_window_;
      bool user_quit_ = false;
      bool failed_ = false;
      int original_cursor_state_;
      bool show_top_window_ = true;

      std::vector<double> diagram_data_;
      bool data_set_ = false;

      void handle_resize();
      void toggle_upper_window();
      void handle_user_input();
      void create_top_window();
      void update_top_window();
      void create_main_window();
      void update_main_window();
      void print_center(WINDOW *window, const char *string);
    };
  } // namespace taylortrack::vis
} // namespace taylortrack



#endif //TAYLORTRACK_OUTPUTVISUALIZER_H
