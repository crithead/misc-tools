/**
 * Reader
 * This is a  test program to build an IA32 statically linked binary to
 * test the IA32 syscall API.
 * Run with 'strace' and it will tell you is is running in 32-bit mode.
 * The explicit casts to 'unsigned int' and the like are due to the size
 * difference between compiling size_t for IA64 (long iunsigned int) and
 * IA32 (unsigned int).
 */

#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define LINELEN 1000

static size_t dump_to_console(int f_in);
static void print_summary(const char *file_name, unsigned int num_bytes);

/**
 * Print files, names given on the command line, to stdout with a summary.
 * @param argc Argument count
 * @param argv Argument vector
 * @retval 0 Always
 */
int main(int argc, char **argv)
{
    for (int i = 1; i < argc; i++) {
        int fd = open(argv[i], O_RDONLY);
        if (fd < 0) {
            perror("open");
            continue;
        }
        size_t n = dump_to_console(fd);
        (void)close(fd);
        print_summary(argv[i], (unsigned int)n);
    }
    return 0;
}

/**
 * Write to the contents of a file to the console.
 * @param f_in A readable file descriptor.
 * @return The number of bytes read.
 */
static size_t dump_to_console(int f_in)
{
    char line[LINELEN];
    size_t num_read = 0;
    while (true) {
        ssize_t ni = read(f_in, line, LINELEN);
        if (ni == -1) {
            fprintf(stderr, "%s: read( %d ):  %s\n", __func__, f_in, strerror(errno));
            break;
        } else if (ni == 0) {
            break;
        } else {
            num_read =+ ni;
            ssize_t no = write(1, line, ni);
            if (no != ni) {
                fprintf(stderr, "IN (%ld), OUT (%ld)\n", (long unsigned int)ni, (long unsigned int)no);
            }
        }
    }

    return num_read;
}

/**
 * Print a summary.
 * @param name A name
 * @param number A number
 */
static void print_summary(const char *name, unsigned int number)
{
    puts("==============================");
    printf("File: %s\n", name);
    printf("Size: %d\n", number);
    puts("==============================");
}
