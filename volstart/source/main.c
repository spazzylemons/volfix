/**
 * volfix - background process for controlling volume
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

#define VOLFIX_TID 0x000401300E621002ULL

int main(void) {
    nsInit();

    NS_TerminateProcessTID(VOLFIX_TID, 0);

    hidScanInput();

    if((hidKeysHeld() & KEY_X) == 0) {
        u32 pid;
        NS_LaunchTitle(VOLFIX_TID, 0, &pid);
    }

    nsExit();

    return 0;
}
