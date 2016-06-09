#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup() {
  lcd.begin(20, 4);
}

void loop() {
  lcd.setCursor(0, 0); 
  lcd.print("Explore M3"); 
  lcd.setCursor(0, 1); 
  lcd.print("Character LCD");
  lcd.setCursor(0, 2);
  lcd.print("4 lines"); 
  lcd.setCursor(0, 3); 
  lcd.print("20 Characters ;)"); 
}
