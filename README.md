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

HDMI Drivers for the  RTD2660H for Linux do not support brightness control or backlight. Only local brightness adjustment is possible using built-in buttons on the display. I believe that this is because firmware inside RTD2660H does not implement the DDC/CI (Display Data Channel/Command Interface). Probabaly, for cutting expenses. I checked it with the ddcutil (https://www.ddcutil.com/) and was not able to control brightness (returned an I2C communication error) while I was able to control the brightness of a big PC monitor.

# The solution

It is as easy as:
* Disconnect backlight driver EN (enable) signal from the RTD2660H.
* Use a microcontroller to control this EN pin:
  - Turn ON (Pull EN pin high): when a touch is detected. By reading INT (interrupt) line (active low) from the integrated touch controller. 
  - Turn OFF(Pull EN pin low): Automatic shutdown using a timer with a predefined timeout of 60s when no touch event is received. Every touch event restarts the countdown.

I used a PIC12F509 because I had several laying around.

# Parts List

1 x PIC12F509
1 x Programer
1 x Soldering Iron
4 x wires
Some solder

# The rework





