/*******************************************************************************
 * File:    accelerometer.h
 * Author:  Esseiva Nicolas
 * Company: EMF (Ecole des Métiers de Fribourg) http://www.emf.ch
 * Desc.:   Définitions accéléromètre MMA845XQ
 * Date :   20170901 Création (YYYYMMDD)
 * Dernière modif. : 20180701 (YYYYMMDD)
 ******************************************************************************/
//OK

#ifndef ACCELEROMETER_HEADER
#define ACCELEROMETER_HEADER

//##############################################################################
// Constantes utilisateur
//##############################################################################

// Nombre maximum d'envoi de commande par I2C quand le résultat est incorrect
#define CMD_COUNT_TIMEOUT   5

// Résolution par défaut (RESOLUTION_8bit ou RESOLUTION_14bit)
#define RESOLUTION          RESOLUTION_8bit
#define RESOLUTION_8bit     1
#define RESOLUTION_14bit    2

//##############################################################################
// Constantes
//##############################################################################

#define uchar unsigned char

//******************************************************************************
// Registres et configuration de l'accéléromètre par défaut
//******************************************************************************

// Configuration de l'impulsion
#define PULSE_CFG_ADDR      0x21
#define PULSE_CFG           0b00010101
//                            ||||||||
//                            |||||||+- XSPEFE      = 1 : X Axis single pulse detection
//                            ||||||+-- XDPEFE      = 0 : X Axis double pulse detection
//                            |||||+--- YSPEFE      = 1 : Y Axis single pulse detection
//                            ||||+---- YDPEFE      = 0 : Y Axis double pulse detection
//                            |||+----- ZSPEFE      = 1 : Z Axis single pulse detection
//                            ||+------ ZDPEFE      = 0 : Z Axis double pulse detection
//                            |+------- ELE         = 0 : Pulse event latch
//                            +-------- DPA         = 0 : Double pulse abort

// Seuil de détection d'impulsion sur l'axe X
#define PULSE_THSX_ADDR     0x23

// Seuil de détection d'impulsion sur l'axe Y
#define PULSE_THSY_ADDR     0x24

// Seuil de détection d'impulsion sur l'axe Z
#define PULSE_THSZ_ADDR     0x25

//#TODO
// Durée maximale de l'impulsion pour être détectée
#define PULSE_TMLT_ADDR     0x26
#define PULSE_TMLT          0b11001000
//                            ||||||||
//                            ++++++++- TMLT0..7    = 0xC8 : Pulse time limmit

//#TODO
// 100ms latency
#define PULSE_LTCY_ADDR     0x27
#define PULSE_LTCY          0b01000000
//                            ||||||||
//                            ++++++++- LTCY0..7    = 0x40 : Latency time limit

// Configuration générale
#define XYZ_DATA_CFG_ADDR   0x0E
#define XYZ_DATA_CFG        0b00000010
//                            xxx|xx||
//                            ||||||++- FS0..1      = 0b10 : Full-scale range : 8g
//                            |||+----- HPF_OUT     = 0 : High-pass output data

// Délai d'inactivité pour entrer en mode veille
#define ASLP_Count_ADDR     0x29
#define ASLP_Count          0b11111111
//                            ||||||||
//                            ++++++++- D0..7       = 0xFF : Delay to sleep

// Configuration générale
#define CTRL_REG1_ADDR      0x2A
#define CTRL_REG1           0b00000010
//                            ||||||||
//                            |||||||+- ACTIVE          = 0 : Standby/Active mode selection
//                            ||||||+-- F_READ          = 1 : Fast read mode (8-bit mode)
//                            |||||+--- LNOISE          = 0 : Reduced noise mode (and range reduced to 4g)
//                            ||+++---- DR0..2          = 0b000 : Data-rate selection
//                            ++------- ASLP_RATE0..1   = 0b00 : Sleep mode rate

// Configuration générale
#define CTRL_REG2_ADDR      0x2B
#define CTRL_REG2           0b00000010
//                            ||x|||||
//                            || |||++- MODS0..1    = 0b10 : Active mode power scheme
//                            || ||+--- SLPE        = 0 : Auto-sleep mode enabled
//                            || ++---- SMODS0..1   = 0b00 : Sleep mode power scheme
//                            |+------- RST         = 0 : Software reset
//                            +-------- ST          = 0 : Self-test enable

