/**
 * Check if one or more files exist.
 */

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

static bool help_requested(int, char **);
static void print_usage(void);



int main(int argc, char **argv)
{
	if (help_requested(argc, argv)) {
		print_usage();
		return 0;
	}

	for (int i = 1; i < argc; i++) {
		/* stat(2) requires non-null arguments */
		struct stat sb;
		if (stat(argv[i], &sb) == 0) {
			printf("%s: Yes\n", argv[i]);
		} else if (errno == EACCES) {
			printf("%s: Maybe\n", argv[i]);
		} else {
			printf("%s: No\n", argv[i]);
		}
	}

	return 0;
}

static bool help_requested(int argc, char **argv)
{
	for (int i = 1; i < argc; i++) {
		if ((strncmp(argv[i], "--help", 6) == 0) ||
			(strncmp(argv[i], "-h", 3) == 0)) {
			return true;
		}
	}
	return false;
}

static void print_usage(void)
{
	const char *USAGE =
	"\n"
	"\texists - check if one or more files exist\n"
	"\n"
	"\texists FILE1 [ FILE2 ... ]\n"
	"\n";
	puts(USAGE);
}
