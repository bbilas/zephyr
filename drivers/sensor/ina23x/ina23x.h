/*
 * Copyright (c) 2021  The Chromium OS Authors
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_DRIVERS_SENSOR_INA23X_H_
#define ZEPHYR_DRIVERS_SENSOR_INA23X_H_

#include <drivers/gpio.h>
#include <drivers/i2c.h>

#define INA237_REG_MANUFACTURER_ID 0x3E
#define INA237_REG_ADC_CONFIG     0x01

#define INA237_MANUFACTURER_ID 0x5449

struct ina23x_data {
	const struct device *dev;
	int32_t id;
	const uint8_t *registers_map;
	int32_t current;
	int32_t bus_voltage;
	int32_t power;
#ifdef CONFIG_INA23X_TRIGGER
	const struct device *gpio;
	struct gpio_callback gpio_cb;
	struct k_work work;
	sensor_trigger_handler_t handler_alert;
#endif  /* CONFIG_INA23X_TRIGGER */
};

struct ina23x_config {
	const struct device *bus;
	const uint16_t i2c_slv_addr;
	uint16_t config;
	uint16_t adc_config;
	uint16_t current_lsb;
	uint16_t rshunt;
#ifdef CONFIG_INA23X_TRIGGER
	bool trig_enabled;
	uint16_t mask;
	const struct gpio_dt_spec gpio_alert;
	uint16_t alert_limit;
#endif  /* CONFIG_INA23X_TRIGGER */
};

int ina23x_trigger_mode_init(const struct device *dev);
int ina23x_trigger_set(const struct device *dev,
		       const struct sensor_trigger *trig,
		       sensor_trigger_handler_t handler);

#endif /* ZEPHYR_DRIVERS_SENSOR_INA23X_H_ */
