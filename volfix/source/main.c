/**
 * volfix - background process for controlling volume and brightness
 * Copyright (C) 2022 spazzylemons
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <3ds.h>

#define APPMEMTYPE (*(u32*)0x1FF80030)

extern void __system_allocateHeaps(void) {
    extern char* fake_heap_start;
    extern char* fake_heap_end;

    extern u32 __ctru_heap;
    extern u32 __ctru_heap_size;
    extern u32 __ctru_linear_heap;
    extern u32 __ctru_linear_heap_size;

    extern int __stacksize__;

    bool is_new = APPMEMTYPE > 5;

    u32 tmp = 0;
    Result res = 0;
    // Distribute available memory into halves, aligning to page size.
    __ctru_heap_size = is_new ? 0x320000 : 0x84000;
    __ctru_linear_heap_size = is_new ? 0x2A0000 : 0x1000;
    __stacksize__ = is_new ? 0x10000 : 0x8000;
    // Allocate the application heap
    __ctru_heap = 0x08000000;
    res = svcControlMemory(&tmp, __ctru_heap, 0x0, __ctru_heap_size, (MemOp)MEMOP_ALLOC, (MemPerm)(MEMPERM_READ | MEMPERM_WRITE));
    if(res < 0) *(u32*)0x00100100 = res;
    // Allocate the linear heap
    res = svcControlMemory(&__ctru_linear_heap, 0x0, 0x0, __ctru_linear_heap_size, (MemOp)MEMOP_ALLOC_LINEAR, (MemPerm)(MEMPERM_READ | MEMPERM_WRITE));
    if(res < 0) *(u32*)0x00100200 = res;
    if(__ctru_linear_heap < 0x10000000) *(u32*)0x00100071 = __ctru_linear_heap;
	// Mappable allocator init
	mappableInit(OS_MAP_AREA_BEGIN, OS_MAP_AREA_END);
    // Set up newlib heap
    fake_heap_start = (char*)__ctru_heap;
    fake_heap_end = fake_heap_start + __ctru_heap_size;
}

static void adjust(u8 *out, float slider, float value) {
    // special case for mute
    if (value == 0.0f) {
        out[0] = 255;
        out[1] = 0;
        return;
    }
    // calculate the volume offsets to approximate the desired volume
    float diff = slider - value;
    float min = (diff > 0.0f) ? (diff / (1.0f - value)) : 0.0f;
    float max = (diff < 0.0f) ? (-diff / value) : 1.0f;
    out[0] = (u8) (255.0f * min);
    out[1] = (u8) (255.0f * max);
}

static u8 volume;

static void volumeAdjust(s8 delta) {
    // disable volume slider
    u8 regTransfer[2] = { 0xff, 0x00 };
    MCUHWC_WriteRegister(0x58, regTransfer, 2);
    // get volume offsets
    MCUHWC_ReadRegister(0x58, regTransfer, 2);
    // get raw volume
    u8 volumeSlider;
    MCUHWC_ReadRegister(0x27, &volumeSlider, 1);
    // adjust
    s32 newVolume = volume + delta;
    if (newVolume > 63) {
        volume = 63;
    } else if (newVolume < 0) {
        volume = 0;
    } else {
        volume = newVolume;
    }
    // and update
    adjust(regTransfer, volumeSlider / 255.0f, volume / 63.0f);
    MCUHWC_WriteRegister(0x58, regTransfer, 2);
}

int main(void) {
    hidInit();
    mcuHwcInit();
    MCUHWC_GetSoundSliderLevel(&volume);

    for (;;) {
        hidScanInput();
        u32 held = hidKeysHeld();

        if (held & KEY_SELECT) {
            if (held & KEY_DLEFT) {
                // volume down
                volumeAdjust(-1);
            } else if (held & KEY_DRIGHT) {
                // volume up
                volumeAdjust(+1);
            }
        }

        svcSleepThread(20000000LL);
    }

    mcuHwcExit();
    hidExit();

    return 0;
}
