# DisplayPort OSD Framebuffer

This takes Betaflight MSP DisplayPort (so-called "canvas" although this is a misnomer as there is another Betaflight "canvas" mode for Pixel OSDs) messages through UDP and, using a font provided at `font.bin`, renders them to a framebuffer.

SFML and DJI viewports available, as well as a mux which creates a pty and provides filtered MSP access, and reroutes DisplayPort messages to UDP.
