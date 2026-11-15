#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <cstdint>

int main() {
    uint32_t counter = 0;

    while (true) {
        printk("Hello from C++20 on Zephyr! Tick: %u\n", counter++);
        k_msleep(1000);
    }

    return 0;
}