#include <Adafruit_SSD1306.h>

const int derPin = 5;
const int diePin = 6;
const int dasPin = 7;

const char* derWords[] = {"Hund", "Mann", "Schlussel", "Computer", "Artz", "Fernseher"};
const char* dieWords[] = {"Arbeit", "Frau", "Zeit", "Wohnung", "Mutter"};
const char* dasWords[] = {"Baby", "Auto", "Kind", "Fleisch", "Land", "Kino", "Handy"};//, "Wörterbuch"};

int noDer = 6;
int noDie = 5;
int noDas = 7;

bool needNewWord = true;
char * currentWord="";
int gender;

Adafruit_SSD1306 display(4);

void setup() {
  //Pins
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(dasPin, INPUT);
  pinMode(derPin, INPUT);
  pinMode(diePin, INPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
  //Setup display
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.display();
  delay(2000);
  
  //Seed Random
  randomSeed(analogRead(0));
}

const char* getWordForGender(int gender) {
  Serial.print(noDer);
  Serial.print("getting word for: ");

  Serial.println(gender);
  
  if (gender == 0)
  {
     int r = random(noDer);
    
     
     Serial.print(r);
     return derWords[r];  
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
    display.clearDisplay();
    display.setCursor(20, 30);
    display.print(toPrint);
    display.display();
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

