/*
  Morse Out
  Display some morse output on the built-in LED
 
*/
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
static int LED = 13;
static int SOUND_OUT = 9;
static int SPEED = 75; // in milliseconds
static int SHORT = SPEED;
static int LONG = SPEED * 3;
static int LETTER_SPACE = SPEED * 3;
static int WORD_SPACE = SPEED * 7;

static char DOT = '.';
static char DASH = '-';
static char SPACE_CHAR = ' ';
static char EOC = '$';
static char EOS = '\0';
static char char_a[4] = {'.','-',EOC,EOS};
static char char_b[6] = {'-','.','.','.',EOC,EOS};
static char char_c[6] = {'-','.','-','.',EOC,EOS};
static char char_d[5] = {'-','.','.',EOC,EOS};
static char char_e[3] = {'.',EOC,EOS};
static char char_f[6] = {'.','.','-','.',EOC,EOS};
static char char_g[5] = {'-','-','.',EOC,EOS};
static char char_h[6] = {'.','.','.','.',EOC,EOS};
static char char_i[4] = {'.','.',EOC,EOS};
static char char_j[6] = {'.','-','-','-',EOC,EOS};
static char char_k[5] = {'-','.','-',EOC,EOS};
static char char_l[6] = {'.','-','.','.',EOC,EOS};
static char char_m[4] = {'-','-',EOC,EOS};
static char char_n[4] = {'-','.',EOC,EOS};
static char char_o[5] = {'-','-','-',EOC,EOS};
static char char_p[6] = {'.','-','-','.',EOC,EOS};
static char char_q[6] = {'-','-','.','-',EOC,EOS};
static char char_r[5] = {'.','-','.',EOC,EOS};
static char char_s[5] = {'.','.','.',EOC,EOS};
static char char_t[3] = {'-',EOC,EOS};
static char char_u[5] = {'.','.','-',EOC,EOS};
static char char_v[6] = {'.','.','.','-',EOC,EOS};
static char char_w[5] = {'.','-','-',EOC,EOS};
static char char_x[6] = {'-','.','.','-',EOC,EOS};
static char char_y[6] = {'-','.','-','-',EOC,EOS};
static char char_z[6] = {'-','-','.','.',EOC,EOS};

static char char_0[7] = {'-','-','-','-','-',EOC,EOS};
static char char_1[7] = {'.','-','-','-','-',EOC,EOS};
static char char_2[7] = {'.','.','-','-','-',EOC,EOS};
static char char_3[7] = {'.','.','.','-','-',EOC,EOS};
static char char_4[7] = {'.','.','.','.','-',EOC,EOS};
static char char_5[7] = {'.','-','-','-','-',EOC,EOS};
static char char_6[7] = {'-','.','.','.','.',EOC,EOS};
static char char_7[7] = {'-','-','.','.','.',EOC,EOS};
static char char_8[7] = {'-','-','-','.','.',EOC,EOS};
static char char_9[7] = {'-','-','-','-','.',EOC,EOS};

static char SPACE[3]  = {' ',EOC,EOS};
static char PERIOD[8]  = {'.','-','.','-','.','-',EOC,EOS};
static char ILLEGAL_CHARACTER[1]  = {EOS};

static char* letters[26] = {
  char_a,
  char_b,
  char_c,
  char_d,
  char_e,
  char_f,
  char_g,
  char_h,
  char_i,
  char_j,
  char_k,
  char_l,
  char_m,
  char_n,
  char_o,
  char_p,
  char_q,
  char_r,
  char_s,
  char_t,
  char_u,
  char_v,
  char_w,
  char_x,
  char_y,
  char_z,
};

static char* numbers[10] = {
  char_0,
  char_1,
  char_2,
  char_3,
  char_4,
  char_5,
  char_6,
  char_7,
  char_8,
  char_9,
};

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(LED, OUTPUT); 
  pinMode(SOUND_OUT, OUTPUT);  
}

// the loop routine runs over and over again forever:
void loop() {
//  fast_blink();
  read_string("sos morse code ftw \0");
  read_string("cqd cqd cqd cqd cqd cqd de mgy de mgy de mgy de mgy de mgy de mgy position 41.44n. 50.24w\0");
  read_string("come at once. we have hit a berg. \0");
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
  } else if (ch == '.') {
    return PERIOD;
  } else if (ch == SPACE_CHAR) {
    return SPACE;
  }
  else return ILLEGAL_CHARACTER;
}


void show(char* letter) {
   for (int i = 0; letter[i] != EOS; i++) {
     if (letter[i] == DOT) dot();
     else if (letter[i] == DASH) dash();
     else if (letter[i] == EOC) end_of_character();
     else if (letter[i] == SPACE_CHAR) pause();
   }
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
