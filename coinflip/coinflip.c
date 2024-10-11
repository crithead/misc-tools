/**
 * @defgroup coinflip 
 *  Produce a plot of a random coin flip.
 *  Sums the bits.
 * @{
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "bits.h"

#define DEFAULT_NUM_VALUES 365
#define FILE_NAME_SIZE 256
#define DEFAULT_PLOT_TITLE "Coin Flip"

extern char *optarg;
extern int optind, opterr, optopt;


/**
 * Plot infomation
 */
struct info {
    /** The name of the plot file */
    const char *plotname;
    /** The  plot title */
    const char *plot_title;
    /** The number of coins to flip */
    int num_values;
    int bits_style;
    /** Include a count column on each data line */
    int count_column;
    /** Put a column header line in each data file */
    int data_headers;
    int min_total;
    int max_total;
};


static void create_data(struct info *);
static void create_plot(struct info *);
static struct info *clone_info(struct info*, const char *);
static struct info *new_info(const char *);
static void free_info(struct info *);
static void adjust_info(int, char **, struct info*);
static void print_help(void);


/**
 * Generate a coin flip plot for each plotname parameter.
 *
 * @param argc Argument count
 * @param argv Argument vector
 * @retval 0 On success
 * @retval 1 On any failure
 */
int main(int argc, char **argv)
{
    int i;

    struct info *default_info = new_info("default");
    adjust_info(argc, argv, default_info);

    if (optind == argc) {
        create_data(default_info);
        create_plot(default_info);
    } else {
        for (i = optind; i < argc; i++) {
            struct info *info = clone_info(default_info, argv[i]);
            create_data(info);
            create_plot(info);
            free_info(info);
        }
    }

    free_info(default_info);
    return 0;
}


/**
 * Generate plot data and write to a file.
 *
 * @param info A pointer to a plot info structure
 */
static void create_data(struct info *info)
{
    char datafile[FILE_NAME_SIZE];
    int i;
    struct bits *bits;
    int total = 0;
    FILE *fp;

    if (!info) {
        fprintf(stderr, "%s: info is NULL\n", __FILE__);
        return;
    }

    snprintf(datafile, FILE_NAME_SIZE, "%s.data", info->plotname);

    fp = fopen(datafile, "w+");
    if (!fp) {
        perror(info->plotname);
        return;
    }

    if (info->data_headers && info->count_column)
        fprintf(fp, "count\t%s\n", info->plotname);
    else if (info->data_headers)
        fprintf(fp, "%s\n", info->plotname);

    bits = new_bits(info->num_values, info->bits_style);

    for (i = 0; i < info->num_values; i++) {
        total += next_bit(bits);
        if (total > info->max_total)
            info->max_total = total;
        if (total < info->min_total)
            info->min_total = total;

        if (info->count_column)
            fprintf(fp, "%d\t%d\n", i + 1, total);
        else
            fprintf(fp, "%d\n", total);
    }

    free(bits);
    fclose(fp);
}


/**
 * Generate a GNUPLOT script to plot the generated data file.
 *
 * @param info a pointer to a plot info structure
 */
static void create_plot(struct info *info)
{
    char plotfile[FILE_NAME_SIZE];
    FILE *fp;

    if (!info) {
        fprintf(stderr, "%s: info is NULL\n", __FILE__);
        return;
    }

    snprintf(plotfile, FILE_NAME_SIZE, "%s.plot", info->plotname);

    fp = fopen(plotfile, "w+");
    if (!fp) {
        perror(info->plotname);
        return;
    }
    fprintf(fp, "set title '%s'\n", info->plot_title);
    fprintf(fp, "set term png size 800, 600\n");
    fprintf(fp, "set output \"%s.png\"\n", info->plotname);
    fprintf(fp, "set style line 1 linecolor rgb \"navy\"\n");
    fprintf(fp, "plot \"%s.data\" with lines ls 1 %s\n", info->plotname,
            info->count_column ? "title columnheader" : "");
    fclose(fp);
}


/**
 *  Copy an info structure into a new info structure with a new name.
 *
 *  @param info The info stricture to copy.
 *  @param plotname The new plot name.
 *  @return An copy of an info structure with a new name.
 */
static struct info *clone_info(struct info* info, const char *plotname)
{
    struct info *copy = (struct info*)malloc(sizeof(struct info));

    if (info && copy) {
        memcpy(copy, info, sizeof(struct info));
        copy->plotname = plotname;
        info->min_total = 0;
        info->max_total = 0;
    }

    return copy;
}


/**
 *  Allocate and initialize a new info structure.
 *
 *  @param plotname The base file name to use for output files.
 *  @return An initialized info structure or NULL
 */
static struct info *new_info(const char *plotname)
{
    struct info *info = (struct info*)malloc(sizeof(struct info));

    if (info) {
        memset(info, 0, sizeof(struct info));

        info->plotname = plotname;
        info->num_values = DEFAULT_NUM_VALUES;
        info->bits_style = BITS_STYLE_SIGNED;
        info->plot_title = DEFAULT_PLOT_TITLE;
    }

    return info;
}


/**
 * Deallocate an info structure.
 * @param info A pointer to an info structure.
 */
static void free_info(struct info *info)
{
    if (info) {
        free(info);
    }
}


/**
 * Read command line parameters and adjust the info struct.
 *
 *  @param argc Number of command line arguments
 *  @param argv Array of command line arguments
 *  @param info Pointer to an info structure
 */
static void adjust_info(int argc, char **argv, struct info *info)
{
    int opt;
    const char *OPTIONS = "cdhn:st:u";

    if (!info || ! argv)
        return;

    opt = getopt(argc, argv, OPTIONS);
    while (opt != -1) {
        switch (opt) {
        case 'c':
            info->count_column = 1;
            break;
        case 'd':
            info->data_headers = 1;
            break;
        case 'h':
            print_help();
            exit(0);
            break;
        case 'n':
            info->num_values = atoi(optarg);
            break;
        case 's':
            info->bits_style = BITS_STYLE_SIGNED;
            break;
        case 't':
            info->plot_title = optarg;
            break;
        case 'u':
            info->bits_style = BITS_STYLE_UNSIGNED;
            break;
        default:
            break;
        }
        opt = getopt(argc, argv, OPTIONS);
    }
}


/**
 * Print program usage information.
 */
static void print_help(void)
{
    puts("");
    puts("coinflip [ -cdhsu ] [ -n N ] [-t TITLE ] plotname1, plotname2, ...");
    puts("");
    puts("  -c          Include a count column in the output");
    puts("  -d          Include a data header row in the output");
    puts("  -h          Print a usage message and exit");
    puts("  -n N        Number of data points");
    puts("  -s          Use signed bits (+1 or -1)");
    puts("  -t TITLE    Set the plot title");
    puts("  -u          Use unsigned bits (0 or 1)");
    puts("");
}

/** @} End of coinflip group */

