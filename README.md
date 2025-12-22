# PONG

This is an study/experimental game that uses linux's legacy frame buffer mode ```/dev/fb0``` to for rendering the game and the rendering is CPU based. 
##setup
It does not have a feature to automatically detect screen size so please do modify it in ```/include/config.h``` to fit your screen.
Use ```sudo evtest``` to search for your keyboard and modify ```/src/input_event.c``` accordingly to point to your keyboard's file.
Run the ```./build.sh``` script to compile and run it with ```./sun.sh``` in a linux tty. (Note: the executable does require root privileges to run)
