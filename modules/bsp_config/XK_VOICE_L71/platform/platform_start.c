// Copyright (c) 2022 XMOS LIMITED. This Software is subject to the terms of the
// XMOS Public License: Version 1

/* System headers */
#include <platform.h>

/* FreeRTOS headers */
#include "FreeRTOS.h"

/* Library headers */
#include "fs_support.h"

/* App headers */
#include "platform_conf.h"
#include "platform/driver_instances.h"
// #include "dac3101.h"
#include "app_conf.h"

#include "i2c_slave_app.h"
#include "spi_slave_app.h"


extern void i2s_rate_conversion_enable(void);

static void gpio_start(void)
{
    rtos_gpio_rpc_config(gpio_ctx_t0, appconfGPIO_T0_RPC_PORT, appconfGPIO_RPC_PRIORITY);
    rtos_gpio_rpc_config(gpio_ctx_t1, appconfGPIO_T1_RPC_PORT, appconfGPIO_RPC_PRIORITY);

#if ON_TILE(0)
    rtos_gpio_start(gpio_ctx_t0);
#endif
#if ON_TILE(1)
    rtos_gpio_start(gpio_ctx_t1);
#endif
}

static void flash_start(void)
{
#if ON_TILE(FLASH_TILE_NO)
    rtos_qspi_flash_start(qspi_flash_ctx, appconfQSPI_FLASH_TASK_PRIORITY);
#endif
}

static void i2c_master_start(void)
{
    rtos_i2c_master_rpc_config(i2c_master_ctx, appconfI2C_MASTER_RPC_PORT, appconfI2C_MASTER_RPC_PRIORITY);

#if ON_TILE(I2C_TILE_NO)
    rtos_i2c_master_start(i2c_master_ctx);
#endif
}

static void i2c_slave_platform_start(void)
{
#if ON_TILE(I2C_TILE_NO)
    start_i2c_slave();
#endif
}

// static void audio_codec_start(void)
// {
// #if appconfI2S_ENABLED
//     int ret = 0;
// #if ON_TILE(I2C_TILE_NO)
//     if (dac3101_init(appconfI2S_AUDIO_SAMPLE_RATE) != 0) {
//         rtos_printf("DAC initialization failed\n");
//     }
//     rtos_intertile_tx(intertile_ctx, 0, &ret, sizeof(ret));
// #else
//     rtos_intertile_rx_len(intertile_ctx, 0, RTOS_OSAL_WAIT_FOREVER);
//     rtos_intertile_rx_data(intertile_ctx, &ret, sizeof(ret));
// #endif
// #endif
// }

static void mics_start(void)
{
#if ON_TILE(MICARRAY_TILE_NO)
    rtos_mic_array_start(
            mic_array_ctx,
            2 * MIC_ARRAY_CONFIG_SAMPLES_PER_FRAME,
            appconfPDM_MIC_INTERRUPT_CORE);
#endif
}

static void i2s_start(void)
{
#if appconfI2S_ENABLED
    rtos_i2s_rpc_config(i2s_ctx, appconfI2S_RPC_PORT, appconfI2S_RPC_PRIORITY);
#if ON_TILE(I2S_TILE_NO)

    if (appconfI2S_AUDIO_SAMPLE_RATE == 3*appconfAUDIO_PIPELINE_SAMPLE_RATE) {
        i2s_rate_conversion_enable();
    }

    rtos_i2s_start(
            i2s_ctx,
            rtos_i2s_mclk_bclk_ratio(appconfAUDIO_CLOCK_FREQUENCY, appconfI2S_AUDIO_SAMPLE_RATE),
            I2S_MODE_I2S,
            2.2 * appconfAUDIO_PIPELINE_FRAME_ADVANCE,
            1.2 * appconfAUDIO_PIPELINE_FRAME_ADVANCE,
            appconfI2S_INTERRUPT_CORE);
#endif
#endif
}

static void uart_start(void)
{
#if ON_TILE(UART_TILE_NO)
    rtos_uart_tx_start(uart_tx_ctx);
#endif
}

static void spi_start(void)
{
#if ON_TILE(0)
    rtos_spi_master_start(spi_master_ctx, appconfSPI_MASTER_TASK_PRIORITY);
#endif
}

extern void start_spi_devices();

static void spi_slave_platform_start(void)
{
#if ON_TILE(0)
    rtos_printf("spi_slave_start\n");
    start_spi_devices();
#endif
}

void platform_start(void)
{
    rtos_intertile_start(intertile_ctx);

#ifdef APPCONF_SPI_I2C_SLAVE_TEST == 1
    spi_slave_platform_start();
    
    // i2c_slave_platform_start();
#else
    // gpio_start();
    // flash_start();
    i2c_master_start();
    // audio_codec_start();
    spi_start();
    // mics_start();
    // i2s_start();
    // uart_start();
#endif
}