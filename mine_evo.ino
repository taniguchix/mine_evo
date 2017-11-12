// mine evolutions
// taniguchi kotaro
// https://www.youtube.com/channel/UCBqoH73F31mbhyLkG3wj1HA

#include <EEPROM.h>
#include <Arduboy2.h>
#include <ArduboyPlaytune.h>

Arduboy2 display;
ArduboyPlaytune tunes(display.audio.enabled);

void setup() {
  display.begin();

  // audio setup
  tunes.initChannel(PIN_SPEAKER_1);
#ifndef AB_DEVKIT
  // if not a DevKit
  tunes.initChannel(PIN_SPEAKER_2);
#else
  // if it's a DevKit
  tunes.initChannel(PIN_SPEAKER_1); // use the same pin for both channels
  tunes.toneMutesScore(true);       // mute the score when a tone is sounding
#endif
}

#define EEPROM_SCORES EEPROM_STORAGE_SPACE_START

#define ONPU_HI_16    0
#define ONPU_LO_16   64
#define ONPU_HI_8     0
#define ONPU_LO_8   128
#define ONPU_HI_53    0
#define ONPU_LO_53  192
#define ONPU_HI_4     1
#define ONPU_LO_4     0
#define ONPU_HI_26    1
#define ONPU_LO_26  128
#define ONPU_HI_2     2
#define ONPU_LO_2     0
#define ONPU_HI_1     4
#define ONPU_LO_1     0

// 8*8
PROGMEM const unsigned char bitmap_panel [][8] = {
{ // panel
  0b11111110,
  0b11111110,
  0b11111110,
  0b11111110,
  0b11111110,
  0b11111110,
  0b11111110,
  0b00000000,
},
{ // panel_flag
  0b11111110,
  0b10000010,
  0b11000110,
  0b11100110,
  0b11100110,
  0b11110110,
  0b11111110,
  0b00000000,
},
{ // panel_hatena
  0b11111110,
  0b11110110,
  0b11111010,
  0b10101010,
  0b11101010,
  0b11110110,
  0b11111110,
  0b00000000,
},
};

PROGMEM const unsigned char bitmap_panel_miss [] = {
  0b10000010,
  0b01000100,
  0b00101000,
  0b00010000,
  0b00101000,
  0b01000100,
  0b10000010,
  0b00000000,
};

#define BITMAP_BASE_YEN 12

// 8*8
PROGMEM const unsigned char bitmap_base [][8] = {
{ // base
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
},
{ // base_1
  0b00000000,
  0b00000000,
  0b10000100,
  0b11111110,
  0b10000000,
  0b00000000,
  0b00000000,
  0b00000000,
},
{ // base_2
  0b00000000,
  0b11100100,
  0b10010010,
  0b10010010,
  0b10010010,
  0b10001100,
  0b00000000,
  0b00000000,
},
{ // base_3
  0b00000000,
  0b01000010,
  0b10000010,
  0b10010010,
  0b10011010,
  0b01100110,
  0b00000000,
  0b00000000,
},
{ // base_4
  0b00000000,
  0b00110000,
  0b00101000,
  0b00100100,
  0b11111110,
  0b00100000,
  0b00000000,
  0b00000000,
},
{ // base_5
  0b00000000,
  0b01001110,
  0b10001010,
  0b10001010,
  0b10001010,
  0b01110010,
  0b00000000,
  0b00000000,
},
{ // base_6
  0b00000000,
  0b01111000,
  0b10010100,
  0b10010010,
  0b10010010,
  0b01100010,
  0b00000000,
  0b00000000,
},
{ // base_7
  0b00000000,
  0b10000010,
  0b01000010,
  0b00100010,
  0b00010010,
  0b00001110,
  0b00000000,
  0b00000000,
},
{ // base_8
  0b00000000,
  0b01101100,
  0b10010010,
  0b10010010,
  0b10010010,
  0b01101100,
  0b00000000,
  0b00000000,
},
{ // base_9
  0b00000000,
  0b10001100,
  0b10010010,
  0b10010010,
  0b01010010,
  0b00111100,
  0b00000000,
  0b00000000,
},
{ // base_10
  0b00000000,
  0b11111110,
  0b00000000,
  0b01111100,
  0b10000010,
  0b01111100,
  0b00000000,
  0b00000000,
},
{ // base_11
  0b00000000,
  0b00000010,
  0b11111110,
  0b00000000,
  0b00000010,
  0b11111110,
  0b00000000,
  0b00000000,
},
{ // base_yen
  0b00000000,
  0b11111110,
  0b00010010,
  0b00011110,
  0b10010010,
  0b11111110,
  0b00000000,
  0b00000000,
},
#if 0
{ // base_12
  0b00000000,
  0b11111110,
  0b00000000,
  0b11100100,
  0b10010010,
  0b10001100,
  0b00000000,
  0b00000000,
},
{ // base_13
  0b00000000,
  0b11111110,
  0b00000000,
  0b01010010,
  0b10011010,
  0b01100110,
  0b00000000,
  0b00000000,
},
{ // base_14
  0b00000000,
  0b11111110,
  0b00000000,
  0b00110000,
  0b00101000,
  0b11111110,
  0b00000000,
  0b00000000,
},
{ // base_15
  0b00000000,
  0b11111110,
  0b00000000,
  0b01001110,
  0b10001010,
  0b01110010,
  0b00000000,
  0b00000000,
},
{ // base_16
  0b00000000,
  0b11111110,
  0b00000000,
  0b01111000,
  0b10010100,
  0b01100010,
  0b00000000,
  0b00000000,
},
#endif
};

