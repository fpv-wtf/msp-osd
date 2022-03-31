# DisplayPort OSD Framebuffer

This takes Betaflight MSP DisplayPort (so-called "canvas" although this is a misnomer as there is another Betaflight "canvas" mode for Pixel OSDs) messages through UDP and, using a font provided at `font.bin`, renders them to a framebuffer.

SFML and DJI viewports available, as well as a mux which creates a pty and provides filtered MSP access, and reroutes DisplayPort messages to UDP.

To build for DJI, install the Android NDK and add it to your path, then use make -f Makefile.dji .

To build for UNIXes, install CSFML and make -f Makefile.unix .

Provided targets and tools are:

* `msp_displayport_mux` - takes MSP DisplayPort messages, bundles each frame (all DisplayPort messages between Draw commands) into a single UDP Datagram, and then blasts it over UDP. Also creates a PTY which passes through all _other_ MSP messages, for `dji_hdvt_uav` to connect to.
* `osd_dji` - Listens for these MSP DisplayPort messages over UDP and blits them to a DJI framebuffer screen using the DJI framebuffer HAL `libduml_hal` access library, and a converted Betaflight font font stored in `font.bin` .
* `osd_sfml` - The same thing as `osd_dji`, but for a desktop PC using SFML and `bold.png` .

Currently works very well on desktop, but the UDP layer from the DJI air side to the goggles is too slow and drops too many packets to be practically useful yet.
