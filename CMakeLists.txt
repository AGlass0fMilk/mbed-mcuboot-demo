# Copyright (c) 2021 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

# Mbed-MCUboot Demo Bootloader

cmake_minimum_required(VERSION 3.19.0 FATAL_ERROR)

set(MBED_PATH ${CMAKE_CURRENT_SOURCE_DIR}/mbed-os CACHE INTERNAL "")
set(MCUBOOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/mcuboot CACHE INTERNAL "")
set(MBED_CONFIG_PATH ${CMAKE_CURRENT_BINARY_DIR} CACHE INTERNAL "")
set(APP_TARGET bootloader)

include(${MBED_PATH}/tools/cmake/app.cmake)

project(${APP_TARGET})

add_subdirectory(${MBED_PATH})
add_subdirectory(${MCUBOOT_PATH}/boot/bootutil/)
add_subdirectory(${MCUBOOT_PATH}/boot/mbed/)  # Mbed-MCUboot Port

add_executable(${APP_TARGET})

target_sources(${APP_TARGET}
    PUBLIC
        default_bd.cpp
        signing_keys.c
)

target_link_libraries(${APP_TARGET}
    PUBLIC
        bootutil
        mbed-mcuboot
        mbed-storage-spif
        mbed-storage-qspif
        mbed-baremetal
)

mbed_set_post_build(${APP_TARGET})

option(VERBOSE_BUILD "Have a verbose build process")
if(VERBOSE_BUILD)
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif()