#!/bin/sh
rm /usr/bin/genfortune
mkdir -p /usr/share/genfortune
cp Fortune\ Files/*.frtn /usr/share/genfortune
cp Fortune\ Files/*.nki /usr/share/genfortune
cp genfortune.py /usr/bin/genfortune
chmod -R 755 /usr/share/genfortune
chmod 755 /usr/bin/genfortune
chown root /usr/bin/genfortune
echo "Install Complete"
