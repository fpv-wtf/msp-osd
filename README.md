# DisplayPort OSD Framebuffer

This takes Betaflight MSP DisplayPort (so-called "canvas" although this is a misnomer as there is another Betaflight "canvas" mode for Pixel OSDs) messages through UDP and, using a font provided at `/blackbox/font.bin`, renders them to a framebuffer.

A custom `font.bin` may be placed on the root of the goggles SD card, at which point it will override the font in `/blackbox/font.bin`.

SFML and DJI viewports are available, as well as a *mux* which creates a *pty* and provides filtered MSP access, and reroutes DisplayPort messages to UDP.

To build for DJI, install the [Android NDK](https://developer.android.com/ndk/downloads) and add the NDK toolchain to your PATH, then use `make -f Makefile.dji` to build the targets. Set `DJI_LIB_PATH` to point to the content of `/system/lib` pulled from your DJI hardware or a firmware dump, so that the linker can find `libduml_hal.so`.

> On Windows, note that `make` and the actual `armv7a-linux-*` compiler binaries may be installed in different directories.

To build for UNIXes, install CSFML and run:

```
make -f Makefile.unix
```

Provided targets and tools are:

* `msp_displayport_mux` - takes MSP DisplayPort messages, bundles each frame (all DisplayPort messages between Draw commands) into a single UDP Datagram, and then blasts it over UDP. Also creates a PTY which passes through all _other_ MSP messages, for `dji_hdvt_uav` to connect to.
* `osd_dji` - Listens for these MSP DisplayPort messages over UDP and blits them to a DJI framebuffer screen using the DJI framebuffer HAL `libduml_hal` access library, and a converted Betaflight font font stored in `font.bin`.
* `osd_sfml` - The same thing as `osd_dji`, but for a desktop PC using SFML and `bold.png`.

## Installation

Build the needed targets or install using WTFOS:

```
make -f Makefile.dji msp_displayport_mux
make -f Makefile.dji osd_dji
```

### Flight Controller

* Ensure that the correct UART is set to use MSP
* Enable MSP DisplayPort

On *Betaflight*, this is done using the following commands:

```
set osd_displayport_device = MSP
set displayport_msp_serial = <ConfiguratorUART - 1>
```

Eg.: If the Configurator says UART2, the value for **<ConfiguratorUART - 1>** is **1**.

On *iNav*, this is done by selecting "HDZero VTx" as the Peripheral.

On *Ardupilot*, this is done by setting:

```
SERIALx_PROTOCOL = 42
OSD_TYPE = 5
```

and optionally

`MSP_OPTIONS = 4` to allow the use of a Betaflight font.

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

### Goggles

```
adb push osd_dji /blackbox
adb push font.bin /blackbox
cd /blackbox
nohup ./osd_dji &
```

Hold the BACK button for 5 seconds. You should see the DJI UI disappear and be replaced by the MSP OSD (or at least a `WAITING` message at the bottom of your screen).

To restart the DJI goggles, hold the BACK button for 5 seconds again.

Rebooting will kill the process and return the goggles to "normal."

Enjoy.

## FAQ / Suggestions

### Why can't we keep dji_glasses (the Goggles UI) running while we render the OSD?

Access to the DJI video driver is exclusive. We would have to build some kind of userspace frame-buffer sharing system to get this to work. The `dji_glasses` system uses DirectFB which provides this functionality on paper, but the DJI backend driver as well as the overall stack are not configured to use it properly.

### I can't change channels / see my bitrate / record video / etc. while the overlay is running?

See above - `dji_glasses` has three primary purposes:
1. turning user input into commands for the radio/CP layer
2. displaying the UI
3. for whatever reason, recording video

Without `dji_glasses` running we will have to replicate these functionalities.

### How do I create a new font (for iNav, Ardupilot, etc.)?

Use [mcm2img](https://github.com/bri3d/mcm2img).

```
python3 mcm2img.py mcmfile.mcm font.bin RGBA
```

## Additional Reading / Learning

https://github.com/fpv-wtf/margerine/wiki

## Shoutouts / Thank You

* http://github.com/fpv-wtf team, for making this all possible and very helpful random bits of advice
