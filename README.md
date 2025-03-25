# Introduction
This projects creates a standalone hardware solution for controlling backlight of cheap TFT 7" display with only a cheap low end PIC microcontroller.

# The display

I based my research and development based on a cheap 7" 1024x600 TFT HDMI display from Aliexpress (less than 35€).
![image](https://github.com/user-attachments/assets/bd290c25-45b3-4e62-ab8f-7d5c8d6e37c4)

If you take a look at the EDID information, read from the HDMI I2C bus, this is the report:

![display_info](https://github.com/user-attachments/assets/538d24ad-ca7d-4c43-b161-d804fbf4eda4)

So, the model can be recognized as JRP7007. If you do a quick search on google, you will find some results.

# The issue

There are several variants of this display scattered around, but mainly all of them use an RTD2660H LCD controller, a touchscreen controller embedded into the display shell and a Backlight LED Driver based on a DCDC converter.

HDMI Drivers for the  RTD2660H for Linux do not support brightness control or backlight. Only local brightness adjustment is possible using built-in buttons on the display.
It uses only an 8bit PIC microcontroller to detect 
