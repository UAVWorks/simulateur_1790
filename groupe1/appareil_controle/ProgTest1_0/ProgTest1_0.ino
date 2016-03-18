#include <LiquidCrystal.h>

LiquidCrystal lcd(11,10,5,4,3,2);

const int interupt = 7;
const int led = 12;
int sensorValue;   // Valeur potentiometre
int etatInterupt;  // État interrupteur
float count;       // Étape du controle
float butMin;      // Butée minimum
float butMax;      // Butée maximum
int course;        // Course du potentiometre
int coursUtil;     // Course utilisée
int zoneMorte;     // Pourcentage utilisé pour la zone morte

void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  pinMode(led, OUTPUT);
  pinMode(interupt, INPUT_PULLUP);
}

void loop()
{
  lcd.clear();
  lcd.setCursor(7,1);
  sensorValue = analogRead(A0);
  if(!butMin || !butMax)  lcd.print(sensorValue);
  etatInterupt = digitalRead(interupt);
  delay(50);
  
  ////    Définission de la butée minimum ////
  
  if(etatInterupt == 1 && count == 0 && !butMin)
  {
    count = 1;
    butMin = sensorValue;
    lcd.setCursor(0,0);
    lcd.print("Enregistre");
    delay(200);
  }
  
  ////    FIN    ////
  
  ////   Définission de la butée maximum    ////
  
  else if(etatInterupt == 0 && butMin && count == 1)
  {
    count = 2;
    butMax = sensorValue;
    lcd.setCursor(0,0);
    lcd.print("Enregistre");
    delay(200);
  }
  
  else if(etatInterupt == 0 && count == 2)
 {
   lcd.setCursor(0,0);
   lcd.print("Zone Morte:");
   lcd.setCursor(0,1);
   lcd.print("Basculez interup");
   delay(50);
 } 
  
  else if(etatInterupt == 1 && butMin && butMax)
  {
    count = 3;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Zone morte (%)");
    lcd.setCursor(7,1);
    lcd.print(map(analogRead(A0),0,1024,0,100));
    delay(50);
  }
  
  ////    FIN    ////

  ////    Définission de la taille de la zone morte    ////
  
  else if(etatInterupt == 0 && count == 3)
  {
    count = 4;
    zoneMorte = map(analogRead(A0),0,1024,0,100);
  }
  
    ////    FIN    ////
  
  while(butMin && butMax && count == 4)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(butMin);
    lcd.setCursor(8,0);
    lcd.print(butMax);
    
    if(butMin < butMax)
    {
      course = ((butMax - butMin) * 100 )  / 1024;
    }
    
    else if(butMin > butMax)
    {
      course = ((butMin - butMax) * 100 ) / 1024;
    }
    delay(50);
    
    while(course < 50)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Course faible !");
      lcd.setCursor(0,1);
      lcd.print(course);
      lcd.setCursor(2,1);
      lcd.print("%");
      digitalWrite(led, HIGH);
      delay(50);
      digitalWrite(led, LOW);
      delay(50);
    }
    
    while(course > 50)
    {
      lcd.clear();
      lcd.setCursor(3,0);
      
      if(butMin < butMax)
      {
        coursUtil = map(analogRead(A0),butMin,butMax,0,100);
      }
      
      ////      Si les butée ont été inversé lors de leur enregistrement
      ////      elles sont enncore inversées et remis à la normal
      
      if(butMin > butMax)
      {
        coursUtil = map(analogRead(A0),butMax,butMin,0,100);
      }
      
      if(coursUtil < (100 - zoneMorte) && coursUtil > zoneMorte)
      {
        lcd.print("De 0 a 100");
        lcd.setCursor(0,1);
        lcd.print(coursUtil);
        delay(50);
      }
      
      else if(coursUtil <= zoneMorte && coursUtil >= 0)
      {
        lcd.print("Zone Morte");
        lcd.setCursor(3,1);
        lcd.print("Trop bas");
        delay(50);
      }
      
      else if(coursUtil >= (100 - zoneMorte) && coursUtil <= 100)
      {
        lcd.print("Zone Morte");
        lcd.setCursor(3,1);
        lcd.print("Trop haut");
        delay(50);
      }
      
      else if(coursUtil < 0)
      {
        lcd.print("Erreur !!!");
        lcd.setCursor(0,1);
        lcd.print("Zone non utilise");
        delay(50);
      }
      
      else if(coursUtil > 100)
      {
        lcd.print("Erreur !!!");
        lcd.setCursor(0,1);
        lcd.print("Zone non utilise");
        delay(50);
      }
    }
  }
}
