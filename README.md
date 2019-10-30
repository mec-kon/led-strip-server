# led-strip-server
### This is a simple server program for a Raspberry Pi that hosts a web page to select different colors on it.
### These colors are then displayed on an RGB led strip.
### In addition, the server can receive commands over MQTT to control the led strip from Openhab.

![](demo/led_strip_website.png)

Demo
--------

Try out a demo <a href="https://mec-kon.github.io/led-strip-website/src/" target="_blank">here</a>

Modes
--------

Three different modes are currently available.
* The one color mode allows you to select a simple color.
* The fade mode can be used to smoothly transition inbetween several selected colors.
* The changing colors mode switches between all selected colors.

## Download ##
Download the server ```git clone https://github.com/mec-kon/led-strip-server.git```
Then navigate into the server folder with ```cd led-strip-server```.
Initialize the submodules with ```git submodule update --init```

## Config ##
To use the server, you must change the ip address of the server.
You can do this by typing ```nano static/src/deviceConfig.json```.

## Installation: ## 
The easiest way to build the program is with CMake.  

First you need to install all required dependencies.
You can do this with ```sudo apt-get install cmake wiringpi build-essential```.

You will also need to install libmosquittopp if you want to use mqtt in this project.
You can do this with ```sudo apt-get install libmosquittopp-dev```.

Then, all you have to do is create a new folder with ```mkdir build``` in the current project folder, change to this folder with ```cd build``` and create a makefile  
with ```cmake ..``` or ```cmake .. -DUSE_MQTT=OFF``` if you don't want to use mqtt .  
Then you can create the executables by simply typing ```make```  
Now install the server with ```sudo make install```.

### Autostart ###

To start the server automatically when booting, you can use crontab.
But first you have to activate the automatic login.
For this you have to open the settings with ```sudo raspi-config```.

Navigate to "Boot Options" and then to "Desktop/CLI".
Select "Console Autologin" and then "Finish".

Restart the Raspberry Pi.

Next type ```crontab -e```.
In the window that opens, add the line "@reboot /usr/local/bin/led-strip-server".

### Openhab ###

To receive commands from Openhab, the following files must be added or modified in "/etc/openhab2/":
* create "color.items" in "/etc/openhab2/items"
* modify "default.sitemap" in "/etc/openhab2/sitemaps"
* create "color.rules" in "/etc/openhab2/rules"

The mentioned files can be found <a href="https://gist.github.com/mec-kon/e4c0c31d593cc22c0699b9fac8d17851" target="_blank">here</a>

Pull requests
--------

Pull requests are always welcome !