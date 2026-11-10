#!/bin/bash
# List the Ambient capability set of all running proceeses

#for dir in $(ls -d /proc/+([[:digit:]])); do
#for pid in $(ls /proc | grep -E '[0-9][0-9]*'); do
for pid in $(ps -A | awk '{print $1}'); do
    [ -d "/proc/$pid" ] || continue
    capamask=$(grep CapEff "/proc/$pid/status" | cut -f2)
    capalist=$(capsh --decode=$capamask)
    [ "$capalist" == "0x0000000000000000=" ] && continue
    cmdline=$(cat "/proc/$pid/cmdline")
    if [ -n "$cmdline" ]; then 
        command=$(cat "/proc/$pid/cmdline" | cut -f1)
        echo "$command: $capalist"
    fi
done

exit 0

# Results are not enlightening.
# Processes have all effective or no ambient.
# Things run as root have all, otherwise none.

