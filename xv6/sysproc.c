#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_setlog(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return setlog(pid);
}

int
sys_printtime(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return printtime(pid);
}


int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;
  if(argint(0, &n) < 0)
    return -1;
  // cprintf("-----------tick : %d---------\n", n);
  acquire(&tickslock);
  ticks0 = ticks;
  if(myproc()->PRINT_TIME) cprintf("put %d to sleep %d ticks\n", myproc()->pid, n);
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    // cprintf("sleep again\n");
    sleep(&ticks, &tickslock);
  }
  if(myproc()->PRINT_TIME) cprintf("proc %d slept %d ticks, ticks: %d\n", myproc()->pid, ticks - ticks0, myproc()->tick);
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
