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

int main(void) {
    nsInit();

    NS_TerminateProcessTID(0x000401300E621002ULL, 1000000000);

    hidScanInput();

    if(((hidKeysHeld() & (KEY_X | KEY_B))) == 0) {
        u32 pid;
        NS_LaunchTitle(0x000401300E621002ULL, 0, &pid);
    }

    nsExit();

    return 0;
}
