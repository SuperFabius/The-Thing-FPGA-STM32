More info here: https://hackaday.io/project/163683-the-thing-fpga-stm32

Two dev boards into one: a STM32 based Arduino ("Maple Mini" compatible) and a Cyclone II FPGA dev. board to start playing with VHDL/Verilog. It is also "Multicomp" compatible ("Multicomp" is a modular VHDL design to "run" some famous retro 8 bit CPUs made by Grant Searle) giving the option to "run" easily a VHDL SOC with a Z80/6809/6502 CPU and I/O, including HD (on SD) and a color VDU.

# Table of contents
* [QuartusII Project](https://github.com/SuperFabius/The-Thing-FPGA-STM32/tree/master/QuartusII%20Project):
In this folder there are the Quartus II projects examples for the Cyclone II FPGA. They are generally paired with a given Arduino Sketch (.ino file) for the STM32 (read the comments inside the project main source file).

* [STM32 Sketch](https://github.com/SuperFabius/The-Thing-FPGA-STM32/tree/master/STM32%20Sketch):
In this folder there are the "sketch" examples (.ino files) for the STM32 Arduino. They are generally paired with a given Quartus II project example (read the comments inside the sketch source).





<b>* * * UNDER CONTRUCTION!!! * * *</b>
