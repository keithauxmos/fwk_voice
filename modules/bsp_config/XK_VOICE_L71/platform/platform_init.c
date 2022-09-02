// Copyright (c) 2022 XMOS LIMITED. This Software is subject to the terms of the
// XMOS Public License: Version 1

/* System headers */
#include <platform.h>

/* App headers */
#include "platform_conf.h"
#include "platform/app_pll_ctrl.h"
#include "platform/driver_instances.h"
#include "platform/platform_init.h"

static void mclk_init(chanend_t other_tile_c)
{
#if ON_TILE(1)
    app_pll_init();
#endif
}

static void flash_init(void)
{
#if ON_TILE(FLASH_TILE_NO)
    rtos_qspi_flash_init(
            qspi_flash_ctx,
            FLASH_CLKBLK,
            PORT_SQI_CS,
            PORT_SQI_SCLK,
            PORT_SQI_SIO,

            /** Derive QSPI clock from the 600 MHz xcore clock **/
            qspi_io_source_clock_xcore,

            /** Full speed clock configuration **/
            5, // 600 MHz / (2*5) -> 60 MHz,
            1,
            qspi_io_sample_edge_rising,
            0,

            /** SPI read clock configuration **/
            12, // 600 MHz / (2*12) -> 25 MHz
            0,
            qspi_io_sample_edge_falling,
            0,

            qspi_flash_page_program_1_4_4);
#endif
}

static void gpio_init(void)
{
    static rtos_driver_rpc_t gpio_rpc_config_t0;
    static rtos_driver_rpc_t gpio_rpc_config_t1;
    rtos_intertile_t *client_intertile_ctx[1] = {intertile_ctx};

#if ON_TILE(0)
    rtos_gpio_init(gpio_ctx_t0);

    rtos_gpio_rpc_host_init(
            gpio_ctx_t0,
            &gpio_rpc_config_t0,
            client_intertile_ctx,
            1);

    rtos_gpio_rpc_client_init(
            gpio_ctx_t1,
            &gpio_rpc_config_t1,
            intertile_ctx);
#endif

#if ON_TILE(1)
    rtos_gpio_init(gpio_ctx_t1);

    rtos_gpio_rpc_client_init(
            gpio_ctx_t0,
            &gpio_rpc_config_t0,
            intertile_ctx);

    rtos_gpio_rpc_host_init(
            gpio_ctx_t1,
            &gpio_rpc_config_t1,
            client_intertile_ctx,
            1);
#endif
}

static void i2c_init(void)
{
    static rtos_driver_rpc_t i2c_rpc_config;

#if ON_TILE(I2C_TILE_NO)
    rtos_intertile_t *client_intertile_ctx[1] = {intertile_ctx};
    rtos_i2c_master_init(
            i2c_master_ctx,
            PORT_I2C_SCL, 0, 0,
            PORT_I2C_SDA, 0, 0,
            0,
            400);

    rtos_i2c_master_rpc_host_init(
            i2c_master_ctx,
            &i2c_rpc_config,
            client_intertile_ctx,
            1);
#else
    rtos_i2c_master_rpc_client_init(
            i2c_master_ctx,
            &i2c_rpc_config,
            intertile_ctx);
#endif
}

static void i2c_slave_init(void)
{
    rtos_i2c_slave_init(
            i2c_slave_ctx,
            I2C_SLAVE_CORE_MASK,
            PORT_I2C_SCL,
            PORT_I2C_SDA,
            I2C_SLAVE_ADDR);
}

static void spi_init(void)
{
#if ON_TILE(0)
    rtos_spi_master_init(
            spi_master_ctx,
            SPI_CLKBLK,
            PORT_SSB,
            PORT_SQI_SCLK_0,
            PORT_SPI_MOSI,
            PORT_SPI_MISO);

    rtos_spi_master_device_init(
            spi_device_ctx,
            spi_master_ctx,
            0, /* WiFi CS pin is on bit 1 of the CS port */
            SPI_MODE_0,
            spi_master_source_clock_ref,
            50, /* 50 MHz */
            spi_master_sample_delay_2, /* what should this be? 2? 3? 4? */
            0, /* should this be > 0 if the above is 3-4 ? */
            1,
            0,
            0);
#endif
}

static void spi_slave_init(void)
{
#if ON_TILE(0)

    rtos_printf("spi_slave_init\n");
    rtos_spi_slave_init(
            spi_slave_ctx,
            SPI_SLAVE_CORE_MASK,
            SPI_SLAVE_CLKBLK,
            SPI_TEST_CPOL,
            SPI_TEST_CPHA,
            PORT_SQI_SCLK_0,    
            PORT_SPI_MOSI,    
            PORT_SPI_MISO,    
            PORT_SSB);   
#endif
}



static void mics_init(void)
{
#if ON_TILE(MICARRAY_TILE_NO)
    rtos_mic_array_init(
            mic_array_ctx,
            (1 << appconfPDM_MIC_IO_CORE),
            RTOS_MIC_ARRAY_CHANNEL_SAMPLE);
#endif
}

static void i2s_init(void)
{
#if appconfI2S_ENABLED
    static rtos_driver_rpc_t i2s_rpc_config;
#if ON_TILE(I2S_TILE_NO)
    rtos_intertile_t *client_intertile_ctx[1] = {intertile_ctx};
    port_t p_i2s_dout[1] = {
            PORT_I2S_DAC_DATA
    };
    port_t p_i2s_din[1] = {
            PORT_I2S_ADC_DATA
    };

    rtos_i2s_master_init(
            i2s_ctx,
            (1 << appconfI2S_IO_CORE),
            p_i2s_dout,
            1,
            p_i2s_din,
            1,
            PORT_I2S_BCLK,
            PORT_I2S_LRCLK,
            PORT_MCLK,
            I2S_CLKBLK);


    rtos_i2s_rpc_host_init(
            i2s_ctx,
            &i2s_rpc_config,
            client_intertile_ctx,
            1);
#else
    rtos_i2s_rpc_client_init(
            i2s_ctx,
            &i2s_rpc_config,
            intertile_ctx);
#endif
#endif
}

// static void uart_init(void)
// {
// #if ON_TILE(UART_TILE_NO)
//     hwtimer_t tmr_tx = hwtimer_alloc();

//     rtos_uart_tx_init(
//             uart_tx_ctx,
//             XS1_PORT_1A,    /* J4:24*/
//             appconfUART_BAUD_RATE,
//             8,
//             UART_PARITY_NONE,
//             1,
//             tmr_tx);
// #endif
// }

void platform_init(chanend_t other_tile_c)
{
    rtos_intertile_init(intertile_ctx, other_tile_c);

#ifdef APPCONF_SPI_I2C_SLAVE_TEST == 1
    spi_slave_init();
    // i2c_slave_init();
#else
//     mclk_init(other_tile_c);
//     gpio_init();
    spi_init();
//     flash_init();
    i2c_init();
#endif
//     mics_init();
//     i2s_init();
//     uart_init();
}
