/*
The MIT License (MIT)

Copyright (c) 2015 Marius Kaufmann, Tamara Frieß, Jannis Hoppe, Christian Hack

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/**
* @file
* @brief Contains implementation for taylortrack::vis::OutputVisualizer class.
*/

#include "vis/output_visualizer.h"
#include <string.h>
#include <string>
#include <vector>
#include <ncurses.h>


namespace taylortrack {
namespace vis {

OutputVisualizer::OutputVisualizer(utils::GeneralOptions general_options) {
  // Initialize console window
  initscr();

  // Disable character echoing
  noecho();

  // Hide cursor
  this->original_cursor_state_ = curs_set(0);

  // Activate special keyboard keys
  keypad(stdscr, TRUE);

  // Disable input line buffering
  cbreak();

  // Make input calls non-blocking
  nodelay(stdscr, true);

  // Initialize colors
  if (has_colors()) {
    start_color();

    // Define color pair 1 as white on blue
    init_pair(1, COLOR_WHITE, COLOR_BLUE);

    // Define color pair 2 as blue on white
    init_pair(2, COLOR_BLUE, COLOR_WHITE);

    /*
     * Redefine colors if terminal supports it
     * (We only have 8 colors available, so the names might be a bit unfitting)
    */
    init_color(COLOR_RED, 933, 461, 0);  // Dark Orange
    init_color(COLOR_YELLOW, 1000, 645, 0);  // Light Orange

    // Define color pair 3 and 4 for use in the diagram
    init_pair(3, COLOR_WHITE, COLOR_RED);
    init_pair(4, COLOR_WHITE, COLOR_YELLOW);

    int rows, cols;

    // retrieve window size
    getmaxyx(stdscr, rows, cols);

    this->rows_ = rows;
    this->cols_ = cols;

    refresh();
    create_top_window();
    create_main_window();

  } else {
    failed_ = true;
  }
}

void taylortrack::vis::OutputVisualizer::create_top_window() {
  this->top_window_ = newwin(4, this->cols_, 0, 0);
  // Set color pair 1 for the top window
  wbkgd(this->top_window_, COLOR_PAIR(1));

  update_top_window();
}

taylortrack::vis::OutputVisualizer::~OutputVisualizer() {
  delwin(this->top_window_);
  delwin(this->main_window_);

  // Reactivate cursor
  curs_set(this->original_cursor_state_);

  endwin();
}

void taylortrack::vis::OutputVisualizer::draw_frame() {
  this->handle_resize();
  this->handle_user_input();
  werase(this->main_window_);
  this->update_main_window();
}

void taylortrack::vis::OutputVisualizer::handle_resize() {
  int rows, cols;

  // retrieve window size
  getmaxyx(stdscr, rows, cols);

  if (rows != this->rows_ || cols != this->cols_) {
    if (this->show_top_window_) {
      wresize(this->top_window_, 4, cols);
      wresize(this->main_window_, rows - 4, cols);
      if (cols != this->cols_) {
        this->update_top_window();
      }
    } else {
      wresize(this->main_window_, rows, cols);
    }
    this->rows_ = rows;
    this->cols_ = cols;
  }
}

void taylortrack::vis::OutputVisualizer::handle_user_input() {
  int chr = getch();
  if (chr != ERR) {
    switch (chr) {
      case 27:  // ESC key or ALT key
        // If we can't read another character right away it was the ESC-Key
        if (getch() == ERR)
          this->user_quit_ = true;
        break;
      case 'q':
        this->user_quit_ = true;
        break;
      case 'h':
        this->toggle_upper_window();
        break;
      default:
        break;
    }
  }
}

bool taylortrack::vis::OutputVisualizer::term_supports_color() {
  return has_colors();
}

bool taylortrack::vis::OutputVisualizer::user_has_quit() const {
  return user_quit_;
}

bool taylortrack::vis::OutputVisualizer::has_failed() const {
  return failed_;
}

void taylortrack::vis::OutputVisualizer::update_top_window() {
  werase(this->top_window_);
  box(this->top_window_, 0, 0);
  wmove(this->top_window_, 1, 1);

  this->print_center(this->top_window_, "TaylorTrack - Tracking Visualizer");

  this->print_center(this->top_window_,
                     "Press 'q' or ESC to quit and 'h' to toggle this window.");

  wrefresh(this->top_window_);
}

/* Prints String in the center of the window's current line
 * Assumes a necessary padding in the size of the current cursor position (for box lines etc.)
 * Sets the cursor to the next same x position in the next line afterwards
 * */
void OutputVisualizer::print_center(WINDOW *window, const char *string) {
  int cy, cx;

  getyx(window, cy, cx);

  int cols = getmaxx(window);

  int position = ((cols - 2 * cx) - static_cast<int>(strlen(string))) / 2;

  wmove(window, cy, cx + position);

  wprintw(window, string);

  wmove(window, cy + 1, cx);
}

void taylortrack::vis::OutputVisualizer::toggle_upper_window() {
  this->show_top_window_ = !this->show_top_window_;

  if (show_top_window_) {
    delwin(this->main_window_);
    this->create_top_window();
    this->create_main_window();
  } else {
    delwin(this->top_window_);
    delwin(this->main_window_);
    this->create_main_window();
  }
}

void taylortrack::vis::OutputVisualizer::create_main_window() {
  if (show_top_window_) {
    this->main_window_ = newwin(this->rows_ - 4, this->cols_, 4, 0);
  } else {
    this->main_window_ = newwin(this->rows_, this->cols_, 0, 0);
  }
}

void taylortrack::vis::OutputVisualizer::update_main_window() {
  // Create Box around main window
  box(this->main_window_, 0, 0);

  wmove(this->main_window_, 1, 1);
  if (this->data_set_) {
    double x_axis_size = diagram_data_.size();
    int height, width;
    getmaxyx(this->main_window_, height, width);

    // Not the entire window usable
    width -= 2;
    height -= 4;

    // Calculate values per character
    int vpc = static_cast<int>(ceil(x_axis_size / static_cast<double>(width)));
    int actual_size = static_cast<int>(x_axis_size / vpc);

    // Calculate max value
    double max_value = 0.0f;
    for (int i = 0; i < actual_size; ++i) {
      double current_value = 0;
      for (int j = 0; j < vpc; ++j) {
        current_value += diagram_data_[i * vpc + j];
      }
      if (current_value > max_value) {
        max_value = current_value;
      }
    }

    wprintw(this->main_window_,
            "Debug-Values: %d %d %d %d %f",
            vpc,
            actual_size,
            COLORS,
            can_change_color(),
            max_value);

    if (max_value > 0.0) {
      // calculate the value of one square in the terminal
      double delta = max_value / height;

      // Add the vpc next values together and draw block if value high enough
      for (int y = 0; y < height; ++y) {
        for (int x = 0; x < actual_size; ++x) {
          double current_value = 0;
          for (int j = 0; j < vpc; ++j) {
            current_value += diagram_data_[x * vpc + j];
          }

          if (current_value >= (height - y) * delta) {
            wmove(this->main_window_, 1 + y, 1 + x);

            if (x % 2 == 0) {
              waddch(this->main_window_, ' ' | COLOR_PAIR(3));
            } else {
              waddch(this->main_window_, ' ' | COLOR_PAIR(4));
            }
          }
        }
      }
    } else {
      height = getmaxy(this->main_window_);
      height -= 2;

      wmove(this->main_window_, height / 2, 1);
      print_center(this->main_window_, "Invalid Data!");
    }
  } else {
    int height;
    height = getmaxy(this->main_window_);
    height -= 2;

    wmove(this->main_window_, height / 2, 1);
    print_center(this->main_window_, "Waiting for Data...");
  }

  // flush display buffer and write to screen
  wrefresh(this->main_window_);
}

void OutputVisualizer::set_diagram_data(
    const std::vector<double> &diagram_data) {
  this->diagram_data_ = diagram_data;
  this->data_set_ = true;
}
}  // namespace vis
}  // namespace taylortrack
