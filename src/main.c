/*
 *	Author: Wild.Mustango
 *	Creation date: March 2025
 *	Modification date: -
 *	Modified by: -
 *  Version: 1.00
 * 
 *  ChangeLog:
 *      - v1.00 - Initial release
 * 
*/

/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC12F1501
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/
// CONFIG1
#pragma config OSC = IntRC    // Oscillator Selection Bits->INTOSC oscillator (4 MHz): I/O function on CLKIN pin
#pragma config WDT = OFF    // Watchdog Timer Enable->WDT enabled
#pragma config MCLRE = OFF   // MCLR Pin Function Select->MCLR/VPP pin function is MCLR
#pragma config CP = OFF    // Flash Program Memory Code Protection->Program memory code protection is disabled


#define _XTAL_FREQ 4000000

// PIN DEFINITION

#define BACKLIGHT_ENABLE_PIN GPIObits.GP4               //ChangeMe: Change if pin is changed - Pin3 (GP4) - PIC12F509
//for TOUCH_INTERRUPT_PIN define check "tmr0.h"         

#include <xc.h>
#include <stdint.h>
#include "tmr0.h"


void SYSTEM_Initialize()
{
    /* I/O Pin Initialize*/
    
    /*
    GPIO and TRISGUPIO register
    */
    TRISGPIO = 0b00000010; // GP1 Input - GP4 Output // ChangeMe: Change if pins are changed
    GPIO = 0x00;     //clear all pins


    
    /*
     * OPTION Register
     * 
     * GPWU = 0 Enable Wake-up on Pin Change bit (GP0, GP1, GP3)
     * GPPU = 0 Enable Weak Pull-ups bit (GP0, GP1, GP3)
     * 
     * Timer0 Initialize
     * 
     * T0CS = 0 Transition on internal instruction cycle clock, FOSC/4 
     * T0SE = 0 N/A when selecting Internal T0CS = 1
     * PSA = 0; // Pre-scaler assigned to the Timer0
     * Pre-scaler 1:4 PS<2:0> 001
     * 
     * Using IntRC Fosc=4MHz, Fcycle=1MHz Tcycle=1us
     * For 1ms TimerTick using prescaler 1:4 --> Tcycle=4us
     * Preloading TMR0 with with a value of 6
     * will overflow after 250 timer ticks 250*4us = 1000us = 1ms
     * 
     * Result OPTION = 0b00000001 = 0x01
     */
    
    TMR0 = 0x00; //clear timer value
    
    __asm("MOVLW 0x01");
    __asm("OPTION");
    //OPTION=0xD1;

}

/*
                         Main application
 */
void main(void)
{
    uint8_t gpioValue;
    // initialize the device
    SYSTEM_Initialize();

    while (1)
    {
        /* Check if reset was caused by a touch event (wake-up from Sleep on pin change)*/
        
        if(STATUSbits.GPWUF == 1)
        {
            
            STATUSbits.GPWUF = 0; // Clear flag
            /* Enable backlight */
            BACKLIGHT_ENABLE_PIN = 1;

            /* Keep backligh on for a period until next touch event */
            while(TMR0_Touch_DelayMs(60000));
            
            BACKLIGHT_ENABLE_PIN = 0;
        }
        else
        {
            /* Wait for touch event */
            gpioValue = GPIO; //This is required by datasheet. Read inputs before entering sleep.
            __asm("sleep");
        }

            
        //}
        
   }
}
/**
 End of File
*/