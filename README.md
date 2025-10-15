# FRAM-XPLAT

## Intro
A cross-platform serial [FRAM (Ferroelectric RAM)](FRAM.md) library designed for embedded devices that require high-end logging functionalities, with minimal logging latency, low power consumption and high frequency write/read rates making it ideal for mission-critical applications.
## Design
This library is designed in layered manner:
```text
+-------------------+
|    application    | - Embedded application that uses FRAM as a storage medium
+-------------------+
          ^
          |
+-------------------+
|       driver      | - FRAM driver layer: constant, cross-platform
+-------------------+
          ^
          |
+-------------------+
|        port       | - FRAM port: user configurable, depends on hardware platform
+-------------------+
```

The FRAM **driver** layer provides a unified interface that remains identical across all devices supported by the library. The **port** layer, on the other hand, acts as a hardware abstraction layer that connects the specific platform implementation to the driver layer.

The main application can use some file/storage system above the library's driver layer if the intention is not to use FRAM on the lowest, byte-access level.

## Porting the library
Porting the **fram-xplat** library to your desired hardware platform is being done by providing functions needed by **driver** layer to operate, and those functions should have prototypes like this:

``` int spi_write(void *context, uint8_t *data, uint16_t size); ```

``` int spi_read(void *context, uint8_t *data, uint16_t size); ```

``` int spi_chip_select(void *context); ```

``` int spi_chip_deselect(void *context); ```

An example of a complete port implementation can be found under ```fram-xplat/port/stm32/```, which targets STM32 devices using the STM32 HAL.

## Demos
A complete demo of the **fram-xplat** library running on the WeAct blackpill_f411ce board can be found in the following [repository](https://github.com/filipembedded/stm32-nvs-demos).

## License
This project is licensed under the BSD 3-Clause License — see the [LICENSE](LICENSE) file for details.
