#!/bin/bash
set -e

# Reference:
# http://playground.arduino.cc/Linux/All#Permission

# Add user to required group
GROUP=dialout

if id -nG "$USER" | grep -qw $GROUP; then
    echo "The user $USER is already member of the $GROUP group"
else
    sudo usermod -aG $GROUP $USER
fi

echo "Finished setting up Arduino!"
