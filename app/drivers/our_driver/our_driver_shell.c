#include <zephyr/shell/shell.h>
#include <zephyr/drivers/sensor.h>
#include "our_driver.h"

static int shell_our_driver_sample_fetch(const struct shell* sh, size_t argc, char** argv);
static int shell_our_driver_channel_get(const struct shell* sh, size_t argc, char** argv);
static int shell_our_driver_info(const struct shell* sh, size_t argc, char** argv);
static int shell_our_driver_set(const struct shell* sh, size_t argc, char** argv);


SHELL_STATIC_SUBCMD_SET_CREATE(our_driver_subcmd,
    SHELL_CMD_ARG(read,   NULL, "Get channel of the our driver sensor",   shell_our_driver_channel_get,  2, 0),
    SHELL_CMD_ARG(fetch,  NULL, "Sample fetch of the our driver sensor",  shell_our_driver_sample_fetch, 2, 0),
    SHELL_CMD_ARG(info,   NULL, "Get info of the our driver sensor",      shell_our_driver_info,         2, 0),
    SHELL_CMD_ARG(set,    NULL, "Set parameter of the our driver sensor", shell_our_driver_set,          3, 0),
    SHELL_SUBCMD_SET_END);

SHELL_CMD_REGISTER(our_driver, &our_driver_subcmd, "Our Driver sensor", NULL);

static int shell_our_driver_sample_fetch(const struct shell* sh, size_t argc, char** argv)
{
    int ret = 0;
    const struct device* dev = shell_device_get_binding(argv[1]);

    if(NULL == dev)
    {
        shell_error(sh, "Couldn't find device %s", argv[1]);
        return -EFAULT;
    }

    ret = sensor_sample_fetch(dev);

    return 0;
}

static int shell_our_driver_channel_get(const struct shell* sh, size_t argc, char** argv)
{
    struct sensor_value val;
    int ret = 0;
    const struct device* dev = shell_device_get_binding(argv[1]);

    if(NULL == dev)
    {
        shell_error(sh, "Couldn't find device %s", argv[1]);
        return -EFAULT;
    }

    ret = sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &val);
    if ( 0 != ret)
    {
        shell_error(sh, "Couldn't fetch channel get %d", ret);
        return -EFAULT;
    }

    shell_info(sh, "The sensor channel get result is %d", val.val1);

    return 0;
}

static int shell_our_driver_info(const struct shell* sh, size_t argc, char** argv)
{
    shell_info(sh, "The device name is %s", argv[1]);
    shell_info(sh, "Ready state");

    return 0;
}

static int shell_our_driver_set(const struct shell* sh, size_t argc, char** argv)
{
    const struct device* dev = shell_device_get_binding(argv[1]);

    if(NULL == dev)
    {
        shell_error(sh, "Couldn't find device %s", argv[1]);
        return -EFAULT;
    }

    if (0 > atoi(argv[2]) || 255 < atoi(argv[2]))
    {
        shell_error(sh, "Parameter must be between 0 and 255");
        return -EFAULT;
    }

    our_driver_set_param(dev, (uint32_t)atoi(argv[2]));

    return 0;
}
