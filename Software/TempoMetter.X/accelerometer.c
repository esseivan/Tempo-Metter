/*******************************************************************************
 * File:    accelerometer.c
 * Author:  Esseiva Nicolas
 * Company: EMF (Ecole des M�tiers de Fribourg) http://www.emf.ch
 * Desc.:   Acc�l�rom�tre MMA845XQ
 * Date :   20170901 Cr�ation (YYYYMMDD)
 * Derni�re modif. : 20180701 (YYYYMMDD)
 ******************************************************************************/
//OK

#include "accelerometer.h"
#include "mcc_generated_files/mcc.h"

//##############################################################################
// Fonctions (prototypes)
//##############################################################################

// Ecriture d'un registre et v�rification (continue jusqu'� timeout)
uchar WriteVerifyRegister(uchar Address, uchar Data);
// Ecriture d'un registre
void WriteRegister(uchar Address, uchar Data);
// Lecture d'un registre
uchar ReadRegister(uchar Address);

//##############################################################################
// Fonctions (impl�mentation)
//##############################################################################

//******************************************************************************
// Initialisation de l'acc�l�rom�tre
//******************************************************************************

void ACCEL_Init(void) {
    // L'acc�l�rom�tre ne conserve pas ses param�tres au red�marrage,
    // il faut donc l'initialiser � chaque initialisation

    // Initialisation de la communication I2C
    I2C_Master_Init();

    // V�rification que l'acc�l�rom�tre est actif et le correct
    uchar ok = false;
    uchar _timeout = 0;
    uchar _maxTimeout = 5;
    uchar Timeout = false;
    do {

        uchar WhoAmI = ReadRegister(WHO_AM_I_ADDR);
        if (WhoAmI == WHO_AM_I_ANSWER)
            ok = true;
        else if (_timeout++ >= _maxTimeout)
            Timeout = true;
    } while ((!ok) && (!Timeout));

    // Si le mod�le est correct
    if (ok) {
        // Mise � jour du mode actuel
        GetMode();

        // V�rification si initialisation n�cessaire
        // Reset de l'acc�l�rom�tre
        WriteRegister(CTRL_REG2_ADDR, 0x40);
        // Attente du clear du flag automatique
        uchar timeout = 0;
        uchar result = 0;
        do {
            Delay_Xms(5);
            result = ReadRegister(CTRL_REG2_ADDR);
            timeout++;
        } while ((result != 0x00) || (timeout == CMD_COUNT_TIMEOUT));

        if (AccelerometerMode == MODE_ACTIVE) {
            // Si l'acc�l�rom�tre est actif, mettre en mode standby
            SetMode(MODE_STANDBY);
        }

        // Configuration g�n�rale
        WriteVerifyRegister(CTRL_REG1_ADDR, CTRL_REG1);
        WriteVerifyRegister(CTRL_REG2_ADDR, CTRL_REG2);
        WriteVerifyRegister(CTRL_REG3_ADDR, CTRL_REG3);

        // Plage de fonctionnement
        WriteVerifyRegister(XYZ_DATA_CFG_ADDR, XYZ_DATA_CFG);

        // Interruptions
        WriteVerifyRegister(CTRL_REG4_ADDR, CTRL_REG4);
        WriteVerifyRegister(CTRL_REG5_ADDR, CTRL_REG5);

        // Pulse
        WriteVerifyRegister(PULSE_CFG_ADDR, PULSE_CFG);
        WriteVerifyRegister(PULSE_TMLT_ADDR, PULSE_TMLT);
        WriteVerifyRegister(PULSE_LTCY_ADDR, PULSE_LTCY);

        SSET_THRESHOLD(getThreshold(mode));

        SetMode(MODE_ACTIVE);
        
    } else {
        // Si le mod�le est incorrect, erreur 2
        LedBlink_Error(2);
    }
}

//******************************************************************************
// Modifications suivant la configuration actuelle
//******************************************************************************

unsigned char getThreshold(unsigned char mode)
{    
    // Threshold
//    unsigned char thresholdMode = mode & 0b0001;
//    if (thresholdMode == 0)
//        // 2g
//        return 0x1F;
//    if (thresholdMode == 1)
//        // 7g
//        return 0x6E;
    
    // 3g
    return 0x2F;
}

unsigned char getPrecision(unsigned char mode)
{    
    // Threshold
    unsigned char precisionMode = (mode & 0b0011);
    if (precisionMode == 0)
        // 10ms or 1%
        return 1;
    if (precisionMode == 1)
        // 50ms or 5%
        return 5;
    if (precisionMode == 2)
        // 100ms or 10%
        return 10;
    if (precisionMode == 3)
        // 200ms or 20%
        return 20;
}


unsigned char getPrecisionMode(unsigned char mode)
{    
    // Threshold
    unsigned char precisionMode = (mode & 0b0100) >> 2;
    if (precisionMode == 0)
        // 10ms or 1%
        return 0;
    if (precisionMode == 1)
        // 50ms or 5%
        return 1;
}

//unsigned char getLatency(unsigned char mode)
//{
//    // Frequency
//    unsigned char LatencyMode = (mode & 0b1100) >> 2;
//    if (LatencyMode == 0)
//        // 10ms
//        return 4;
//    if (LatencyMode == 1)
//        // 100ms
//        return 40;
//    if (LatencyMode == 2)
//        // 240ms
//        return 62;
//    if (LatencyMode == 3)
//        // 500ms
//        return 200;
//    
//}
//
//unsigned char getFrequency(unsigned char mode)
//{
//    // Frequency
//    unsigned char FrequencyMode = (mode & 0b1100) >> 2;
//    if (FrequencyMode == 0)
//        // 800Hz
//        return 0b000;
//    if (FrequencyMode == 1)
//        // 200Hz
//        return 0b010;
//    if (FrequencyMode == 2)
//        // 50Hz
//        return 0b100;
//    if (FrequencyMode == 3)
//        // 1.56Hz
//        return 0b111;
//    
//}

