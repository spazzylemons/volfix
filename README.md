# volfix

volfix is a background process for controlling volume on your 3DS in case your
volume slider is broken.

## Building

Run `make`. (TODO: list dependencies)

## Installation

Install both volfix.cia and volstart.cia via your CIA manager.

NOTE: volstart can be uninstalled from the System Settings, but volfix cannot.
You will need to use your CIA manager (e.g. FBI) to uninstall volfix. Look for
title ID **000401300E621002** and product code **CTR-N-SLVF**.

## Usage

To start volfix, run volstart from the Home Menu. To close volfix,
run volstart while holding X. While volfix is running, holding left or right
while holding select will decrease or increase the volume respectively.

## Credits

Built on the process-spawning capabilities of
[HorizonM](https://github.com/Bas25/HorizonMod).
