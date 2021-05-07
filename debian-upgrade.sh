#!/bin/bash
set -e
[ $UID -eq 0 ] || { echo "Must be root" ; exit 1; }
apt-get update
apt-get upgrade
apt-get dist-upgrade
apt-get autoremove
apt-get autoclean
