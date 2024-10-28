#!/bin/bash
sudo ./dj_make_chroot -y -c "$(pwd)"/archives -d chroot \
  -s "$(ls $(pwd)/assets/*.list 2>/dev/null | tr '\n' ',')" \
  -m https://sysopspackages.icpc.global/ubuntu \
  -D Ubuntu -R jammy -a amd64 && sudo tar -C chroot -zcvf chroot.tar.gz .
