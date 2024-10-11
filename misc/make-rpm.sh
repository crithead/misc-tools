#!/bin/bash
readonly PROJECT=${1:-example}
readonly VERSION="0.1.1"
HOME=/work

# Create rpmbuild tree, if it does not already exist
if [[ ! -d $HOME/rpmbuild ]]; then
    rpmdev-setuptree
fi

cd $HOME/rpmbuild

# Create a spec file, if one does not already exists
if [[ ! -f SPECS/$PROJECT.spec ]]; then
    rpmdev-newspec --output SPECS/${PROJECT}.spec ${PROJECT}
    sed -e "s/Name:.*$/Name:           ${PROJECT}/" \
        -e "s/Version:.*$/Version:        ${VERSION}/" \
        -e 's/Summary:.*$/Summary:        An example/' \
        -e 's/License:.*$/License:        CCO/' \
        -e 's|URL:.*$|URL:            https://github.com/crithead/misc-tools|' \
        -e "s/Source0:.*$/Source0:        ${PROJECT}-${VERSION}.tar.gz/" \
        -i SPECS/${PROJECT}.spec
    echo "Edit SPECS/${PROJECT}.spec and re-run this script."
    exit 0
fi

# Check the spec file for errors
rpmlint SPECS/${PROJECT}.spec
if [[ $? -ne 0 ]]; then
    echo "Fix the errors in the spec file and try again."
    exit 1
fi

# Build the rpm
rpmbuild -bb SPECS/${PROJECT}.spec

exit 0
