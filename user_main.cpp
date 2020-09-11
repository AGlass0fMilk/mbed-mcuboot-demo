/*
 * user_main.cpp
 *
 *  Created on: Jul 30, 2020
 *      Author: gdbeckstein
 */

/** Enable serial bootloader feature by default */
#ifndef MBED_CONF_APP_SERIAL_BOOTLOADER_ENABLE
#define MBED_CONF_APP_SERIAL_BOOTLOADER_ENABLE 1
#endif

#ifndef MBED_CONF_APP_SERIAL_BOOTLOADER_BAUD
#define MBED_CONF_APP_SERIAL_BOOTLOADER_BAUD 115200
#endif

#if MBED_CONF_APP_SERIAL_BOOTLOADER_ENABLE

#include "secondary_bd.h"

#include "SerialOTA.h"

#include "rtos/ThisThread.h"

#include "platform/mbed_version.h"

#if MBED_MAJOR_VERSION == 6
#include "drivers/BufferedSerial.h"
#include "rtos/Kernel.h"
#include <chrono>
#else
#include "drivers/UARTSerial.h"
#endif

#include "drivers/DigitalIn.h"
#include "SerialCOBS.h"

#include "SlicingBlockDevice.h"

#include "bootutil.h"

#if MBED_MAJOR_VERSION == 6
using namespace std::chrono;
#define BOOT_WAIT_TIMEOUT 5s
#else
#define BOOT_WAIT_TIMEOUT 5000
#endif

#if MBED_CONF_APP_USE_BUTTON
mbed::DigitalIn button(BUTTON1);
#endif

// TODO - add led status indicator?

#endif // MBED_CONF_APP_SERIAL_BOOTLOADER_ENABLE

void mbed_mcuboot_user_init(void) {

#if MBED_CONF_APP_SERIAL_BOOTLOADER_ENABLE

#if MBED_CONF_APP_USE_BUTTON
    // If the button is held down upon bootup, start the serial bootloader
    if(button) {
       return;
    }
#endif

    // Set up the serial interface
#if MBED_MAJOR_VERSION == 6
    mbed::BufferedSerial pc(STDIO_UART_TX, STDIO_UART_RX, MBED_CONF_APP_SERIAL_BOOTLOADER_BAUD);
#else
    mbed::UARTSerial pc(STDIO_UART_TX, STDIO_UART_RX, MBED_CONF_APP_SERIAL_BOOTLOADER_BAUD);
#endif
    // Wait for a specified timeout until just booting
#if MBED_MAJOR_VERSION == 6
    rtos::Kernel::Clock::duration time_waited = 0ms;
#else
    uint32_t time_waited = 0;
#endif
    bool timed_out = true;
    uint8_t c = 1;
    while(time_waited < BOOT_WAIT_TIMEOUT) {
        // The serial bootloader should send 0-bytes until we respond we're ready, look for that
        if(pc.readable()) {
            if(pc.read(&c, 1)) {
                if(c == 0) {
                    timed_out = false;
                    break;
                }
            }
        }

        // Otherwise, keep waiting
#if MBED_MAJOR_VERSION == 6
        rtos::ThisThread::sleep_for(100ms);
        time_waited += 100ms;
#else
        rtos::ThisThread::sleep_for(100);
        time_waited += 100;
#endif
    }

    // Serial bootloader timed out, boot the main application
    if(timed_out) {
        return;
    }

    // Serial bootloader connected, send an acknowledgement
    c = 1;
    pc.write(&c, 1);

    // Wrap it with COBS-R encoding (0-byte delimeters)
    SerialCOBS serial_cobs(pc);

    // Create the SerialOTA object and let it do its thing
    SerialOTA ota(serial_cobs, *get_secondary_bd());

    SerialOTA::ota_error_t error = ota.begin();

    if(error == SerialOTA::OTA_SUCCESS) {
        boot_set_pending(false);
    }

#endif // MBED_CONF_APP_SERIAL_BOOTLOADER_ENABLE

}



