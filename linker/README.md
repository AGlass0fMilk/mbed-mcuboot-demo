# Customized Linker Scripts

The mainstream version of some targets' linker scripts do not allow the kind of configuration needed to supported sharing data (ie: reserving RAM regions using `MBED_RAM_SIZE` and `MBED_RAM_START`). To accomodate this, this directory contains customized linker scripts for supported targets.

**Please note:** Only the GCC ARM toolchain is supported by the customized linker scripts. You can use these customized scripts as a starting point if you are using a different toolchain.

To build using a customized linker script, add the following to your `mbed compile` command:

`-l <path-to-linker-script>`

This tells Mbed CLI 1 to use the given linker script specified by `<path-to-linker-script>`.

**IMPORTANT:** Make sure to build the bootable application with this customized linker script as well!!!

## K64F

The mainstream K64F linker script does not use the `MBED_RAM_START` and `MBED_RAM_SIZE` symbols. This customized linker script reserves a section of RAM at the end of SRAM_U (0x2003 0000). The start of the reserved region depends on the size of the shared data region (128 bytes by default):

`start_of_shared_region = end_of_SRAM_U - size_of_shared_region = 0x20030000 - 0x80 = 0x2002FF80`

To build this demo with data sharing for the K64F target, use the following command:

`mbed compile -t GCC_ARM -m K64F --app-config mbed_app_data_sharing.json -l ./linker/TARGET_K64F/TOOLCHAIN_GCC_ARM/MK64FN1M0xxx12.ld`
