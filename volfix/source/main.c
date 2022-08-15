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

int main(void) {
    hidInit();

    for (;;) {
        hidScanInput();
        u16 keys = hidKeysDown();

        if (keys & KEY_SELECT) {
            if (keys & KEY_DLEFT) {
                // volume down
                break;
            } else if (keys & KEY_DRIGHT) {
                // volume up
                break;
            }
        }

        svcSleepThread(20000000LL);
    }

    hidExit();

    return 0;
}
