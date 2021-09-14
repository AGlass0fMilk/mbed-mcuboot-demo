/**
 * Created on: Sep 13, 2021
 * Created by: gdbeckstein
 *
 * Built with ARM Mbed-OS
 *
 * Copyright (c) Embedded Planet, Inc - All rights reserved
 * 
 * This source file is private and confidential.
 * Unauthorized copying of this file is strictly prohibited.
 */

/**
 * If the shared data feature of MCUboot is used in this demo,
 * this feature uses an uninitialized region of RAM to share data between the bootloader and the
 * booted application. When building the for the K64F target, the K64F has two RAM
 * regions (that are adjacent): `SRAM_L` and `SRAM_U`. The default K64F linker script will not initialize variables
 * stored in the "uninitialized" section of RAM, which begins at `SRAM_U` aka 0x20000000. `SRMA_L` is the first 64kB
 * of RAM while `SRAM_U` is the rest (64kB for a total of 128kB).
 *
 * To ensure a section of RAM is uninitialized at startup, we must declare an array here. We use GCC attributes to specify that the linker should
 * keep this symbol and the name of the section ("uninitialized") into which it should be placed.
 *
 * See the linker script and associated documentation for more details
 */

#if defined(MCUBOOT_DATA_SHARING)

static char SHARED_DATA_RESERVED_MEMORY_REGION[MCUBOOT_SHARED_DATA_SIZE] __attribute__((used,section(".keep.uninitialized")));

#endif