// 8*8
PROGMEM const unsigned char bitmap_mine [][8] = {
{ // base_mine1
  0b00010000,
  0b00010000,
  0b00111000,
  0b11111110,
  0b00111000,
  0b00010000,
  0b00010000,
  0b00000000,
},
{ // base_mine2
  0b00001000,
  0b00001000,
  0b00111110,
  0b00101000,
  0b11111000,
  0b00100000,
  0b00100000,
  0b00000000,
},
};

// 8*8
PROGMEM const unsigned char smiles [][8] = {
{ // smile_1
  0b00111100,
  0b01101110,
  0b11011011,
  0b11011111,
  0b11011111,
  0b11011011,
  0b01101110,
  0b00111100,
},
{ // smile_2
  0b00111100,
  0b01111110,
  0b10001011,
  0b10101111,
  0b10101111,
  0b10001011,
  0b01111110,
  0b00111100,
},
{ // smile_3
  0b00110100,
  0b01110010,
  0b11010011,
  0b11011011,
  0b11011011,
  0b11010011,
  0b01110010,
  0b00110100,
},
{ // smile_4
  0b00111100,
  0b01101010,
  0b11110111,
  0b11011111,
  0b11011111,
  0b11110111,
  0b01101010,
  0b00111100,
},
};


// 8*8
PROGMEM const unsigned char bitmap_mine4 [][8] = {
{ // base_mine4
  0b10000000,
  0b10000000,
  0b10000000,
  0b11000000,
  0b11100000,
  0b11110000,
  0b11111110,
  0b00000000,
},
{ // base
  0b00000010,
  0b00000010,
  0b00000010,
  0b00000110,
  0b00001110,
  0b00011110,
  0b11111110,
  0b00000000,
},
{ // base
  0b11111110,
  0b11110000,
  0b11100000,
  0b11000000,
  0b10000000,
  0b10000000,
  0b10000000,
  0b00000000,
},
{ // base
  0b11111110,
  0b00011110,
  0b00001110,
  0b00000110,
  0b00000010,
  0b00000010,
  0b00000010,
  0b00000000,
},
};

PROGMEM const unsigned char count_no [][4] = {
{ // count_0
  0b10000001,
  0b10111101,
  0b10000001,
  0b11111111,
},
{ // count_1
  0b11111111,
  0b11111111,
  0b10000001,
  0b11111111,
},
{ // count_2
  0b10000101,
  0b10110101,
  0b10110001,
  0b11111111,
},
{ // count_3
  0b10110101,
  0b10110101,
  0b10000001,
  0b11111111,
},
{ // count_4
  0b11110001,
  0b11110111,
  0b10000001,
  0b11111111,
},
{ // count_5
  0b10110001,
  0b10110101,
  0b10000101,
  0b11111111,
},
{ // count_6
  0b10000001,
  0b10110101,
  0b10000101,
  0b11111111,
},
{ // count_7
  0b11110001,
  0b11111101,
  0b10000001,
  0b11111111,
},
{ // count_8
  0b10000001,
  0b10110101,
  0b10000001,
  0b11111111,
},
{ // count_9
  0b10110001,
  0b10110101,
  0b10000001,
  0b11111111,
},
};

PROGMEM const unsigned char count_start [1] = {
 // count_end
  0b11111111,
};
PROGMEM const unsigned char count_end [][5] = {
{ // count_0
  0b11111111,
  0b10000001,
  0b10111101,
  0b10000001,
  0b11111111,
},
{ // count_end
  0b11111111,
  0b11110111,
  0b11110111,
  0b11110111,
  0b11111111,
},
};

PROGMEM const unsigned char cursol [] = {
  0b11000110,
  0b10000010,
  0b00000000,
  0b00000000,
  0b00000000,
  0b10000010,
  0b11000110,
  0b00000000,
};
PROGMEM const unsigned char menu_cursol [] = {
  0b00111110,
  0b00011100,
  0b00001000,
};




// 8*8
PROGMEM const unsigned char bitmap_omikujis [][8] = {
{ // omikuji
  0b00000100,
  0b00000100,
  0b00000100,
  0b00000100,
  0b00000100,
  0b00000100,
  0b00000100,
  0b00000100,
},
{ // omikuji
  0b00000100,
  0b11000100,
  0b01110100,
  0b00011110,
  0b00001110,
  0b00011100,
  0b00110100,
  0b11000100,
},
};
// 33*8
PROGMEM const unsigned char omikuji_title [] = {
  0b00000000,
  0b00000010,
  0b01111110,
  0b00001010,
  0b00001110,
  0b00001010,
  0b01111110,
  0b00000010,
  0b00000000,
  0b01110100,
  0b01010100,
  0b01111110,
  0b00010100,
  0b01110010,
  0b00000000,
  0b01110010,
  0b01010010,
  0b01111110,
  0b00010000,
  0b01111000,
  0b00000000,
  0b00000000,
  0b00011000,
  0b00100100,
  0b01000010,
  0b00000000,
  0b00000000,
  0b00111110,
  0b01000000,
  0b01000100,
  0b00100000,
  0b00000100,
  0b00000000,
};

byte map_omikuji [][16] {
{ // 吉
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b11101010,
  0b10101010,
  0b10101111,
  0b10101010,
  0b11101010,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
},
{ // 末吉
  0b00000000,
  0b00000000,
  0b01001010,
  0b00101010,
  0b11111111,
  0b00101010,
  0b01001010,
  0b00000000,
  0b11101010,
  0b10101010,
  0b10101111,
  0b10101010,
  0b11101010,
  0b00000000,
  0b00000000,
  0b00000000,
},
{ // 大吉
  0b00000000,
  0b00000000,
  0b00000000,
  0b10000100,
  0b01100100,
  0b00011111,
  0b01100100,
  0b10000100,
  0b00000000,
  0b11101010,
  0b10101010,
  0b10101111,
  0b10101010,
  0b11101010,
  0b00000000,
  0b00000000,
},
{ // 凶
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b11111100,
  0b10000000,
  0b10010100,
  0b10001000,
  0b10010100,
  0b10100010,
  0b10000000,
  0b11111100,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
},
};

