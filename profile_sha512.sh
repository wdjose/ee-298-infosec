#!/bin/bash
echo 'sha512sum ubuntu-18.04.3-desktop-amd64.iso'
time sha512sum ubuntu-18.04.3-desktop-amd64.iso | head -n1 | awk '{print $1;}'
echo 'python file_sha512.py ubuntu-18.04.3-desktop-amd64.iso'
time python file_sha512.py ubuntu-18.04.3-desktop-amd64.iso
echo './file_sha512v4.out ubuntu-18.04.3-desktop-amd64.iso'
time ./file_sha512v4.out ubuntu-18.04.3-desktop-amd64.iso
