/*
 * -Smart Mood Light-
 *
 * author jihoonkimtech (jihoonkimtech@naver.com)
 *      (Republic of Korea)
 * version  V1.0.0
 * date  2020-03-10
*/

/*
 * Dev Note
 * 
 * 1.0.0
 * - Left shift display function
 * - Brightness control function
 * - Shift speed control function
 * - sentence save function (using EEPROM)
 * 
*/

#include <EEPROM.h> //EEPROM library
#include <MaxMatrix.h> //dotmatrix library
#include <SoftwareSerial.h> //bluetooth serial
#include <avr/pgmspace.h> //for dotmatrix


PROGMEM const unsigned char ASCII_Font_8[] = { //ASCII font set
//w, h, Bnnnnnnnn, Bnnnnnnnn, Bnnnnnnnn, Bnnnnnnnn, Bnnnnnnnn, 
  3, 8, B00000000, B00000000, B00000000, B00000000, B00000000, // space
  1, 8, B01011111, B00000000, B00000000, B00000000, B00000000, // !
  3, 8, B00000011, B00000000, B00000011, B00000000, B00000000, // "
  5, 8, B00010100, B00111110, B00010100, B00111110, B00010100, // #
  4, 8, B00100100, B01101010, B00101011, B00010010, B00000000, // $
  5, 8, B01100011, B00010011, B00001000, B01100100, B01100011, // %
  5, 8, B00110110, B01001001, B01010110, B00100000, B01010000, // &
  1, 8, B00000011, B00000000, B00000000, B00000000, B00000000, // '
  3, 8, B00011100, B00100010, B01000001, B00000000, B00000000, // (
  3, 8, B01000001, B00100010, B00011100, B00000000, B00000000, // )
  5, 8, B00101000, B00011000, B00001110, B00011000, B00101000, // *
  5, 8, B00001000, B00001000, B00111110, B00001000, B00001000, // +
  2, 8, B10110000, B01110000, B00000000, B00000000, B00000000, // ,
  4, 8, B00001000, B00001000, B00001000, B00001000, B00000000, // -
  2, 8, B01100000, B01100000, B00000000, B00000000, B00000000, // .
  4, 8, B01100000, B00011000, B00000110, B00000001, B00000000, // /
  4, 8, B00111110, B01000001, B01000001, B00111110, B00000000, // 0
  3, 8, B01000010, B01111111, B01000000, B00000000, B00000000, // 1
  4, 8, B01100010, B01010001, B01001001, B01000110, B00000000, // 2
  4, 8, B00100010, B01000001, B01001001, B00110110, B00000000, // 3
  4, 8, B00011000, B00010100, B00010010, B01111111, B00000000, // 4
  4, 8, B00100111, B01000101, B01000101, B00111001, B00000000, // 5
  4, 8, B00111110, B01001001, B01001001, B00110000, B00000000, // 6
  4, 8, B01100001, B00010001, B00001001, B00000111, B00000000, // 7
  4, 8, B00110110, B01001001, B01001001, B00110110, B00000000, // 8
  4, 8, B00000110, B01001001, B01001001, B00111110, B00000000, // 9
  2, 8, B01010000, B00000000, B00000000, B00000000, B00000000, // :
  2, 8, B10000000, B01010000, B00000000, B00000000, B00000000, // ;
  3, 8, B00010000, B00101000, B01000100, B00000000, B00000000, // <
  3, 8, B00010100, B00010100, B00010100, B00000000, B00000000, // =
  3, 8, B01000100, B00101000, B00010000, B00000000, B00000000, // >
  4, 8, B00000010, B01011001, B00001001, B00000110, B00000000, // ?
  5, 8, B00111110, B01001001, B01010101, B01011101, B00001110, // @
  4, 8, B01111110, B00010001, B00010001, B01111110, B00000000, // A
  4, 8, B01111111, B01001001, B01001001, B00110110, B00000000, // B
  4, 8, B00111110, B01000001, B01000001, B00100010, B00000000, // C
  4, 8, B01111111, B01000001, B01000001, B00111110, B00000000, // D
  4, 8, B01111111, B01001001, B01001001, B01000001, B00000000, // E
  4, 8, B01111111, B00001001, B00001001, B00000001, B00000000, // F
  4, 8, B00111110, B01000001, B01001001, B01111010, B00000000, // G
  4, 8, B01111111, B00001000, B00001000, B01111111, B00000000, // H
  3, 8, B01000001, B01111111, B01000001, B00000000, B00000000, // I
  4, 8, B00110000, B01000000, B01000001, B00111111, B00000000, // J
  4, 8, B01111111, B00001000, B00010100, B01100011, B00000000, // K
  4, 8, B01111111, B01000000, B01000000, B01000000, B00000000, // L
  5, 8, B01111111, B00000010, B00001100, B00000010, B01111111, // M
  5, 8, B01111111, B00000100, B00001000, B00010000, B01111111, // N
  4, 8, B00111110, B01000001, B01000001, B00111110, B00000000, // O
  4, 8, B01111111, B00001001, B00001001, B00000110, B00000000, // P
  4, 8, B00111110, B01000001, B01000001, B10111110, B00000000, // Q
  4, 8, B01111111, B00001001, B00001001, B01110110, B00000000, // R
  4, 8, B01000110, B01001001, B01001001, B00110010, B00000000, // S
  5, 8, B00000001, B00000001, B01111111, B00000001, B00000001, // T
  4, 8, B00111111, B01000000, B01000000, B00111111, B00000000, // U
  5, 8, B00001111, B00110000, B01000000, B00110000, B00001111, // V
  5, 8, B00111111, B01000000, B00111000, B01000000, B00111111, // W
  5, 8, B01100011, B00010100, B00001000, B00010100, B01100011, // X
  5, 8, B00000111, B00001000, B01110000, B00001000, B00000111, // Y
  4, 8, B01100001, B01010001, B01001001, B01000111, B00000000, // Z
  2, 8, B01111111, B01000001, B00000000, B00000000, B00000000, // [
  4, 8, B00000001, B00000110, B00011000, B01100000, B00000000, // \ backslash
  2, 8, B01000001, B01111111, B00000000, B00000000, B00000000, // ]
  3, 8, B00000010, B00000001, B00000010, B00000000, B00000000, // hat
  4, 8, B01000000, B01000000, B01000000, B01000000, B00000000, // _
  2, 8, B00000001, B00000010, B00000000, B00000000, B00000000, // `
  4, 8, B00100000, B01010100, B01010100, B01111000, B00000000, // a
  4, 8, B01111111, B01000100, B01000100, B00111000, B00000000, // b
  4, 8, B00111000, B01000100, B01000100, B00101000, B00000000, // c
  4, 8, B00111000, B01000100, B01000100, B01111111, B00000000, // d
  4, 8, B00111000, B01010100, B01010100, B00011000, B00000000, // e
  3, 8, B00000100, B01111110, B00000101, B00000000, B00000000, // f
  4, 8, B10011000, B10100100, B10100100, B01111000, B00000000, // g
  4, 8, B01111111, B00000100, B00000100, B01111000, B00000000, // h
  3, 8, B01000100, B01111101, B01000000, B00000000, B00000000, // i
  4, 8, B01000000, B10000000, B10000100, B01111101, B00000000, // j
  4, 8, B01111111, B00010000, B00101000, B01000100, B00000000, // k
  3, 8, B01000001, B01111111, B01000000, B00000000, B00000000, // l
  5, 8, B01111100, B00000100, B01111100, B00000100, B01111000, // m
  4, 8, B01111100, B00000100, B00000100, B01111000, B00000000, // n
  4, 8, B00111000, B01000100, B01000100, B00111000, B00000000, // o
  4, 8, B11111100, B00100100, B00100100, B00011000, B00000000, // p
  4, 8, B00011000, B00100100, B00100100, B11111100, B00000000, // q
  4, 8, B01111100, B00001000, B00000100, B00000100, B00000000, // r
  4, 8, B01001000, B01010100, B01010100, B00100100, B00000000, // s
  3, 8, B00000100, B00111111, B01000100, B00000000, B00000000, // t
  4, 8, B00111100, B01000000, B01000000, B01111100, B00000000, // u
  5, 8, B00011100, B00100000, B01000000, B00100000, B00011100, // v
  5, 8, B00111100, B01000000, B00111100, B01000000, B00111100, // w
  5, 8, B01000100, B00101000, B00010000, B00101000, B01000100, // x
  4, 8, B10011100, B10100000, B10100000, B01111100, B00000000, // y
  3, 8, B01100100, B01010100, B01001100, B00000000, B00000000, // z
  3, 8, B00001000, B00110110, B01000001, B00000000, B00000000, // {
  1, 8, B01111111, B00000000, B00000000, B00000000, B00000000, // |
  3, 8, B01000001, B00110110, B00001000, B00000000, B00000000, // }
  4, 8, B00001000, B00000100, B00001000, B00000100, B00000000, // ~ 
};