void SSET_FREQ(uchar value) {
    uchar freq = value;

    bool state = MODE_STANDBY;
    if (AccelerometerMode == MODE_ACTIVE) {
        // Si l'acc�l�rom�tre est actif, mettre en mode standby
        SetMode(MODE_STANDBY);
        state = MODE_ACTIVE;
    }

    uchar value_2 = CTRL_REG1 & 0xC6;
    value_2 |= ((freq << 3) & 0x38);
    WriteData(CTRL_REG1_ADDR, value_2, true);

    if (state == MODE_ACTIVE)
        // Passage � nouveau en mode actif
        SetMode(MODE_ACTIVE);
}

void SSET_Latency(uchar value) {
    bool state = MODE_STANDBY;
    if (AccelerometerMode == MODE_ACTIVE) {
        // Si l'acc�l�rom�tre est actif, mettre en mode standby
        SetMode(MODE_STANDBY);
        state = MODE_ACTIVE;
    }
    
    WriteData(PULSE_LTCY_ADDR, value, true);

    if (state == MODE_ACTIVE)
        // Passage � nouveau en mode actif
        SetMode(MODE_ACTIVE);
}

void SSET_THRESHOLD(uchar value) {
    uchar Threshold = value;

    bool state = MODE_STANDBY;
    if (AccelerometerMode == MODE_ACTIVE) {
        // Si l'acc�l�rom�tre est actif, mettre en mode standby
        SetMode(MODE_STANDBY);
        state = MODE_ACTIVE;
    }

    WriteVerifyRegister(PULSE_THSX_ADDR, Threshold);
    WriteVerifyRegister(PULSE_THSY_ADDR, Threshold);
    WriteVerifyRegister(PULSE_THSZ_ADDR, Threshold);

    if (state == MODE_ACTIVE)
        // Passage � nouveau en mode actif
        SetMode(MODE_ACTIVE);
}

//******************************************************************************
// Ecriture d'un registre et v�rification (continue jusqu'� timeout)
// Param�tres :
//      Address : Adresse du registre
//      Data : Donn�e � �crire
// Retour : Donn�e lue
//******************************************************************************

uchar WriteVerifyRegister(uchar Address, uchar Data) {
    uchar timeout = 0;
    uchar result = 0;
    do {
        WriteRegister(Address, Data);
        result = ReadRegister(Address);
        timeout++;
    } while ((result != Data) || (timeout == CMD_COUNT_TIMEOUT));
    return result;
}

//******************************************************************************
// Ecriture d'un registre
// Param�tres :
//      Address : Adresse du registre
//      Data : Donn�e � �crire
//******************************************************************************

void WriteRegister(uchar Address, uchar Data) {
    I2C_WriteData(CURRENT_TARGET_ADDRESS, Address, Data);
}

//******************************************************************************
// Ecriture d'un registre, fonction publique
// Param�tres :
//      Address : Adresse du registre
//      Data : Donn�e � �crire
//******************************************************************************

void WriteData(uchar Address, uchar Data, uchar Verify) {
    bool state = MODE_STANDBY;
    if (AccelerometerMode == MODE_ACTIVE) {
        // Si l'acc�l�rom�tre est actif, mettre en mode standby
        SetMode(MODE_STANDBY);
        state = MODE_ACTIVE;
    }

    if (Verify)
        WriteVerifyRegister(Address, Data);
    else
        WriteRegister(Address, Data);

    if ((Address == CTRL_REG1_ADDR) && (Data & 0x01 == 0))
        return;

    if (state == MODE_ACTIVE)
        // Passage � nouveau en mode actif
        SetMode(MODE_ACTIVE);
}

//******************************************************************************
// Lecture d'un registre, fonction publique
// Param�tres :
//      Address : Adresse du registre
// Retour : Donn�e lue
//******************************************************************************

uchar ReadData(uchar Address) {
    return ReadRegister(Address);
}

//******************************************************************************
// Lecture d'un registre
// Param�tres :
//      Address : Adresse du registre
// Retour : Donn�e lue
//******************************************************************************

uchar ReadRegister(uchar Address) {
    return I2C_ReadData(CURRENT_TARGET_ADDRESS, Address);
}

//******************************************************************************
// Lecture de l'�tat de l'acc�l�rom�tre
// Retour : Mode actuel (MODE_STANDBY ou MODE_ACTIVE)
//******************************************************************************

uchar GetMode(void) {
    // Lecture de la valeur
    uchar Mode = ReadRegister(CTRL_REG1_ADDR);
    // Garder le bit 0
    Mode = Mode & 0x01;
    // Mise � jour
    AccelerometerMode = Mode;

    return Mode;
}

//******************************************************************************
// Changement de l'�tat de l'acc�l�rom�tre
// Param�tres :
//      Mode : Mode (MODE_STANDBY ou MODE_ACTIVE)
//******************************************************************************

void SetMode(uchar Mode) {
    // Garder le bit 0
    Mode = Mode & 0x01;
    // Mise � jour
    AccelerometerMode = Mode;
    // Lecture de la valeur
    uchar data = ReadRegister(CTRL_REG1_ADDR);
    // Effacer le bit 0
    data = data & 0xFE;
    // Appliquer le bit 0
    data = data | Mode;
    // Ecriture de la nouvelle valeur
    WriteVerifyRegister(CTRL_REG1_ADDR, data);
}

/* END OF FILE ****************************************************************/
