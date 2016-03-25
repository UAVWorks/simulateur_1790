#include <SparkFunColorLCDShield.h>
#include <stdio.h> 

LCDShield lcd;

int buttonPins[3] = {3, 4, 5};
char timeChar[12];

void setup()
{
 // following two required for LCD
 lcd.init(PHILIPS); 
 lcd.contrast(63); // sets LCD contrast (value between 0~63)
 Serial.begin(9600);

 float test = (/*joyReport.axis[3] + */  3000)/468.75 + 5.50 ;
 Serial.print(test,2);
}

void loop()
{

 
  lcd.clear(BLACK);
  lcd.setStr("   SELECTION :", 15,2, WHITE, BLACK);
  lcd.setStr("B1:Rt Cyclique", 45,2, WHITE, BLACK);
  lcd.setStr("B2:Rt Generique", 75,2, WHITE, BLACK);
  lcd.setStr("B3:Rt Arriere", 105,2, WHITE, BLACK);
  do {
  
   if (!digitalRead(buttonPins[0]))
  {
    lcd.clear(BLACK);
    lcd.setRect(24,24,104,104 ,40, BLUE);
    lcd.setRect(25,25,105,105 ,40, BLUE);
    lcd.setLine(61,66,71,66,RED);
    lcd.setLine(66,61,66,71,RED);
   }

   
   if (!digitalRead(buttonPins[1]))
    {
    lcd.clear(BLACK);
    lcd.setRect(50,15,79,113 ,40, BLUE);
    lcd.setRect(51,15,80,113 ,40, BLUE);
    lcd.setRect(50,16,79,114 ,40, BLUE);
    }
   if (!digitalRead(buttonPins[2]))
   {
   lcd.clear(BLACK);
   lcd.setRect(50,15,79,113 ,40, BLUE);
   lcd.setRect(51,15,80,113 ,40, BLUE);
   lcd.setLine(50,66,79,66,BLUE);
   lcd.setRect(50,16,79,114 ,40, BLUE);
   }
  } while (1);  
 }
