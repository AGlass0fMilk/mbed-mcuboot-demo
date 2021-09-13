/**
 * ep-oc-mcu
 * Embedded Planet Open Core for Microcontrollers
 *
 * Built with ARM Mbed-OS
 *
 * Copyright (c) 2019-2021 Embedded Planet, Inc.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "boot_record.h"
#include "shared_data.h"

#if MCUBOOT_DATA_SHARING && MCUBOOT_BOOTLOADER_BUILD

int boot_save_shared_data(const struct image_header *hdr,
                          const struct flash_area *fap) {

    char msg[] = "hello world :)";
    char second_msg[] = "abcdefghijklmnopqrstuvwxyz012345789";

    int result = boot_add_data_to_shared_area(TLV_MAJOR_APP_SPECIFIC, TLV_MINOR_BOOTLOADER_VERSION, strlen(msg), msg);
    if(result) {
        return result;
    }

    result = boot_add_data_to_shared_area(TLV_MAJOR_APP_SPECIFIC, TLV_MINOR_MY_MESSAGE, strlen(second_msg), second_msg);

    return result;

}

#endif /* MCUBOOT_DATA_SHARING */

