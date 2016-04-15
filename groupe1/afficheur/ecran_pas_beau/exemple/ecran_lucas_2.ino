/*
  ADS7846 Touch-Controller Example
 */

#include <SPI.h>
#include <digitalWriteFast.h>
#include <GraphicsLib.h>
#include <MI0283QT2.h>
//#include <MI0283QT9.h>
#include <ADS7846.h>


ADS7846 ads;
MI0283QT2 lcd;


void setup()
{
    lcd.begin();
   lcd.fillScreen(RGB(0,0,0));
   //lcd.drawText(5, 5, "Bonjours", RGB(0,0,0), RGB(255,255,255), 1);
   //lcd.drawRect(60, 20, 200, 200, RGB(142,162,198));//cyclique
   /*lcd.drawRect(40, 60, 240, 100, RGB(142,162,198));
   lcd.drawLine(160, 60, 160, 159, RGB(142,162,198));//pallonier*/
   //lcd.drawRect(40, 60, 240, 100, RGB(142,162,198));//collectif
  //init Serial port
  //menu
  lcd.fillRect(20,20,120,80, RGB(142,162,198));
  lcd.fillRect(180,20,120,80, RGB(142,162,198));
  lcd.fillRect(20,140,120,80, RGB(142,162,198));
  lcd.fillRect(180,140,120,80, RGB(142,162,198));
  Serial.begin(9600);
  while(!Serial); //wait for serial port to connect - needed for Leonardo only

  //init Touch-Controller
  Serial.println("Init...");
  ads.begin();
}


void loop()
{
  ads.service();

  uint16_t x = ads.getXraw();
  uint16_t y = ads.getYraw();
  uint16_t z = ads.getPressure();
  if(z)
  {
    Serial.println(x, DEC);
    Serial.println(y, DEC);
    Serial.println(z, DEC);
  }

  delay(500);
}
