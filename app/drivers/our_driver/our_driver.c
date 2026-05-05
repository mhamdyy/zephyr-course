#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

#define DT_DRV_COMPAT our_driver

LOG_MODULE_REGISTER(our_driver, LOG_LEVEL_INF);

static int our_driver_init(const struct device *dev);
static int our_driver_channel_get(const struct device *dev, enum sensor_channel channel, struct sensor_value* val);
static int our_driver_sample_fetch(const struct device *dev, enum sensor_channel channel);

static DEVICE_API(sensor, api_our_driver) = {
    .sample_fetch = our_driver_sample_fetch,
    .channel_get = our_driver_channel_get,
};

#define DEV_INST(inst) DEVICE_DT_INST_DEFINE(inst, our_driver_init, NULL, NULL, NULL, POST_KERNEL, 80, &api_our_driver);
DT_INST_FOREACH_STATUS_OKAY(DEV_INST);

static int our_driver_sample_fetch(const struct device *dev, enum sensor_channel channel)
{
    LOG_INF("Hello from our driver sample fetch %d", channel);
    return 0;
}

static int our_driver_channel_get(const struct device *dev, enum sensor_channel channel, struct sensor_value* val)
{
    LOG_INF("Hello from our driver channel get %d", channel);
    return 0;
}

static int our_driver_init(const struct device *dev)
{
    LOG_INF("Hello from our driver init");
    return 0;
}