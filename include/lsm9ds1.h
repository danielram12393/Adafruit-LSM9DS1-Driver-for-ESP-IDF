#include <stdint.h>
#include "driver/i2c_master.h"
#include "esp_err.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct
    {
        i2c_device_config_t lsm9ds1_ag_device; /*!< Configuration for accelgyro device */
        i2c_device_config_t lsm9ds1_m_device;  /*!< Configuration for mag device */
        uint8_t addr_wordlen;                  /*!< block address wordlen */
        uint8_t write_time_ms;                 /*!< eeprom write time, typically 10ms*/
    } i2c_lsm9ds1_config_t;

    struct i2c_lsm9ds1_t
    {
        i2c_master_dev_handle_t i2c_dev; /*!< I2C device handle */
        uint8_t addr_wordlen;            /*!< block address wordlen */
        uint8_t *buffer;                 /*!< I2C transaction buffer */
        uint8_t write_time_ms;           /*!< I2C eeprom write time(ms)*/
    };

    typedef struct i2c_lsm9ds1_t i2c_lsm9ds1_t;

    /* handle of LSM9DS1 device */
    typedef struct i2c_lsm9ds1_t *i2c_lsm9ds1_handle_t;

    /**
     * @brief Init an LSM9DS1 device.
     *
     * @param[in] bus_handle I2C master bus handle
     * @param[in] lsm9ds1_config Configuration of LSM9DS1
     * @param[out] lsm9ds1_handle Handle of LSM9DS1
     * @return ESP_OK: Init success. ESP_FAIL: Not success.
     */
    esp_err_t i2c_lsm9ds1_init(i2c_master_bus_handle_t bus_handle, const i2c_lsm9ds1_config_t *lsm9ds1_config, i2c_lsm9ds1_handle_t *lsm9ds1_handle);

    /**
     * @brief Write data to LSM9DS1
     *
     * @param[in] lsm9ds1_handle LSM9DS1 handle
     * @param[in] address Block address inside LSM9DS1
     * @param[in] data Data to write
     * @param[in] size Data write size
     * @return ESP_OK: Write success. Otherwise failed, please check I2C function fail reason.
     */
    esp_err_t i2c_lsm9ds1_write(i2c_lsm9ds1_handle_t lsm9ds1_handle, uint32_t address, const uint8_t *data, uint32_t size);

    /**
     * @brief Read data to LSM9DS1
     *
     * @param lsm9ds1_handle LSM9DS1 handle
     * @param address Block address inside LSM9DS1
     * @param data Data read from LSM9DS1
     * @param size Data read size
     * @return ESP_OK: Read success. Otherwise failed, please check I2C function fail reason.
     */
    esp_err_t i2c_lsm9ds1_read(i2c_lsm9ds1_handle_t lsm9ds1_handle, uint32_t address, uint8_t *data, uint32_t size);

    /**
     * @brief Wait LSM9DS1 finish.
     * @param lsm9ds1_handle LSM9DS1 handle
     */
    void i2c_lsm9ds1_wait_idle(i2c_lsm9ds1_handle_t lsm9ds1_handle);

#ifdef __cplusplus
}
#endif