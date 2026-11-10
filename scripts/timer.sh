#!/bin/bash

if [[ "$1" == "-h" ]] || [[ "$1" == "--help" ]]; then
    script=$(basename "$0")
    cat <<EOH
    $script - print elapsed seconds for some time

    $script [ -h | --help ]
    $script [ TIMEOUT [ INTERVAL ] ]

    Print elapsed seconds each INTERAL for TIMEOUT seconds.
EOH
    exit 0
fi

readonly expires=${1:-300}
readonly interval=${2:-1}

echo "Count to $expires by $interval sec"

counter=0

while [[ $counter -lt $expires ]]; do
    sleep "$interval"
    counter=$(( $counter + $interval ))
    printf "\t%d\e[\r]" $counter
done

echo

exit 0

