/**
 *  Bit stream management.
 */

/**
 *  Bits constants.
 */
enum {
    BITS_STYLE_SIGNED,      /* +1 or -1 */
    BITS_STYLE_UNSIGNED,    /* 1 or 0 */
    BITS_ERROR = 0x7f
};

/**
 *  An opaque structure containing bit stream information.
 */
struct bits;

/**
 *  Initialize a new stream of bits.
 *
 * @param num_bits The minimum number of bits that stream will produce.
 * @param style The style of values to return.
 */
extern struct bits *new_bits(int num_bits, int style);

/**
 *  Get the next bit in the stream.
 *
 *  The next bit value is determined by the chosen style when the bit stream
 *  is initially generated.  Signed style produces values of +1 or -1 and
 *  unsigned style produces values of 0 or 1.
 *
 * @param bits A pointer to a struct bits.
 * @return A char with a value for the next bit.
 */
extern char next_bit(struct bits *bits);

