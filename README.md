# async-love

An open DIY alternative to the LoveBox.
Send cute messages to a simple box, without distracting anyone with notifications.

## How it works

- Connect the device to a wifi network
- It fetches a message from a gist
- The translucid heart on the box is lit in a breathing fashion by a red led.
- Open the box and read the message! The LED will turn off.

## Installation

You have two options. One uses github's gists and the other one uses a custom made firebase/react application.

### Option 1

Create a file named credentials.h in the include/ folder.

Add these lines:
```cpp
const char *mySSID = "<SSID (Wifi name)>";
const char *myPassword = "<Wifi Password>";

// url to gist: /yourUsername/generatedHashValue/raw/yourFilename
const char *myGist = "<GIST URL>";
```
Then, go write something in the gist and the box should get display the message.

### Option 2

Deploy the lovebox app that I made, [available here](https://github.com/hainsdominic/lovebox-app/). The instructions are in the README.

Use the lovebox-app branch:

`git checkout lovebox-app`

Create a file named credentials.h in the include/ folder.

Add these lines:
```cpp
const char *mySSID = "<SSID (Wifi name)>";
const char *myPassword = "<Wifi Password>";

const char *boxName = "<NAME OF YOUR BOX>";
```

Thats it, you can now use the user-friendly front-end that you deployed.

## Wiring

![wiring diagram](https://github.com/hainsdominic/async-love/blob/master/docs/images/wiring.png)

## Parts list

I suggest buying all of them on aliexpress
- WeMos D1 Mini
- Ligh sensor (photoresistor)
- Red LED (or the color you want)
- OLED display (SSD1306 128x64)
- 10kΩ resistor
- 220Ω resistor

To build it you can use whatever you want, however I suggest using a perfboard.

## Issues / Limitations

I suspect there is some kind of caching on the gists, so the message only updates in around 3 minutes after the intial message.

## Contribution

The code is developed in C++ using the Arduino framework with PlatformIO on VSCode. Feel free to improve the code and add features!
Possible new features list:
- Images
- Multiple LEDs for more colors or RGB LED
- A build guide

## Acknowledgement
Thanks to [@julisa99](https://github.com/julisa99) for the [Lovebox](https://github.com/julisa99/Lovebox) project she made. I was greatly inspired by this project.
