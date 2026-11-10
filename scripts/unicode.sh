#!/bin/bash
# Usage: unicode.sh A [ B ]
# Print Unicode characters from A to B.

readonly A=${1:-0x20}
readonly B=${2:-${A}}


for i in $(seq $A $B); do
    N=$(printf "%04x"  $i)
    echo -e "  $N  \u$N"
done

exit 0
