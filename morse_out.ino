/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
static int LED = 13;
static char DOT = '.';
static char DASH = '-';
static char EOC = '$';
static char char_a[3] = {'.','-',EOC};
static char char_m[3] = {'-','-',EOC};
static char char_o[4] = {'-','-','-',EOC};
static char char_s[4] = {'.','.','.',EOC};

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(LED, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
//  fast_blink();
  s();
  o();
  s();
  pause();
  show(char_a);
}

void show(char* letter) {
   for (int i = 0; letter[i] != EOC; i++) {
     if (letter[i] == DOT) dot();
     else if (letter[i] == DASH) dash();
   }
   end_of_character();
}

void o() {
  show(char_o);
//  dash();
//  dash();
//  dash();
//  end_of_character();
}

void s() {
  dot();
  dot();
  dot();
  end_of_character();
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
  delay(on);
  digitalWrite(LED, LOW);
  delay(off);
}
