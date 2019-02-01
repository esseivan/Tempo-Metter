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
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC16LF18324
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

#include "mcc_generated_files/mcc.h"
#include "accelerometer.h"
/*
                         Main application
 */


void int_interrupt()
{
    check = true;
    lastOccurence = lastOccurenceTimeout;
}

void tmr2_interrupt()
{
    // Timestamp every 1ms, up to 49 days count
    ++timestamp;
    
//    if(ledResult != -1)
//    {
//        if(timestamp % (10 * lastTempo) == 0)
//        {
//            if(ledResult == 0)
//            {
//                LED_GREEN_Off();
//                LED_RED_On();
//            }
//            else
//            {
//                LED_RED_Off();
//                LED_GREEN_On();
//            }
//        }
//        else if(timestamp % (10 * lastTempo) == (lastTempo / 2))
//        {
//            LED_GREEN_Off();
//            LED_RED_Off();
//        }
//    }
}

void tmr4_interrupt()
{
    // Mode selection interrupt, every 2s
    if(lastOccurence != -1)
    {
        if(lastOccurence == 0)
        {
            LED_GREEN_Off();
            LED_RED_Off();
            lastOccurence = -1;
            ledResult = -1;
            last0 = 0;
            last1 = 0;
            last2 = 0;
            
            setMode();
        }
        else
        {
            lastOccurence--;
        }
    }
    else
    {
        setMode();
    }
}

void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
    LED_RED_Off();
    LED_RED_Off();
    timestamp = 0;
    
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    
    mode = 0;
    mode |= (DIP1_Value()) ? 0b0001 : 0;
    mode |= (DIP2_Value()) ? 0b0010 : 0;
    mode |= (DIP3_Value()) ? 0b0100 : 0;
    mode |= (DIP4_Value()) ? 0b1000 : 0;
    precision = getPrecision(mode);
    precisionMode = getPrecisionMode(mode);
    
    TMR4_StopTimer();
    TMR2_StopTimer();
    ACCEL_Init();
    TMR4_StartTimer();
    TMR2_StartTimer();
    
    LED_RED_On();
    LED_GREEN_On();
    __delay_ms(125);
    LED_GREEN_Off();
    LED_GREEN_Off();
    __delay_ms(500);
    displayMode();
    
    TMR2_SetInterruptHandler(tmr2_interrupt);
    TMR4_SetInterruptHandler(tmr4_interrupt);
    INT_SetInterruptHandler(int_interrupt);
    
    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    while (1)
    {
        // Enable the Global Interrupts
        INTERRUPT_GlobalInterruptEnable();
        // Enable the Peripheral Interrupts
        INTERRUPT_PeripheralInterruptEnable();
    
        WaitAndCheck(1000);
//        Delay_Xms(1000);
        if(verify)
        {
            verify = false;
            displayMode();
            
            precision = getPrecision(mode);
            precisionMode = getPrecisionMode(mode);
            
            asm("nop");
        }
    }
}

/**
 End of File
*/