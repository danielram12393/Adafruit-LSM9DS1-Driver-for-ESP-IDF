#include <string.h>
#include <stdio.h>
#include "sdkconfig.h"
#include "esp_types.h"
#include "esp_log.h"
#include "esp_check.h"
#include "driver/i2c_master.h"
#include "lsm9ds1.h"
#include "esp_check.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char TAG[] = "i2c-lsm9ds1-ag";

esp_err_t i2c_lsm9ds1_init(i2c_master_bus_handle_t bus_handle, const i2c_lsm9ds1_config_t *lsm9ds1_config, i2c_lsm9ds1_handle_t *lsm9ds1_handle)
{
    // Check if there is enough memory for the device
    esp_err_t ret = ESP_OK;
    i2c_lsm9ds1_handle_t out_handle;
    out_handle = (i2c_lsm9ds1_handle_t)calloc(1, sizeof(*out_handle));
    ESP_GOTO_ON_FALSE(out_handle, ESP_ERR_NO_MEM, err, TAG, "no memory for i2c lsm9ds1 device");

    // Initialize accelerometer/gyroscope
    ESP_GOTO_ON_ERROR(
        i2c_master_bus_add_device(bus_handle, &lsm9ds1_config->accel_gyro_config, &out_handle->accel_gyro_dev),
        err, TAG, "Failed to add accel/gyro device");

    // Initialize magnetometer
    ESP_GOTO_ON_ERROR(
        i2c_master_bus_add_device(bus_handle, &lsm9ds1_config->mag_config, &out_handle->mag_dev),
        err, TAG, "Failed to add magnetometer device");

    // Allocate buffer
    out_handle->buffer = (uint8_t *)calloc(1, lsm9ds1_config->buffer_size);
    ESP_GOTO_ON_FALSE(out_handle->buffer, ESP_ERR_NO_MEM, err, TAG, "no memory for LSM9DS1 buffer");

    *lsm9ds1_handle = out_handle;
    return ESP_OK;

err:
    if (out_handle)
    {
        if (out_handle->accel_gyro_dev)
        {
            i2c_master_bus_rm_device(out_handle->accel_gyro_dev);
        }
        if (out_handle->mag_dev)
        {
            i2c_master_bus_rm_device(out_handle->mag_dev);
        }
        free(out_handle->buffer);
    }
    free(out_handle);
    return ret;
}