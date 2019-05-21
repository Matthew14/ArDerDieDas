#include <U8x8lib.h>
#include <SPI.h>
#include <SD.h>

const byte derPin = 5;
const byte diePin = 6;
const byte dasPin = 7;

const char* derWords[] = {"Hund", "Mann", "Schlussel", "Computer", "Artz", "Fernseher"};
const char* dieWords[] = {"Arbeit", "Frau", "Zeit", "Wohnung", "Mutter"};
const char* dasWords[] = {"Baby", "Auto", "Kind", "Fleisch", "Land", "Kino", "Handy", "Wörterbuch"};

const int noDer = 6;
const int noDie = 5;
const int noDas = 8;

bool needNewWord = true;
char * currentWord="";
byte gender;
byte correctStreak = 0;

U8X8_SSD1306_128X64_NONAME_HW_I2C oled(U8X8_PIN_NONE);

void setup() {
  //Pins
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(dasPin, INPUT);
  pinMode(derPin, INPUT);
  pinMode(diePin, INPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
  //Setup display
  Serial.begin(9600);
  oled.begin();
  oled.setPowerSave(0);
  oled.setFont(u8x8_font_amstrad_cpc_extended_f);
  
  //Seed Random
  randomSeed(analogRead(0));
}

const char* getWordForGender(int gender) {
  Serial.print("getting word for: ");
  Serial.println(gender);
  
  if (gender == 0)
  {
     return derWords[random(noDer)];  
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

void printOnLcd(char * toPrint)
{
    oled.clearDisplay();
    oled.setCursor(2, 0);
    
    oled.print("Streak: ");
    oled.print(correctStreak);
    oled.drawUTF8(2, 4, toPrint);
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
      ++correctStreak;
      delay(1000);
  }
  else if(selectedGender != -1)
  {
      Serial.print("Selected Gender: ");
      Serial.println(selectedGender);
      printOnLcd("Nein");
      correctStreak = 0;
      delay(1000);
      printOnLcd(currentWord);
  }
  
  delay(50);
}
