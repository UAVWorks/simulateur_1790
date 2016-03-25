void affiche_menu(){
  lcd.clear(BLACK);
  lcd.setStr("   SELECTION :", 15,2, WHITE, BLACK);
  lcd.setStr("B1:Rt Cyclique", 45,2, WHITE, BLACK);
  lcd.setStr("B2:Rt Generique", 75,2, WHITE, BLACK);
  lcd.setStr("B3:Rt Arriere", 105,2, WHITE, BLACK);
}

void affiche_cyclique(){
	lcd.clear(BLACK);
    lcd.setRect(24,24,104,104 ,40, BLUE);
    lcd.setRect(25,25,105,105 ,40, BLUE);
    lcd.setLine(61,66,71,66,RED);
    lcd.setLine(66,61,66,71,RED);
}
void affiche_collectif(){
	lcd.clear(BLACK);
    lcd.setRect(50,15,79,113 ,40, BLUE);
    lcd.setRect(51,15,80,113 ,40, BLUE);
    lcd.setRect(50,16,79,114 ,40, BLUE);
}
void affiche_pallonier(){
   lcd.clear(BLACK);
   lcd.setRect(50,15,79,113 ,40, BLUE);
   lcd.setRect(51,15,80,113 ,40, BLUE);
   lcd.setLine(50,66,79,66,BLUE);
   lcd.setRect(50,16,79,114 ,40, BLUE);
}

void affiche(){
	if(!digitalRead(buttonPins[0]))
		affiche_cyclique();
	else if(!digitalRead(buttonPins[1]))
		affiche_collectif();
}