// Configuration des interruptions
#define CTRL_REG3_ADDR      0x2C
#define CTRL_REG3           0b00010000
//                            |||||x||
//                            ||||| |+- PP_OD       = 0 : Interrupt output mode (push-pull / open drain)
//                            ||||| +-- IPOL        = 0 : Interrupt active polarity
//                            ||||+---- WAKE_FF_MT  = 0 : Freefall/motion can wake up
//                            |||+----- WAKE_PULSE  = 1 : Pulse can wake up
//                            ||+------ WAKE_LNDPRT = 0 : Orientation can wake up
//                            |+------- WAKE_TRANS  = 0 : Transient can wake up
//                            +-------- FIFO_GATE   = 0 : FIFO gate flushed when enterring/exitting sleep mode

// Configuration des interruptions
#define CTRL_REG4_ADDR      0x2D
#define CTRL_REG4           0b00001000
//                            ||||||x|
//                            |||||| +- INT_EN_DRDY     = 0 : Data-ready interrupt enable
//                            |||||+--- INT_EN_FF_MT    = 0 : Freefall/motion interrupt enable
//                            ||||+---- INT_EN_PULSE    = 1 : Pulse interrupt enable
//                            |||+----- INT_EN_LNDPRT   = 0 : Orientation interrupt enable
//                            ||+------ INT_EN_TRANS    = 0 : Transient interrupt enable
//                            |+------- INT_EN_FIFO     = 0 : FIFO interrupt enable
//                            +-------- INT_EN_ASLP     = 0 : Auto-sleep interrupt enable

// Configuration des interruptions
#define CTRL_REG5_ADDR      0x2E
#define CTRL_REG5           0b10111101
//                            ||||||x|
//                            |||||| +- INT_CFG_DRDY    = 1 : Data-ready int pin selection
//                            |||||+--- INT_CFG_FF_MT   = 1 : Freefall/motion int pin selection
//                            ||||+---- INT_CFG_PULSE   = 1 : Pulse int pin selection
//                            |||+----- INT_CFG_LNDPRT  = 1 : Orientation int pin selection
//                            ||+------ INT_CFG_TRANS   = 1 : Transient int pin selection
//                            |+------- INT_CFG_FIFO    = 1 : FIFO int pin selection
//                            +-------- INT_CFG_ASLP    = 1 : Auto-sleep int pin selection

//******************************************************************************
// Autres
//******************************************************************************

// Adresse avec la pin SA0 à '1'
#define ACC_TARGET_ADDRESS_SA0      0x3A
// Adresse avec la pin SA0 à '0'
#define ACC_TARGET_ADDRESS_N_SA0    0x38
// Adresse de l'accéléromètre
#define CURRENT_TARGET_ADDRESS ACC_TARGET_ADDRESS_N_SA0

// Registre WHO_AM_I
#define WHO_AM_I_ADDR       0x0D
// Réponse devant être reçue de l'accéléromètre après lecture du registre WHO_AM_I
#define WHO_AM_I_ANSWER     0x2A

// Modes standby et actif
#define MODE_STANDBY        0
#define MODE_ACTIVE         1

//##############################################################################
// Variables globales
//##############################################################################

// Mode actuel de l'accéléromètre
uchar AccelerometerMode = MODE_STANDBY;

//##############################################################################
// Fonctions (Prototypes)
//##############################################################################

// Initialisation de l'accéléromètre
void ACCEL_Init(void);
// Appliquer les paramètres configurables
void SSET_THRESHOLD(uchar value);
void SSET_Latency(uchar value);
void SSET_Freq(uchar value);
// Ecriture d'un registre
void WriteData(uchar Address, uchar Data, uchar Verify);
// Lecture d'un registre
uchar ReadData(uchar Address);
// Lecture de l'état de l'accéléromètre
uchar GetMode(void);
// Changement de l'état de l'accéléromètre
void SetMode(uchar Mode);
//unsigned char getFrequency(unsigned char mode);
//unsigned char getLatency(unsigned char mode);
unsigned char getPrecision(unsigned char mode);
unsigned char getThreshold(unsigned char mode);
unsigned char getPrecisionMode(unsigned char mode);
#endif

/* END OF FILE ****************************************************************/
