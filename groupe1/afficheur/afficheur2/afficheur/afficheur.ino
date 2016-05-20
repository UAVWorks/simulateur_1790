#include <SPI.h>
#include <Ucglib.h>
int buttonPins[2] = {8,9};
boolean buttonEtat[2] = {false, false};
int pressBouton = 0;
int flag = 0;
int oldX = 0;
int oldY = 0;
int flagD = 1;
Ucglib_ILI9341_18x240x320_SWSPI ucg(/*sclk=*/ 7, /*data=*/ 6, /*cd=*/ 5 , /*cs=*/ 3, /*reset=*/ 4);
const int boutonSuiv = 8 ;
const int boutonPrec = 9 ;

  
void setup(void){
   Serial.begin(9600);
   delay(1000);
   ucg.begin(UCG_FONT_MODE_TRANSPARENT);
   ucg.clearScreen();
 
   // afficheCollectif();
   // affichePallonier();
   //afficheCyclique();
  
   pinMode(boutonSuiv,INPUT_PULLUP);
   pinMode(boutonPrec,INPUT_PULLUP);
   }

void loop(void){

   etatBouton();
   deplacement();
   afficheD();
 
  //jaugeCollectif();
   
   //if(digitalRead(boutonSuiv)==1{
  // ucg.clearScreen ;}
   
}

void affichePallonier(void){
  ucg.clearScreen();
  ucg.setColor(255,255,255);
  ucg.drawFrame(40,60,121,122);
  ucg.drawFrame(40,180,121,122);
  }

void afficheCyclique(void){
  ucg.clearScreen();
  ucg.setColor(255,255,255);
  ucg.drawFrame(10,50,220,220);   //largeur de l'écran = 240x320 pixels 
  }
  
void afficheCollectif(void){
  ucg.clearScreen();
  ucg.setColor(255,255,255);
  ucg.drawFrame(40,60,120,240);
  }



  
void positionCyclique(void){
   int potardX = analogRead(0);
   int potardY = analogRead(1);

   int newX = map(potardX,0,1024,0,200);
   int newY = map(potardY,0,1024,0,200);

   if(oldY != newY || oldX != newX){
      if(newY > oldY + 1 || newX > oldX + 1){
         ucg.setColor(255,255,255);
         ucg.drawDisc(newX+20,newY+60,5,15);
         // ucg.drawLine(newX+10,100,newX+30,100);
         ucg.setColor(0,0,0);
         ucg.drawDisc(oldX+20,oldY+60,5,15);
         // ucg.drawLine(oldX+10,100,oldX+30,100);
         oldX=newX;
         oldY=newY;
         Serial.println(potardX);
         }
      else if(newY < oldY - 1 || newX < oldY - 1){
         ucg.setColor(255,255,255);
         ucg.drawDisc(newX+20,newY+60,5,15);
         //ucg.drawLine(newX+10,100,newX+30,100);
         ucg.setColor(0,0,0);
         ucg.drawDisc(oldX+20,oldY+60,5,15);
         //ucg.drawLine(oldX+10,100,oldX+30,100);
         oldX=newX;
         oldY=newY;
         Serial.println(potardX);
         }
      }
   }



void jaugeCollectif(){
  
   int potard = analogRead(0);
   int newX = map(potard,0,1024,0,240);

 
   if(oldX != newX ){
      if(newX > oldX +1){
         ucg.setColor(255,255,255);
         ucg.drawBox(40,oldX + 61,119,newX-oldX);
         // ucg.setColor(0,0,0);
         // ucg.drawBox(41,oldX+61,119,newX-oldX);
         oldX = newX;
         Serial.println("newx > oldx");
         }
         
      else if(newX < oldX - 1){
         ucg.setColor(0,0,0);
         //ucg.drawBox(41,newX+61,119,-newX);
         ucg.drawBox(40, newX+61,119, oldX-newX);
         oldX = newX;
         Serial.println("newx < oldx");
         }
      }
   }


void jaugePallonier(){
  
   int potard = analogRead(0) ;
   int newX = map(potard,-512,512,0,240);

   potard -= 512;
 
   if(potard<0){
      if(oldX != newX ) {
         if(newX > oldX +1 ){
            ucg.setColor(0,0,0);
            ucg.drawBox(41,oldX + 61,119,newX-oldX);
            oldX = newX;
            Serial.println("newx > oldx");   
            } 
            
         else if(newX < oldX - 1){
            ucg.setColor(255,255,255);
            ucg.drawBox(41, newX+61,119, oldX-newX);
            oldX = newX;
            Serial.println("newx < oldx");
            }
         }
      }
   else{
      if(oldX != newX ){
         if(newX > oldX +1){
            ucg.setColor(255,255,255);
            ucg.drawBox(41,oldX + 62,119,newX-oldX);
            oldX = newX;
            Serial.println("newx > oldx");   
            } 
         else if(newX < oldX - 1){
            ucg.setColor(0,0,0);
            ucg.drawBox(41, newX+62,119, oldX-newX);
            oldX = newX;
            Serial.println("newx < oldx");
            }
         }  
      }
   }


void etatBouton(){
  if (!digitalRead(boutonSuiv)==1 ){
  //  buttonEtat[0] = true ;
  //  buttonEtat[1] = false ;
    pressBouton = 1 ;
  }

  if (!digitalRead(boutonPrec)==1){
  //  buttonEtat[0] = false ;
  //  buttonEtat[1] = true ;
    pressBouton = 2 ;
  }
}


void deplacement(){
  if((pressBouton==1) && (flagD < 3)){
    flagD++;
    pressBouton = 0;
    affiche1();}
  if((pressBouton==2) && (flagD > 1)){
    flagD--;
    pressBouton= 0;
    affiche1();}
}


void affiche1(){
  if (flagD == 1)
    afficheCyclique();
  if (flagD == 2)
    afficheCollectif();
  if (flagD == 3)
    affichePallonier();
}

void afficheD(){
    if (flagD == 1)
    positionCyclique();
  if (flagD == 2)
    jaugeCollectif();
  if (flagD == 3)
    jaugePallonier();
}
