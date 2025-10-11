/**
 * @file fram_ll.h 
 * @brief FRAM low-level driver 
 * @author Filip Stojanovic
 */

#include <stdlib.h>

/**
 * @brief FRAM Opcodes
 * @note Provides list of opcodes used to interact with FRAM memory
 */
typedef enum {
    FRAM_OPCODE_WREN = 0b00000110, // Set write enable latch
    FRAM_OPCODE_WRDI = 0b00000100, // Reset write enable latch
    FRAM_OPCODE_RDSR = 0b00000101, // Read Status Register
    FRAM_OPCODE_WRSR = 0b00000001, // Write Status Register
    FRAM_OPCODE_READ = 0b00000011, // Read memory data
    FRAM_OPCODE_FSTRD = 0b00001011, // Fast read memory data
    FRAM_OPCODE_WRITE = 0b00000010, // Write memory data
    FRAM_OPCODE_SLEEP = 0b10111001, // Enter sleep mode
    FRAM_OPCODE_RDID = 0b10011111 // Read device ID
} FRAM_Opcode_TypeDef;

typedef enum {
    FRAM_STATUS_SUCCESS = 0,
    FRAM_STATUS_ERROR = -1,
    FRAM_STATUS_TIMEOUT = -2,
} FRAM_Status_TypeDef;



/**
 * @brief FRAM Instance
 * @note The FRAM instance struct, consists of functions pointers passed by
 *       a layer bellow - platform-level-drivers and FRAM memory specs 
 */
typedef struct {
    void *context;
    uint16_t capacity_mbit;
    uint16_t max_bus_speed_mhz;
    //NOTE: Put down platform-level function pointers
    int(*spi_write)(void *context, uint8_t *data, uint16_t size);
    int(*spi_read)(void *context, uint8_t *data, uint16_t size);
    int(*spi_chip_select)(void *context);
    int(*spi_chip_deselect)(void *context);
} FRAM_Instance_TypeDef;

FRAM_Status_TypeDef FRAM_Write(FRAM_Instance_TypeDef *fram, uint8_t *address, uint8_t *data, uint16_t size);

FRAM_Status_TypeDef FRAM_Read(FRAM_Instance_TypeDef *fram, uint8_t *address, uint8_t *data, uint16_t size);

FRAM_Status_TypeDef FRAM_ReadStatusReg(FRAM_Instance_TypeDef *fram, uint8_t data);
