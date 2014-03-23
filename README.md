zero-copy
=========

Simple zero and non-zero file copy example in Java and C.

Zero copy lets you avoid redundant data copies between intermediate buffers and reduces the number of context switches between user space and kernel space.

Let's try out example in C
---------------------------

To try out zero and non-zero copy we need files. Let's quiclky create 2 files each 1G.

```shell
fallocate -l 1G /tmp/rbigfile.dat
fallocate -l 1G /tmp/wbigfile.dat
```

It's time to compile our c code:
```shell
gcc -Wall -W -Werror fcopy.c -o fcopy
```


Now let's execute non-zero file copy where 8K buffer is used to read and write data.
```shell
time ./fcopy /tmp/rbigfile.dat /tmp/wbigfile.dat 1

-----------------------
real  0m13.528s 
user  0m0.080s 
sys   0m2.160s
-----------------------
```

Now let's execute zero file copy where **sendfile** is used to copy data between one file descriptor and another. 
```shell
time ./fcopy /tmp/rbigfile.dat /tmp/wbigfile.dat 2

-----------------------
real  0m12.725s
user  0m0.000s
sys   0m0.880s
-----------------------
```
As copying is done within the kernel space, **sendfile** is more efficient than the combination of read and write, which would require transferring data to and from user space.


Let's try out example in Java
---------------------------

Compiling a java class is as simple as:
```shell
javac JioChannel.java
```

Now let's execute non-zero file copy where 8K buffer is used to read and write data.
```shell
time java JioChannel /tmp/rbigfile.dat /tmp/wbigfile.dat 1

-----------------------
real  0m14.445s
user  0m0.364s
sys   0m1.956s
-----------------------
```


Now let's execute zero file copy where **FileChannel.transferTo()** is used to copy data between one file channel and another.
```shell
time java JioChannel /tmp/rbigfile.dat /tmp/wbigfile.dat 2

-----------------------
real  0m13.721s 
user  0m0.228s 
sys   0m1.508s
-----------------------
```
Again as copying is done within the kernel space, **FileChannel.transferTo()** is more efficient than the combination of read and write, which would require transferring data to and from user space.


