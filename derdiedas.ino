#include <LiquidCrystal_I2C.h>

const int derPin = 5;
const int diePin = 6;
const int dasPin = 7;

LiquidCrystal_I2C lcd(0x3F, 16, 4);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(dasPin, INPUT);
  digitalWrite(LED_BUILTIN, LOW);

  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Matthew O'Neill");
  lcd.setCursor(0, 2);
  lcd.print("Is the best");
}

void loop() {
  if (digitalRead(dasPin) == HIGH)
    lcd.print("green");
  else if (digitalRead(derPin) == HIGH)
    lcd.print("blue");
  else if (digitalRead(diePin) == HIGH)
    lcd.print("red");
  delay(100);
}
