#include <MI0283QT2.h>
#include <GraphicsLib.h>
#include <SPI.h>
#include <digitalWriteFast.h>

 MI0283QT2 lcd;
 
 void setup(){
   lcd.begin();
   lcd.fillScreen(RGB(0,0,0));
   //lcd.drawText(5, 5, "Bonjours", RGB(0,0,0), RGB(255,255,255), 1);
   //lcd.drawRect(60, 20, 200, 200, RGB(142,162,198));//cyclique
   /*lcd.drawRect(40, 60, 240, 100, RGB(142,162,198));
   lcd.drawLine(160, 60, 160, 159, RGB(142,162,198));//pallonier*/
   lcd.drawRect(40, 60, 240, 100, RGB(142,162,198));//collectif
   
 }
 
 void loop(){}
