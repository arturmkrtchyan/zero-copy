zero-copy
=========

zero copy in Java and C

gcc -Wall -W -Werror fcopy.c -o fcopy


fallocate -l 1G /tmp/rbigfile.dat
fallocate -l 1G /tmp/wbigfile.dat

time ./fcopy /tmp/rbigfile.dat /tmp/wbigfile.dat 1
time ./fcopy /tmp/rbigfile.dat /tmp/wbigfile.dat 2

javac JioChannel.java

time java JioChannel /tmp/rbigfile.dat /tmp/wbigfile.dat 1
time java JioChannel /tmp/rbigfile.dat /tmp/wbigfile.dat 2


