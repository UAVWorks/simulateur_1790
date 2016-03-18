/*
CÃ¢blage pour le module LG-ADXL345 en i2c, sur la la planche d'expÃ©rimentation :

ACCELEROMETRE_1_SCL  broche  1 : (a41) et cÃ¢ble de (b41) Ã  (b47) ECRAN_LCD_1_J6_1
ACCELEROMETRE_1_SDA  broche  2 : (a42) et cÃ¢ble de (c42) Ã  (c48) ECRAN_LCD_1_J6_2
ACCELEROMETRE_1_SDO  broche  3 :
ACCELEROMETRE_1_INT2 broche  4 :
ACCELEROMETRE_1_INT1 broche  5 :
ACCELEROMETRE_1_CS   broche  6 : (i45) et cÃ¢ble de (j45) Ã  (+45D)
ACCELEROMETRE_1_VS   broche  7 :
ACCELEROMETRE_1_GND  broche  8 : (i43) et cÃ¢ble de (j43) Ã  (-43D)
ACCELEROMETRE_1_3V3  broche  9 :
ACCELEROMETRE_1_5V   broche 10 : (i41) et cÃ¢ble de (j41) Ã  (+41D)
*/

//*****************************************************************************
// Inclusion des librairies utilisÃ©es.
//*****************************************************************************
#include <Wire.h>
/*
Cette bibliothÃ¨que vous permet de communiquer avec des pÃ©riphÃ©riques I2C/TWI.
Sur les cartes Arduino rÃ©vision R3, les broches SDA (ligne de donnÃ©es) et SCL
(ligne d'horloge) sont Ã  proximitÃ© de la broche AREF.

En rÃ©fÃ©rence le tableau ci-dessous montre ont situÃ©s les broches avec les cartes
Arduino.

Carte         Broches I2C / TWI
Uno, Ethernet A4 (SDA), A5 (SCL)

Avec Arduino version 1.0 et plus, la bibliothÃ¨que hÃ©rite des fonctions de flux,
ce qui rend compatible avec les autres bibliothÃ¨ques en lecture/Ã©criture. Pour
cette raison, Â« send () Â» et Â« receive () Â» ont Ã©tÃ© remplacÃ©s par Â« read () Â» et
Â« write () Â».

Remarque :

Il y a deux variante d'adresse de communication I2C, une de 7 bits et une de
8 bits. La variante 7 bits identifier le dispositif et le huitiÃ¨me bit
dÃ©termine si elle est en cours d'Ã©criture ou de lecture Ã  partir. La
bibliothÃ¨que de fil utilise des adresses 7 bits partout. Si vous avez un code
de fiche ou d'Ã©chantillon qui utilise 8 bits d'adresse, vous aurez besoin de
laisser tomber le bit bas, c'est a dire, de dÃ©caler la valeur d'un bit vers la
droite), ce qui donne une adresse entre 0 et 127.
*/
//*****************************************************************************
// Constantes des connecteurs.
//*****************************************************************************
// Broche d'Arduino pour communication I2C avec accÃ©lÃ©romÃ¨tre LG-ADXL345.
const int ACCELEROMETRE_1_SCL = A5;
const int ACCELEROMETRE_1_SDA = A4;

// Adresses de communication I2C avec accÃ©lÃ©romÃ¨tre ADXL345.
const char Accellerometre3AxesAdresse = 0x53;
byte Accellerometre3AxesMemoire [6];
const char POWER_CTL = 0x2D;// Registre "Power Control".
const char DATA_FORMAT = 0x31;// Registre "Data Format".
const char DATAX0 = 0x32;//X-Axis Data 0
const char DATAX1 = 0x33;//X-Axis Data 1
const char DATAY0 = 0x34;//Y-Axis Data 0
const char DATAY1 = 0x35;//Y-Axis Data 1
const char DATAZ0 = 0x36;//Z-Axis Data 0
const char DATAZ1 = 0x37;//Z-Axis Data 1

const char Accellerometre_1_Precision2G  = 0x00;
const char Accellerometre_1_Precision4G  = 0x01;
const char Accellerometre_1_Precision8G  = 0x02;
const char Accellerometre_1_Precision16G = 0x03;
const char Accellerometre_1_ModeMesure   = 0x08;

// Pour recevoir les valeurs des 3 axes de l'accÃ©lÃ©romÃ¨tre.
int Accelerometre1_AxeX = 0;
int Accelerometre1_AxeY = 0;
int Accelerometre1_AxeZ = 0;

