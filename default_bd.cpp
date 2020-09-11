/*
 * default_bd.cpp
 *
 *  Created on: Jul 30, 2020
 *      Author: gdbeckstein
 */

#include "BlockDevice.h"

#include "SlicingBlockDevice.h"

#if COMPONENT_SPIF
#include "components/storage/blockdevice/COMPONENT_SPIF/SPIFBlockDevice.h"
#endif

#if COMPONENT_RSPIF
#include "components/storage/blockdevice/COMPONENT_RSPIF/SPIFReducedBlockDevice.h"
#endif

#if COMPONENT_QSPIF
#include "components/storage/blockdevice/COMPONENT_QSPIF/QSPIFBlockDevice.h"
#endif

#if COMPONENT_DATAFLASH
#include "components/storage/blockdevice/COMPONENT_DATAFLASH/DataFlashBlockDevice.h"
#endif

#if COMPONENT_SD
#include "components/storage/blockdevice/COMPONENT_SD/SDBlockDevice.h"

#if (STATIC_PINMAP_READY)
const spi_pinmap_t static_spi_pinmap = get_spi_pinmap(MBED_CONF_SD_SPI_MOSI, MBED_CONF_SD_SPI_MISO, MBED_CONF_SD_SPI_CLK, NC);
#endif
#endif

#if COMPONENT_FLASHIAP
#include "components/storage/blockdevice/COMPONENT_FLASHIAP/FlashIAPBlockDevice.h"
#endif

BlockDevice *BlockDevice::get_default_instance()
{
#if COMPONENT_SPIF

    static SPIFBlockDevice default_bd(
        MBED_CONF_SPIF_DRIVER_SPI_MOSI,
        MBED_CONF_SPIF_DRIVER_SPI_MISO,
        MBED_CONF_SPIF_DRIVER_SPI_CLK,
        MBED_CONF_SPIF_DRIVER_SPI_CS,
        MBED_CONF_SPIF_DRIVER_SPI_FREQ
    );

    return &default_bd;

#elif COMPONENT_RSPIF

    static SPIFReducedBlockDevice default_bd(
        MBED_CONF_RSPIF_DRIVER_SPI_MOSI,
        MBED_CONF_RSPIF_DRIVER_SPI_MISO,
        MBED_CONF_RSPIF_DRIVER_SPI_CLK,
        MBED_CONF_RSPIF_DRIVER_SPI_CS,
        MBED_CONF_RSPIF_DRIVER_SPI_FREQ
    );

    return &default_bd;

#elif COMPONENT_QSPIF

    static QSPIFBlockDevice default_bd(
        MBED_CONF_QSPIF_QSPI_IO0,
        MBED_CONF_QSPIF_QSPI_IO1,
        MBED_CONF_QSPIF_QSPI_IO2,
        MBED_CONF_QSPIF_QSPI_IO3,
        MBED_CONF_QSPIF_QSPI_SCK,
        MBED_CONF_QSPIF_QSPI_CSN,
        MBED_CONF_QSPIF_QSPI_POLARITY_MODE,
        MBED_CONF_QSPIF_QSPI_FREQ
    );

    return &default_bd;

#elif COMPONENT_DATAFLASH

    static DataFlashBlockDevice default_bd(
        MBED_CONF_DATAFLASH_SPI_MOSI,
        MBED_CONF_DATAFLASH_SPI_MISO,
        MBED_CONF_DATAFLASH_SPI_CLK,
        MBED_CONF_DATAFLASH_SPI_CS
    );

    return &default_bd;

#elif COMPONENT_SD

#if (STATIC_PINMAP_READY)
    static SDBlockDevice default_bd(
        static_spi_pinmap,
        MBED_CONF_SD_SPI_CS
    );
#else
    static SDBlockDevice default_bd(
        MBED_CONF_SD_SPI_MOSI,
        MBED_CONF_SD_SPI_MISO,
        MBED_CONF_SD_SPI_CLK,
        MBED_CONF_SD_SPI_CS
    );
#endif

    return &default_bd;

#elif COMPONENT_FLASHIAP

#if (MBED_CONF_FLASHIAP_BLOCK_DEVICE_SIZE == 0) && (MBED_CONF_FLASHIAP_BLOCK_DEVICE_BASE_ADDRESS == 0xFFFFFFFF)

    size_t flash_size;
    uint32_t start_address;
    uint32_t bottom_address;
    FlashIAP flash;

    int ret = flash.init();
    if (ret != 0) {
        return 0;
    }

    //Find the start of first sector after text area
    bottom_address = align_up(FLASHIAP_APP_ROM_END_ADDR, flash.get_sector_size(FLASHIAP_APP_ROM_END_ADDR));
    start_address = flash.get_flash_start();
    flash_size = flash.get_flash_size();

    ret = flash.deinit();

    static FlashIAPBlockDevice default_bd(bottom_address, start_address + flash_size - bottom_address);

#else

    static FlashIAPBlockDevice default_bd;

#endif

    return &default_bd;

#else

    return NULL;

#endif

}

/**
 * You can override this function to suit your hardware/memory configuration
 * By default it simply returns what is returned by BlockDevice::get_default_instance();
 */
mbed::BlockDevice* get_secondary_bd(void) {
    // In this case, our flash is much larger than a single image so
    // slice it into a smaller size, 1MB at the beginning

    mbed::BlockDevice* default_bd = mbed::BlockDevice::get_default_instance();
    static mbed::SlicingBlockDevice sliced_bd(default_bd, 0x0, 0xDD000);
    return &sliced_bd;
}

