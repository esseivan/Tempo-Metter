/*******************************************************************************
 * File:    iic.c
 * Author:  Esseiva Nicolas
 * Company: EMF (Ecole des Métiers de Fribourg) http://www.emf.ch
 * Desc.:   Communication I2C
 * Date :   20170901 Création (YYYYMMDD)
 * Dernière modif. : 20180701 (YYYYMMDD)
 ******************************************************************************/
//OK

#include "iic.h"

//##############################################################################
// Fonctions (Prototypes)
//##############################################################################
// Attente
void I2C_Master_Wait(void);
// Restart
void I2C_Master_RepeatedStart(void);
// Start
void I2C_Master_Start(void);
// Stop
void I2C_Master_Stop(void);
// Read
unsigned char I2C_Master_Read(unsigned char Ack);
// Write
void I2C_Master_Write(unsigned char d);

//##############################################################################
// Fonctions (implémentation)
//##############################################################################

//******************************************************************************
// Initialisation en mode Master 
//******************************************************************************

void I2C_Master_Init(void) {
    // R_nW write_noTX; P stopbit_notdetected; S startbit_notdetected; BF RCinprocess_TXcomplete; SMP High Speed; UA dontupdate; CKE disabled; D_nA lastbyte_address; 
    SSP1STAT = 0x00;
    // SSPEN enabled; WCOL no_collision; CKP Idle:Low, Active:High; SSPM FOSC/4_SSPxADD_I2C; SSPOV no_overflow; 
    SSP1CON1 = 0x28;
    // ACKTIM ackseq; SBCDE disabled; BOEN disabled; SCIE disabled; PCIE disabled; DHEN disabled; SDAHT 100ns; AHEN disabled; 
    SSP1CON3 = 0x00;
    // SSP1ADD 15; 
    SSP1ADD = 0x0F;

    PIR1bits.BCL1IF = 0;

    PIE1bits.BCL1IE = 1;
}
//******************************************************************************
// Attente
//******************************************************************************

void I2C_Master_Wait(void) {
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F)); //Transmit is in progress
}
//******************************************************************************
// Restart
//******************************************************************************

void I2C_Master_RepeatedStart(void) {
    I2C_Master_Wait();
    SSP1CON2bits.RSEN = 1; //Initiate repeated start condition
}
//******************************************************************************
// Start
//******************************************************************************

void I2C_Master_Start(void) {
    I2C_Master_Wait();
    SSP1CON2bits.SEN = 1; //Initiate start condition
}
//******************************************************************************
// Stop
//******************************************************************************

void I2C_Master_Stop(void) {
    I2C_Master_Wait();
    SSP1CON2bits.PEN = 1; //Initiate stop condition
}
//******************************************************************************
// Read
//******************************************************************************

unsigned char I2C_Master_Read(unsigned char Ack) {
    unsigned char temp;
    I2C_Master_Wait();
    SSP1CON2bits.RCEN = 1;
    I2C_Master_Wait();
    temp = SSP1BUF; //Read data from SSPBUF
    I2C_Master_Wait();
    SSP1CON2bits.ACKDT = Ack ? 0 : 1; //Acknowledge bit
    SSP1CON2bits.ACKEN = 1; //Acknowledge sequence
    //while(SSP1CON2bits.ACKEN == 1);
    return temp;
}
//******************************************************************************
// Write
//******************************************************************************

void I2C_Master_Write(unsigned char d) {
    I2C_Master_Wait();
    SSPBUF = d; //Write data to SSPBUF
}

//******************************************************************************
// Ecriture d'un registre à la cible définie
// Paramètres   :
//      Target  : Adresse de la cible
//      Address : Adresse de l'emplacement
//      Data    : Donnée
//******************************************************************************

void I2C_WriteData(unsigned char Target, unsigned char Address, unsigned char Data) {
    I2C_Master_Start();
    I2C_Master_Write(Target);
    I2C_Master_Write(Address);
    I2C_Master_Write(Data);
    I2C_Master_Stop();
}
//******************************************************************************
// Ecriture d'un registre à la cible définie avec une adresse sur 2 bytes
// Paramètres :
//      Target  : Adresse de la cible
//      Address : Adresse de l'emplacement
//      Data    : Donnée
//******************************************************************************

// Write byte with extended addres

void I2C_WriteData_E(unsigned char Target, ushort Address, unsigned char Data) {
    I2C_Master_Start();
    I2C_Master_Write(Target);
    I2C_Master_Write((Address & 0xFF00) >> 8);
    I2C_Master_Write(Address & 0xFF);
    I2C_Master_Write(Data);
    I2C_Master_Stop();
}
//******************************************************************************
// Ecriture d'un tableau à la cible définie avec une adresse sur 2 bytes
// Paramètres :
//      Target  : Adresse de la cible
//      Address : Adresse de l'emplacement
//      Length  : Taille du tableau
//      Data    : Tableau de donnée
//******************************************************************************

