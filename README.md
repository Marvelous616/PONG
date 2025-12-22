# PONG

This is a study/experimental game that uses Linux's legacy frame buffer mode /dev/fb0 for rendering. The rendering engine is entirely CPU-based.
Setup

## 1. Screen Configuration

This project does not currently support automatic screen size detection. Please modify the resolution constants in your header file to fit your display:

File: include/config.h
## 2. Input Configuration

Use evtest to find the device event path for your keyboard:
Bash

```
sudo evtest
```
Update the path in src/input_event.c to point to the correct device (e.g., /dev/input/eventX).

## 3. Build and Run

The game must be run in a Linux TTY (not inside a terminal emulator like Alacritty or Kitty) and requires root privileges to access the framebuffer and input devices.
Bash

# Give execution permissions

```
chmod +x build.sh sun.sh
```
# Compile

```
./build.sh
```
# Run (requires root)

sudo ./sun.sh

## project structure
```
.
├── 312x598_hand_dithered_1_bit.data
├── 468x897_hand_dithered_1_bit.data
├── 468x897_hand_dithered_1_bit.data.pal
├── 624x1196_hand_dithered_1_bit.data.pal
├── 624x1196_hand_dithered.data
├── build
│   └── main
├── build.sh
├── compile_flags.txt
├── game_log.csv
├── include
│   ├── base_masks.h
│   ├── config.h
│   ├── entity.h
│   ├── gameloop.h
│   ├── inp_event.h
│   ├── numbers.h
│   ├── num.h
│   ├── pixel.h
│   ├── point.h
│   ├── render.h
│   ├── sprite.h
│   └── text_renderer.h
├── LICENSE
├── README.md
├── run.sh
└── src
├── entity.c
├── inp_event.c
├── main.c
├── num.c
├── pixel.c
├── point.c
├── render.c
└── sprite.c
```