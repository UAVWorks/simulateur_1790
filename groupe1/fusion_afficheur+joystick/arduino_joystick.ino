#include <SparkFunColorLCDShield.h>
#include <stdio.h> 

#define NUM_AXES    4         // 4 axes, X, Y, Z, etc

LCDShield lcd;
int buttonPins[3] = {3, 4, 5};
char timeChar[12];

typedef struct joyReport_t {
    int16_t axis[NUM_AXES];
} joyReport_t;

joyReport_t joyReport;

int valeur_Min[NUM_AXES];
int valeur_Max[NUM_AXES];
void setup(void);
void loop(void);
void sendJoyReport(joyReport_t *report);

void setup() 
{ 
  lcd.init(PHILIPS); 
  lcd.contrast(63); // sets LCD contrast (value between 0~63)
  Serial.begin(115200);
  menu();
  delay(200);

  for (uint8_t ind=0; ind<NUM_AXES; ind++) 
  {
    valeur_Min[ind] = analogRead(ind) ;
    valeur_Max[ind] = analogRead(ind)+1 ;
  }
    
}

void sendJoyReport(struct joyReport_t *report)
{    
  Serial.write((uint8_t *)report, sizeof(joyReport_t));
}

void loop() 
{
  for (uint8_t ind=0; ind<NUM_AXES; ind++){
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

  affiche_commande();
  sendJoyReport(&joyReport);
  delay(100);
}

void menu(){
  lcd.clear(BLACK);
  lcd.setStr("   SELECTION :", 15,2, WHITE, BLACK);
  lcd.setStr("B1:Rt Cyclique", 45,2, WHITE, BLACK);
  lcd.setStr("B2:Rt Generique", 75,2, WHITE, BLACK);
  lcd.setStr("B3:Rt Arriere", 105,2, WHITE, BLACK);
}

void affiche_commande(){
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
}