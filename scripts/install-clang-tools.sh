#!/bin/bash
# Install llvm-project tools built ...
[ $UID -eq 0 ] || { echo "Must be root" ; exit 1 ; }

readonly BIN_DIR=${1:/usr/local/bin}
readonly TOOLS="clang-format clang-tidy clang-check clang-refactor llvm-nm llvm-objdump llvm-readobj"

for tool in ${TOOLS}; do
    /usr/bin/install -m 0755 -o root -g root ${tool} ${BIN_DIR}
done
exit 0

