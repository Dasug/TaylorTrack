#include <ncurses.h>
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

        int rows, cols;

        // retrieve window size
        getmaxyx(stdscr, rows, cols);

        this->rows = rows;
        this->cols = cols;

        this->top_window = newwin(2, cols, 0, 0);
        this->main_window = newwin(rows - 2, cols, 2, 0);
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

    // TODO Actual visualisation


    // flush display buffer and write to screen
    refresh();
}

void taylortrack::vis::OutputVisualizer::handle_resize() {
    int rows, cols;

    // retrieve window size
    getmaxyx(stdscr,rows,cols);

    if(rows != this->rows || cols != this->cols) {
        wresize(this->top_window, 2, cols);
        wresize(this->main_window, rows - 2, cols);
        this->rows = rows;
        this->cols = cols;
        mvprintw(0, 0, "(%d|%d)", cols, rows); // Debug output

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
