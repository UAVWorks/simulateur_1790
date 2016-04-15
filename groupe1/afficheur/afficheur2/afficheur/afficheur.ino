#include <SPI.h>
#include <Ucglib.h>

int flag = 0;

 int oldX = 0;
Ucglib_ILI9341_18x240x320_SWSPI ucg(/*sclk=*/ 7, /*data=*/ 6, /*cd=*/ 5 , /*cs=*/ 3, /*reset=*/ 4);

void setup(void){
  Serial.begin(9600);
 delay(1000);
 ucg.begin(UCG_FONT_MODE_TRANSPARENT);
 ucg.clearScreen();
   afficheCollectif();
   
}

void loop(void){

 if(flag == 0)
 
 jaugeCollectif();

}

void afficheCollectif(void){
 ucg.clearScreen();
 ucg.setColor(255,255,255);
 ucg.drawFrame(40,60,120,240);
}

void jaugeCollectif(){
 int y = 0;
 int potard = analogRead(0);
 int ancienPotard = 0 ;
 int newX = map(potard,0,1024,0,240);
 //Serial.println(potard);
 //Serial.println(x);
 // y = map(potard,0,1024,0,240);
 // y=y-100;
  //Serial.println(y);
 
  if(oldX != newX ) {
    if(newX > oldX +1 )
   {
      ucg.setColor(255,255,255);
      ucg.drawBox(41,oldX + 61,119,newX-oldX);
     // ucg.setColor(0,0,0);
     // ucg.drawBox(41,oldX+61,119,newX-oldX);
      oldX = newX;
   Serial.println("newx > oldx");
   } else if(newX < oldX - 1){
      ucg.setColor(0,0,0);
      //ucg.drawBox(41,newX+61,119,-newX);
       ucg.drawBox(41, newX+61,119, oldX-newX);
      oldX = newX;
       Serial.println("newx < oldx");
   }
  }
 // if(x<=y)
 //{
// ucg.setColor(0,0,0);
// ucg.drawBox(41,61,119,x);
 // }
}

void affichePalloniers(void){
 ucg.clearScreen();
 ucg.setColor(255,255,255);
 ucg.drawFrame(40,60,120,240);
}

