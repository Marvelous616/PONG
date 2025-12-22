# PONG

This is a study/experimental game that uses Linux's legacy frame buffer mode /dev/fb0 for rendering. The rendering engine is entirely CPU-based.
Setup
## 1. Screen Configuration

This project does not currently support automatic screen size detection. Please modify the resolution constants in your header file to fit your display:

    File: include/config.h

## 2. Input Configuration

Use evtest to find the device event path for your keyboard:
Bash

sudo evtest

Update the path in src/input_event.c to point to the correct device (e.g., /dev/input/eventX).
## 3. Build and Run

The game must be run in a Linux TTY (not inside a terminal emulator like Alacritty or Kitty) and requires root privileges to access the framebuffer and input devices.
Bash

# Give execution permissions
chmod +x build.sh sun.sh

# Compile
./build.sh

# Run (requires root)
sudo ./sun.sh
