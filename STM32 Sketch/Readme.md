

"The Thing": Cyclone II FPGA + Arduino STM32F103C8T6 board, Multicomp compatible.

In this folder there are the "sketch" examples (.ino files) for the STM32 Arduino. They are generally paired with a given Quartus II project example or a Quartus II Multicomp. 

See in the [QuartusII Project](https://github.com/SuperFabius/The-Thing-FPGA-STM32/tree/master/QuartusII%20Project) or [QuartusII Multicomp](https://github.com/SuperFabius/The-Thing-FPGA-STM32/tree/master/QuartusII%20Multicomp) directory to know which Quartus II project they belong to, or read the comments inside the sketch source.

NOTE: To avoid conflicts with the FPGA on the common pins when any STM32 GPIO must be used, it is recommended to load the "neutral" [STM32_PB1_Blink.ino](https://github.com/SuperFabius/The-Thing-FPGA-STM32/blob/master/STM32%20Sketch/STM32_PB1_Blink.ino) sketch on the STM32.
