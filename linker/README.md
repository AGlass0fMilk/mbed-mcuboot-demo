# Customized Linker Scripts

The mainstream version of some targets' linker scripts do not allow the kind of configuration needed to supported sharing data (ie: reserving RAM regions). To accomodate this, this directory contains customized linker scripts for supported targets.

**Please note:** Only the GCC ARM toolchain is supported by the customized linker scripts. You can use these customized scripts as a starting point if you are using a different toolchain.

To build using a customized linker script, add the following to your `mbed compile` command:

`-l <path-to-linker-script>`

This tells Mbed CLI 1 to use the given linker script specified by `<path-to-linker-script>`.

**IMPORTANT:** Make sure to build the bootable application with this customized linker script as well!!!

## K64F

The mainstream K64F linker script does not use the `MBED_RAM_START` and `MBED_RAM_SIZE` symbols. This customized linker script reserves a section of RAM at the beginning of SRAM_U (0x2000 0000)
