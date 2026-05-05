#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>

#define DT_DRV_COMPAT our_driver

/* The devicetree node identifier for the "led0" alias. */
#define LED_NODE DT_ALIAS(app_led)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

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
    gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    return 0;
}

static int our_driver_channel_get(const struct device *dev, enum sensor_channel channel, struct sensor_value* val)
{
    LOG_INF("Hello from our driver channel get %d", channel);
    gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
    return 0;
}

static int our_driver_init(const struct device *dev)
{
    LOG_INF("Hello from our driver init");
    if (!gpio_is_ready_dt(&led))
    {
        LOG_ERR("LED not ready");
        return -ENODEV;
    }

    if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE) < 0)
    {
        LOG_ERR("Failed to configure LED");
        return -ENODEV;
    }
    return 0;
}