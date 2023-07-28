
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bits.h"


struct bits {
    int style;
    char *octets;
    size_t max_counts;      /* the maximum number of values */
    size_t num_octets;
    size_t bit;             /* the current bit in the current octet */
    size_t octet;           /* the current octet */
    size_t count;           /* the next value to get */
};


static void incr_bit(struct bits *bits)
{
    bits->bit++;
    if (bits->bit >= 8) {
        bits->bit = 0;
        bits->octet++;
    }
}


struct bits *new_bits(int num_bits, int style)
{
    int num_octets;
    char *octets;
    struct bits *bits;
    FILE *fp;
    int num_read;
    ssize_t n;

    bits = (struct bits *)malloc(sizeof(struct bits));
    if (!bits) {
        perror("malloc struct bits");
        return NULL;
    }
    memset(bits, 0, sizeof(struct bits));

    num_octets = (num_bits + 7) / 8;
    octets = (char *)malloc(num_octets);
    if (!octets) {
        perror("malloc octets");
        return NULL;
    }
    memset(octets, 0, num_octets);

    bits->max_counts = num_bits;
    bits->style = style;

    fp = fopen("/dev/urandom", "r");
    n = 0;
    num_read = 0;
    do {
        n = fread(octets + n, 1, num_octets - n, fp);
        num_read += n;
    } while (num_read < num_octets);
    fclose(fp);

    bits->octets = (char *)octets;

    return bits;
}

char next_bit(struct bits* bits)
{
    char value;

    if (bits->count > bits->max_counts) {
        value = 0;
    } else {
        char v = bits->octets[bits->octet];
        value = (v >> bits->bit) & 1;
        incr_bit(bits);
        bits->count++;
        if (bits->style == BITS_STYLE_SIGNED && value == 0)
            value = -1;
    }

    return value;
}

