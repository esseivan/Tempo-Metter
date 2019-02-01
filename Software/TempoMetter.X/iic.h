/*******************************************************************************
 * File:    iic.h
 * Author:  Esseiva Nicolas
 * Company: EMF (Ecole des M�tiers de Fribourg) http://www.emf.ch
 * Desc.:   D�finitions pour communication I2C
 * Date :   20170901 Cr�ation (YYYYMMDD)
 * Derni�re modif. : 20180701 (YYYYMMDD) 
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
// Ecriture d'un registre � la cible d�finie
void I2C_WriteData(unsigned char Target, unsigned char Address, unsigned char Data);
// Ecriture d'un registre � la cible d�finie avec une adresse sur 2 bytes
void I2C_WriteData_E(unsigned char Target, unsigned short Address, unsigned char Data);
// Ecriture d'un tableau � la cible d�finie avec une adresse sur 2 bytes
void I2C_WriteLength_E(unsigned char Target, unsigned short Address, unsigned char Length, unsigned char *Data);
// Ecriture de la m�me valeur dans une certaine plage � la cible
void I2C_WriteLength_E_R(unsigned char Target, unsigned short Address, unsigned short Length, unsigned char Data);
// Lecture d'un emplacement de la cible d�finie
unsigned char I2C_ReadData(unsigned char Target, unsigned char Address);
// Lecture d'un emplacement de la cible d�finie avec une adresse sur 2 bytes
unsigned char I2C_ReadData_E(unsigned char Target, unsigned short Address);
// Lecture d'un tableau de la cible d�finie
void I2C_ReadLength(unsigned char Target, unsigned char Address, unsigned char Length, unsigned char *Output);
// Lecture d'un tableau de la cible d�finie avec une adresse sur 2 bytes
void I2C_ReadLength_E(unsigned char Target, unsigned short Address, unsigned short Length, unsigned char *Output);
// Contr�le l'erreur de collision de bus
void I2C_BusCollisionISR(void);

#endif

/* END OF FILE ****************************************************************/
