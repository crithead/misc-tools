#!/usr/bin/env python3
# Generate a Table of Contents for a directory of Markdown documents.

import argparse
import os


def extract_title(file_name):
    """Get the title from the first line of the file."""
    try:
        with open(file_name, 'r') as f:
            for line in f:
                if line.startswith('#'):
                    return line[1:].strip().title()
                else:
                    return os.path.basename(file_name).upper()
    except:
        return os.path.basename(file_name).upper()


def get_args():
    """Parse command line aruments."""
    parser = argparse.ArgumentParser(
        description='Generate a Table Of Contents from a set of markdown documents.',
        epilog='   ###   ')
    # String argument
    parser.add_argument('-o', '--output', action='store', default='output.txt',
            type=str, help='Output file')
    # Boolean flag
    parser.add_argument('-r', '--recurse', action='store_true', default=False,
            help='Recursively search directories')
    parser.add_argument('-v', '--verbose', action='store_true', default=False,
            help='Enable noisy messages')
    # Required positional arguments
    parser.add_argument('doc_dirs', nargs='+',
            help='The base document directory (-ies)')
    return parser.parse_args()


def list_files(base_dir=None, file_ext=None):
    """Return a list of files in a directory with the specified extension."""
    value = list()
    for file in os.listdir(base_dir):
        if file_ext is None or file.endswith(file_ext):
            value.append(file)
    return value


def make_table_of_contents(dir_name, file_list):
    lines = list()
    lines.append(f'# Table of Contents -- {os.path.basename(dir_name)}')
    lines.append('')
    for file_name in file_list:
        title = extract_title(os.path.join(dir_name, file_name))
        lines.append(f'- [{title}]({file_name})')
    return lines


def main(args):
    """
        The script's main function.
        args: command line arguments, parsed into a namespace object
        returns: 0 = Success, 1 = General failure, ...
    """
    for directory in args.doc_dirs:
        file_list = list_files(directory, '.md')
        toc = make_table_of_contents(directory, file_list)
        toc_file = os.path.join(directory, 'toc.md')
        with open(toc_file, 'w') as f:
            for line in toc:
                print(line, file=f)
        print('toc_file', toc_file)


if __name__ == '__main__':
    exit_code = 0
    try:
        args = get_args()
        if args.verbose:
            # Enable verbose output here!
            print(args)
        main(args)
    except KeyboardInterrupt:
        exit_code = 9
    except SystemExit:
        pass
    except Exception as e:
        import traceback
        traceback.print_exc(file=sys.stderr)
        exit_code = 1
    finally:
        exit(exit_code)

