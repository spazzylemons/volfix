# volfix - background process for controlling volume and brightness
# Copyright (C) 2022 spazzylemons
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

TOPDIR ?= $(CURDIR)

APP_TITLE        := volfix
APP_DESCRIPTION  := Volume Controls
APP_AUTHOR       := spazzylemons
APP_PRODUCT_CODE := CTR-N-SLVF
APP_UNIQUE_ID    := 0xE6210

include $(TOPDIR)/../common.mk

ifeq ($(BUILD),$(notdir $(CURDIR)))

$(OUTPUT).cia: $(OUTPUT).elf
	@makerom -f cia -o $(OUTPUT).cia -rsf $(TOPDIR)/volfix.rsf -target t -exefslogo -elf $(OUTPUT).elf -DAPP_TITLE="$(APP_TITLE)" -DAPP_PRODUCT_CODE="$(APP_PRODUCT_CODE)" -DAPP_UNIQUE_ID="$(APP_UNIQUE_ID)"

endif
