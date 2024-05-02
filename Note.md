# Add new syscall
### Files to be modified:
proc.c \
defs.h \
sysproc.c\
syscall.h\
syscall.c\
usys.S

### New user program to test:
user.h \
a new .c file (optional)\
MakeFile


# fork()
how a child process is added to ptable: proc.c -> allocproc()