// ModifiÃ© de Â±0.1 seconde le taux de rafraÃ®chissement des donnÃ©es (+/-).
int TauxRafraichissementDonnees = (1000 / 2);

void setup ()
{
  Serial.begin(9600);
  // Initialisation de la communication I2C bus pour le capteur dâ€™accÃ©lÃ©ration.
  Wire.begin ();
  // Mettre le ADXL345 Ã  plage +/-4G en Ã©crivant la valeur 0x01 dans le
  // registre DATA_FORMAT.
  AccellerometreConfigure (DATA_FORMAT, Accellerometre_1_Precision4G);
  // Mettre le ADXL345 en mode de mesure en Ã©crivant 0x08 dans le registre
  // POWER_CTL.
  AccellerometreConfigure (POWER_CTL, Accellerometre_1_ModeMesure);

}

void loop()
{
    Serial.print (" AxeX:");
    Serial.print (Accelerometre1_AxeX);
    Serial.println ();
    Serial.print (" AxeY:");
    Serial.print (Accelerometre1_AxeY);
    Serial.println ();
    Serial.print (" AxeZ:");
    Serial.print (Accelerometre1_AxeZ);
    Serial.println ();
}
//*****************************************************************************
// FONCTION AccellerometreConfigure
//*****************************************************************************
void AccellerometreConfigure (byte address, byte val)
{
  // Commencer la transmission Ã  trois axes accÃ©lÃ©romÃ¨tre
  Wire.beginTransmission (Accellerometre3AxesAdresse);
  // Envoyer l'adresse de registre
  Wire.write (address);
  // Envoyer la valeur Ã  Ã©crire.
  Wire.write (val);
  // Fin de la transmission.
  Wire.endTransmission ();
}
//*****************************************************************************

//*****************************************************************************
// FONCTION AccellerometreLecture ()
//*****************************************************************************
void AccellerometreLecture ()
{
  uint8_t NombreOctets_a_Lire = 6;
  // Lire les donnÃ©es d'accÃ©lÃ©ration Ã  partir du module ADXL345.
  AccellerometreLectureMemoire (DATAX0, NombreOctets_a_Lire,
                                Accellerometre3AxesMemoire);

  // Chaque lecture de l'axe vient dans une rÃ©solution de 10 bits, soit 2 octets.
  // PremiÃ¨re Octet significatif !
  // Donc nous convertissons les deux octets pour un Â« int Â».
  Accelerometre1_AxeX = (((int)Accellerometre3AxesMemoire[1]) << 8) |
      Accellerometre3AxesMemoire[0];
  Accelerometre1_AxeY = (((int)Accellerometre3AxesMemoire[3]) << 8) |
      Accellerometre3AxesMemoire[2];
  Accelerometre1_AxeZ = (((int)Accellerometre3AxesMemoire[5]) << 8) |
      Accellerometre3AxesMemoire[4];
}
//*****************************************************************************

//*****************************************************************************
// FONCTION AccellerometreLectureMemoire
//*****************************************************************************
/*
Lit le nombre d'octets Ã  partir du registre d'adresse sur accÃ©lÃ©romÃ¨tre dans le
tableau en mÃ©moire de l'accÃ©lÃ©romÃ¨tre.
*/
void AccellerometreLectureMemoire (byte address, int num, byte
                                   Accellerometre3AxesMemoire[])
{
  // DÃ©marrer la transmission Ã  accÃ©lÃ©romÃ¨tre.
  Wire.beginTransmission (Accellerometre3AxesAdresse);
  // Envoie l'adresse de lire.
  Wire.write (address);
  // Fin de la transmission.
  Wire.endTransmission ();
  // DÃ©marrer la transmission Ã  accÃ©lÃ©romÃ¨tre.
  Wire.beginTransmission (Accellerometre3AxesAdresse);
  // Demande 6 octets Ã  l'accÃ©lÃ©romÃ¨tre.
  Wire.requestFrom (Accellerometre3AxesAdresse, num);

  int i = 0;
  // L'accÃ©lÃ©romÃ¨tre peut envoyer moins que demandÃ©, c'est anormal, mais...
  while (Wire.available())
  {
    // Recevoir un octet.
    Accellerometre3AxesMemoire[i] = Wire.read ();
    i++;
  }
    // Fin de la transmission.
  Wire.endTransmission ();
}

