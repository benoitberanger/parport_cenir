# Parallel port source code written in C for MATLAB/Octave in **Linux**. To be compiled in mex.

Purpose
-------
When compiled (see below), this program `ppmex` allows you to send messages through the parallel port (DB25) on a Linux system,
via MATLAB or Octave.

Test if you can compile MEX files
---------------------------------
In [helloworld-test-compile-mex](helloworld-test-compile-mex) subdir, you will find [helloworldMEX.c](helloworld-test-compile-mex/helloworldMEX.c).  
When, in MATLAB/Octave, you are in this folder, enter `mex -O helloworldMEX.c`.  
If the compilation is complet, you should have a new file such as *helloworldMEX.mex**  

Compilation
-----------
When you have tested the compilation process (see above), simply type `mex -O -v ppmex.c` in the root dir.  
The _warning_ about the line #21 `extern int pport = 0;` is nothing to worry about.  
When completed, a file *ppmex.mex** should have been created.  

Usage
-----
```
ppmex('open')          : opens  the device, and get it ready to send messages  
ppmex('write',message) : sends  the message = {0, 1, 2, ..., 255} uint8  
ppmex('close')         : closes the device  
```
