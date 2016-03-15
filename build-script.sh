# /bin/bash
test -d ./lu-container-root/bin | mkdir -p ./lu-container-root/bin
test -d ./lu-container-root/proc | mkdir -p ./lu-container-root/proc
test -d ./lu-container-root/sys/fs/cgroup | mkdir -p ./lu-container-root/sys/fs/cgroup
test -d ./lu-container-root/lib | mkdir -p ./lu-container-root/lib
test -d ./lu-container-root/lib/x86_64-linux-gnu | mkdir -p ./lu-container-root/lib/x86_64-linux-gnu
test -d ./lu-container-root/lib64 | mkdir -p ./lu-container-root/lib64

cp /bin/dash ./lu-container-root/bin/
cp /bin/sh ./lu-container-root/bin/
cp /bin/ls ./lu-container-root/bin/
cp /bin/pwd ./lu-container-root/bin/
cp /bin/ps ./lu-container-root/bin/
cp /bin/netstat ./lu-container-root/bin/
cp /usr/bin/top ./lu-container-root/bin/
cp /usr/bin/free ./lu-container-root/bin/
cp /usr/bin/tree ./lu-container-root/bin/

cp /lib/x86_64-linux-gnu/libselinux.so.1  ./lu-container-root/lib/x86_64-linux-gnu/libselinux.so.1
cp /lib/x86_64-linux-gnu/libacl.so.1 ./lu-container-root/lib/x86_64-linux-gnu/libacl.so.1
cp /lib/x86_64-linux-gnu/libc.so.6 ./lu-container-root/lib/x86_64-linux-gnu/libc.so.6
cp /lib/x86_64-linux-gnu/libpcre.so.3 ./lu-container-root/lib/x86_64-linux-gnu/libpcre.so.3
cp /lib/x86_64-linux-gnu/libdl.so.2 ./lu-container-root/lib/x86_64-linux-gnu/libdl.so.2
cp /lib/x86_64-linux-gnu/libattr.so.1 ./lu-container-root/lib/x86_64-linux-gnu/libattr.so.1
cp /lib/x86_64-linux-gnu/libprocps.so.3  ./lu-container-root/lib/x86_64-linux-gnu/libprocps.so.3
cp /lib/x86_64-linux-gnu/libtinfo.so.5  ./lu-container-root/lib/x86_64-linux-gnu/libtinfo.so.5

cp /lib64/ld-linux-x86-64.so.2 ./lu-container-root/lib64/ld-linux-x86-64.so.2

