#include <timer.h>

#include "uart.h"

int * remote_addr(char node_x, char node_y, int *addr) {
    long long int_addr = (long long)addr;
    int_addr = int_addr & ~(((long long)0x1FF) << 47);
    int_addr = (((long long)1) << 63) |
               (((long long)node_y) << 55) |
               (((long long)node_x) << 47) | int_addr;
    return (int *) int_addr;
}

int remote_get(char node_x, char node_y, int *addr) {
    return remote_addr(node_x, node_y, addr)[0];
}

void remote_put(char node_x, char node_y, int *addr, int val) {
    remote_addr(node_x, node_y, addr)[0] = val;
}

int main() {
    uart_init();

    while (1) {
        print_s("Hello world! Cycle ");
        print_i(get_time());
        print_s("\n");
        wait_cycles(250000); // 1 second at 25MHz
        int * remote_test = (int *)0xc0020000;
        for (int i = 0; i < 8; i++) {
            int pre_cycle = get_cycle();
            remote_put(0, i, remote_test, i);
            int latency = get_cycle() - pre_cycle;
            print_s("write latency node 0,0 to 0,");
            print_i(i);
            print_s(": ");
            print_i(latency);
            print_s("\n");
        }
        for (int i = 0; i < 8; i++) {
            int pre_cycle = get_cycle();
            int remote_val = remote_get(0, i, remote_test);
            int latency = get_cycle() - pre_cycle;
            print_s("read node 0,0 to 0,");
            print_i(i);
            print_s(" latency: ");
            print_i(latency);
            print_s(" val: ");
            print_i(remote_val);
            print_s("\n");
        }
        
    }
    return 0;
}

void handle_trap() {
        print_s("trap");
        while (1);
}
