#!/usr/bin/env python
"""
A tool to convert mp3 files to a different bit rate.

    -b, --bitrate N
    -q
    -v
    
mp3convert [-b N] [-v] -o TARGET SOURCE ...
"""

from __future__ import print_function
from argparse import ArgumentParser
from os import listdir, mkdir, unlink
from os.path import basename, exists, isfile, join, split
import random
from shutil import move
from subprocess import check_call
import sys
import traceback

messages_on = True

DEFAULT_BITRATE = 128


class TaskError(Exception):
    pass

class Task(object):
    """A conversion task."""
    def __init__(self, src, res, br=DEFAULT_BITRATE):
        self.source = src
        self.target = res
        self.bitrate = br
        self.success = False
    
    def check_output(self):
        """Check the target.
        Create the directory if it does not exists.
        Remove the file if it exists.
        """
        directory, file = split(self.target)
        if not exists(directory):
            mkdir(directory)
        if exists(self.target):
            unlink(self.target)
    
    def convert(self):
        """Call 'lame' to convert the source into target."""
        #lame --mp3input --silent -h -b BITRATE SOURCE TARGET
        self.success = False
        command = ['lame', '-h', '--silent']
        command.append('-b ' + str(self.bitrate))
        command.append(self.source)
        command.append(self.target)
        msg('command', command)
        error = check_call(command)
        if error != 0:
            raise TaskError(subprocess.CalledProcessError)
        self.success = True

    def print_command(self):
        """Print the conversion command."""
        self.success = False
        command = ['lame', '-h', '--silent']
        command.append('-b ' + str(self.bitrate))
        command.append(self.source)
        command.append(self.target)
        print(' '.join(command))
        
    def replace(self):
        """Replace the source file with the target file."""
        if self.success is False:
            raise TaskError('not ready')
        try:
            temp_src = '/tmp/' + str(random.randint(10000, 99999)) + '.mp3'
            os.move(self.source, temp_src)
            os.move(self.target, self.source)
            os.unlink(temp_src)
        except OSError as e:
            print(e)


def create_argument_parser():
    parser = ArgumentParser(
            description='Convert mp3 files to a different bit rate.',
            epilog='Script footnote.')
    parser.add_argument('-b', '--bitrate', action='store', default=128, type=int,
            help='The bit rate to convert to..')
    parser.add_argument('-o', '--output', action='store', default='/tmp',
            help='The destination directory for converted files.')
    parser.add_argument('-q', '--quiet', action='store_true', default=False,
            help='Disable all messages.')
    parser.add_argument('-r', '--replace', action='store_true', default=False,
            help='Replace the .')
    parser.add_argument('-v', '--verbose', action='store_true', default=False,
            help='Enable debugging messages.')
    parser.add_argument('sources', nargs='+',
            help='File or directories of files to convert.')
    return parser

def create_tasks(from_dir, to_dir):
    """
    Create a list of tasks to convert each file in 'from_dir' to a file
    in 'to_dir'.  The leaf directory name is appended to 'to_dir' to create
    the target file name.
    :from_dir: A Directory of mp3 files.
    :to_dir: A 
    """
    try:
        tasks = []
        source_files = list_directory(from_dir)
        dir_name = get_last_dir(from_dir)
        print('dir_name', dir_name)
        for file in source_files:
            source = join(from_dir, file)
            target = join(to_dir, dir_name, file)
            t = Task(source, target)
            tasks.append(t)
        return tasks
    except Exception as e:
        print(e)
        traceback.print_exc(file=sys.stdout)

def get_last_dir(path):
    """Get the name of the last directory in the path."""
    head, tail = split(path)
    while not tail:
        head, tail = split(head)
    return tail

def list_directory(path):
    """Return a list of files from the specified directory."""
    files = []
    for f in listdir(path):
        if isfile(join(path, f)) and f.endswith('.mp3'):
            files.append(f)
    return files
    
def msg(*args):
    """Print the argument list, if messages are enabled."""
    if messages_on:
        print(*args)

def main(args):

    msg('BitRate:', args.bitrate)
    msg('Output:', args.output)
    msg('Quiet:', args.quiet)
    msg('Verbose:', args.verbose)
    msg('Output file:', args.output)
    for file in args.sources:
        msg('\tDirectory:', file);
    
    for dir in args.sources:
        msg('Source', dir)
        d = list_directory(dir)
        for f in d:
            msg('\t', f)
        
    msg('--- create tasks for each file')
    tasks = []
    for dir in args.sources:
        print('dir', dir, 'args.output', args.output)
        tasks += create_tasks(dir, args.output)
        
    msg('--- call convert on each task')
    for task in tasks:
        task.check_output()
        task.convert()

if __name__ == '__main__':
    exit_code = None
    try:
        parser = create_argument_parser()
        args = parser.parse_args()
        if args.verbose:
            messages_on = True
        if args.quiet:
            messages_on = False
        main(args)
        exit_code = 0
    except Exception as e:
        traceback.print_exc(file=sys.stdout)
        exit_code = 1
    exit(exit_code)
    