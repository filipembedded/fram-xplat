/**
 * @file port_stm32.c
 * @brief STM32 HAL port for FRAM-XPLAT library 
 * @author Filip Stojanovic
 */

#include "stm32f4xx_hal.h"

#define SPI_TIMEOUT_MS 50

int spi_write(SPI_HandleTypeDef *hspi, uint8_t *data, uint16_t size);

int spi_read(SPI_HandleTypeDef *hspi, uint8_t *data, uint16_t size);

int spi_chip_select();

int spi_chip_deselect();
