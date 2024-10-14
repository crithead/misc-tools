#!/bin/bash
readonly PROJECT=${1:-example}
readonly VERSION=${2:-"0.1.1"}
HOME=/work

# Create rpmbuild tree, if it does not already exist
if [[ ! -d $HOME/rpmbuild ]]; then
    rpmdev-setuptree
fi

cd $HOME/rpmbuild

# Add macros
echo "%_sourcedir %{_topdir}/SOURCES" >> $HOME/.rpmmacros

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

# There is a lot that must be done to get a properly working spec file.
# See `misc/dice.spec`

# The archive it will build from must be named `%{name}-%{version}.tar.gz`
# and contains the files to be installed.  They are all in the top level
# directory "%{name}-%{version} in the archive.

# Check the spec file for errors
rpmlint SPECS/${PROJECT}.spec
if [[ $? -ne 0 ]]; then
    echo "Fix the errors in the spec file and try again."
    exit 1
fi

# Build the rpm
rpmbuild -bb SPECS/${PROJECT}.spec

exit 0

# To build a dice RPM:
#   pushd cpp
#   make dice
#   strip dice
#   popd
#   mkdir /work/dice-1.0.1
#   cp man1/dice.1 /work/dice-1.0.1/
#   gzip /work/dice-1.0.1/dice.1
#   cp cpp/dice /work/dice-1.0.1/
#   cp misc/dice.spec /work/rpmbuild/SPECS
#   cd /work/rpmbuild
#   tar czf SOURCES/dice-1.0.1.tar.gz dice-1.0.1 -C /work
#   HOME=/work rpmbuild -bb SPECS/dice.spec
#   -- output in "RPMS/%{arch}"