void write_String(int addrs, String source) //Saving sentence in EEPROM
{               //start addr, source
  int stringSize = source.length(); //Sentence length

  for(int i=0;i<100;i++) //limit sentence length 100
  {
    EEPROM.write(addrs+i, source[i]); //Saving character in EEPROM
  }

  EEPROM.write(addrs + stringSize,'\0'); //Save a space character behind a sentence
}

String read_String(int addrs) //Return saved sentence form EEPROM
{
  char source[100]; //return variable (limit sentence length 100)
  int leng=0;   //init length
  unsigned char _char; //temp char

  while(_char != '\0' && leng < 100) //if reading done -> break
  {
    _char = EEPROM.read(addrs + leng); //Extraction character
    source[leng] = _char; //Save extracted character in return variable
    leng++; //counting length
  }
  source[leng]='\0';  //Add space character at last of sentence
  return String(source); //return read sentence (format String)
}

//MAX7219 pin set
int dIn = 7; //DIN PIN
int clk = 6; //CLK PIN
int cs = 5; //CS PIN
int moduleUsed = 4; //Number of modules used



MaxMatrix DotMatrix(dIn, cs, clk, moduleUsed); //Creat DotMatrix object
SoftwareSerial Bluetooth(8, 9);  //Creat Bluetooth Serial object (TX, RX)
byte buffer[10]; //buffer array
char recvData; //received data at bluetooth (for using)
int shiftSpeed; //Shift speed
String lastWords = read_String(0); //reading sentence from EEPROM
char text[100] = ""; //Sentence array
int brightness; //Dotmatrix module brightness
int count = 0; //count array
char recvCmd; //received data at bluetooth (for command)


