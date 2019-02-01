/*******************************************************************************
 * File:    accelerometer.c
 * Author:  Esseiva Nicolas
 * Company: EMF (Ecole des Métiers de Fribourg) http://www.emf.ch
 * Desc.:   Accéléromètre MMA845XQ
 * Date :   20170901 Création (YYYYMMDD)
 * Dernière modif. : 20180701 (YYYYMMDD)
 ******************************************************************************/
//OK

#include "accelerometer.h"
#include "mcc_generated_files/mcc.h"

//##############################################################################
// Fonctions (prototypes)
//##############################################################################

// Ecriture d'un registre et vérification (continue jusqu'à timeout)
uchar WriteVerifyRegister(uchar Address, uchar Data);
// Ecriture d'un registre
void WriteRegister(uchar Address, uchar Data);
// Lecture d'un registre
uchar ReadRegister(uchar Address);

//##############################################################################
// Fonctions (implémentation)
//##############################################################################

//******************************************************************************
// Initialisation de l'accéléromètre
//******************************************************************************

void ACCEL_Init(void) {
    // L'accéléromètre ne conserve pas ses paramètres au redémarrage,
    // il faut donc l'initialiser à chaque initialisation

    // Initialisation de la communication I2C
    I2C_Master_Init();

    // Vérification que l'accéléromètre est actif et le correct
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

    // Si le modèle est correct
    if (ok) {
        // Mise à jour du mode actuel
        GetMode();

        // Vérification si initialisation nécessaire
        // Reset de l'accéléromètre
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
            // Si l'accéléromètre est actif, mettre en mode standby
            SetMode(MODE_STANDBY);
        }

        // Configuration générale
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
        // Si le modèle est incorrect, erreur 2
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
        // Si l'accéléromètre est actif, mettre en mode standby
        SetMode(MODE_STANDBY);
        state = MODE_ACTIVE;
    }

    uchar value_2 = CTRL_REG1 & 0xC6;
    value_2 |= ((freq << 3) & 0x38);
    WriteData(CTRL_REG1_ADDR, value_2, true);

    if (state == MODE_ACTIVE)
        // Passage à nouveau en mode actif
        SetMode(MODE_ACTIVE);
}

void SSET_Latency(uchar value) {
    bool state = MODE_STANDBY;
    if (AccelerometerMode == MODE_ACTIVE) {
        // Si l'accéléromètre est actif, mettre en mode standby
        SetMode(MODE_STANDBY);
        state = MODE_ACTIVE;
    }
    
    WriteData(PULSE_LTCY_ADDR, value, true);

    if (state == MODE_ACTIVE)
        // Passage à nouveau en mode actif
        SetMode(MODE_ACTIVE);
}

void SSET_THRESHOLD(uchar value) {
    uchar Threshold = value;

    bool state = MODE_STANDBY;
    if (AccelerometerMode == MODE_ACTIVE) {
        // Si l'accéléromètre est actif, mettre en mode standby
        SetMode(MODE_STANDBY);
        state = MODE_ACTIVE;
    }

    WriteVerifyRegister(PULSE_THSX_ADDR, Threshold);
    WriteVerifyRegister(PULSE_THSY_ADDR, Threshold);
    WriteVerifyRegister(PULSE_THSZ_ADDR, Threshold);

    if (state == MODE_ACTIVE)
        // Passage à nouveau en mode actif
        SetMode(MODE_ACTIVE);
}

//******************************************************************************
// Ecriture d'un registre et vérification (continue jusqu'à timeout)
// Paramètres :
//      Address : Adresse du registre
//      Data : Donnée à écrire
// Retour : Donnée lue
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
// Paramètres :
//      Address : Adresse du registre
//      Data : Donnée à écrire
//******************************************************************************

void WriteRegister(uchar Address, uchar Data) {
    I2C_WriteData(CURRENT_TARGET_ADDRESS, Address, Data);
}

//******************************************************************************
// Ecriture d'un registre, fonction publique
// Paramètres :
//      Address : Adresse du registre
//      Data : Donnée à écrire
//******************************************************************************

void WriteData(uchar Address, uchar Data, uchar Verify) {
    bool state = MODE_STANDBY;
    if (AccelerometerMode == MODE_ACTIVE) {
        // Si l'accéléromètre est actif, mettre en mode standby
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
        // Passage à nouveau en mode actif
        SetMode(MODE_ACTIVE);
}

//******************************************************************************
// Lecture d'un registre, fonction publique
// Paramètres :
//      Address : Adresse du registre
// Retour : Donnée lue
//******************************************************************************

uchar ReadData(uchar Address) {
    return ReadRegister(Address);
}

//******************************************************************************
// Lecture d'un registre
// Paramètres :
//      Address : Adresse du registre
// Retour : Donnée lue
//******************************************************************************

uchar ReadRegister(uchar Address) {
    return I2C_ReadData(CURRENT_TARGET_ADDRESS, Address);
}

//******************************************************************************
// Lecture de l'état de l'accéléromètre
// Retour : Mode actuel (MODE_STANDBY ou MODE_ACTIVE)
//******************************************************************************

uchar GetMode(void) {
    // Lecture de la valeur
    uchar Mode = ReadRegister(CTRL_REG1_ADDR);
    // Garder le bit 0
    Mode = Mode & 0x01;
    // Mise à jour
    AccelerometerMode = Mode;

    return Mode;
}

//******************************************************************************
// Changement de l'état de l'accéléromètre
// Paramètres :
//      Mode : Mode (MODE_STANDBY ou MODE_ACTIVE)
//******************************************************************************

void SetMode(uchar Mode) {
    // Garder le bit 0
    Mode = Mode & 0x01;
    // Mise à jour
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
