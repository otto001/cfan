#! /bin/sh
mkdir -p /etc/cfan/
systemctl restart cfan.service
systemctl enable cfan.service

