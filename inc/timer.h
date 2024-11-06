#ifndef TIMER_H
#define TIMER_H
void timer_init();
#endif

long long get_time();
void wait_cycles(long long cycles);
long long get_cycle(void);

#define CLINT_BASE 0x10000000
#define MTIME (volatile unsigned long long int *)(CLINT_BASE + 0xbff8)
#define MTIMECMP (volatile unsigned long long int *)(CLINT_BASE + 0x4000)
