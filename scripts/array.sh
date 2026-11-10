#!/usr/bin/bash
# Bash array example.

declare -a xxx
xxx=(one two five four three 'si ix' seven)
echo "len xxx ${#xxx[*]}"
echo "${xxx[*]}"

echo '--- "${xxx[@]}"'
for x in "${xxx[@]}"; do
    echo "$x"
done

echo '--- "${xxx[*]}"'
for x in "${xxx[*]}"; do
    echo "$x"
done

echo '--- ${xxx[@]}'
for x in ${xxx[@]}; do
    echo "$x"
done

echo '--- ${xxx[*]}'
for x in ${xxx[*]}; do
    echo "$x"
done

exit 0

