#include <SPI.h>
#include <Ucglib.h>

int flag = 0;

Ucglib_ILI9341_18x240X320_SWSPI ucg(7, 6, 5, 3, 4);

void setup(void){
 delay(1000);
 ucg.begin(UCG_FONT_MODE_TRANSPARENT);
 ucg.clearScreen();
}

void loop(void){

 if(flag == 0)
   afficheCollectif();
 jaugeCollectif();

}

void afficheCOllectif(void){
 ucg.clearScreen();
 ucg.setColol(255,255,255);
 ucg.drawFrame(40,60,240,120);
}

void jaugeCollectif(){
 int x = map(analogRead(0),0,1024,0,239);
 ucg.setcolor(255,255,255);
 ucg.drawBox(41,61,x,119);
 ucg.setColor(0,0,0);
 ucg.drawBox(41,61,-(239-x),119);
}
