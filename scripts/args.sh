#!/usr/bin/bash
# Shell argument list index example.
# "$#" is equivalent to "argc - 1"
# "$#" does not count Arg 0
echo "\$# = $#"

[ $# -ge  $((1 - 1)) ] && { echo "\$0 = ${0}" ; }
[ $# -ge  $((2 - 1)) ] && { echo "\$1 = ${1}" ; }
[ $# -ge  $((3 - 1)) ] && { echo "\$2 = ${2}" ; }
[ $# -ge  $((4 - 1)) ] && { echo "\$3 = ${3}" ; }
[ $# -ge  $((5 - 1)) ] && { echo "\$4 = ${4}" ; }
[ $# -ge  $((6 - 1)) ] && { echo "\$5 = ${5}" ; }
[ $# -ge  $((7 - 1)) ] && { echo "\$6 = ${6}" ; }
[ $# -ge  $((8 - 1)) ] && { echo "\$7 = ${7}" ; }
[ $# -ge  $((9 - 1)) ] && { echo "\$8 = ${8}" ; }
[ $# -ge $((10 - 1)) ] && { echo "\$9 = ${9}" ; }

exit 0

