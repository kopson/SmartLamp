# SmartLamp
Arduino Smart Lamp

#Arduino configuration for Ubuntu 12.04
Add followiing lines to ~/.bashrc:

export PATH=$PATH:~/Downloads/arduino-1.6.6
JAVA_HOME=/usr/local/java/jdk1.7.0_75
export PATH=$PATH:$HOME/bin:$JAVA_HOME/bin

enableUSB()
{
	USER=`whoami`
	sudo usermod -a -G dialout $USER 
	sudo chmod a+rw /dev/ttyACM0 || sudo chmod a+rw /dev/ttyACM1
}

alias enableusb='enableUSB'

#Troubleshooting

Arduino IDE shows:
	avrdude: ser_open(): can't open device "/dev/ttyACM0": Device or resource busy
	ioctl("TIOCMGET"): Inappropriate ioctl for device

Solution:
	$ enableusb

