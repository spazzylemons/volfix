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

APP_TITLE        := volstart
APP_DESCRIPTION  := volfix Launcher
APP_AUTHOR       := spazzylemons
APP_PRODUCT_CODE := CTR-N-SLVS
APP_UNIQUE_ID    := 0xE6211

ICON   := assets/logo.png
BANNER := assets/banner.png

include $(TOPDIR)/../common.mk

ifeq ($(BUILD),$(notdir $(CURDIR)))

$(TOPDIR)/$(BUILD)/banner.bin: $(TOPDIR)/$(BANNER) $(TOPDIR)/assets/banner.wav
	@bannertool makebanner -i $(TOPDIR)/$(BANNER) -a $(TOPDIR)/assets/banner.wav -o $(TOPDIR)/$(BUILD)/banner.bin

$(TOPDIR)/$(BUILD)/image.bin: $(TOPDIR)/$(ICON)
	@bannertool makesmdh -s "$(APP_TITLE)" -l "$(APP_DESCRIPTION)" -p "$(APP_AUTHOR)" -i $(TOPDIR)/$(ICON) -o $(TOPDIR)/$(BUILD)/image.bin

$(OUTPUT).cia: $(OUTPUT).elf $(TOPDIR)/$(BUILD)/banner.bin $(TOPDIR)/$(BUILD)/image.bin
	@makerom -f cia -o $(OUTPUT).cia -rsf $(TOPDIR)/volstart.rsf -target t -exefslogo -elf $(OUTPUT).elf -icon $(TOPDIR)/$(BUILD)/image.bin -banner $(TOPDIR)/$(BUILD)/banner.bin -DAPP_TITLE="$(APP_TITLE)" -DAPP_PRODUCT_CODE="$(APP_PRODUCT_CODE)" -DAPP_UNIQUE_ID="$(APP_UNIQUE_ID)"

endif
