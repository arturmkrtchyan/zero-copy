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



artur@artur-laptop:~/fcopy/zero-copy$ time java JioChannel /tmp/rbigfile.dat /tmp/wbigfile.dat 2

real	0m13.721s
user	0m0.228s
sys	0m1.508s
artur@artur-laptop:~/fcopy/zero-copy$ time java JioChannel /tmp/rbigfile.dat /tmp/wbigfile.dat 2

real	0m13.477s
user	0m0.224s
sys	0m1.512s
artur@artur-laptop:~/fcopy/zero-copy$ time ./fcopy /tmp/rbigfile.dat /tmp/wbigfile.dat 1

real	0m13.528s
user	0m0.080s
sys	0m2.160s
artur@artur-laptop:~/fcopy/zero-copy$ time ./fcopy /tmp/rbigfile.dat /tmp/wbigfile.dat 1

real	0m13.632s
user	0m0.080s
sys	0m2.152s
artur@artur-laptop:~/fcopy/zero-copy$ time ./fcopy /tmp/rbigfile.dat /tmp/wbigfile.dat 2

real	0m12.111s
user	0m0.004s
sys	0m0.956s
artur@artur-laptop:~/fcopy/zero-copy$ time ./fcopy /tmp/rbigfile.dat /tmp/wbigfile.dat 2

real	0m12.725s
user	0m0.000s
sys	0m0.880s
artur@artur-laptop:~/fcopy/zero-copy$ time ./fcopy /tmp/rbigfile.dat /tmp/wbigfile.dat 2

real	0m12.433s
user	0m0.000s
sys	0m0.872s

