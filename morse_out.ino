/*
  Morse Out
  Display some morse output on the built-in LED
 
*/
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
static int LED = 13;
static int SOUND_OUT = 9;

static char DOT = '.';
static char DASH = '-';
static char SPACE = ' ';
static char EOC = '$';
static char EOS = '\0';
static char char_a[4] = {'.','-',EOC,EOS};
static char char_c[6] = {'-','.','-','.',EOC,EOS};
static char char_d[5] = {'-','.','.',EOC,EOS};
static char char_e[3] = {'.',EOC,EOS};
static char char_f[6] = {'.','.','-','.',EOC,EOS};
static char char_m[4] = {'-','-',EOC,EOS};
static char char_o[5] = {'-','-','-',EOC,EOS};
static char char_r[5] = {'.','-','.',EOC,EOS};
static char char_s[5] = {'.','.','.',EOC,EOS};
static char char_t[3] = {'-',EOC,EOS};
static char char_w[5] = {'.','-','-',EOC,EOS};

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(LED, OUTPUT); 
  pinMode(SOUNT_OUT, OUTPUT);  
}

// the loop routine runs over and over again forever:
void loop() {
//  fast_blink();
  s();
  o();
  s();
  pause();
//  show(char_a);
//  pause();
  show(char_m);
  show(char_o);
  show(char_r);
  show(char_s);
  show(char_e);
  pause();
  show(char_c);
  show(char_o);
  show(char_d);
  show(char_e);
  pause();
  show(char_f);
  show(char_t);
  show(char_w);
  pause();
}

void show(char* letter) {
   for (int i = 0; letter[i] != EOS; i++) {
     if (letter[i] == DOT) dot();
     else if (letter[i] == DASH) dash();
     else if (letter[i] == EOC) end_of_character();
     else if (letter[i] == SPACE) pause();
   }
}

void o() {
  show(char_o);
//  dash();
//  dash();
//  dash();
//  end_of_character();
}

void s() {
  show(char_s);
//  dot();
//  dot();
//  dot();
//  end_of_character();
}

void dot() {
  blink(100, 100);
}

void dash() {
  blink(400,100);
}

void end_of_character() {
  delay(500);
}

void pause() {
  delay(2000);
}

void banner() {
    for (int i = 0; i < 10; i++) {
    blink(100, 100);
  }
  pause();
}

void fast_blink() {
  blink(750, 250);               // wait for a second  
}

void blink(int on, int off) {
  digitalWrite(LED, HIGH);
  emit_tone(on);
  digitalWrite(LED, LOW);
  delay(off);
}

void emit_tone(int duration) { // Emit 1K tone on pin SOUND_OUT
  for (int i = 0; i < duration; i++) {
    digitalWrite(SOUND_OUT, HIGH);
    delayMicroseconds(500);
    digitalWrite(SOUND_OUT, LOW);
    delayMicroseconds(500);
  }
}