void I2C_WriteLength_E(unsigned char Target, ushort Address, unsigned char Length, unsigned char *Data) {
    I2C_Master_Start();
    I2C_Master_Write(Target);
    I2C_Master_Write((Address & 0xFF00) >> 8);
    I2C_Master_Write(Address & 0xFF);

    for (ushort i = 0; i < Length; i++) {
        I2C_Master_Write(Data[i]);
    }

    I2C_Master_Stop();
}
//******************************************************************************
// Ecriture de la même valeur dans une certaine plage à la cible
// définie avec une adresse sur 2 bytes
// Paramètres :
//      Target  : Adresse de la cible
//      Address : Adresse de l'emplacement
//      Length  : Taille de la plage
//      Data    : Valeur unique à écrire dans la plage
//******************************************************************************

void I2C_WriteLength_E_R(unsigned char Target, ushort Address, ushort Length, unsigned char Data) {
    I2C_Master_Start();
    I2C_Master_Write(Target);
    I2C_Master_Write((Address & 0xFF00) >> 8);
    I2C_Master_Write(Address & 0xFF);

    for (ushort i = 0; i < Length; i++) {
        I2C_Master_Write(Data);
    }

    I2C_Master_Stop();
}
//******************************************************************************
// Lecture d'un emplacement de la cible définie
// Paramètres   :
//      Target  : Adresse de la cible
//      Address : Adresse de l'emplacement
// Retour : Valeur lue
//******************************************************************************

unsigned char I2C_ReadData(unsigned char Target, unsigned char Address) {
    I2C_Master_Start();
    I2C_Master_Write(Target);
    I2C_Master_Write(Address);

    I2C_Master_RepeatedStart();

    I2C_Master_Write(Target | 0x01);
    unsigned char result = I2C_Master_Read(0);
    I2C_Master_Stop();
    return result;
}
//******************************************************************************
// Lecture d'un emplacement de la cible définie avec une adresse sur 2 bytes
// Paramètres   :
//      Target  : Adresse de la cible
//      Address : Adresse de l'emplacement
// Retour : Valeur lue
//******************************************************************************

unsigned char I2C_ReadData_E(unsigned char Target, ushort Address) {
    I2C_Master_Start();
    I2C_Master_Write(Target);
    I2C_Master_Write((Address & 0xFF00) >> 8);
    I2C_Master_Write(Address & 0x00FF);

    I2C_Master_RepeatedStart();

    I2C_Master_Write(Target | 0x01);
    unsigned char result = I2C_Master_Read(0);
    I2C_Master_Stop();
    return result;
}

//******************************************************************************
// Lecture d'un tableau de la cible définie
// Paramètres :
//      Target  : Adresse de la cible
//      Address : Adresse de l'emplacement
//      Length  : Taille du tableau
//      Output  : Tableau de sortie
//******************************************************************************

void I2C_ReadLength(unsigned char Target, unsigned char Address, unsigned char Length, unsigned char *Output) {
    I2C_Master_Start();
    I2C_Master_Write(Target);
    I2C_Master_Write(Address);

    I2C_Master_RepeatedStart();

    I2C_Master_Write(Target | 0x01);

    for (unsigned char i = 0; i < Length; i++) {
        Output[i] = I2C_Master_Read(((i + 1) == Length) ? 0 : 1);
    }
    Output[Length] = 0x00;

    I2C_Master_Stop();
}

//******************************************************************************
// Lecture d'un tableau de la cible définie avec une adresse sur 2 bytes
// Paramètres :
//      Target  : Adresse de la cible
//      Address : Adresse de l'emplacement
//      Length  : Taille du tableau
//      Output  : Tableau de sortie
//******************************************************************************

void I2C_ReadLength_E(unsigned char Target, ushort Address, ushort Length, unsigned char *Output) {
    I2C_Master_Start();
    I2C_Master_Write(Target);
    I2C_Master_Write((Address & 0xFF00) >> 8);
    I2C_Master_Write(Address & 0xFF);

    I2C_Master_RepeatedStart();

    I2C_Master_Write(Target | 0x01);

    for (ushort i = 0; i < Length; i++) {
        Output[i] = I2C_Master_Read(((i + 1) == Length) ? 0 : 1);
    }

    I2C_Master_Stop();
}


//******************************************************************************
// Contrôle l'erreur de collision de bus
//******************************************************************************

void I2C_BusCollisionISR(void) {
    // enter bus collision handling code here
    PIR1bits.BCL1IF = 0;
}

/* END OF FILE ****************************************************************/
