#ifndef TAYLORTRACK_OUTPUTVISUALIZER_H
#define TAYLORTRACK_OUTPUTVISUALIZER_H

#include <vector>
#include "../utils/config.h"


namespace taylortrack {
    namespace vis {
        class OutputVisualizer {
        private:
            taylortrack::utils::Options options;
            int rows, cols;
            WINDOW *top_window;
            WINDOW *main_window;
            bool user_quit = false;
            bool failed = false;
            int original_cursor_state;
            bool show_top_window = true;
        public:
            void set_diagram_data(const std::vector<double> &diagram_data);

        private:
            std::vector<double> diagram_data;
            bool data_set = false;

            void handle_resize();
            void toggle_upper_window();
            void handle_user_input();
            void create_top_window();
            void update_top_window();
            void create_main_window();
            void update_main_window();
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