PROGMEM const byte saruoto_11 [] = {
0x90,74, ONPU_HI_8, ONPU_LO_8,
0x90,79, ONPU_HI_4, ONPU_LO_4,
0x90,76, ONPU_HI_8, ONPU_LO_8,
0x90,78, ONPU_HI_53, ONPU_LO_53,
0x90,74, ONPU_HI_53, ONPU_LO_53,
0x90,81, ONPU_HI_8, ONPU_LO_8,
0x90,79, ONPU_HI_1, ONPU_LO_1,
0x80,0xf0
};

enum game_state {
  state_menu,
  state_help,
  state_high_score,
  state_omikuji_bef,
  state_omikuji,
  state_omikuji2,
  state_omikuji_aft,
  state_omikuji_aft2,
  state_game_bef,
  state_game,
  state_game_aft,
};
enum game_state state = state_menu;

int count = 0;
bool now_push = false;
bool now_push_a = false;
bool now_push_b = false;

struct {
  unsigned int open  : 1;
  unsigned int push  : 1;
  unsigned int panel : 2;
  unsigned int mine  : 2;
  unsigned int mine4 : 3;
  unsigned int base  : 4;
} map_flags[16][8] = {0};  // [x][y]

bool game_over = false;
int game_over_x=0;
int game_over_y=0;
bool open_update = false;
bool clear_flag = false;
bool game_start = false;

int base_no=0;
int count_time=0;
int count_flags=20;
int count_mine=0;

const struct {
  int mine;
  int x_min;
  int x_max;
  int y_min;
  int y_max;
  int smile_offset;
} initvalue[] = {
{  9, 4, 11, 0, 7, 100},
{ 18, 0, 15, 1, 7,  60},
{ 18, 0, 15, 1, 7,  60},
};

byte map_musubi [16] = {0};

int omikuji_kekka=0;

int level = 0;
bool sound = true;
bool hatena = true;

bool hi_score_update = false;
bool get_yen = false;
int menu_select = 0;
int yen_x=0;
int yen_y=0;

unsigned int money_yen = 0;
unsigned int hi_score[3] = {0};

int help_count=0;

int cur_x=8;
int cur_y=4;

unsigned long currTime;
unsigned long prevTime = 0;
#define FPSDELAY      1000/30

