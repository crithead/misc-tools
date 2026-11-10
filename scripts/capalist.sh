#!/bin/bash

if [ "$1" == "--help" ] || [ "$1" == "-h" ] ; then
    cat <<EOH
Produce a report of all service programs and their capabilities.

    $(basename "$0") [ REPO_DIR ]

REPO_DIR is a project root directory.
Default = '/lib/systemd/system'

EOH
    exit 0
fi

readonly REPO_DIR="${1:-/lib/systemd}"
readonly SERVICE_FILES=$(mktemp /tmp/capalist.svc.XXXXXXXX)
readonly SOURCE_FILES=$(mktemp /tmp/capalist.src.XXXXXXXX)
readonly REPORT_FILE="/tmp/capalist-$(date +%Y%m%d%H%M%S).txt"

echo "--- Find service files"
#find "$REPO_DIR" -name \*.service 2> /dev/null > "$SERVICE_FILES"
find /home /lib/systemd /etc/systemd -name \*.service 2> /dev/null > "$SERVICE_FILES"

echo "--- Search service files"
while read -r service_file; do
    exec_start=$(grep -e ^ExecStart "$service_file" | cut -d= -f2 | cut -d' ' -f1)
    echo "$(basename "$service_file")" >> "$REPORT_FILE"
    readarray -t lines <<<"$exec_start"
    for line in "${lines[@]}"; do
        echo "- $line" >> "$REPORT_FILE"
    done

    cap_set=$(grep -e ^CapabilityBoundingSet -e ^AmbientCapabilities -e ^User -e ^Group -e SecureBits "$service_file")
    if [ -n "$cap_set" ]; then
        readarray -t lines <<<"$cap_set"
        for line in "${lines[@]}"; do
            echo "- $line" >> "$REPORT_FILE"
        done
    fi
    echo "" >> "$REPORT_FILE"
done < "$SERVICE_FILES"
rm -f "$SERVICE_FILES"

# Find files that call capset(2)
echo "--- Find source files"
find "$HOME" /work -name \*.[cC] 2> /dev/null > "$SOURCE_FILES"

echo "--- Search source files"
echo -e "\nSource files that adjust capabilities:\n" >> "$REPORT_FILE"
while read -r source_file; do
    capsets=$(grep capset "$source_file")
    if grep -q -e capset -e prctl "$source_file"; then
        echo "- $source_file" >> "$REPORT_FILE"
    fi
done < "$SOURCE_FILES"

#rm -f "$SOURCE_FILES"
echo "--- Done"

echo "Report: $REPORT_FILE"

exit 0

