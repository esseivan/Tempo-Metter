/*******************************************************************************
 * File:    iic.h
 * Author:  Esseiva Nicolas
 * Company: EMF (Ecole des Métiers de Fribourg) http://www.emf.ch
 * Desc.:   Définitions pour communication I2C
 * Date :   20170901 Création (YYYYMMDD)
 * Dernière modif. : 20180701 (YYYYMMDD) 
 ******************************************************************************/
//OK

#ifndef IIC_HEADER    
#define IIC_HEADER

#include "mcc_generated_files/mcc.h"

//##############################################################################
// Fonctions (prototype)
//##############################################################################

// Initialisation en mode Master 
void I2C_Master_Init(void);
// Ecriture d'un registre à la cible définie
void I2C_WriteData(unsigned char Target, unsigned char Address, unsigned char Data);
// Ecriture d'un registre à la cible définie avec une adresse sur 2 bytes
void I2C_WriteData_E(unsigned char Target, unsigned short Address, unsigned char Data);
// Ecriture d'un tableau à la cible définie avec une adresse sur 2 bytes
void I2C_WriteLength_E(unsigned char Target, unsigned short Address, unsigned char Length, unsigned char *Data);
// Ecriture de la même valeur dans une certaine plage à la cible
void I2C_WriteLength_E_R(unsigned char Target, unsigned short Address, unsigned short Length, unsigned char Data);
// Lecture d'un emplacement de la cible définie
unsigned char I2C_ReadData(unsigned char Target, unsigned char Address);
// Lecture d'un emplacement de la cible définie avec une adresse sur 2 bytes
unsigned char I2C_ReadData_E(unsigned char Target, unsigned short Address);
// Lecture d'un tableau de la cible définie
void I2C_ReadLength(unsigned char Target, unsigned char Address, unsigned char Length, unsigned char *Output);
// Lecture d'un tableau de la cible définie avec une adresse sur 2 bytes
void I2C_ReadLength_E(unsigned char Target, unsigned short Address, unsigned short Length, unsigned char *Output);
// Contrôle l'erreur de collision de bus
void I2C_BusCollisionISR(void);

#endif

/* END OF FILE ****************************************************************/
