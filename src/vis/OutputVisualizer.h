#ifndef TAYLORTRACK_OUTPUTVISUALIZER_H
#define TAYLORTRACK_OUTPUTVISUALIZER_H

#include "../utils/config.h"


namespace taylortrack {
    namespace vis {
        class OutputVisualizer {
        private:
            taylortrack::utils::Options options;
            int rows, cols;
            WINDOW *top_window;
            WINDOW *main_window;
            void handle_resize();
            void handle_user_input();
            bool user_quit = false;
            bool failed = false;
            int original_cursor_state;
            void update_top_window();
            void print_center(WINDOW *window, const char *string);
        public:
            bool user_has_quit() const;
            bool has_failed() const;
            OutputVisualizer(taylortrack::utils::Options);
            void draw_frame();
            bool term_supports_color();

            virtual ~OutputVisualizer();

        };
    } // namespace taylortrack::vis
} // namespace taylortrack



#endif //TAYLORTRACK_OUTPUTVISUALIZER_H
