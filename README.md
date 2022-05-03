# async-love

An open DIY alternative to the LoveBox.
Send cute messages to a simple box, without distracting anyone with notifications.

## How it works
- Connect the device to a wifi network
- It fetches a message from a gist
- The translucid heart on the box is lit in a breathing fashion by a red led.
- Open the box and read the message! The LED will turn off.

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

## Contribution
The code is developed in C++ using the Arduino framework with PlatformIO on VSCode. Feel free to improve the code and add features!
Possible new features list:
- Images
- Multiple LEDs for more colors or RGB LED
- A build guide

## Acknowledgement
Thanks to [@julisa99](https://github.com/julisa99) for the [Lovebox](https://github.com/julisa99/Lovebox) project she made. I was greatly inspired by this project.
