#! /usr/bin/env python
#
# Convert numbers to their representation in multiple base systems.
# Command line arguments:
#  -a       Enable all output types (binary)
#  -b       Force following args to be interpreted as binary.
#  -d       Force following args to be interpreted as decimal.
#  -h       Force following args to be interpreted as hexidecimal.
#  -n       Unset the force flag.
#  -o       Force following args to be interpreted as octal.
#
# TODO Force binary output width to multiples of 4
# TODO Force hexidecimal output width to multiples of 2
#
from __future__ import print_function
from argparse import ArgumentParser

messages_on = False

def msg(*args):
    """Print the argument list, if messages are enabled."""
    if messages_on:
        print(*args)


def create_argument_parser():
    parser = ArgumentParser(
            description='Convert numbers to other bases.',
            epilog='\n')
    parser.add_argument('-a', '--all', action='store_true', default=False,
            help='Enable all output types (binary)')
    parser.add_argument('-b', '--binary', action='store_true', default=False,
            help='Force input to be interpreted as binary')
    parser.add_argument('-d', '--decimal', action='store_true', default=False,
            help='Force input to be interpreted as decimal')
    parser.add_argument('-o', '--octal', action='store_true', default=False,
            help='Force input to be interpreted as octal')
    parser.add_argument('-x', '--hexidecimal', action='store_true', default=False,
            help='Force input to be interpreted as hexidecimal')
    parser.add_argument('-v', '--verbose', action='store_true', default=False,
            help='Enable debugging messages')
    parser.add_argument('numbers', nargs='+',
            help='Numbers to convert')
    return parser


def main(args):

    for n in args.numbers:
        if args.binary:
            value = int(n, 2)
            fmt = '{0:b}: 0x{0:X}, {0:d}, 0{0:o}'
        elif args.octal:
            value = int(n, 8)
            fmt = '{0:o}: 0x{0:X}, {0:d}, 0{0:o}'
        elif args.decimal:
            value = int(n, 10)
            fmt = '{0:d}: 0x{0:X}, {0:d}, 0{0:o}'
        elif args.hexidecimal:
            value = int(n, 16)
            fmt = '{0:X}: 0x{0:X}, {0:d}, 0{0:o}'
        else: # decimal
            value = int(n, 10)
            fmt = '{0:d}: 0x{0:X}, {0:d}, 0{0:o}'

        if args.all:
            fmt = fmt + ', {0:b}'

        print(fmt.format(value))


if __name__ == '__main__':
    exit_code = None
    try:
        parser = create_argument_parser()
        args = parser.parse_args()
        messages_on = args.verbose
        main(args)
        exit_code = 0
    except Exception as e:
        print(e)
        exit_code = 1
    finally:
        exit(exit_code)


