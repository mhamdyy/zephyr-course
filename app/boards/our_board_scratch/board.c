#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <esp_rom_uart.h>

void board_early_init_hook (void)
{
    /*Some function to run before boot*/
    esp_rom_printf("Board Initialized\n");
}
