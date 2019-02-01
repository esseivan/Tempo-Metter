
#include "drumMetter.h"

void Delay_Xms(unsigned short Delay) {
    unsigned short i;
    for (i = 0; i < Delay; i++) {
        __delay_ms(1);
    }

    asm("nop");
}

void WaitAndCheck(unsigned short Delay) {
    unsigned short i;
    for (i = 0; i < Delay; i++) {
        __delay_ms(1);
        if(check)
        {
            CheckValid();
            break;
        }
    }

    asm("nop");
}

void LedBlink_Period(unsigned short Period, unsigned char Count, unsigned short EndDelay) {
    unsigned short Delay = (Period / 2);

    while (Count != 0) {
        LED_RED_On();
        LED_GREEN_On();
        Delay_Xms(Delay);
        LED_RED_Off();
        LED_GREEN_Off();
        Delay_Xms(Delay);
        Count--;
    }
    Delay_Xms(EndDelay);
}

void LedBlink_Error(unsigned char ErrorIndex) {
    INTERRUPT_GlobalInterruptDisable();

    while (1) {
        LedBlink_Period(2000, ErrorIndex, 2 * 1000);
    }
}

void displayState(bool state)
{
    LED_GREEN_LAT = (state > 0) ? LED_ON : LED_OFF;
    LED_RED_LAT = (state > 0) ? LED_OFF : LED_ON;
    __delay_ms(250);
    LED_RED_Off();
    LED_GREEN_Off();
    __delay_ms(250);
}

void displayMode()
{
    unsigned char mask = 0b0001;
    displayState((mode & mask ) > 0);
    mask = mask << 1;
    displayState((mode & mask) > 0);
    mask = mask << 1;
    displayState((mode & mask) > 0);
    mask = mask << 1;
    displayState((mode & mask) > 0);
}

void setMode_2nd(bool state, unsigned char maskOr)
{
    if(state)
    {
        mode |= maskOr;
    }
    else
    {
        mode &= (~maskOr);
    }
}

void setMode()
{
    unsigned char mask_1st = 0b0001;
    unsigned char lastMode = mode;
    
    setMode_2nd(DIP1_Value(), mask_1st << 0);
    setMode_2nd(DIP2_Value(), mask_1st << 1);
    setMode_2nd(DIP3_Value(), mask_1st << 2);
    setMode_2nd(DIP4_Value(), mask_1st << 3);
    
    if(mode != lastMode)
        verify = true;
}

void CheckValid()
{
    LED_GREEN_Off();
    LED_RED_Off();
    
    unsigned int32_t calculs_1 = 0, calculs_2 = 0;
    // Copy timestamps
    last2 = last1;
    last1 = last0;
    last0 = timestamp;
    
    if(last2 == 0 && last1 != 0 && !DIP4_Value())
    {
        lastTempo = 0;
    }
    
    if(lastTempo != 0)
    {
        // Dernier tempo
        calculs_1 = last0 - last1;
        // Dernier tempo correct
        calculs_2 = lastTempo;
    }
    // SINON
    else
    {
        // Attente des valeurs de départ
        if(last0 == 0 || last1 == 0 || last2 == 0)
        {
            LED_GREEN_Off();
            LED_RED_Off();
            // debounce delay
            Delay_Xms(100);
            // Réarmer
            check = false;
            return;
        }

        // Différence de temps entre les 2 derniers coups
        calculs_1 = last0 - last1;

        // Différence entre les 2 coups précédents
        calculs_2 = last1 - last2;
    }
    
    // Différence entre les 2
    
    
    // debounce delay
    Delay_Xms(100);
    
    // Comparaison
    // Absolue
    if(precisionMode == 0)
    {
        if(calculs_1 < calculs_2)
        {
            calculs_1 = calculs_2 - calculs_1;
        }
        else 
        {
            calculs_1 = calculs_1 - calculs_2;
        }
        
        if (calculs_1 <= precision)
        {
            // Correct
            LED_GREEN_On();
            LED_RED_Off();
            ledResult = 1;

            if(((calculs_1 * 10 <= precision) && !DIP4_Value()) || lastTempo == 0 )
            {
                // Si DIP4 off, sauvegarde continue
                lastTempo = last0 - last1;
            }
        }
        else
        {
            // Mauvais
            LED_GREEN_Off();
            LED_RED_On();
            ledResult = 0;
        }
    }
    // Relative
    else if(precisionMode == 1)
    {
        float Error = 0;
        if(calculs_1 < calculs_2)
        {
            Error = (calculs_2 - calculs_1);
        }
        else 
        {
            Error = (calculs_1 - calculs_2);
        }
        
        Error = Error * (100 / calculs_2);
        
        if (Error <= precision)
        {
            // Correct
            LED_GREEN_On();
            LED_RED_Off();
            ledResult = 1;

            if(((Error * 10 <= precision) && !DIP4_Value()) || lastTempo == 0 )
            {
                // Si DIP4 off, sauvegarde continue
                lastTempo = last0 - last1;
            }
        }
        else
        {
            // Mauvais
            LED_GREEN_Off();
            LED_RED_On();
            ledResult = 0;
        }
    }
    
    
    
    // Réarmer
    check = false;
}
