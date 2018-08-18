#include <LiquidCrystal_I2C.h>

const int derPin = 5;
const int diePin = 6;
const int dasPin = 7;

const String derWords[] = {"Hund", "Mann", "Schlussel", "Computer", "Artz"};
const String dieWords[] = {"Arbeit", "Frau", "Zeit", "Wohnung"};
const String dasWords[] = {"Baby", "Auto", "Kind", "Fleisch", "Land", "Kino", "Handy"};//, "Wörterbuch"};
int noDer = sizeof(derWords);
int noDie = sizeof(dieWords);
int noDas = sizeof(dasWords);

bool needNewWord = true;
String currentWord="";
int gender;

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

const String getWordForGender(int gender) {

  Serial.print("getting word for: ");

  Serial.println(gender);
  
  if (gender == 0)
  {
      derWords[random(noDer)];  
  }
  else if (gender == 1)
  {
    return dieWords[random(noDie)];
  }
  else if (gender == 2)
  {
    return dasWords[random(noDas)];
  }

  
}

void printOnLcd(String toPrint)
{
    lcd.clear();
    lcd.setCursor(3, 1);
    lcd.print(toPrint);
  
}


void loop() {

  if (needNewWord) {
    gender = random(3);   
    Serial.print("Random gender is: ");  
    Serial.println(gender);     
    currentWord = getWordForGender(gender);
    Serial.print("the word is: ");
    Serial.println(currentWord);
    printOnLcd(currentWord);
    needNewWord = false;
  }
  int selectedGender = -1;
  if (digitalRead(derPin) == HIGH)
    selectedGender = 0;
  else if (digitalRead(diePin) == HIGH)
    selectedGender = 1;
  else if (digitalRead(dasPin) == HIGH)
    selectedGender = 2;

  if(selectedGender == gender)
  {
      printOnLcd("Richtig!");
      needNewWord = true;
      delay(1000);
  }
  else if(selectedGender != -1)
  {
      printOnLcd("Nein");
      delay(1000);
      printOnLcd(currentWord);
  }
  
  delay(50);
}

