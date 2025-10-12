/**
 * @file port_stm32.c
 * @brief STM32 HAL port for FRAM-XPLAT library 
 * @author Filip Stojanovic
 */

#include "port_stm32.h"

int spi_write(void *context, uint8_t *data, uint16_t size) {
    SPI_HandleTypeDef *hspi = (SPI_HandleTypeDef *)context;
    
    HAL_StatusTypeDef status = HAL_SPI_Transmit(hspi, data, size, SPI_TIMEOUT_MS);
    if (status != HAL_OK) {
        return -1;
    }
    return 0;
}

int spi_read(void *context, uint8_t *data, uint16_t size) {
    SPI_HandleTypeDef *hspi = (SPI_HandleTypeDef *)context;

    HAL_StatusTypeDef status = HAL_SPI_Receive(hspi, data, size, SPI_TIMEOUT_MS);
    if (status != HAL_OK) {
        return -1;
    }
    return 0;
}

int spi_chip_select(void *context) {
    GPIO_CS_Config *gpio = (GPIO_CS_Config *)context;
    HAL_GPIO_WritePin(gpio->cs_port, gpio->cs_pin, GPIO_PIN_RESET);
    return 0;
}

int spi_chip_deselect(void *context) {
    GPIO_CS_Config *gpio = (GPIO_CS_Config *)context;
    HAL_GPIO_WritePin(gpio->cs_port, gpio->cs_pin, GPIO_PIN_SET);
    return 0;
}
