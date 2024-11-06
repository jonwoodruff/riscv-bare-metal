#include "riscv.h"
#include "uart.h"
#include "timer.h"

void timer_init() {
    *MTIMECMP = *MTIME + 0xfffff * 5;
    int mie = r_mie();
    mie |= (1 << 7);
    w_mie(mie);
}

long long get_time() {
    return *MTIME;
}

long long get_cycle(void)
{
    unsigned long dst;
    // output into any register, likely a0
    // regular instruction:
    asm volatile ("csrrs %0, 0xc00, x0" : "=r" (dst) );
    // regular instruction with symbolic csr and register names
    // asm volatile ("csrrs %0, cycle, zero" : "=r" (dst) );
    // pseudo-instruction:
    // asm volatile ("csrr %0, cycle" : "=r" (dst) );
    // pseudo-instruction:
    //asm volatile ("rdcycle %0" : "=r" (dst) );
    return dst;
}

void wait_cycles(long long cycles) {
    long long stop_time = get_time()+cycles;
    while (get_time() < stop_time);
}
