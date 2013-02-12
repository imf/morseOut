/*
  Morse Out
 Display some morse output on the built-in LED
 Pin 2 (SOUNT_OUT) provides a line-level (but LOUD) output to emit a 1K tone matching the dots and dashes
 
 Uses LCD to display the message as well.
 
 */
 
 #include <LiquidCrystal.h>


const int SOUND_OUT = 2;
const int LED = 13;

LiquidCrystal lcd(7, 8, 9, 10, 11, 12); 

static int SPEED = 60; // in milliseconds. 40ms is about the fastest where the tones are distinct. 50 is very fast. 75 is reasonable. 100 might be good for learning.
static int SHORT = SPEED;
static int LONG = SPEED * 3;
static int LETTER_SPACE = SPEED * 3;
static int WORD_SPACE = SPEED * 7;

const int FREQ_1K = 1000;
static int FREQUENCY = FREQ_1K;
static int ERROR_FREQUENCY = 500;

static char DOT = '.';
static char DASH = '-';
static char SPACE_CHAR = ' ';
static char EOC = '$';
static char EOS = '\0';

static char* letters[26] = {
  ".-",
  "-...",
  "-.-.",
  "-..",
  ".",
  "..-.",
  "--.",
  "....",
  "..",
  ".---",
  "-.-",
  ".-..",
  "--",
  "-.",
  "---",
  ".--.",
  "--.-",
  ".-.",
  "...",
  "-",
  "..-",
  "...-",
  ".--",
  "-..-",
  "-.--",
  "--.."
};

static char* numbers[10] = {
  "-----",
  ".----",
  "..---",
  "...--",
  "....-",
  ".----",
  "-....",
  "--...",
  "---..",
  "----.",
};

static char* SPACE             = " ";
static char* PERIOD            = ".-.-.-";
static char* QUESTION_MARK     = "--..--";
static char* EXCLAMATION_POINT = "..--.";
static char* COLON             = "---...";
static char* SINGLE_QUOTE      = ".----.";
static char* DOUBLE_QUOTE      = ".-..-.";
static char* EQUALS_SIGN       = "-...-";
static char ILLEGAL_CHARACTER[1] = {EOS};


void setup() {                
  pinMode(LED, OUTPUT); 
  pinMode(SOUND_OUT, OUTPUT);  
  lcd.begin(16, 2);
  lcd.print("MorseOut LCD");
  delay(3000);
}

void loop() {
  readString("sos morse code ftw ");
  readString("morse code is cool. \t");
  readString("cqd cqd cqd cqd cqd cqd de mgy mgy mgy mgy mgy mgy position 41.44n. 50.24w  ");
  readString("come at once. we have hit a berg. ");
  readString("\t");  
  readString("the quick brown fox jumps over the lazy dogs.");
  readString("\t");
}


void readString(char* input) {
  for (int i = 0; input[i] != EOS; i++) {
    char* myChar = getChar(input[i]);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(myChar);
    lcd.setCursor(0,1);
    lcd.print(input[i]);
    show(myChar);
  }
}


char* getChar(char ch) {
   if (ch >= 'a' && ch <= 'z') {
     return letters[ch - 'a'];
   } else if (ch >= '0' && ch <= '9') {
     return numbers[ch - '0'];
   } else  switch (ch) {
    case '.':
      return PERIOD;
    case ' ':
      return SPACE;
    case '?':
      return QUESTION_MARK;
    case '!':
      return EXCLAMATION_POINT;
    case ':':
      return COLON;
    case '\'':
      return SINGLE_QUOTE;
    case '"':
      return DOUBLE_QUOTE;
    case '=':
      return EQUALS_SIGN;
    default:
      error();
      return ILLEGAL_CHARACTER;
  }
}

void show(char* letter) {
  for (int i = 0; letter[i] != EOS; i++) {
    if (letter[i] == DOT) dot();
    else if (letter[i] == DASH) dash();
    else if (letter[i] == EOC) endOfCharacter();
    else if (letter[i] == SPACE_CHAR) {
      pause();
      return;
    }
  }
  endOfCharacter();
}

void dot() {
  blink(SHORT, SHORT);
}

void dash() {
  blink(LONG,SHORT);
}

void endOfCharacter() {
  delay(LETTER_SPACE);
}
s
void pause() {
  delay(WORD_SPACE);
}

void banner() {
  for (int i = 0; i < 10; i++) {
    blink(100, 100);
  }
  pause();
}

void error() {
  for (int i = 0; i < 20; i++) {
    blink(50, 50, ERROR_FREQUENCY);
  }
}

void blink(int on, int off) {
  blink(on, off, FREQUENCY);
}

void blink(int on, int off, int frequency) {
  digitalWrite(LED, HIGH);
  emitTone(on, frequency);
  digitalWrite(LED, LOW);
  delay(off);
}

void emitTone(int duration, int frequency) { // Emit 1K tone on pin SOUND_OUT
  for (int i = 0; i < duration; i++) {
    digitalWrite(SOUND_OUT, HIGH);
    delayMicroseconds(frequency / 2);
    digitalWrite(SOUND_OUT, LOW);
    delayMicroseconds(frequency / 2);
  }
}

