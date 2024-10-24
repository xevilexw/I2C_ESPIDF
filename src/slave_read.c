#include "driver/gpio.h"
#include "driver/i2c.h"
#include "esp_err.h"
#include "esp_log.h"

/* I2C MACROS */
#define     I2C_SLAVE_SDA     GPIO_NUM_21
#define     I2C_SLAVE_SCL     GPIO_NUM_22
#define     I2C_FREQUENCY   100000
#define     I2C_SLAVE_ADDR      0x01

uint8_t data_buffer[10];

i2c_config_t configuration = {
    .mode = I2C_MODE_SLAVE,
    .sda_io_num = I2C_SLAVE_SDA,
    .scl_io_num = I2C_SLAVE_SCL,
    .sda_pullup_en = GPIO_PULLUP_ENABLE,
    .scl_pullup_en = GPIO_PULLUP_ENABLE,
    .slave.addr_10bit_en = 0,
    .slave.slave_addr = I2C_SLAVE_ADDR,
};

void app_main() {
    int length = i2c_slave_read_buffer(I2C_NUM_0, data_buffer, sizeof(data_buffer), pdMS_TO_TICKS(100));
    if(length > 0) {
        ESP_LOGI("I2C", "Data received: %d", length);
    }
    while(1) {
        
    }
}