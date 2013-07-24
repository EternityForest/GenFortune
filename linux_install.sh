#!/bin/sh
rm /usr/bin/openfortune
cp Fortune\ Files/*.frtn /usr/share/openfortune
cp Python\ Version/OpenFortune.py /usr/bin/openfortune
chmod -R 555 /usr/share/openfortune
chmod 555 /usr/bin/openfortune
echo "Install Complete"
