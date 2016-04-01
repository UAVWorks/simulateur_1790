#include <SparkFunColorLCDShield.h>
#include <stdio.h> 

#define BACKGROUND BLACK 
#define RECT_COLOR BLUE
#define CROSS      RED

LCDShield lcd;

int buttonPins[3] = {3, 4, 5};
boolean buttonEtat[3] = {false, false, false};
int x = -32768;
int c ;
int pressButton = 0;
int flagD = 1;

void setup()
{ 
 lcd.init(PHILIPS); 
 lcd.contrast(63); // sets LCD contrast (value between 0~63)
 Serial.begin(9600);
 lcd.clear(BACKGROUND);
}

void loop()
{
   x = x+1000;
   etatBouton();
   deplacement();
   afficheD();
}

void deplacement(){
  if((pressButton==3) && (flagD < 3)){
    flagD++;
    affiche();}
  if((pressButton==2) && (flagD > 1)){
    flagD--;
    affiche();}
}

void affiche(){
  if (flagD == 1)
    cyclique();
  if (flagD == 2)
    collectif();
  if (flagD == 3)
    pallonier();
}

void afficheD(){
    if (flagD == 1)
    DynamiqueCyclique();
  if (flagD == 2)
    DynamiqueCollectif();
  if (flagD == 3)
    DynamiquePallonier();
}

void cyclique(){
    lcd.clear(BACKGROUND);
    lcd.setRect(24,24,104,104 ,40, RECT_COLOR);
    lcd.setRect(25,25,105,105 ,40, RECT_COLOR);
    lcd.setLine(61,66,71,66,CROSS);
    lcd.setLine(66,61,66,71,CROSS);	
}

void collectif(){
   lcd.clear(BACKGROUND);
   lcd.setRect(50,15,79,113 ,40, RECT_COLOR);      
   lcd.setRect(51,15,80,113 ,40, RECT_COLOR);       
   lcd.setRect(50,16,79,114 ,40, RECT_COLOR);      
}

void pallonier(){
   lcd.clear(BACKGROUND);
   lcd.setRect(50,15,79,113 ,40, RECT_COLOR);
   lcd.setRect(51,15,80,113 ,40, RECT_COLOR);
   lcd.setLine(50,66,79,66,RECT_COLOR);
   lcd.setRect(50,16,79,114 ,40, RECT_COLOR);	
}

void DynamiqueCyclique(){
}


void DynamiqueCollectif(){
  
   c = map(x,-32768 ,32767, 16, 114);  
   
   lcd.setRline(50,c+1,79,114,0,RECT_COLOR);
   lcd.setRline(50,c,79,114,0, RECT_COLOR);
  
   Serial.println(x);
   Serial.println('\t');
      
}


void DynamiquePallonier(){
 
}

void etatBouton(){
	if (!digitalRead(buttonPins[0])){
		buttonEtat[0] = true ;
		buttonEtat[1] = false ;
		buttonEtat[2] = false ;
    pressButton = 1 ;
	}

	if (!digitalRead(buttonPins[1])){
		buttonEtat[0] = false ;
		buttonEtat[1] = true ;
		buttonEtat[2] = false ;
    pressButton = 2 ;
	}

	if (!digitalRead(buttonPins[2])){
		buttonEtat[0] = false ;
		buttonEtat[1] = false ;
		buttonEtat[2] = true ;
    pressButton = 3 ;
	}
}