void setup() {
  DotMatrix.init(); //Module init
  DotMatrix.setIntensity(brightness); //Setting brightness
  Bluetooth.begin(9600); //Setting Bluetooth Serial baudrate
  Serial.begin(9600); //Setting Serial baudrate

  //Saving displayed text in the last sentence saved
  for(int i= 0; i < 100; i++){
    text[i] = lastWords[i];
  }


  DotMatrix.setIntensity(EEPROM.read(103)); //Setting brightness from EEPROM
  shiftSpeed = EEPROM.read(102); //Setting shift speed from EEPROM
}


void loop() {
  
  printStringWithShift(text, shiftSpeed); //display sentence
  
  if (Bluetooth.available()) { //Is communication?

    recvCmd = Bluetooth.read(); //read command
    
    /*
     * command 1 : display sentence change 
     */
    if (recvCmd == '1') {

      //sentence clear
      for (int i = 0; i < 100; i++) {
        text[i] = 0;
        DotMatrix.clear();
      }
      write_String(0, text);
      
      //reading text
      while (Bluetooth.available()) { //while end communication
        recvData = Bluetooth.read();
        text[count] = recvData;
        count++;
      }
      count = 0;
      write_String(0, text);

    }
    

    /*
     * command 2 : setting shift speed
     */
    else if (recvCmd == '2') {
      String tempStr = Bluetooth.readString();
      shiftSpeed = 100 - tempStr.toInt(); 
      EEPROM.write(102, shiftSpeed);
    }

    /*
     * command 2 : setting brightness
     */
    else if (recvCmd == '3') {
      String tempStr = Bluetooth.readString();
      brightness = tempStr.toInt();
      EEPROM.write(103, brightness);
      DotMatrix.setIntensity(brightness);
    }
  }
}


  //shifting character
  void printCharWithShift(char c, int shift_speed) {
    if (c < 32) return;
    c -= 32;
    memcpy_P(buffer, ASCII_Font_8 + 7 * c, 7);
    DotMatrix.writeSprite(32, 0, buffer);
    DotMatrix.setColumn(32 + buffer[0], 0);
    for (int i = 0; i < buffer[0] + 1; i++)
    {
      delay(shift_speed);
      DotMatrix.shiftLeft(false, false);
    }
  }

  //shifting all character
  void printStringWithShift(char* s, int shift_speed) {
    while (*s != 0) {
      printCharWithShift(*s, shift_speed);
      s++;
    }
  }

  //print all character
  void printString(char* s)
  {
    int col = 0;
    while (*s != 0)
    {
      if (*s < 32) continue;
      char c = *s - 32;
      memcpy_P(buffer, ASCII_Font_8 + 7 * c, 7);
      DotMatrix.writeSprite(col, 0, buffer);
      DotMatrix.setColumn(col + buffer[0], 0);
      col += buffer[0] + 1;
      s++;
    }
  }
