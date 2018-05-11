# simple-http-server
### This is a simple, single threaded http server for handling http-post and http-get requests running on Linux.
The server makes all files in the "static" folder available in the case of an HTTP GET request.    
It also stores all data that it receives with an HTTP POST in the respective file.  

#### No additional packages need to be installed to use the server

## Installation: ## 
The easiest way to install the program is with CMake.  
All you have to do is create a new folder with ```mkdir build``` in the current project folder,  
change to this folder with ```cd build``` and create a makefile  
with ```cmake .. -DCMAKE_BUILD_TYPE=Debug``` .  
Then you can create the executables by simply typing ```make```  
Now you can start the server with ```./http_server```.