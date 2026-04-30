#include <zephyr/init.h>
#include <zephyr/kernel.h>

void board_early_init_hook (void)
{
    /*Some function to run before boot*/
    printf("Board Initialized");
}
