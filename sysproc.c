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
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
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


//Processes || Copy elements from the kernel ptable to the user space
extern struct proc * getptable_proc(void);

int sys_getptable(void){
  int size;
  char *buf;
  char *s;
  struct proc *p = '\0';

  if (argint(0, &size) <0){
    return -1;
  }
  if (argptr(1, &buf,size) <0){
    return -1;
  }

  s = buf;
  p = getptable_proc();

  while(buf + size > s && p->state != UNUSED){
    *(int *)s = p->state;
    s+=4;
    *(int *)s = p->pid;
    s+=4;
    *(int *)s = p->parent->pid;
    s+=4;
    *(int *)s = p->priority;
    s+=4;
    *(int *)s = p->burst_time;
    s+=4;
    *(int *)s = p->ctime;
    s+=4;
    memmove(s,p->name,16);
    s+=16;
    p++;
  }
  return 0;
}

extern int setp(int, int);

int
sys_setp(void)
{
  int pid, pr;
  if(argint(0, &pid) < 0)
    return -1;
  if(argint(1, &pr) < 0)
    return -1;

  return setp(pid, pr);
}


// Assignment 3 random number generator 
//taking ideas from http://www.iro.umontreal.ca/~simardr/rng/lfsr113.c

#define SEED 123456789

int 
sys_randnum(void)
{
  static unsigned int z1 = SEED, z2 = SEED, z3 = SEED, z4 = SEED;
  unsigned int b;
  b  = ((z1 << 6) ^ z1) >> 13;
  z1 = ((z1 & 4294967294U) << 18) ^ b;
  b  = ((z2 << 2) ^ z2) >> 27; 
  z2 = ((z2 & 4294967288U) << 2) ^ b;
  b  = ((z3 << 13) ^ z3) >> 21;
  z3 = ((z3 & 4294967280U) << 7) ^ b;
  b  = ((z4 << 3) ^ z4) >> 12;
  z4 = ((z4 & 4294967168U) << 13) ^ b;

  return (z1 ^ z2 ^ z3 ^ z4);
}

int 
sys_setbursttime(int n){
  argint(0,&n);
  setbursttime(n);
  return 1;
}

int 
sys_getbursttime(){
  return getbursttime();
}