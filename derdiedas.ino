#include <LiquidCrystal_I2C.h>

const int derPin = 5;
const int diePin = 6;
const int dasPin = 7;

const char* derWords[] = {"Hund", "Mann", "Schlussel"};
const char* dieWords[] = {"Arbeit", "Frau", "Zeit", "Wohnung"};
const char* dasWords[] = {"Baby", "Auto", "Kind", "Fleisch"};

bool needNewWord = true;

LiquidCrystal_I2C lcd(0x3F, 16, 4);


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(dasPin, INPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
}


const char * getWordForGender(int gender) {

  const char** words = dieWords;

  if (gender != 2)
    words = gender ? dasWords : dasWords;

  int numberOfWords = sizeof(words);

  Serial.println(numberOfWords);

  return words[random(numberOfWords)];
}

void loop() {

  int gender = random(3);

  if (needNewWord) {
    const char * w = getWordForGender(gender);
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print(w);
    needNewWord = false; 
  }

  if (digitalRead(dasPin) == HIGH)
    lcd.print("green");
  else if (digitalRead(derPin) == HIGH)
    lcd.print("blue");
  else if (digitalRead(diePin) == HIGH)
    lcd.print("red");
  delay(3000);
}
