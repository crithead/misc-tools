#!/usr/bin/bash
# Stripping the $) and passing the args along.
# "$#" is equivalent to "argc - 1"
# "$#" does not count Arg 0
echo "\$# = $#"
echo '${@} ' "${@}"

exit 0

