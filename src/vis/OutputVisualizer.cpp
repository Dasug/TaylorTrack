#include <ncurses.h>
#include <string.h>
#include "OutputVisualizer.h"

taylortrack::vis::OutputVisualizer::OutputVisualizer(taylortrack::utils::Options options) {
    this->options = options;

    // Initialize console window
    initscr();

    // Disable character echoing
    noecho();

    // Hide cursor
    this->original_cursor_state = curs_set(0);

    // Activate special keyboard keys
    keypad(stdscr, TRUE);

    // Disable input line buffering
    cbreak();

    // Make input calls non-blocking
    nodelay(stdscr, true);

    // Initialize colors
    if(has_colors()) {
        start_color();

        // Define color pair 1 as white on blue
        init_pair(1, COLOR_WHITE, COLOR_BLUE);

        // Define color pair 2 as blue on white
        init_pair(2, COLOR_BLUE, COLOR_WHITE);

        int rows, cols;

        // retrieve window size
        getmaxyx(stdscr, rows, cols);

        this->rows = rows;
        this->cols = cols;

        refresh();

        this->top_window = newwin(4, cols, 0, 0);
        // Set color pair 1 for thetop window
        wbkgd(this->top_window, COLOR_PAIR(1));

        this->main_window = newwin(rows - 4, cols, 4, 0);

        update_top_window();
    } else {
        failed = true;
    }
}

taylortrack::vis::OutputVisualizer::~OutputVisualizer() {
    delwin(this->top_window);
    delwin(this->main_window);

    // Reactivate cursor
    curs_set(this->original_cursor_state);

    endwin();
}

void taylortrack::vis::OutputVisualizer::draw_frame() {
    this->handle_resize();
    this->handle_user_input();
    werase(this->main_window);

    // TODO Actual visualisation

    // Create Box around main window
    box(this->main_window, 0, 0);

    // flush display buffer and write to screen
    wrefresh(this->main_window);
}

void taylortrack::vis::OutputVisualizer::handle_resize() {
    int rows, cols;

    // retrieve window size
    getmaxyx(stdscr,rows,cols);

    if(rows != this->rows || cols != this->cols) {
        wresize(this->top_window, 4, cols);
        wresize(this->main_window, rows - 4, cols);
        if(cols != this->cols) {
            this->update_top_window();
        }
        this->rows = rows;
        this->cols = cols;

    }
}

void taylortrack::vis::OutputVisualizer::handle_user_input() {
    int chr = getch();
    if(chr != ERR) {
        switch(chr) {
            case 27: // ESC key or ALT key
                // If we can't read another character right away it was the ESC-Key
                if(getch() == ERR)
                    this->user_quit = true;
                break;
            case 'q':
                this->user_quit = true;
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
    return user_quit;
}

bool taylortrack::vis::OutputVisualizer::has_failed() const {
    return failed;
}

void taylortrack::vis::OutputVisualizer::update_top_window() {
    werase(this->top_window);
    box(this->top_window, 0, 0);
    wmove(this->top_window, 1, 1);

    this->print_center(this->top_window, "TaylorTrack - Tracking Visualizer");
    wrefresh(this->top_window);
}

/* Prints String in the center of the window's current line
 * Assumes a necessary padding in the size of the current cursor position (for box lines etc.)
 * Sets the cursor to the next same x position in the next line afterwards
 * */
void taylortrack::vis::OutputVisualizer::print_center(WINDOW *window, const char *string) {
    int cy, cx;

    getyx(window, cy, cx);

    int cols = getmaxx(window);

    int position = ((cols - 2*cx) - (int) strlen(string)) / 2;

    wmove(window, cy, cx + position);

    wprintw(window, string);

    wmove(window, cy + 1, cx);
}
