"The Thing": Cyclone II FPGA + Arduino STM32F103C8T6 board, Multicomp compatible.

In this folder there are the Quartus II Multicomp projects for the Cyclone II FPGA. They could be paired with a given Arduino Sketch (.ino file) for the STM32 and with a given SD image for HD emulation.

These Multicomp have been already adapted to run inside the "The Thing" board "out of the box" ("The Thing" board HW design requires some adaptations from the original Multicomp design reference).

To write the SD image into a SD card, unzip the image file and simply copy it to your SD card using the [Win32 Disk Imager](https://sourceforge.net/projects/win32diskimager/) 

### Table of Quartus II Multicomp projects:
* [6809 2KB(Int RAM) VGA PS/2](https://github.com/SuperFabius/The-Thing-FPGA-STM32/blob/master/QuartusII%20Multicomp/M6809_VGA_PS2_IntRAM(2K)_TheThing.zip):
Multicomp con CPU 6809, 2KB RAM, VGA, PS/2, ROM Basic.  It uses only FPGA internal RAM (external 512KB SRAM and the SD card are not used). This can be used to test the FPGA, the VGA output and the PS/2 keyboard.
