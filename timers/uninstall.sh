#!/usr/bin/bash
/usr/bin/systemctl disable vacuum-journal.service
/usr/bin/systemctl stop vacuum-journal.timer
/usr/bin/systemctl disable vacuum-journal.timer
/usr/bin/rm -f /usr/lib/systemd/system/vacuum-journal.timer /usr/lib/systemd/system/vacuum-journal.service
exit 0
