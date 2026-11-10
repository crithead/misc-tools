#!/usr/bin/bash
/usr/bin/install -m 0600 -o 0 -g 0 vacuum-journal.timer /usr/lib/systemd/system
/usr/bin/install -m 0600 -o 0 -g 0 vacuum-journal.service /usr/lib/systemd/system
/usr/bin/systemctl enable vacuum-journal.service
/usr/bin/systemctl enable vacuum-journal.timer
/usr/bin/systemctl start vacuum-journal.timer
exit 0
