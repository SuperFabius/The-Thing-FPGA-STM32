

"The Thing": Cyclone II FPGA + Arduino STM32F103C8T6 board, Multicomp compatible.

In this folder there are the Quartus II projects examples for the Cyclone II FPGA. 
They are generally paired with a given Arduino Sketch (.ino file) for the STM32 (read the comments inside the project main source file).


### Table of contents:
* [Blink led example (H160119_Blink.zip)](https://github.com/SuperFabius/The-Thing-FPGA-STM32/blob/master/QuartusII%20Project/H160119_Blinks.zip):
Blink the LED1 led on the board using the "Schematic editor" of Quartus II. No HDL language is required to understand it. No sketch is needed on the STM32 side.
* [Multifunctional interface example (H170119_Multifun.zip)](https://github.com/SuperFabius/The-Thing-FPGA-STM32/blob/master/QuartusII%20Project/H170119_Multifun.zip):
The FPGA acts as a multifuntional custom interface to drive the 7-segment display and the 3 led LED1-3, and to check the status of the USR4-7 keys. It is used the "Schematic editor" of Quartus II. No HDL language is required to understand it. You must upload the sketch [S030319_MultiFun.ino](https://github.com/SuperFabius/The-Thing-FPGA-STM32/blob/master/STM32%20Sketch/S030319_MultiFun.ino) on the STM32 side. The BUT and USR1-3 keys and the PB1 led are managed by the STM32.
