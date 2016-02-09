#include <LiquidCrystal.h> //Dołączenie bilbioteki
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //Informacja o podłączeniu nowego wyświetlacza

void setup() {
  lcd.begin(16, 2); //Deklaracja typu
  lcd.setCursor(0, 0); //Ustawienie kursora
  lcd.print("Kurs Arduino"); //Wyświetlenie tekstu
  lcd.setCursor(0, 1); //Ustawienie kursora
  lcd.print("Na Forbocie!"); //Wyświetlenie tekstu
}

void loop() {
}
