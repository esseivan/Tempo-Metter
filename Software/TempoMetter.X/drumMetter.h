/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include "mcc_generated_files/mcc.h"

#define LED_GREEN_On() LED_GREEN_SetLow()
#define LED_GREEN_Off() LED_GREEN_SetHigh()
#define LED_RED_On() LED_RED_SetLow()
#define LED_RED_Off() LED_RED_SetHigh()
#define LED_ON 0
#define LED_OFF 1

#define DIP1_Value() !DIP1_GetValue()
#define DIP2_Value() !DIP2_GetValue()
#define DIP3_Value() !DIP3_GetValue()
#define DIP4_Value() !DIP4_GetValue()

unsigned char mode = 0;
bool verify = false;
unsigned char precision = 0;

// 0 : absolute
// 1 : relative
unsigned char precisionMode = 0;
bool check = false;
char lastOccurence = 0;
char lastOccurenceTimeout = 1;     // 1 * 2s
// Timestamp 1ms precision
unsigned int32_t timestamp = 0;

unsigned char ledResult = 0;

// Last timestamps
unsigned char lastIndex = 0;
unsigned int32_t last0 = 0;
unsigned int32_t last1 = 0;
unsigned int32_t last2 = 0;
unsigned int32_t lastTempo = 0;

void Delay_Xms(unsigned short Delay);
void WaitAndCheck(unsigned short Delay);
void LedBlink_Error(unsigned char ErrorIndex);
void LedBlink_Period(unsigned short Period, unsigned char Count, unsigned short EndDelay);
void displayMode();
void setMode();
void CheckValid();

#endif	/* XC_HEADER_TEMPLATE_H */

