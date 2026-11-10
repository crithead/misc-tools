#!/usr/bin/env python3
"""
A new script template.
"""

import argparse
import sys

def print_usage():
    """Print a helpful usage message."""
    print(USAGE)


def get_args():
    """Parse command line aruments."""

    parser = argparse.ArgumentParser(
        description='What this script does.',
        epilog='A thing at the end.')
    # String argument
    parser.add_argument('-o', '--output', action='store', default='output.txt',
            type=str, help='Output file')
    # Boolean flag
    parser.add_argument('-v', '--verbose', action='store_true', default=False,
            help='Enable noisy messages')
    # Required positional arguments
    parser.add_argument(files, nargs='+',
            help='Files to process')
    return parser.parse_args()


def main(args):
    """
        The script's main function.
        args: command line arguments, parsed into a namespace object
        returns: 0 = Success, 1 = General failure, ...
    """
    if args.verbose:
        print(args)

    return 0


if __name__ == '__main__':
    exit_code = 0
    try:
        args = get_args()
        if args.verbose:
            pass    # Enable verbose output here
        exit_code = main(args)
    except KeyboardInterrupt:
        exit_code = 9
    except Exception as e:
        import traceback
        traceback.print_exc(file=sys.stderr)
        exit_code = 1
    finally:
        exit(exit_code)

