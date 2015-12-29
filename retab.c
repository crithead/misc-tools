/*
 * Re-TAB -- Fix indents in source files.
 *
 * -h       Help
 * -i N     Indent size
 * -r       Trim trailing whitespace
 * -s       Indent with spaces only
 * -t       Indent with TABs only
 */

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEFAULT_INDENT 8
#define LINESIZE 256

#define TRIM_RIGHT (1 << 16)
#define USE_TABS   (1 << 17)


static void msg(const char *fmt, ...);
static void print_help(void);
static void retab(FILE *, int);
static void trim_back(char *);
static void indent_spaces(char *, int);
static void indent_tabs(char *, int);


static int messages_on = 1;

extern char *optarg;
extern int optind, opterr, optopt;
static char *OPTSTR = "hi:qrstv";

int main(int argc, char **argv)
{
	int i, opt;
	int opts = DEFAULT_INDENT;
	int status = 0;

	opt = getopt(argc, argv, OPTSTR);
	while(opt != -1) {
		switch (opt) {
		case 'h':
			print_help();
			exit(0);
			break;
		case 'i':
			opts &= 0xFFFF0000;
			opts |= 0x0000FFFF & atoi(optarg);
			break;
		case 'r':
			opts |= TRIM_RIGHT;
			break;
		case 'q':
			messages_on = 0;
			break;
		case 's':
			opts &= ~USE_TABS;
			break;
		case 't':
			opts |= USE_TABS;
			break;
		case 'v':
			messages_on = 1;
			break;
		default:
			break;
		}
		opt = getopt(argc, argv, OPTSTR);
	}

	for (i = 1; i < argc; i++) {
		FILE *fp = fopen(argv[i], "r+");
		if (fp) {
			retab(fp, opts);
			fclose(fp);
		}
	}

	return status;
}


/*
 * Print a message to stdout, if messages are turned on.
 */
static void msg(const char *fmt, ...)
{
	static char line[LINESIZE];
	va_list args;

	if (!messages_on)
		return;

	va_start(args, fmt);
	vsnprintf(line, LINESIZE, fmt, args);
	va_end(args);

	puts(line);
}


/*
 * Print usage information.
 */
static void print_help(void)
{
	puts("retab [-h] [-i N] [-r] -s | -t file1 ...");
}


/*
 * Fix whitespace ... to stdout
 */
static void retab(FILE *fp, int flags)
{
	int use_tabs = (USE_TABS & flags) ? 1 : 0;
	int trim_right = (TRIM_RIGHT & flags) ? 1 : 0;
	int indent_size = 0xFFFF & flags;
	ssize_t n = 0;
	char *line;
	size_t len;

	msg("fp         %08X", (void *)fp);
	msg("indent     %d", indent_size);
	msg("use tabs   %c", use_tabs ? 'Y' : 'N');
	msg("trim right %c", trim_right ? 'Y' : 'N');

	for(;;) {
		n = getline(&line, &len, fp);
		if (n <= 0)
			break;
		if (trim_right)
			trim_back(line);
		if (use_tabs)
			indent_tabs(line, indent_size);
		else
			indent_spaces(line, indent_size);
		puts(line); /* TODO: write to tmp file */
	}
}


/*
 * Trim whitespace from the back of a line.
 */
static void trim_back(char *line)
{
	size_t n = strlen(line);
	while (n >= 0 && isspace(line[n]))
		line[n--] = '\0';
}


static char buffer[LINESIZE + LINESIZE / 2];

/*
 * Re-indent the front of a line with spaces.
 */
static void indent_spaces(char *line, int isize)
{
	size_t n_spaces = 0;
	size_t i, j;
	size_t len = strlen(line);

	memset(buffer, ' ', len);
	memset(buffer + len, 0, (sizeof buffer) - len);

	for(i = 0; i < len; i++) {
		if (line[i] == ' ')
			n_spaces++;
		else if (line[i] == '\t')
			n_spaces += isize;
		else
			break;
	}

	for(j = 0; j < n_spaces ; j++)
		buffer[j] = ' ';
	for(j = n_spaces ; i < len; i++, j++)
		buffer[j] = line[i];

	memcpy(line, buffer, LINESIZE);
}


/*
 * Re-indent the front of a line with tabs.
 */
static void indent_tabs(char *line, int isize)
{
	/* TODO */
	memcpy(buffer, line, LINESIZE);
	memcpy(line, buffer, sizeof LINESIZE);
}


