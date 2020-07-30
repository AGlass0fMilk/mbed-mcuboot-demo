/*
 * system_overrides.cpp
 *
 *  Created on: Jul 30, 2020
 *      Author: gdbeckstein
 */

#include "platform/mbed_error.h"

/**
 * Override some system calls that add a bit of code size
 * Safety of nullifying error handlers is unknown :)
 */

mbed_error_status_t mbed_error(mbed_error_status_t error_status, const char *error_msg, unsigned int error_value, const char *filename, int line_number)
{
    // Do nothing
    return 0;
}

void mbed_die(void) {
    // Do nothing
}
