#include <Wire.h>
#include <U8g2lib.h>
#include <Preferences.h>

Preferences prefs;

#define BUZZER 1
#define BTN_LEFT 20
#define BTN_RIGHT 21
#define MOTOR 0

#define TYPEFACE u8g2_font_micro_tr

int promptSize = 8;

//const char* promptReflection[10][4] = {
//  {"Name something you've ignored that might matter.", "What makes it easy to ignore?", "What would change if you gave it 10 minutes today?", "How would future-you feel if this stayed ignored?"},
//  {"When did you last feel proud of yourself?", "What made that moment feel meaningful?", "Did anyone witness it, or was it just for you?", "How do you carry that pride now?"},
//  {"When did you last feel misunderstood?", "What did you wish someone had seen in you?", "Did you try to explain, or stay silent?", "What would be different if they had understood you the way you meant?"},
//  {"What's something you're tired of pretending?", "Who do you pretend around most?", "What would happen if you stopped pretending?", "How would that change your relationships?"},
//  {"What are you most grateful for but haven't said out loud?", "Why haven't you expressed it?", "How would it feel to fully acknowledge it to yourself?", "How could fully feeling that gratitude impact you?"},
//  {"Who are you trying to impress lately?", "What do you want them to believe about you?", "Is that belief true for you too?", "How do you feel if they don't see you that way?"},
//  {"When was the last time your mind felt deeply quiet?", "What was your environment like in that moment?", "What thoughts or worries faded away during that time?", "Can you bring a piece of that stillness into today?"},
//  {"What old version of yourself do you miss?", "What made that version feel special?", "What have you gained since then?", "What part of that version could you bring into your life now?"},
//  {"What's something you've forgiven but not forgotten?", "How did forgiveness change you?", "Why does the memory still linger?", "What have you learned from it?"},
//  {"When did you last say yes when you meant no?", "What made you override yourself?", "What did it cost you?", "What would it take to choose differently next time?"}
//};

const char* promptReflection[8][4] = {
  {"Count the colors around you, not the objects, just colors.", "Which color stands out most? Why?", "Rest your eyes on that color for a few seconds. What does your body feel?", "Close your eyes. Do you still feel the presence of that color?"},
  {"Listen for the softest sound you can hear.", "Try to follow the sound for 5 full seconds.", "What is closer: the sound or your breath?", "What disappears when you truly listen?"},
  {"Touch the nearest surface to you. Notice its texture.", "Is it warm, cool, rough, or smooth?", "What part of your hand feels it most clearly?", "Keep your hand there. What else do you notice in your body?"},
  {"Look at the light and shadows in your space.", "What is the sharpest contrast you can see?", "Can you find a spot where shadow fades into light?", "What happens to your body when you look at it gently?"},
  {"Find something still around you.", "How do you know it is still?", "What does your body do when you look at it?", "Can you match that stillness for a moment?"},
  {"Notice three different textures near you.", "Touch them one by one. Which feels most familiar?", "Which one surprised you?", "Which texture made you feel most present?"},
  {"Find a color that feels calming to you right now.", "Keep your gaze there. What softens in you?", "Imagine that color spreading gently in your body.", "What feels different now?"},
  {"Stretch one part of your body gently.", "What sensation shows up first?", "What is different before and after the stretch?", "Where wants to stretch next?"}
};




int currentReflection = 0;
int currentStreak = 0;
int currentStep = -1;
int buttonLeftState;
int buttonRightState;
bool isSleeping = true;
int catAnimFrame = 0;
unsigned long lastCatAnimTime = 0;

bool catState = true;
const unsigned long catAnimIntervalOpen = 3800;
const unsigned long catAnimIntervalClose = 800;

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R2, U8X8_PIN_NONE);

#define cat_width 32
#define cat_height 32

static const unsigned char cat_open_bits[] U8X8_PROGMEM = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x04,0x00,0x00,0x0a,0x0a,0x00,0x00,0xf1,0x11,0x00,0x00,0x51,0x11,0x00,0x80,0x10,0x21,0x00,0x80,0x00,0x20,0x00,0x40,0x00,0x40,0x00,0x40,0x0c,0x46,0x00,0x40,0x04,0x42,0x00,0xf0,0x0c,0xe6,0x01,0x40,0x00,0x40,0x00,0xf0,0x00,0xe0,0x01,0xc0,0x48,0x62,0x00,0x80,0xb0,0x21,0x0c,0x00,0x03,0x18,0x14,0x00,0xfc,0x07,0x24,0x00,0x02,0x08,0x48,0x00,0x01,0x10,0x48,0x80,0x00,0x20,0x48,0x80,0x00,0x20,0x44,0x80,0x00,0x60,0x42,0xc0,0x00,0xc0,0x21,0xa0,0x00,0x40,0x11,0xa0,0x12,0x49,0x09,0xa0,0x12,0x69,0x05,0x20,0x12,0x29,0x05,0x60,0x13,0xd9,0x0d,0xc0,0x11,0xf9,0x03,0xc0,0xff,0xff,0x01
};

