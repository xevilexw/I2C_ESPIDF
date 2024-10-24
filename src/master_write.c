#include "driver/gpio.h"
#include "driver/i2c.h"
#include "esp_err.h"
#include "esp_log.h"

/* I2C MACROS */
#define     I2C_MASTER_SDA     GPIO_NUM_21
#define     I2C_MASTER_SCL     GPIO_NUM_22
#define     I2C_FREQUENCY   100000
#define     I2C_SLAVE_ADDR      0x01

/* Data to send through I2C to another MCU */
uint8_t data_to_send[2] = {0x01, 0x02};

/* I2C Config */
i2c_config_t configuration = {
    .mode = I2C_MODE_MASTER,
    .sda_io_num = I2C_MASTER_SDA,
    .scl_io_num = I2C_MASTER_SCL,
    .sda_pullup_en = GPIO_PULLUP_ENABLE,
    .scl_pullup_en = GPIO_PULLUP_ENABLE,
    .master.clk_speed = I2C_FREQUENCY,
    .clk_flags = I2C_SCLK_SRC_FLAG_AWARE_DFS,
};

void app_main() {
    i2c_port_t i2c_port = I2C_NUM_0;
    i2c_mode_t i2c_mode = I2C_MODE_MASTER;
    i2c_driver_install(i2c_port, i2c_mode, 0, 0, ESP_INTR_FLAG_LOWMED);
    
    /* Create frame handle */
    i2c_cmd_handle_t i2c_cmd_handle = i2c_cmd_link_create();
    i2c_master_start(i2c_cmd_handle);

    /* Write slave addr */
    i2c_master_write_byte(i2c_cmd_handle, (I2C_SLAVE_ADDR << 1) | I2C_MASTER_READ, true);

    /* Send data to this address */
    i2c_master_write(i2c_cmd_handle, data_to_send, sizeof(data_to_send), true);
    i2c_master_stop(i2c_cmd_handle);

    /* Sending with error logging... */
    if(i2c_master_cmd_begin(i2c_port, i2c_cmd_handle, pdMS_TO_TICKS(100)) == ESP_OK) {
        ESP_LOGI("I2C", "Send su   ccessfully");
    }
    i2c_cmd_link_delete(i2c_cmd_handle);

    while(1) {

    }
    i2c_driver_delete(i2c_port);
}