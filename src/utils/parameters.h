/**
* @file
* @brief Header file for the structs for the parameters.
* @version 1
*/
#ifndef TAYLORTRACK_PARAMETERS_H
#define TAYLORTRACK_PARAMETERS_H
namespace taylortrack {
    namespace utils {
        /**
         * @Struct
         * @brief Contains the given start parameters.
        */
        struct Parameters {
            /**
             * @var *file
             * Path to the file.
            */
            const char *file;

            /**
             * @var *outport
             * Output port which should be used.
            */
            const char *outport = "/bp39_out";

            /**
             * @var *inport
             * Input port which should be used.
            */
            const char *inport = "/bp39_in";

            /**
             * @var size
             * Size of packages that should be streamed
            */
            int size = 0;

            /**
             * @var valid
             * Stores if the given parameters are valid.
            */
            bool valid = false;
        };
    }
}
#endif //TAYLORTRACK_PARAMETERS_H
