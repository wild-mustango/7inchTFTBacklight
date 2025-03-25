# Introduction
This projects creates a standalone hardware solution for controlling backlight of cheap TFT 7" display with only a cheap low end PIC microcontroller.

# The display

I based my research and development based on a cheap 7" 1024x600 TFT HDMI display from Aliexpress (less than 35€).
![image](https://github.com/user-attachments/assets/bd290c25-45b3-4e62-ab8f-7d5c8d6e37c4)

If you take a look at the EDID information, read from the HDMI I2C bus, this is the report:

![display_info](https://github.com/user-attachments/assets/538d24ad-ca7d-4c43-b161-d804fbf4eda4)

So, the model can be recognized as JRP7007. If you do a quick search on google, you will find some results.

This is the PCB:

![IMPORTANT_AREAS](https://github.com/user-attachments/assets/97ea48aa-c9a7-42a5-99c9-476fe3aceab8)



# The issue

There are several variants of this display scattered around, but mainly all of them use an RTD2660H LCD controller, a touchscreen controller embedded into the display shell and a Backlight LED Driver based on a DCDC converter.

HDMI Drivers for the  RTD2660H for Linux do not support brightness control or backlight. Only local brightness adjustment is possible using built-in buttons on the display. I believe that this is because firmware inside RTD2660H does not implement the DDC/CI (Display Data Channel/Command Interface). Probabaly, for cutting expenses. I checked it with the ddcutil (https://www.ddcutil.com/) and was not able to control brightness (returned an I2C communication error) while I was able to control the brightness of a big PC monitor.

# The solution

It is as easy as:
* Disconnect backlight driver EN (enable) signal from the RTD2660H.
* Use a microcontroller to control this EN pin:
  - Turn ON (Pull EN pin high): when a touch is detected. By reading INT (interrupt) line (active low) from the integrated touch controller. 
  - Turn OFF(Pull EN pin low): Automatic shutdown using a timer with a predefined timeout of 60s when no touch event is received. Every touch event restarts the countdown.

![BACKLIGHT_DRIVER_EN_SIGNAL](https://github.com/user-attachments/assets/288f8d05-dfe5-409b-8c38-6fba32f52d95)![IMG_20250316_235502_modif](https://github.com/user-attachments/assets/8a7bbbb4-fcbc-4d8b-bb98-d7cfac186495)

I used a PIC12F509 because I had several laying around.

I also did some reverse engineering of the schematic. For better understanding, please check the sch.

# Parts List

* 1 x PIC12F509 (no matter package, I used PIC12F509-I/SN which is a SOIC8)
* 1 x Programer
* HEX file
* 1 x Soldering Iron
* 4 x wires
* Some solder

# The rework instructions

- Load HEX file into the PIC12F509 using your favourite PIC programmer and software. I used a clone of PICkit3 and the Integrated Programming Environment bundled with MPLABX 5.25.
- Remove R29 and D3.
- Rotate R35 so it is connected from D3 anode (EN Pin 4 of U9) to GND.
- Connect Pin 4 (EN) of U4 to Pin 3 (GP4) of PIC1.
- Connect Pin 1 (INT0) of U7 to Pin 6 (GP1) of PIC1.
- Connect C35 (Pin 19-VDD) of U7 to Pin 1 (VDD) of PIC1.
- Connect Pin 8 (VSS) of PIC1 to any GND point.
- Secure everthing with kapton tape

![rework](https://github.com/user-attachments/assets/a441c060-547c-4aea-8c4e-8889b9ae9f32)


![IMG_20250323_142258](https://github.com/user-attachments/assets/5a93541d-3f68-40cb-88d3-bca153ee2fe1)

# Rework detail

![usb_uc_detail](https://github.com/user-attachments/assets/5a47fdfd-bae9-440a-a72e-e18d492e178e)
![backlight_driver_detail](https://github.com/user-attachments/assets/da0e5f0e-8fc2-4ab6-aa78-209c3b80f352)



# The firmware

I used MPLABX 5.10 and its XC8 Compiler to create the code, composed of:

* main.c
* tmr0.c
* tmr0.h

I used interna RC oscillator to avoid use of external components. Also used the internal Timer for delay function.

For more detail check SRC folder.

# Closing

It was a weekend project very amusing I hope you find it useful.

Probably similar displays would only require different rework and the PIC programming is still valid. If I have come across similar boards in the future I will start to post the different reworks needed for each display variant.

Best regards to everyone!

