# SmartLamp using Maple Mini  

Arduino Smart Lamp project

### Environment setup for Ubuntu 12.04

* Download [Arduino 1.6.5 IDE](https://www.arduino.cc/en/Main/Software). Newer versions are not supported!
* Run the IDE, and on the Tools menu, select the Boards manager, and install the Arduino Due from the list of available boards.
* Download zip file containing the STM32 files from [here](https://github.com/rogerclarkmelbourne/Arduino_STM32/archive/master.zip)
* Unzip to create the **Arduino_STM32** folder. Copy Arduino_STM32 folder to: **~/Arduino/hardware/Arduino_STM32**. If the hardware folder does not exist, please create one.
* Run the udev rulues installation script in **tools/linux/install.sh**

### Arduino IDE

### Troubleshooting

Problem: 

Failed to open serial device.
~/Arduino/hardware/Arduino_STM32/tools/linux/dfu-util/dfu-util: cannot execute binary file

Solution:

From the **~/Arduino/hardware/Arduino_STM32/tools/src/dfu-util** dir:

	sudo apt-get build-dep dfu-util
	./autogen.sh
	./configure
	make

now copy **dfu-prefix**, **dfu-suffix** and **dfu-util** from **~/Arduino/hardware/Arduino_STM32/tools/src/dfu-util/src/** to **~/Arduino/hardware/Arduino_STM32/tools/linux/dfu-util/** and overwrite the old ones.

### Links

1. [Arduino home page](https://www.arduino.cc/en/Guide/HomePage)
2. [Maple port to Arduino IDE](https://github.com/rogerclarkmelbourne/Arduino_STM32)