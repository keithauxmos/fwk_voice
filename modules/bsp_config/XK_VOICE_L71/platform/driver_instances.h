// Copyright (c) 2022 XMOS LIMITED. This Software is subject to the terms of the
// XMOS Public License: Version 1

#ifndef DRIVER_INSTANCES_H_
#define DRIVER_INSTANCES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "rtos_intertile.h"
#include "rtos_qspi_flash.h"
#include "rtos_gpio.h"
#include "rtos_i2c_master.h"
#include "rtos_i2s.h"
#include "rtos_uart_tx.h"
#include "rtos_spi_master.h"
#include "rtos_spi_slave.h"
#include "rtos_i2c_slave.h"

#ifdef __cplusplus
};
#endif

#include "rtos_mic_array.h"

/* Tile specifiers */
#define FLASH_TILE_NO      0
#define I2C_TILE_NO        0
#define MICARRAY_TILE_NO   1
#define I2S_TILE_NO        1
#define UART_TILE_NO       0

/** TILE 0 Clock Blocks */
#define FLASH_CLKBLK  XS1_CLKBLK_1

/** TILE 1 Clock Blocks */
#define PDM_CLKBLK_1  XS1_CLKBLK_1
#define PDM_CLKBLK_2  XS1_CLKBLK_2
#define I2S_CLKBLK    XS1_CLKBLK_3
#define MCLK_CLKBLK   XS1_CLKBLK_4
#define SPI_CLKBLK   XS1_CLKBLK_3
#define SPI_SLAVE_CLKBLK  XS1_CLKBLK_3

/* Port definitions */
#define PORT_MCLK           PORT_MCLK_IN_OUT
#define PORT_SQI_CS         PORT_SQI_CS_0
#define PORT_SQI_SCLK       PORT_SQI_SCLK_0
#define PORT_SQI_SIO        PORT_SQI_SIO_0
#define PORT_I2S_DAC_DATA   I2S_DATA_IN
#define PORT_I2S_ADC_DATA   I2S_MIC_DATA

extern rtos_intertile_t *intertile_ctx;
extern rtos_qspi_flash_t *qspi_flash_ctx;
extern rtos_gpio_t *gpio_ctx_t0;
extern rtos_gpio_t *gpio_ctx_t1;
extern rtos_mic_array_t *mic_array_ctx;
extern rtos_i2c_master_t *i2c_master_ctx;
extern rtos_i2s_t *i2s_ctx;
extern rtos_uart_tx_t *uart_tx_ctx;
extern rtos_spi_master_t *spi_master_ctx;
extern rtos_spi_master_device_t *spi_device_ctx;

#if APPCONF_SPI_I2C_SLAVE_TEST == 1
extern rtos_i2c_slave_t *i2c_slave_ctx;
extern rtos_spi_slave_t *spi_slave_ctx;
#endif

#endif /* DRIVER_INSTANCES_H_ */
