/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2016-2018 Damien P. George
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef MICROPY_INCLUDED_DRIVERS_MEMORY_SPIFLASH_H
#define MICROPY_INCLUDED_DRIVERS_MEMORY_SPIFLASH_H

#include "drivers/bus/qspi.h"
#include "extmod/machine_spi.h"

enum {
    MP_SPIFLASH_BUS_SPI,
    MP_SPIFLASH_BUS_QSPI,
};

typedef struct _mp_spiflash_config_t {
    uint32_t bus_kind;
    union {
        struct {
            mp_hal_pin_obj_t cs;
            void *data;
            const mp_machine_spi_p_t *proto;
        } u_spi;
        struct {
            void *data;
            const mp_qspi_proto_t *proto;
        } u_qspi;
    } bus;
} mp_spiflash_config_t;

typedef struct _mp_spiflash_t {
    const mp_spiflash_config_t *config;
    volatile uint32_t flags;
} mp_spiflash_t;

void mp_spiflash_init(mp_spiflash_t *self);
void mp_spiflash_flush(mp_spiflash_t *self);
void mp_spiflash_read(mp_spiflash_t *self, uint32_t addr, size_t len, uint8_t *dest);
int mp_spiflash_write(mp_spiflash_t *self, uint32_t addr, size_t len, const uint8_t *src);

#endif // MICROPY_INCLUDED_DRIVERS_MEMORY_SPIFLASH_H
