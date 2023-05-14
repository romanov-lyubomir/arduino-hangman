#include <LiquidCrystal.h>
#include <Keypad.h>


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//define the symbols on the buttons of the keypad
const byte ROWS = 4; //define the number of rows on the keypad
const byte COLS = 4; //define the number of columns on the keypad

char keys1[ROWS][COLS] = {
  {'a','b','c','d'},
  {'e','f','g','h'},
  {'i','j','k','l'},
  {'m','n','o','p'}
};
char keys2[ROWS][COLS] = {
  {'q','r','s','t'},
  {'u','v','w','x'},
  {'y','z','9','C'},
  {'*','0','#','D'}
};


byte rowPins1[ROWS] = { 22, 23, 24, 25 };
byte colPins1[COLS] = { 26, 27, 28, 29 };

byte rowPins2[ROWS] = { 32, 33, 34, 35 };
byte colPins2[COLS] = { 36, 37, 38, 39 };

Keypad keypad1 = Keypad(makeKeymap(keys1), rowPins1, colPins1, ROWS, COLS);
Keypad keypad2 = Keypad(makeKeymap(keys2), rowPins2, colPins2, ROWS, COLS);



String words[60] = {
  "abrogation", "benevolence", "capitulate", "deleterious", "efficacious", "fictitious", 
  "garrulity", "hypothesis", "indefatigable", "juxtaposition", "kleptomaniac", "libertarian",
  "mendacious", "neologistic", "obfuscation", "perpetuity", "quintessence", "resplendent", 
  "supercilious", "translucent", "undulating", "verisimilitude", "welterweight", "xenophobic", 
  "yeomanry", "zeitgeist", "abnegation", "bellicosity", "cacophony", "deprecating",
  "egalitarian", "facetiously", "gallivanting", "histrionic", "incredulous", "jamboree", "kamikaze",
  "luminescent", "megalomaniac", "nefariousness", "obsequious", "panacea", "quizzical",
  "reverberate", "surreptitious", "tantalizing", "unambiguous", "vacillate", "wanton", "xylophone",
  "yesteryear", "zephyr", "acquiesce", "belligerent", "chicanery", "demagogue", "ephemeral",
  "fallacious", "gregarious", "hierarchy"
};
int lives = 20;
String currentWord = words[random(60)];
String wordStructure = String(currentWord[0]) + "________" +  String(currentWord[currentWord.length() - 1]);
void setup() {
  lcd.print(currentWord);
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);
  lcd.print("   Guess the word   ");
  lcd.setCursor(0, 1);
  lcd.print("     " + wordStructure + "     ");
  lcd.setCursor(0, 2);
  lcd.print(" Lives remaining: " + String(lives) + " ");
  lcd.setCursor(0, 3);
}

void loop() {
  char key1 = keypad1.getKey();
  char key2 = keypad2.getKey();
  char pressedKey = '-';
  if (key1 == NO_KEY && key2 != NO_KEY) {
    pressedKey = key2;
  }
  if (key1 != NO_KEY && key2 == NO_KEY) {
    pressedKey = key1;
  }

  if (pressedKey != '-') {
    for(int i = 0; i < currentWord.length(); i++){
      if (currentWord[i] == pressedKey) {
        wordStructure[i] = pressedKey;
        lcd.setCursor(0, 1);
        lcd.print("     " + wordStructure + "     ");
      }
    }
    if (currentWord.indexOf(pressedKey) == -1) {
      lives--;
      lcd.setCursor(0, 2);
      lcd.print(" Lives remaining: " + String(lives) + " ");
      lcd.print(pressedKey);
    }
  }
}