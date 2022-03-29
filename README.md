# DisplayPort OSD Framebuffer

This takes Betaflight MSP DisplayPort (so-called "canvas" although this is a misnomer as there is another Betaflight "canvas" mode for Pixel OSDs) messages through TCP and, using a font provided at `bold.png`, renders them to a framebuffer.

Currently only an SMFL framebuffer is available, soon I intend to add DJI Goggles support.