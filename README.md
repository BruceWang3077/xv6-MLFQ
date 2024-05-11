# MLFQ scheudler on xv6
This project implements Multi-Level Feedback Queue scheduler on xv6

## Test the Program
First change directory to ./xv6
```
cd xv6 
```

In proc.c you can see a flag ``` RUN_MLFQ``` 
``` 
int RUN_MLFQ = 1;
```

When it's set to 1, xv6 is running with MLFQ, when it's 0, xv6 is running with original code.

Re-boot is needed everytime code is modified(exit qemu and run qemu again)

After setting the flag value you want, boot the program
```
make qemu-nox
```
then run ```ls```, you'll see there're three added test user programs
```
...
wc             2 16 17064
zombie         2 17 14880
test1          2 18 15708
test2          2 19 18780
test3          2 20 16716
```
Run any of the tests by typing the program name. For example, if you want to run test1, run
```
test1
```
in the qemu shell.

To exit qemu, use shortcut ```ctrl + A, X ```

## Check Test Results
For test1 and test2, to check the analysis graph of the test result, copy and paste the output from qemu into the corresponding output file(eg. the result of test2 on MLFQ scheduler goes in .evaluation/output/test2_mlfq.out) and run ./evaluation/eval.ipynb


## List of Modified Files
* defs.h
* Makefile
* proc.c
* proc.h
* syscall.c
* syscall.h
* sysproc.c
* traps.c
* user.h
* usys.S


