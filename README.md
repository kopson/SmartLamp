# SmartLamp

Arduino Smart Lamp

#Arduino 1.6.6 IDE download

https://www.arduino.cc/en/Main/Software

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

#Running Arduino

	$ arduino

#Arduino workspace

~/Arduino
	+-libraries 
	+-sketches

#Troubleshooting

Arduino IDE shows:
	avrdude: ser_open(): can't open device "/dev/ttyACM0": Device or resource busy
	ioctl("TIOCMGET"): Inappropriate ioctl for device

Solution:
	$ enableusb

#Fritzing

http://fritzing.org/download/

#Resources

https://www.arduino.cc/en/Guide/HomePage
http://fritzing.org/learning/
http://akademia.nettigo.pl/playlist/arduino_dla_poczatkujacych.html
http://forbot.pl/blog/artykuly/programowanie/kurs-arduino-w-robotyce-1-wstep-id936
http://www.instructables.com/tag/type-id/category-technology/channel-arduino/
https://www.arduino.cc/en/Tutorial/HomePage
