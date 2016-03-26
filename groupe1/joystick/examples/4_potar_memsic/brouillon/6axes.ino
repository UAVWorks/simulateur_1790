#include <SPI.h>
#include "accelerometre.h"

#define NUM_AXES    4         // 4 axes pour les potentiometre uniquement

typedef struct joyReport_t {
    int16_t axis[NUM_AXES];
} joyReport_t;

joyReport_t joyReport;

int valeur_Min[NUM_AXES];
int valeur_Max[NUM_AXES];

int CS=10; //numero de pin pour le cs

char values[10];
int x,y,z;

void setup(void);
void loop(void);
void accelerometre_sensor();
void sendJoyReport(joyReport_t *report);

void setup() 
{
    //configuration du SPI de l'arduino
    SPI.begin();
    SPI.setDataMode(SPI_MODE3);
    //configuration de la communication serial de l'arduino
    Serial.begin(115200);
    delay(200);

    for (uint8_t ind=0; ind<NUM_AXES; ind++) 
    {
    joyReport.axis[ind] = ind*1000;
    valeur_Min[ind] = analogRead(ind) ;
    valeur_Max[ind] = analogRead(ind)+1 ;
    }
    
   pinMode(CS, OUTPUT);
   digitalWrite(CS, HIGH);
  
   writeRegister(DATA_FORMAT, 0x01);
   writeRegister(POWER_CTL, 0x08);  //Measurement mode 
     
}

void sendJoyReport(struct joyReport_t *report)
{
#ifndef DEBUG
    Serial.write((uint8_t *)report, sizeof(joyReport_t));
    #define DEBUG
#else

    // dump human readable output for debugging
    for (uint8_t ind=0; ind<NUM_AXES; ind++) {
	Serial.print("axis[");
	Serial.print(ind);
	Serial.print("]= ");
	Serial.print(report->axis[ind]);
	Serial.print(" ");
    }
    Serial.println();

#endif
}

void loop() 
{
    accelerometre_sensor();
    for (uint8_t ind=0; ind<NUM_AXES; ind++)
    {
      int valeur_Potar = analogRead(ind);
    
      if ( valeur_Potar < valeur_Min[ind])
      {  
        valeur_Min[ind] = valeur_Potar ;
      }   
      if ( valeur_Potar > valeur_Max[ind])
      {
        valeur_Max[ind] = valeur_Potar ;
      }
    
      joyReport.axis[ind] =map(analogRead(ind), valeur_Min[ind], valeur_Max[ind], -32768,32767 );

    }
    
    sendJoyReport(&joyReport);
    
}
void accelerometre_sensor()
{

  /*Reading 6 bytes of data starting at register DATAX0 will retrieve the x,y and z acceleration values from the ADXL345.
  	The results of the read operation will get stored to the values[] buffer.*/
  readRegister(DATAX0, 6, values);

  /*The ADXL345 gives 10-bit acceleration values, but they are stored as bytes (8-bits). To get the full value, two bytes must be combined for each 		axis.*/
  /*The X value is stored in values[0] and values[1].*/
  x = ((int)values[1]<<8)|(int)values[0];
  /*The Y value is stored in values[2] and values[3].*/
  y = ((int)values[3]<<8)|(int)values[2];
  /*The Z value is stored in values[4] and values[5].*/
  z = ((int)values[5]<<8)|(int)values[4];
  
  //Print the results to the terminal.
  Serial.print(x, DEC);
  Serial.print(',');
  Serial.print(y, DEC);
  Serial.print(',');
  Serial.println(z, DEC);      
  delay(10); 

    delay(100);

  //Set the Chips Select pin high to end the SPI packet.
  digitalWrite(CS, HIGH);
}   

void writeRegister(char registerAddress, char value)
{
  //Set Chip Select pin low to signal the beginning of an SPI packet.
  digitalWrite(CS, LOW);
  //Transfer the register address over SPI.
  SPI.transfer(registerAddress);
  //Transfer the desired register value over SPI.
  SPI.transfer(value);
  //Set the Chip Select pin high to signal the end of an SPI packet.
  digitalWrite(CS, HIGH);
}

//This function will read a certain number of registers starting from a specified address and store their values in a buffer.
//Parameters:
//  char registerAddress - The register addresse to start the read sequence from.
//  int numBytes - The number of registers that should be read.
//  char * values - A pointer to a buffer where the results of the operation should be stored.
void readRegister(char registerAddress, int numBytes, char * values)
{
  //Since we're performing a read operation, the most significant bit of the register address should be set.
  char address = 0x80 | registerAddress;
  //If we're doing a multi-byte read, bit 6 needs to be set as well.
  if(numBytes > 1)address = address | 0x40;
  
  //Set the Chip select pin low to start an SPI packet.
  digitalWrite(CS, LOW);
  //Transfer the starting register address that needs to be read.
  SPI.transfer(address);
  //Continue to read registers until we've read the number specified, storing the results to the input buffer.
  for(int i=0; i<numBytes; i++){
    values[i] = SPI.transfer(0x00);
}
