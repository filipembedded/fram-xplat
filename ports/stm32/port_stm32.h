/**
 * @file port_stm32.c
 * @brief STM32 HAL port for FRAM-XPLAT library 
 * @author Filip Stojanovic
 */

#include "stm32f4xx_hal.h"

#define SPI_TIMEOUT_MS 50

typedef struct {
    GPIO_TypeDef *cs_port;
    uint16_t cs_pin;
} GPIO_CS_Config;

int spi_write(void *context, uint8_t *data, uint16_t size);

int spi_read(void *context, uint8_t *data, uint16_t size);

int spi_chip_select(void *context);

int spi_chip_deselect(void *context);
