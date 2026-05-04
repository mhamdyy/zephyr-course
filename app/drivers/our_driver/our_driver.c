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

#define DEV_INST(inst) DEVICE_DT_INST_DEFINE(inst, init_our_driver, NULL, NULL, NULL, POST_KERNEL, 80, &api_our_driver);
DT_INST_FOREACH_STATUS_OKAY(DEV_INST);

static const struct our_driver_config cfg_##inst = {
    .i2c = I2C_DT_SPEC_GET(inst),
    .calibration = DT_INST_PROP(inst, calibration),
};

static int our_driver_sample_fetch(const struct device *dev, enum sensor_channel channel)
{
    LOG_INF("Hello from our driver sample fetch %d\n", channel);
    return 0;
}

static int our_driver_channel_get(const struct device *dev, enum sensor_channel channel, struct sensor_value* val)
{
    LOG_INF("Hello from our driver channel get %d\n", channel);
    return 0;
}

static int our_driver_init(const struct device *dev)
{
    LOG_INF("Hello from our driver init\n");
    return 0;
}