# DisplayPort OSD Framebuffer

This takes Betaflight MSP DisplayPort (so-called "canvas" although this is a misnomer as there is another Betaflight "canvas" mode for Pixel OSDs) messages through UDP and renders them to a framebuffer overlaid under the DJI `dji_glasses` menu system.

A custom `font.bin` package may be placed on the root of the goggles SD card, at which point it will override the font in `/blackbox/font.bin`.

SFML (PC/Mac development) and DJI Goggles viewports are available, as well as a *mux* for the Air Unit / Vista, which creates a *pty* and provides filtered MSP access, and reroutes DisplayPort messages to UDP.

# Setup and Installation

### Easy Installation

* Install WTFOS from https://testing.fpv.wtf . WTFOS must be installed on both the goggles and each AU/Vista.
* Install the msp-osd package on each device using WTFOS.
* Reboot.

### Flight Controller Setup

* Ensure that the correct UART is set to use MSP
* Enable MSP DisplayPort

On *Betaflight*, this is done using the following commands:

```
set osd_displayport_device = MSP
set displayport_msp_serial = <ConfiguratorUART - 1>
set vcd_video_system = PAL
```

Eg.: If the Betaflight Configurator says your DJI VTx is attached to UART2, the value for **<ConfiguratorUART - 1>** is **1** - so you would use ```set displayport_msp_serial = 1```.

For betaflight - ensure you set the Video Format to PAL or Auto in the OSD tab - otherwise you don't get access to the whole OSD area. Note that currently BF Configurator hides these options once you switch to MSP for OSD; the last command above should have done this for you.```

On *iNav*, this is done by selecting "HDZero VTx" as the Peripheral. Also select "HD" in the OSD tab. If the iNav OSD appears garbled at first, try entering the iNav menus using the RC sticks, and then exiting the menus. This will force iNav to switch into HD mode a second time. 

On *Ardupilot*, this is done by setting:

```
SERIALx_PROTOCOL = 42
OSD_TYPE = 5
```

and optionally

`MSP_OPTIONS = 4` to allow the use of a Betaflight font.

### Choose a Font

* Download the latest fonts package from https://github.com/bri3d/mcm2img/releases/download/latest/mcm2img-fonts.tar.gz .
* Rename the files for your desired font to `font` - so you should have four files: `font.bin, font_2.bin, font_hd.bin, font_hd_2.bin` .
* Place these four files on the root of your Goggles SD card.
* Reboot.

### Generate your own Font (advanced)

* Download [mcm2img](https://github.com/bri3d/mcm2img) and set up a working Python environment to run it.

* Locate the font you'd like to install - it will be a `.mcm` file, in the source code repository or configurator for your Flight Controller. 

* For Betaflight: https://github.com/betaflight/betaflight-configurator/tree/master/resources/osd/2
* For iNav: https://github.com/iNavFlight/inav-configurator/blob/master/resources/osd/
* For Ardupilot: https://github.com/ArduPilot/ardupilot/tree/master/libraries/AP_OSD/fonts

* Run `python3 mcm2img.py mcmfile.mcm font RGBA 255 255 255`

* Place the 4 files this makes (font.bin, font_2.bin, font_hd.bin, font_hd_2.bin) on the root of the SD card in the goggles.

* Reboot

You can customize the font color by changing the 255 255 255 RGB values.

## FAQ / Suggestions

### How do I create a new font (for iNav, Ardupilot, etc.)?

Use [mcm2img](https://github.com/bri3d/mcm2img).

```
python3 mcm2img.py mcmfile.mcm font.bin RGBA
```

### Why is everything so big / can I make the text smaller (betaflight)?

Betaflight does not support HD OSD. So you have the same 30 * 16 grid as analog uses. The field of view in the DJI goggles makes this look big. 

You can swap to a different font to make the characters smaller, but the grid spacing is the same.

# Compiling (development and debugging)

To build for DJI, install the [Android NDK](https://developer.android.com/ndk/downloads) and add the NDK toolchain to your PATH, then use `ndk-build` to build the targets. 

To build for UNIXes, install CSFML and run:

```
make -f Makefile.unix
```

Provided targets and tools are:

* `msp_displayport_mux` - takes MSP DisplayPort messages, bundles each frame (all DisplayPort messages between Draw commands) into a single UDP Datagram, and then blasts it over UDP. Also creates a PTY which passes through all _other_ MSP messages, for `dji_hdvt_uav` to connect to.
* `libdisplayport_osd_shim.so` - Patches the `dji_glasses` process to listen for these MSP DisplayPort messages over UDP, and blits them to a DJI framebuffer screen using the DJI framebuffer HAL `libduml_hal` access library, and a converted Betaflight font font stored in `font.bin`.
* `osd_sfml` - The same thing as `osd_dji`, but for a desktop PC using SFML and `bold.png`.

Additional debugging can be enabled using `-DDEBUG` as a CFLAG.

## Custom Build Installation (Goggles)

`setprop dji.dji_glasses_service 0`
`ndk-build`
`adb push libs/armeabi-v7a/libdisplayport_osd_shim.so /tmp`
`LD_PRELOAD=/tmp/libdisplayport_osd_shim.so dji_glasses -g`

### Air Unit / Air Unit Lite (Vista)

```
adb push msp_displayport_mux /blackbox
setprop dji.hdvt_uav_service 0
mv /dev/ttyS1 /dev/ttyS1_moved
nohup /blackbox/msp_displayport_mux 192.168.41.2 /dev/ttyS1_moved /dev/ttyS1 &
setprop dji.hdvt_uav_service 1
```
This tells the displayport mux to send data from /dev/ttyS1_moved to 192.168.41.2 (goggles) and to create a fake serial port at /dev/ttyS1 with the displayport messages filtered out.

Optionally, you can add `-f`, like `nohup /blackbox/msp_displayport_mux -f 192.168.41.2 /dev/ttyS1_moved /dev/ttyS1` to put the serial port in a faster 230400 baud mode, and set the MSP serial port in your flight controller to 230400 to try to improve the framerate.

You can also omit `setprop dji.hdvt_uav_service 1` , which will improve your OSD framerate at the expense of disabling all Air Unit / Vista side coordination functionality (AU recording, channel changes, some RC features, etc.).

Enjoy.

## Additional Reading / Learning

https://github.com/fpv-wtf/margerine/wiki

## Shoutouts / Thank You

* http://github.com/fpv-wtf team, for making this all possible and very helpful random bits of advice
