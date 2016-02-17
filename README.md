# SmartLamp

Arduino Smart Lamp project

### Environment setup for Ubuntu 12.04

* Download [Arduino 1.6.7 IDE](https://www.arduino.cc/en/Main/Software)
* Download [Fritzing](http://fritzing.org/download/)
* Add followiing lines to **~/.bashrc**:

```bash
ARDUINO_HOME=~/Downloads/arduino-1.6.7
ARDUINO_WORKSPACE=~/Arduino
FRITZING_HOME=~/Downloads/fritzing-0.9.2b
JAVA_HOME=/usr/local/java/jdk1.7.0_75
REPO=~/SmartLamp

export PATH=$PATH:/home/piotrek/Downloads/android-sdk-linux/platform-tools:$ARDUINO_HOME:$FRITZING_HOME
export PATH=$PATH:$HOME/bin:$JAVA_HOME/bin

enableUSB()
{
	USER=`whoami`
	sudo usermod -a -G dialout $USER 
	sudo chmod a+rw /dev/ttyACM0 || sudo chmod a+rw /dev/ttyACM1
}

alias enableusb='enableUSB'
alias arduino='$ARDUINO_HOME/arduino'
alias fritzing='$FRITZING_HOME/Fritzing'
```

### Arduino IDE

* Running Arduino:

`$ arduino`

* Running Fritzing:

`$ fritzing`

* Arduino workspace

```
~/Arduino
	+-libraries
	+-sketches
```

### Sublime-Stino alternative IDE

* Download [Sublime-Text 3](https://www.sublimetext.com/3)
* Install [Stino](https://github.com/Robot-Will/Stino)
* Select Arduino Application Folder: **$ARDUINO_HOME**
* Change Sketchbook Folder to **$REPO** folder
* Make links from modules libraries dir to **$ARDUINO_WORKSPACE/libraries**
* Restart sublime

### Troubleshooting

* Arduino IDE shows:

```
avrdude: ser_open(): can't open device "/dev/ttyACM0": 
Device or resource busy ioctl("TIOCMGET"): Inappropriate ioctl for device
```

**Solution:**

`$ enableusb`

#### Stable code releases

| Lamp ID            | Arduino ID | Branch    | Version |
| :----------------: | :--------: | :-------: | :-----: |
| Luna               | UNO        | Lamp-Luna | 1.0.0   |

### Links

1. [Arduino home page](https://www.arduino.cc/en/Guide/HomePage)
2. [Arduino tutorials](https://www.arduino.cc/en/Tutorial/HomePage)
3. [Fritzing home page](http://fritzing.org/learning/)
4. [Arduino tutorial - nettigo](http://akademia.nettigo.pl/playlist/arduino_dla_poczatkujacych.html)
5. [Arduino tutorial - forbot](http://forbot.pl/blog/artykuly/programowanie/kurs-arduino-w-robotyce-1-wstep-id936)
6. [Arduino projects](http://www.instructables.com/tag/type-id/category-technology/channel-arduino/)
