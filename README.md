# led-strip-server
### This is a simple server program for a Raspberry Pi that hosts a web page to select different colors on it.
### These colors are then displayed on an RGB led strip.

## Installation: ## 
The easiest way to install the program is with CMake.  

First you need to install all required dependencies.
You can do this with ```sudo apt-get install cmake wiringpi build-essential```.

Then, all you have to do is create a new folder with ```mkdir build``` in the current project folder, change to this folder with ```cd build``` and create a makefile  
with ```cmake .. -DCMAKE_BUILD_TYPE=Debug``` .  
Then you can create the executables by simply typing ```make```  
Now you can start the server with ```./http_server```.