#!/usr/bin/bash
# Example of bad return value.
set -x

readonly value=""

# ERROR: "exit: : numeric argument required"
exit "$value"

