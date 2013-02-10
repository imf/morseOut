/*
  Morse Out
 Display some morse output on the built-in LED
 Pin 9 (SOUNT_OUT) provides a line-level (but LOUD) output to emit a 1K tone matching the dots and dashes
 
 */

const int SOUND_OUT = 9;
const int LED = 13;

static int SPEED = 75; // in milliseconds. 40ms is about the fastest where the tones are distinct. 50 is very fast. 75 is reasonable. 100 might be good for learning.
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
}

void loop() {
  read_string("sos morse code ftw ");
  read_string("morse code is cool. #");
  read_string("cqd cqd cqd cqd cqd cqd de mgy mgy mgy mgy mgy mgy position 41.44n. 50.24w  ");
  read_string("come at once. we have hit a berg. ");
  read_string("#");
}


void read_string(char* input) {
  for (int i = 0; input[i] != EOS; i++) {
    show(get_char(input[i]));
  }
}


char* get_char(char ch) {
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
    else if (letter[i] == EOC) end_of_character();
    else if (letter[i] == SPACE_CHAR) {
      pause();
      return;
    }
  }
  end_of_character();
}

void dot() {
  blink(SHORT, SHORT);
}

void dash() {
  blink(LONG,SHORT);
}

void end_of_character() {
  delay(LETTER_SPACE);
}

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

void fast_blink() {
  blink(750, 250);               // wait for a second  
}

  
void blink(int on, int off) {
  blink(on, off, FREQUENCY);
}

void blink(int on, int off, int frequency) {
  digitalWrite(LED, HIGH);
  emit_tone(on, frequency);
  digitalWrite(LED, LOW);
  delay(off);
}

void emit_tone(int duration, int frequency) { // Emit 1K tone on pin SOUND_OUT
  for (int i = 0; i < duration; i++) {
    digitalWrite(SOUND_OUT, HIGH);
    delayMicroseconds(frequency / 2);
    digitalWrite(SOUND_OUT, LOW);
    delayMicroseconds(frequency / 2);
  }
}

