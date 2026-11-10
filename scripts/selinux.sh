#!/bin/bash

if ! /usr/sbin/selinuxenabled; then
    echo "Permissive"
    exit 1
else
    echo "Enforcing"
    exit 0
fi
exit 99