void loop() {

  bool data_reset = false;

  for (int i = 0; i < 3; i++) {
    hi_score[i] = EEPROM.read(i*2+EEPROM_SCORES);
    hi_score[i] <<= 8;
    hi_score[i] += EEPROM.read(i*2+1+EEPROM_SCORES);
  }
  money_yen = EEPROM.read(3*2+EEPROM_SCORES);
  money_yen <<= 8;
  money_yen += EEPROM.read(3*2+1+EEPROM_SCORES);
  for (int i = 0; i < 16; i++) {
    map_musubi[i] = EEPROM.read(4*2+i+EEPROM_SCORES);
    if (map_musubi[i] & 0x0F) {
      map_musubi[i] = 0;
      data_reset = true;
      break;
    }
  }
  if (data_reset) {
    for (int i = 0; i < 3; i++) {
      hi_score[i] = 1000;
      EEPROM.update(i*2+EEPROM_SCORES,   ((hi_score[i]) >> 8 & 0xFF));
      EEPROM.update(i*2+1+EEPROM_SCORES, hi_score[i] & 0xFF);
    }
    money_yen = 0;
    EEPROM.update(3*2+EEPROM_SCORES,   (money_yen >> 8) & 0xFF);
    EEPROM.update(3*2+1+EEPROM_SCORES, money_yen & 0xFF);
    for (int i = 0; i < 16; i++) {
      map_musubi[i] = 0;
      EEPROM.update(4*2+i+EEPROM_SCORES, map_musubi[i]);
    }
  }

  while (true) {
    currTime = millis();
    if ( currTime > prevTime + FPSDELAY ) {
      prevTime = currTime;
      byte input = display.buttonsState();
      display.clear();
      switch (state) {
        case state_menu:
          help_count++;
          if (help_count > 150) {
              help_count = 0;
              state = state_help;
              break;
          }
          if (input & (LEFT_BUTTON |RIGHT_BUTTON |UP_BUTTON |DOWN_BUTTON)) {
            help_count = 0;
            if (!now_push) {
              if (input & UP_BUTTON    && menu_select > 0) menu_select--;
              if (input & DOWN_BUTTON  && menu_select < 4) menu_select++;
              switch (menu_select) {
                case 0:
                  if (input & (LEFT_BUTTON | RIGHT_BUTTON)) level++;
                  if (level > 2) level = 0;
                  break;
                case 1:
                  if (input & (LEFT_BUTTON | RIGHT_BUTTON)) sound = !sound;
                  break;                
                case 2:
                  if (input & (LEFT_BUTTON | RIGHT_BUTTON)) hatena = !hatena;
                  break;
              }
              now_push = true;
            }
          } else {
            now_push = false;
          }
          if (input & B_BUTTON) {
            help_count = 0;
            now_push_b = true;
          } else {
            if (now_push_b) {
              switch (menu_select) {
                case 0:
                case 1:
                case 2:
                  state = state_game_bef;
                  break;
                case 3:
                  state = state_high_score;
                  break;
                case 4:
                  state = state_omikuji_bef;
                  break;                
              }
              now_push_b = false;
            }
          }
          display.setCursor(20,8);  display.print(F("MINE EVOLUTIONS"));
          display.setCursor(20,24); display.print(F("LEVEL:"));
          switch (level) {
            case 0: display.print(F("8x8")); break;
            case 1: display.print(F("7x16")); break;
            case 2: display.print(F("EVOLUTIONS")); break;
          }
          display.setCursor(20,32); display.print(F("SOUND:"));
          if (sound) display.print(F("ON"));
          else       display.print(F("OFF"));
          display.setCursor(20,40); display.print(F("?    :"));
          if (hatena) display.print(F("USE"));
          else        display.print(F("NO USE"));
          display.setCursor(20,48); display.print(F("HIGH SCORE"));
          //display.setCursor(30,56); display.print(F("OMIKUJI"));
          display.drawBitmap(20, 57, omikuji_title,33,8,1);
          if (menu_select < 4) {
            display.drawBitmap(15, 24 + menu_select * 8, menu_cursol,3,8,1);
          }else{
            display.drawBitmap(15, 24 + menu_select * 8 + 1, menu_cursol,3,8,1);
          }
          break;
        case state_help:
          if (input & A_BUTTON) {
            now_push_a = true;
          } else {
            if (now_push_a) {
              state = state_menu;
              now_push_a = false;
            }
          }
          display.setCursor(20,8);  display.print(F("MINE EVOLUTIONS"));
          display.drawBitmap(28+ 0 * 8, 3 *8, bitmap_base[1], 8,8,1);
          display.drawBitmap(28+ 0 * 8, 4 *8, bitmap_base[1], 8,8,1);
          display.drawBitmap(28+ 0 * 8, 5 *8, bitmap_base[1], 8,8,1);
          display.drawBitmap(28+ 0 * 8, 6 *8, bitmap_base[1], 8,8,1);
          display.drawBitmap(28+ 1 * 8, 3 *8, bitmap_base[1], 8,8,1);
          display.drawBitmap(28+ 1 * 8, 4 *8, bitmap_mine4[0], 8,8,1);
          display.drawBitmap(28+ 1 * 8, 5 *8, bitmap_mine4[1], 8,8,1);
          display.drawBitmap(28+ 1 * 8, 6 *8, bitmap_base[1], 8,8,1);
          display.drawBitmap(28+ 2 * 8, 3 *8, bitmap_base[1], 8,8,1);
          display.drawBitmap(28+ 2 * 8, 4 *8, bitmap_mine4[2], 8,8,1);
          display.drawBitmap(28+ 2 * 8, 5 *8, bitmap_mine4[3], 8,8,1);
          display.drawBitmap(28+ 2 * 8, 6 *8, bitmap_base[1], 8,8,1);
          display.drawBitmap(28+ 3 * 8, 3 *8, bitmap_base[1], 8,8,1);
          display.drawBitmap(28+ 3 * 8, 4 *8, bitmap_base[1], 8,8,1);
          display.drawBitmap(28+ 3 * 8, 5 *8, bitmap_base[1], 8,8,1);
          display.drawBitmap(28+ 3 * 8, 6 *8, bitmap_base[1], 8,8,1);
          display.drawBitmap(28+ 6 * 8, 4+ 3 *8, bitmap_base[2], 8,8,1);
          display.drawBitmap(28+ 6 * 8, 4+ 4 *8, bitmap_base[2], 8,8,1);
          display.drawBitmap(28+ 6 * 8, 4+ 5 *8, bitmap_base[2], 8,8,1);
          display.drawBitmap(28+ 7 * 8, 4+ 3 *8, bitmap_base[2], 8,8,1);
          display.drawBitmap(28+ 7 * 8, 4+ 4 *8, bitmap_mine[1], 8,8,1);
          display.drawBitmap(28+ 7 * 8, 4+ 5 *8, bitmap_base[2], 8,8,1);
          display.drawBitmap(28+ 8 * 8, 4+ 3 *8, bitmap_base[2], 8,8,1);
          display.drawBitmap(28+ 8 * 8, 4+ 4 *8, bitmap_base[2], 8,8,1);
          display.drawBitmap(28+ 8 * 8, 4+ 5 *8, bitmap_base[2], 8,8,1);
          break;
        case state_high_score:
          display.setCursor(35,0); display.print(F("HIGH SCORE"));
          display.setCursor(20,20); display.print(F("8x8       :"));if (hi_score[0] < 1000) display.print(hi_score[0]);
          display.setCursor(20,30); display.print(F("7x16      :"));if (hi_score[1] < 1000) display.print(hi_score[1]);
          display.setCursor(20,40); display.print(F("EVOLUTIONS:"));if (hi_score[2] < 1000) display.print(hi_score[2]);
          if (input & A_BUTTON) {
            state = state_menu;
            break;
          }
          break;

        case state_omikuji_bef:
          if (input & A_BUTTON) {
            state = state_menu;
            break;
          }
          if (input & B_BUTTON) {
            now_push_b = true;
          } else {
            if (now_push_b) {
              if (money_yen >= 100) {
                money_yen -=100;
                EEPROM.update(3*2+EEPROM_SCORES,   (money_yen >> 8) & 0xFF);
                EEPROM.update(3*2+1+EEPROM_SCORES, money_yen & 0xFF);
                randomSeed(currTime & 0xFF);
                omikuji_kekka = random(255) % 4;
                cur_x=8;
                cur_y=4;
                for (int x = 0; x < 16; x++){
                  for (int y = 0; y < 8; y++){
                    map_flags[x][y].open = 0; // [x][y]
                    map_flags[x][y].push = 0; // [x][y]
                    map_flags[x][y].panel = 0; // [x][y]
                    map_flags[x][y].mine = 0; // [x][y]
                    map_flags[x][y].mine4 = 0; // [x][y]
                    map_flags[x][y].base = 0; // [x][y]
                  }
                }
                state = state_omikuji;
              }
              now_push_b = false;
            }
          }
          display.drawBitmap(50, 0, omikuji_title,33,8,1);
          display.setCursor(48,10); display.print(F("100YEN"));
          display.setCursor(10,20); display.print(F("MY MONEY:"));display.print(money_yen);display.print("YEN");
          for (int x = 0; x <= 15; x++){
            for (int y = 4; y <= 7; y++){
              display.drawBitmap(x * 8, y *8, bitmap_omikujis[(map_musubi[x] >> y) & 0x01], 8,8,1);
            }
          }
          break;
        case state_omikuji:
          open_update = false;
          clear_flag = true;
          for (int x = 0; x <= 15; x++){
            for (int y = 0; y <= 7; y++){
              if (!map_flags[x][y].open) {
                clear_flag = false;
                if (map_flags[x][y].push) {
                  map_flags[x][y].push = 0;
                  map_flags[x][y].open = 1;
                  open_update = true;
                  if (x > 0) {
                               map_flags[x-1][y  ].push = !map_flags[x-1][y  ].open;
                    if (y > 0) map_flags[x-1][y-1].push = !map_flags[x-1][y-1].open;
                    if (y < 7) map_flags[x-1][y+1].push = !map_flags[x-1][y+1].open;
                  }
                  if (y > 0)   map_flags[x  ][y-1].push = !map_flags[x  ][y-1].open;
                  if (y < 7)   map_flags[x  ][y+1].push = !map_flags[x  ][y+1].open;
                  if (x < 15) {
                               map_flags[x+1][y  ].push = !map_flags[x+1][y  ].open;
                    if (y > 0) map_flags[x+1][y-1].push = !map_flags[x+1][y-1].open;
                    if (y < 7) map_flags[x+1][y+1].push = !map_flags[x+1][y+1].open;
                  }
                }
              }
            }
          }
          if (!open_update && clear_flag) {
            if (sound) tunes.playScore(saruoto_11);
            state = state_omikuji2;
          }
          if (input & (LEFT_BUTTON |RIGHT_BUTTON |UP_BUTTON |DOWN_BUTTON)) {
            if (!now_push) {
              if (input & LEFT_BUTTON  && cur_x > 0) cur_x--;
              if (input & RIGHT_BUTTON && cur_x < 15) cur_x++;
              if (input & UP_BUTTON    && cur_y > 0) cur_y--;
              if (input & DOWN_BUTTON  && cur_y < 7) cur_y++;
              now_push = true;
            }
          } else {
            now_push = false;
          }
        case state_omikuji2:
          if (input & B_BUTTON) {
            now_push_b = true;
          } else {
            if (now_push_b) {
              map_flags[cur_x][cur_y].push = !map_flags[cur_x][cur_y].open;
              if (state == state_omikuji2) {
                cur_x=8;
                cur_y=4;
                state = state_omikuji_aft;
              }
              now_push_b = false;
            }
          }
          for (int x = 0; x <= 15; x++){
            for (int y = 0; y <= 7; y++){
              if (map_flags[x][y].open) {
                if ((map_omikuji[omikuji_kekka][x] >> y) & 0x01) {
                  display.drawBitmap(x * 8, y *8, smiles[omikuji_kekka], 8,8,1);
                } else {
                  display.drawBitmap(x * 8, y *8, bitmap_base[0], 8,8,1);
                }
              } else {
                display.drawBitmap(x * 8, y *8, bitmap_panel[0], 8,8,1);
              }
            }
          }
          if (state == state_omikuji) {
            display.drawBitmap(cur_x * 8, cur_y * 8, cursol,  8,8, map_flags[cur_x][cur_y].open);
          }
          break;

        case state_omikuji_aft:
          if (input & (LEFT_BUTTON |RIGHT_BUTTON |UP_BUTTON |DOWN_BUTTON)) {
            if (!now_push) {
              if (input & LEFT_BUTTON  && cur_x > 0) cur_x--;
              if (input & RIGHT_BUTTON && cur_x < 15) cur_x++;
              if (input & UP_BUTTON    && cur_y > 4) cur_y--;
              if (input & DOWN_BUTTON  && cur_y < 7) cur_y++;
              now_push = true;
            }
          } else {
            now_push = false;
          }
        case state_omikuji_aft2:
          if (input & B_BUTTON) {
            now_push_b = true;
          } else {
            if (now_push_b) {
              if (state == state_omikuji_aft2) {
                state = state_menu;
              } else {
                map_musubi[cur_x] |= 0x01 << cur_y;
                EEPROM.update(4*2+cur_x+EEPROM_SCORES, map_musubi[cur_x]);
                state = state_omikuji_aft2;
              }
              now_push_b = false;
            }
          }
          display.drawBitmap(50, 0, omikuji_title,33,8,1);
          for (int x = 0; x <= 15; x++){
            for (int y = 4; y <= 7; y++){
              display.drawBitmap(x * 8, y *8, bitmap_omikujis[(map_musubi[x] >> y) & 0x01], 8,8,1);
            }
          }
          if (state == state_omikuji_aft) {
            display.drawBitmap(cur_x * 8, cur_y * 8, cursol,  8,8, 1);
          }
          break;
        case state_game_bef:
          game_over = false;
          game_over_x=0;
          game_over_y=0;
          clear_flag = false;
          game_start = false;
          hi_score_update = false;
          get_yen = false;
          count_flags = initvalue[level].mine;
          count = 0;
          count_time=0;
          cur_x=8;
          cur_y=4;
          for (int x = 0; x < 16; x++){
            for (int y = 0; y < 8; y++){
              map_flags[x][y].open = 0; // [x][y]
              map_flags[x][y].push = 0; // [x][y]
              map_flags[x][y].panel = 0; // [x][y]
              map_flags[x][y].mine = 0; // [x][y]
              map_flags[x][y].mine4 = 0; // [x][y]
              map_flags[x][y].base = 0; // [x][y]
            }
          }
          state = state_game;
        case state_game:
          if (game_start) {
            count++;
            if (count >= 30) {
              if (count_time < 999) {
                if (sound) {
                  if (!tunes.playing()) tunes.tone(523, 100);
                }
                count_time++;
              }
              count = 0;
            }
          }
          if (input & (LEFT_BUTTON |RIGHT_BUTTON |UP_BUTTON |DOWN_BUTTON)) {
            if (!now_push) {
              if (input & LEFT_BUTTON  && cur_x > initvalue[level].x_min) cur_x--;
              if (input & RIGHT_BUTTON && cur_x < initvalue[level].x_max) cur_x++;
              if (input & UP_BUTTON    && cur_y > initvalue[level].y_min) cur_y--;
              if (input & DOWN_BUTTON  && cur_y < initvalue[level].y_max) cur_y++;
              now_push = true;
            }
          } else {
            now_push = false;
          }
          if (input & A_BUTTON) {
            if (!game_start) {
               state = state_menu;
               break;
            }
            if (!now_push_a) {
              if (!map_flags[cur_x][cur_y].open) {
                switch (map_flags[cur_x][cur_y].panel) {
                  case 0:
                    map_flags[cur_x][cur_y].panel = 1;
                    count_flags--;
                    break;
                  case 1:
                    count_flags++;
                    if (hatena) {
                      map_flags[cur_x][cur_y].panel = 2;
                      break;
                    }
                  case 2:
                    map_flags[cur_x][cur_y].panel = 0;
                    break;
                }
              }
              now_push_a = true;
            }
          } else {
            now_push_a = false;
          }
          if (input & B_BUTTON) {
            now_push_b = true;
          } else {
            if (now_push_b) {
              if (!game_start) {
                randomSeed(currTime & 0xFF);
                count_mine=0;
                if (level == 2) {
                  for (int x = initvalue[level].x_min; x <= initvalue[level].x_max - 1 && count_mine < 4; x++){
                    for (int y = initvalue[level].y_min; y <= initvalue[level].y_max - 1 && count_mine < 4; y++){
                      if (((cur_x != x && cur_x != x + 1) || (cur_y != y && cur_y != y + 1)) && map_flags[x][y].mine==0 && ((random( 255 ) % 10) == 1)) {
                        map_flags[x ][y].mine    = 1;
                        map_flags[x ][y+1].mine  = 1;
                        map_flags[x+1][y].mine   = 1;
                        map_flags[x+1][y+1].mine = 1;
                        map_flags[x ][y].mine4    = 1;
                        map_flags[x ][y+1].mine4  = 2;
                        map_flags[x+1][y].mine4   = 3;
                        map_flags[x+1][y+1].mine4 = 4;
                        count_mine+=4;
                        break;
                      }
                    }
                  }                  
                }
                do {
                  for (int x = initvalue[level].x_min; x <= initvalue[level].x_max && count_mine < initvalue[level].mine; x++){
                    for (int y = initvalue[level].y_min; y <= initvalue[level].y_max && count_mine < initvalue[level].mine; y++){
                      if ((cur_x != x || cur_y != y) && map_flags[x][y].mine==0 && ((random( 255 ) % 10) == 1)) {
                        map_flags[x][y].mine = 1;
                        count_mine++;
                      }
                    }
                  }
                } while (count_mine < initvalue[level].mine);
                if (level == 2) {
                  count_mine=0;
                  do {
                    for (int x = initvalue[level].x_min; x <= initvalue[level].x_max && count_mine < 3; x++){
                      for (int y = initvalue[level].y_min; y <= initvalue[level].y_max && count_mine < 3; y++){
                        if (map_flags[x][y].mine==1 && map_flags[x ][y].mine4==0 && ((random( 255 ) % 10) == 1)) {
                          map_flags[x][y].mine = 2;
                          count_mine++;
                        }
                      }
                    }                
                  } while (count_mine < 3);
                }
 
                for (int x = initvalue[level].x_min; x <= initvalue[level].x_max; x++){
                  for (int y = initvalue[level].y_min; y <= initvalue[level].y_max; y++){
                    base_no=0;
                    if (x > initvalue[level].x_min) {
                                                      base_no += map_flags[x-1][y  ].mine;
                                                      base_no -= (map_flags[x-1][y  ].mine4 > 0) ? 1: 0;
                      if (y > initvalue[level].y_min) base_no += map_flags[x-1][y-1].mine;
                      if (y < initvalue[level].y_max) base_no += map_flags[x-1][y+1].mine;
                    }
                    if (y > initvalue[level].y_min) {
                                                      base_no += map_flags[x  ][y-1].mine;
                                                      base_no -= (map_flags[x  ][y-1].mine4 > 0) ? 1: 0;
                    }
                    if (y < initvalue[level].y_max) {
                                                      base_no += map_flags[x  ][y+1].mine;
                                                      base_no -= (map_flags[x  ][y+1].mine4 > 0) ? 1: 0;
                    }
                    if (x < initvalue[level].x_max) {
                                                      base_no += map_flags[x+1][y  ].mine;
                                                      base_no -= (map_flags[x+1][y  ].mine4 > 0) ? 1: 0;
                      if (y > initvalue[level].y_min) base_no += map_flags[x+1][y-1].mine;
                      if (y < initvalue[level].y_max) base_no += map_flags[x+1][y+1].mine;
                    }
                    map_flags[x][y].base = base_no;
                  }
                }

                count_mine=0;
                get_yen = false;
                do {
                  for (int x = initvalue[level].x_min + 3; x <= initvalue[level].x_max && count_mine < 1; x++){
                    for (int y = initvalue[level].y_min; y <= initvalue[level].y_max && count_mine < 1; y++){
                      if (map_flags[x][y].mine==0 && map_flags[x][y].base==0 &&
                        map_flags[x-1][y].mine==0 && map_flags[x-1][y].base>0 &&
                        ((random( 255 ) % 10) == 1)) {
                        if (money_yen < 50000) {
                          map_flags[x][y].base = BITMAP_BASE_YEN;
                          get_yen = true;
                          yen_x = x;
                          yen_y = y;
                        }
                        count_mine++;
                      }
                    }
                  }                
                } while (level == 2 && count_mine < 1);

                game_start = true;
              }
              map_flags[cur_x][cur_y].push = !map_flags[cur_x][cur_y].open;
              now_push_b = false;
            }
          }

          open_update = false;
          clear_flag = true;
          for (int x = initvalue[level].x_min; x <= initvalue[level].x_max; x++){
            for (int y = initvalue[level].y_min; y <= initvalue[level].y_max; y++){
              if (!map_flags[x][y].open) {
                if (map_flags[x][y].mine==0) { // 開けてないところがまだある
                  clear_flag = false;
                }
                if (map_flags[x][y].push) {
                  map_flags[x][y].push = 0;
                  if (map_flags[x][y].panel != 1) {
                    // 開ける処理
                    map_flags[x][y].open = 1;
                    open_update = true;
                    if (map_flags[x][y].mine > 0) {
                      game_over = true;
                      game_over_x=x;
                      game_over_y=y;
                      if (sound) tunes.tone(1046, 250);
                    }
                    if (map_flags[x][y].base == 0 || map_flags[x][y].base == BITMAP_BASE_YEN) {
                      if (x > initvalue[level].x_min) {
                                                        map_flags[x-1][y  ].push = !map_flags[x-1][y  ].open && map_flags[x-1][y  ].panel != 1;
                        if (y > initvalue[level].y_min) map_flags[x-1][y-1].push = !map_flags[x-1][y-1].open && map_flags[x-1][y-1].panel != 1;
                        if (y < initvalue[level].y_max) map_flags[x-1][y+1].push = !map_flags[x-1][y+1].open && map_flags[x-1][y+1].panel != 1;
                      }
                      if (y > initvalue[level].y_min)   map_flags[x  ][y-1].push = !map_flags[x  ][y-1].open && map_flags[x  ][y-1].panel != 1;
                      if (y < initvalue[level].y_max)   map_flags[x  ][y+1].push = !map_flags[x  ][y+1].open && map_flags[x  ][y+1].panel != 1;
                      if (x < initvalue[level].x_max) {
                                                        map_flags[x+1][y  ].push = !map_flags[x+1][y  ].open && map_flags[x+1][y  ].panel != 1;
                        if (y > initvalue[level].y_min) map_flags[x+1][y-1].push = !map_flags[x+1][y-1].open && map_flags[x+1][y-1].panel != 1;
                        if (y < initvalue[level].y_max) map_flags[x+1][y+1].push = !map_flags[x+1][y+1].open && map_flags[x+1][y+1].panel != 1;
                      }
                    }
                  }
                }
              }
            }
          }
          if (!open_update && (game_over || clear_flag)) {
            for (int x = initvalue[level].x_min; x <= initvalue[level].x_max; x++){
              for (int y = initvalue[level].y_min; y <= initvalue[level].y_max; y++){
                if (!map_flags[x][y].open && map_flags[x][y].mine > 0) {
                  if (game_over) map_flags[x][y].open = map_flags[x][y].panel != 1;
                  else           map_flags[x][y].panel = 1;
                }
              }
            }
            if (game_over) {
              get_yen = false;
            }else{
              if (sound) tunes.playScore(saruoto_11);
              if (hi_score[level] > count_time) {
                hi_score[level] = count_time;
                hi_score_update = true;
                EEPROM.update(level*2+EEPROM_SCORES,   ((hi_score[level]) >> 8 & 0xFF));
                EEPROM.update(level*2+1+EEPROM_SCORES, hi_score[level] & 0xFF);
              }
              if (get_yen) {
                int tmp_yen = 0;
                if (map_flags[yen_x-1][yen_y].mine == 0) {
                  if (map_flags[yen_x-2][yen_y].mine == 0) {
                    if (map_flags[yen_x-3][yen_y].mine == 0) {
                      tmp_yen += map_flags[yen_x-3][yen_y].base * 100;
                    }
                    tmp_yen += map_flags[yen_x-2][yen_y].base * 10;
                  }
                  tmp_yen += map_flags[yen_x-1][yen_y].base;
                }
                if (level == 2)      tmp_yen *= 30;
                else if (level == 1) tmp_yen *= 3;
                money_yen += tmp_yen;
                EEPROM.update(3*2+EEPROM_SCORES,   (money_yen >> 8) & 0xFF);
                EEPROM.update(3*2+1+EEPROM_SCORES, money_yen & 0xFF);
              }
            }
            state = state_game_aft;            
          }

          display.drawBitmap(  2,     0, count_end[(count_flags < 0) ? 1 : 0],  5,8,1);      
          display.drawBitmap(  2 + 5, 0, count_no[(abs(count_flags)/10)%10],4,8,1);
          display.drawBitmap(  2 + 9, 0, count_no[abs(count_flags)%10],4,8,1);
          display.drawBitmap(initvalue[level].smile_offset, 0, smiles[(now_push_b && !map_flags[cur_x][cur_y].open && map_flags[cur_x][cur_y].panel != 1) ? 1 : 0],  8,8,1);
          display.drawBitmap(112    , 0, count_start,1,8,1);
          display.drawBitmap(112 + 1, 0, count_no[count_time/100],4,8,1);
          display.drawBitmap(112 + 5, 0, count_no[(count_time/10)%10],4,8,1);      
          display.drawBitmap(112 + 9, 0, count_no[count_time%10],4,8,1);
          for (int x = initvalue[level].x_min; x <= initvalue[level].x_max; x++){
            for (int y = initvalue[level].y_min; y <= initvalue[level].y_max; y++){
              if (map_flags[x][y].open) {
                if (map_flags[x][y].mine > 0) {
                  if (map_flags[x][y].mine4 > 0) {
                    display.drawBitmap(x * 8, y *8, bitmap_mine4[map_flags[x][y].mine4 - 1], 8,8,1);
                  } else {
                    display.drawBitmap(x * 8, y *8, bitmap_mine[map_flags[x][y].mine - 1], 8,8,1);
                  }
                } else {
                  display.drawBitmap(x * 8, y *8, bitmap_base[map_flags[x][y].base], 8,8,1);
                }
              } else {
                display.drawBitmap(x * 8, y *8, bitmap_panel[map_flags[x][y].panel], 8,8,1);
              }
            }
          }
          display.drawBitmap(cur_x * 8, cur_y * 8, cursol,  8,8, map_flags[cur_x][cur_y].open);
          break;
        case state_game_aft:
          if (input & A_BUTTON) {
            now_push_a = true;
          } else {
            if (now_push_a) {
              now_push_a = false;
              if (!hi_score_update && !get_yen) state = state_game_bef;
            }
          }
          if (input & B_BUTTON) {
            now_push_b = true;
          } else {
            if (now_push_b) {
              now_push_b = false;
              if (hi_score_update) hi_score_update = false;
              else if (get_yen)    get_yen = false;
            }
          }

          display.drawBitmap(  2,     0, count_end[(count_flags < 0) ? 1 : 0],  5,8,1);      
          display.drawBitmap(  2 + 5, 0, count_no[(abs(count_flags)/10)%10],4,8,1);
          display.drawBitmap(  2 + 9, 0, count_no[abs(count_flags)%10],4,8,1);
          display.drawBitmap(initvalue[level].smile_offset, 0, smiles[game_over ? 3 : 2], 8,8,1); 
          display.drawBitmap(112    , 0, count_start,1,8,1);
          display.drawBitmap(112 + 1, 0, count_no[count_time/100],4,8,1);
          display.drawBitmap(112 + 5, 0, count_no[(count_time/10)%10],4,8,1);      
          display.drawBitmap(112 + 9, 0, count_no[count_time%10],4,8,1);
          for (int x = initvalue[level].x_min; x <= initvalue[level].x_max; x++){
            for (int y = initvalue[level].y_min; y <= initvalue[level].y_max; y++){
              if ((hi_score_update || get_yen) && (y == 2 || y == 3 || y == 4)) {
                continue;
              }
              if (map_flags[x][y].open) {
                if (map_flags[x][y].mine > 0) {
                  int hanten = 1;
                  if (game_over_x == x && game_over_y == y) {
                    display.drawBitmap(x * 8, y *8, bitmap_panel[0], 8,8,1);
                    hanten = 0;
                    switch (map_flags[x ][y].mine4) {
                      case 1:
                      case 3:
                      game_over_y++;
                      break;
                      case 2:
                        game_over_x++;
                        game_over_y--;
                      break;
                      case 4:
                        game_over_x--;
                        game_over_y--;
                      break;
                    }
                  }
                  if (map_flags[x][y].mine4 > 0) {
                    display.drawBitmap(x * 8, y *8, bitmap_mine4[map_flags[x][y].mine4 - 1], 8,8,hanten);
                  } else {
                    display.drawBitmap(x * 8, y *8, bitmap_mine[map_flags[x][y].mine - 1], 8,8,hanten);
                  }
                } else {
                  display.drawBitmap(x * 8, y *8, bitmap_base[map_flags[x][y].base], 8,8,1);
                }
              } else {
                if (map_flags[x][y].mine == 0 && (map_flags[x][y].panel == 1)) {
                  display.drawBitmap(x * 8, y *8, bitmap_base[map_flags[x][y].base], 8,8,1);
                  display.drawBitmap(x * 8, y *8, bitmap_panel_miss, 8,8,1);
                } else {
                  display.drawBitmap(x * 8, y *8, bitmap_panel[map_flags[x][y].panel], 8,8,1);
                }
              }
            }
          }
          if (hi_score_update) {
            display.setCursor(5,24); 
            display.print(F("HIGH SCORE UPDATE !!"));
          } else if (get_yen) {
            int x_offset=30;
            if (level == 2) {
              x_offset=15;
            } else if (level == 1) {
              x_offset=20;
            }
            if (map_flags[yen_x-1][yen_y].mine == 0) {
              if (map_flags[yen_x-2][yen_y].mine == 0) {
                if (map_flags[yen_x-3][yen_y].mine == 0) {
                  display.drawBitmap(x_offset, 24, bitmap_base[map_flags[yen_x-3][yen_y].base], 8,8,1);
                }
                display.drawBitmap(x_offset+8, 24, bitmap_base[map_flags[yen_x-2][yen_y].base], 8,8,1);
              }
              display.drawBitmap(x_offset+16, 24, bitmap_base[map_flags[yen_x-1][yen_y].base], 8,8,1);
            }
            display.drawBitmap(x_offset+24, 24, bitmap_base[map_flags[yen_x  ][yen_y].base], 8,8,1);
            display.setCursor(x_offset+32,25);
            if (level == 2) {
              display.print(F(" x30"));
            } else if (level == 1) {
              display.print(F(" x3"));
            }
            display.print(F(" GET !!"));
          }
          break;
      }
      display.display();  
    }
  }
}

