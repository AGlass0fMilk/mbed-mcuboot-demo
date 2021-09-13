/*
 * Mbed-OS Microcontroller Library
 * Copyright (c) 2021 Embedded Planet
 * Copyright (c) 2021 ARM Limited
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
 * limitations under the License
 */

#ifndef SHARED_DATA_H_
#define SHARED_DATA_H_

/* See boot_status.h in mcuboot sources for more information
 * on the format of the tlv_type field of the shared data TLVs
 * The upper 4 bits are the major TLV category */
#define TLV_MAJOR_APP_SPECIFIC 0xF
#define TLV_MINOR_BOOTLOADER_VERSION 0x10D
#define TLV_MINOR_MY_MESSAGE 0x10E

#endif /* SHARED_DATA_H_ */
