/**
 * @file fram_ll.c
 * @brief FRAM low-level driver 
 * @author Filip Stojanovic
 */

#include "fram_ll.h"

FRAM_Status_TypeDef FRAM_Write(FRAM_Instance_TypeDef *fram, uint8_t *address, uint8_t *data, uint16_t size) {
    FRAM_Status_TypeDef status = FRAM_STATUS_SUCCESS;
    uint8_t addr[3];

    if ((fram == NULL) || (data == NULL) || (size == 0U)) {
        return FRAM_STATUS_ERROR;
    }

    // Enable Write Latch (WREN)
    uint8_t cmd = FRAM_OPCODE_WREN;
    fram->spi_chip_select(fram->context);
    
    if (fram->spi_write(fram->context, &cmd, 1) != 0) {
        fram->spi_chip_deselect(fram->context);
        return FRAM_STATUS_ERROR;
    }
    fram->spi_chip_deselect(fram->context);

    // Write command and address
    cmd = FRAM_OPCODE_WRITE;
    addr[0] = (uint8_t)((address >> 16) & 0x07U); // Upper 5 bits ignored
    addr[1] = (uint8_t)((address >> 8) & 0xFFU);
    addr[2] = (uint8_t)(address & 0xFFU);

    // Send Write sequence
    fram->spi_chip_select(fram->context);

    int ret = fram->spi_write(fram->context, &cmd, 1);
    if (ret == 0) {
        ret = fram->spi_write(fram->context, addr, 3);
    }
    if (ret == 0) {
        ret = fram->spi_write(fram->context, data, size);
    }

    fram->spi_chip_deselect(fram->context);

    if (ret != 0) {
        status = FRAM_STATUS_ERROR;
    }

    return status;
}

FRAM_Status_TypeDef FRAM_Read(FRAM_Instance_TypeDef *fram, uint8_t *address, uint8_t *data, uint16_t size) {
    FRAM_Status_TypeDef status = FRAM_STATUS_SUCCESS;
    uint8_t addr[3];

    if ((fram == NULL) || (data == NULL) || (size == 0U)) {
        return FRAM_STATUS_ERROR;
    }

    // Read command and address
    uint8_t cmd = FRAM_OPCODE_READ;
    addr[0] = (uint8_t)((address >> 16) & 0x07U); // Upper 5 bits ignored
    addr[1] = (uint8_t)((address >> 8) & 0xFFU);
    addr[2] = (uint8_t)(address & 0xFFU);

    // Send Read sequence
    fram->spi_chip_select(fram->context);

    int ret = fram->spi_write(fram->context, &cmd, 1);
    if (ret == 0) {
        ret = fram->spi_write(fram->context, addr, 3);
    }
    if (ret == 0) {
        ret = fram->spi_read(fram->context, data, size);
    }

    fram->chip_deselect(fram->context);

    if (ret != 0) {
        status = FRAM_STATUS_ERROR;
    }

    return status;
}

FRAM_Status_TypeDef FRAM_ReadStatusReg(FRAM_Instance_TypeDef *fram, uint8_t data) {
    uint8_t cmd = FRAM_OPCODE_RDSR;

    if ((fram == NULL) || (data == NULL) || (size == 0U)) {
        return FRAM_STATUS_ERROR;
    }

    fram->spi_chip_select(fram->context);

    if (fram->spi_write(fram->context, &cmd, 1) != 0) {
        fram->spi_chip_deselect(fram->context);
        return FRAM_STATUS_ERROR;
    }
    if (fram->spi_read(fram->context, &cmd, 1) != 0) {
        fram->spi_chip_deselect(fram->context);
        return FRAM_STATUS_ERROR;
    }

    fram->spi_chip_deselect(fram->context);

    return FRAM_STATUS_SUCCESS;
}
