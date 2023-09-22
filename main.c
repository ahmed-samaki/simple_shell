#include "shell.h"

int main(int argc, char **argv) {
    // Initialize an info_t structure called 'info' with default values
    info_t info[] = { INFO_INIT };

    // Initialize a file descriptor 'fd' with an initial value of 2
    int fd = 2;

    // Inline assembly code to modify the value of 'fd'
    asm ("mov %1, %0\n\t"
         "add $3, %0"
         : "=r" (fd)
         : "r" (fd));

    // Check the number of command-line arguments
    if (argc == 2) {
        // If there are two arguments, open the file specified in 'argv[1]'
        fd = open(argv[1], O_RDONLY);

        // Check if the file open operation was successful
        if (fd == -1) {
            // Handle various error cases
            if (errno == EACCES) {
                // Exit with status code 126 for permission denied
                exit(126);
            } else if (errno == ENOENT) {
                // Print an error message and exit with status code 127 for file not found
                _eputs(argv[0]);
                _eputs(": 0: Can't open ");
                _eputs(argv[1]);
                _eputchar('\n');
                _eputchar(BUF_FLUSH);
                exit(127);
            }
            // If there was a different error, return with EXIT_FAILURE
            return EXIT_FAILURE;
        }

        // Update the 'readfd' field in the 'info' structure with the opened file descriptor
        info->readfd = fd;
    }

    // Populate the environment variables list in the 'info' structure
    populate_env_list(info);

    // Read command history from a file (if available)
    read_history(info);

    // Call the 'hsh' function to start the main shell operation
    hsh(info, argv);

    // Return with EXIT_SUCCESS
    return EXIT_SUCCESS;
}