static const unsigned char cat_blink_bits[] U8X8_PROGMEM = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x04,0x00,0x00,0x0a,0x0a,0x00,0x00,0xf1,0x11,0x00,0x00,0x51,0x11,0x00,0x80,0x10,0x21,0x00,0x80,0x00,0x20,0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x40,0x00,0xf0,0x00,0xe0,0x01,0x40,0x00,0x40,0x00,0xf0,0x00,0xe0,0x01,0xc0,0x48,0x62,0x00,0x80,0xb0,0x21,0x0c,0x00,0x03,0x18,0x14,0x00,0xfc,0x07,0x24,0x00,0x02,0x08,0x48,0x00,0x01,0x10,0x48,0x80,0x00,0x20,0x48,0x80,0x00,0x20,0x44,0x80,0x00,0x60,0x42,0xc0,0x00,0xc0,0x21,0xa0,0x00,0x40,0x11,0xa0,0x12,0x49,0x09,0xa0,0x12,0x69,0x05,0x20,0x12,0x29,0x05,0x60,0x13,0xd9,0x0d,0xc0,0x11,0xf9,0x03,0xc0,0xff,0xff,0x01
};

void setup() {
  pinMode(MOTOR, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BTN_RIGHT, INPUT);
  pinMode(BTN_LEFT, INPUT);
  prefs.begin("reflect", false);

  prefs.putInt("index", 0);
  currentReflection = prefs.getInt("index", 0);
  
  prefs.putInt("streak", 0);
  currentStreak = prefs.getInt("streak", 0);

  
  u8g2.begin();
  
  lastCatAnimTime = millis();
  catAnimFrame = 0;
}

void splitTextIntoLines(const char* text, char lines[4][21]) {
  int textLen = strlen(text);
  int start = 0;
  int line = 0;

  while (start < textLen && line < 4) {
    int end = start + 20;
    if (end >= textLen) end = textLen;

    int breakAt = -1;
    for (int i = end - 1; i > start; i--) {
      if (text[i] == ' ') {
        breakAt = i;
        break;
      }
    }

    if (breakAt == -1 || end == textLen) breakAt = end;

    int len = breakAt - start;
    if (len > 20) len = 20;

    strncpy(lines[line], text + start, len);
    lines[line][len] = '\0';

    start = (breakAt == end) ? end : breakAt + 1;
    while (text[start] == ' ') start++;  // Skip extra spaces
    line++;
  }

  if (start < textLen && line < 4) {
    strncpy(lines[line], text + start, 20);
    lines[line][20] = '\0';
    line++;
  }

  while (line < 4) {
    lines[line][0] = '\0';
    line++;
  }
}

void createHomeScreen() {
  u8g2.clearBuffer();
  u8g2.setFont(TYPEFACE);
//  char streakText[20];
//  sprintf(streakText, "Streak: %d", currentStreak);
  
  u8g2.drawStr(32, 20, "Meow");
  
  const unsigned char* cat = (catAnimFrame == 0) ? cat_open_bits : cat_blink_bits;
  u8g2.drawXBM((128 - 32) / 2, 12, 32, 32, cat);
  u8g2.drawStr(16, 63, "off");
  u8g2.drawStr(88, 63, "session");
  u8g2.sendBuffer();
}

void createGameMenu() {
  u8g2.setFont(TYPEFACE);
  u8g2.drawStr(12, 58, "<-");
  u8g2.drawStr(114, 58, "->");
  u8g2.setFont(u8g2_font_t0_12_tr);
  u8g2.sendBuffer();
}

void turnOff() {
  isSleeping = true;
  delay(500);
  u8g2.clear();
}

void drawGamePhrase(const char* prompt) {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x12_tr);
  char lines[4][21];
  splitTextIntoLines(prompt, lines);
  for (int i = 0; i < 4; i++) {
    u8g2.drawStr(8, 8 + (i * 12), lines[i]);
  }
  createGameMenu();
  u8g2.sendBuffer();
}

void loop() {
  buttonLeftState = digitalRead(BTN_LEFT);
  buttonRightState = digitalRead(BTN_RIGHT);
  if (isSleeping) {
    if (buttonLeftState == LOW || buttonRightState == LOW) {
      delay(500);
      isSleeping = false;
      currentStep = -1;
      lastCatAnimTime = millis();
      catAnimFrame = 0;
    }
    return;
  }
  if (currentStep == -1) {

    if(catState){
      if (millis() - lastCatAnimTime >= catAnimIntervalOpen) {
        catAnimFrame = 1 - catAnimFrame;
        lastCatAnimTime = millis();
         catState = !catState;
      }
    }
    else{
      if (millis() - lastCatAnimTime >= catAnimIntervalClose) {
        catAnimFrame = 1 - catAnimFrame;
        lastCatAnimTime = millis();
        catState = !catState;
      }      
    }
    
    
    createHomeScreen();
    if (buttonLeftState == LOW) {
      delay(500);
      turnOff();
    }
    if (buttonRightState == LOW) {
      delay(500);
      currentStep = 0;
      drawGamePhrase(promptReflection[currentReflection][currentStep]);
    }
  } else {
    if (buttonLeftState == LOW) {
      delay(500);
      if (currentStep == 0) currentStep = -1;
      else currentStep--;
      drawGamePhrase(promptReflection[currentReflection][currentStep]);
    }
    if (buttonRightState == LOW) {
      delay(500);
      if (currentStep == 3) {
        currentReflection = (currentReflection + 1) % promptSize;
        currentStreak++;
        prefs.putInt("streak", currentStreak);
        prefs.putInt("index", currentReflection);
        currentStep = -1;
      } else {
        currentStep++;
        drawGamePhrase(promptReflection[currentReflection][currentStep]);
      }
    }
  }
}
