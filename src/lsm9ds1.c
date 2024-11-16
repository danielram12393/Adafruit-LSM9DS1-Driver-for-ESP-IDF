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

#define I2C_EEPROM_MAX_TRANS_UNIT (48)
// Maximum number of bytes that can be transferred in a single transaction.
// Different devices might share one I2C bus

static const char TAG[] = "i2c-lsm9ds1";

esp_err_t i2c_lsm9ds1_init(i2c_master_bus_handle_t bus_handle, const i2c_lsm9ds1_config_t *lsm9ds1_config, i2c_lsm9ds1_handle_t *lsm9ds1_handle)
{
    esp_err_t ret = ESP_OK;
    i2c_lsm9ds1_handle_t out_handle;
    out_handle = (i2c_lsm9ds1_handle_t)calloc(1, sizeof(*out_handle));
    ESP_GOTO_ON_FALSE(out_handle, ESP_ERR_NO_MEM, err, TAG, "no memory for i2c lsm9ds1 device");

    return ESP_OK;

err:
    if (out_handle && out_handle->i2c_dev)
    {
        i2c_master_bus_rm_device(out_handle->i2c_dev);
    }
    free(out_handle);
    return ret;
}