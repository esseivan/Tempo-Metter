/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC16LF18324
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.45
        MPLAB 	          :  MPLAB X 4.15	
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RA2 procedures
#define RA2_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define RA2_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define RA2_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define RA2_GetValue()              PORTAbits.RA2
#define RA2_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define RA2_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define RA2_SetPullup()             do { WPUAbits.WPUA2 = 1; } while(0)
#define RA2_ResetPullup()           do { WPUAbits.WPUA2 = 0; } while(0)
#define RA2_SetAnalogMode()         do { ANSELAbits.ANSA2 = 1; } while(0)
#define RA2_SetDigitalMode()        do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set DIP3 aliases
#define DIP3_TRIS                 TRISAbits.TRISA4
#define DIP3_LAT                  LATAbits.LATA4
#define DIP3_PORT                 PORTAbits.RA4
#define DIP3_WPU                  WPUAbits.WPUA4
#define DIP3_OD                   ODCONAbits.ODCA4
#define DIP3_ANS                  ANSELAbits.ANSA4
#define DIP3_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define DIP3_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define DIP3_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define DIP3_GetValue()           PORTAbits.RA4
#define DIP3_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define DIP3_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define DIP3_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define DIP3_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define DIP3_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define DIP3_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define DIP3_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define DIP3_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set DIP4 aliases
#define DIP4_TRIS                 TRISAbits.TRISA5
#define DIP4_LAT                  LATAbits.LATA5
#define DIP4_PORT                 PORTAbits.RA5
#define DIP4_WPU                  WPUAbits.WPUA5
#define DIP4_OD                   ODCONAbits.ODCA5
#define DIP4_ANS                  ANSELAbits.ANSA5
#define DIP4_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define DIP4_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define DIP4_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define DIP4_GetValue()           PORTAbits.RA5
#define DIP4_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define DIP4_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define DIP4_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define DIP4_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define DIP4_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define DIP4_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define DIP4_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define DIP4_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set SCL1 aliases
#define SCL1_TRIS                 TRISCbits.TRISC0
#define SCL1_LAT                  LATCbits.LATC0
#define SCL1_PORT                 PORTCbits.RC0
#define SCL1_WPU                  WPUCbits.WPUC0
#define SCL1_OD                   ODCONCbits.ODCC0
#define SCL1_ANS                  ANSELCbits.ANSC0
#define SCL1_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define SCL1_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define SCL1_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define SCL1_GetValue()           PORTCbits.RC0
#define SCL1_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define SCL1_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define SCL1_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define SCL1_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define SCL1_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define SCL1_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define SCL1_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define SCL1_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set SDA1 aliases
#define SDA1_TRIS                 TRISCbits.TRISC1
#define SDA1_LAT                  LATCbits.LATC1
#define SDA1_PORT                 PORTCbits.RC1
#define SDA1_WPU                  WPUCbits.WPUC1
#define SDA1_OD                   ODCONCbits.ODCC1
#define SDA1_ANS                  ANSELCbits.ANSC1
#define SDA1_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define SDA1_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define SDA1_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define SDA1_GetValue()           PORTCbits.RC1
#define SDA1_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define SDA1_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define SDA1_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define SDA1_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define SDA1_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define SDA1_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define SDA1_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define SDA1_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set LED_RED aliases
#define LED_RED_TRIS                 TRISCbits.TRISC2
#define LED_RED_LAT                  LATCbits.LATC2
#define LED_RED_PORT                 PORTCbits.RC2
#define LED_RED_WPU                  WPUCbits.WPUC2
#define LED_RED_OD                   ODCONCbits.ODCC2
#define LED_RED_ANS                  ANSELCbits.ANSC2
#define LED_RED_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define LED_RED_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define LED_RED_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define LED_RED_GetValue()           PORTCbits.RC2
#define LED_RED_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define LED_RED_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define LED_RED_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define LED_RED_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define LED_RED_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define LED_RED_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define LED_RED_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define LED_RED_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set LED_GREEN aliases
#define LED_GREEN_TRIS                 TRISCbits.TRISC3
#define LED_GREEN_LAT                  LATCbits.LATC3
#define LED_GREEN_PORT                 PORTCbits.RC3
#define LED_GREEN_WPU                  WPUCbits.WPUC3
#define LED_GREEN_OD                   ODCONCbits.ODCC3
#define LED_GREEN_ANS                  ANSELCbits.ANSC3
#define LED_GREEN_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define LED_GREEN_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define LED_GREEN_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define LED_GREEN_GetValue()           PORTCbits.RC3
#define LED_GREEN_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define LED_GREEN_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define LED_GREEN_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define LED_GREEN_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define LED_GREEN_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define LED_GREEN_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define LED_GREEN_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define LED_GREEN_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set DIP1 aliases
#define DIP1_TRIS                 TRISCbits.TRISC4
#define DIP1_LAT                  LATCbits.LATC4
#define DIP1_PORT                 PORTCbits.RC4
#define DIP1_WPU                  WPUCbits.WPUC4
#define DIP1_OD                   ODCONCbits.ODCC4
#define DIP1_ANS                  ANSELCbits.ANSC4
#define DIP1_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define DIP1_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define DIP1_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define DIP1_GetValue()           PORTCbits.RC4
#define DIP1_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define DIP1_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define DIP1_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define DIP1_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define DIP1_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define DIP1_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define DIP1_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define DIP1_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set DIP2 aliases
#define DIP2_TRIS                 TRISCbits.TRISC5
#define DIP2_LAT                  LATCbits.LATC5
#define DIP2_PORT                 PORTCbits.RC5
#define DIP2_WPU                  WPUCbits.WPUC5
#define DIP2_OD                   ODCONCbits.ODCC5
#define DIP2_ANS                  ANSELCbits.ANSC5
#define DIP2_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define DIP2_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define DIP2_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define DIP2_GetValue()           PORTCbits.RC5
#define DIP2_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define DIP2_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define DIP2_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define DIP2_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define DIP2_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define DIP2_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define DIP2_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define DIP2_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/