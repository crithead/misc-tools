#! /bin/bash
readonly TARGET_DIR=${1:-$PWD}
readonly PROJECT_DIR=llvm-project
readonly TAR_FILE=${TARGET_DIR}/clang-tools-$(date +%F).tar.gz
readonly TMP_DIR=$(mktemp -d bct-XXXXXXX)

if [ -f install-clang-tools.sh ]; then
    cp -f install-clang-tools.sh ${TMP_DIR}
fi

if [ -d "$TARGET_DIR/$PROJECT_DIR" ]; then
    pushd "$TARGET_DIR/$PROJECT_DIR" > /dev/null
    git pull origin main
else
    cd "$TARGET_DIR"
    git clone https://github.com/llvm/llvm-project.git
    pushd "$TARGET_DIR/$PROJECT_DIR" > /dev/null
fi

set -e

cmake -S llvm -B build -G "Unix Makefiles" \
    -DLLVM_ENABLE_PROJECTS='clang;clang-tools-extra' \
    -DCMAKE_BUILD_TYPE=MinSizeRel
cmake --build build

readonly TOOLS="clang-format clang-tidy clang-check clang-refactor" \
    "llvm-nm llvm-objdump llvm-readobj"

pushd "build/bin" > /dev/null
cp -f ${TOOLS} ${TMP_DIR}
popd > /dev/null

pushd ${TMP_DIR} > /dev/null
tar czf ${TAR_FILE} ${TOOLS} {$DOCS}
popd > /dev/null

rm -fr ${TMP_DIR}

popd > /dev/null
exit 0

