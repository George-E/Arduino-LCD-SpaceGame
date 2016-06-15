
#include <LiquidCrystal.h>
#include <pitches.h>

byte person[8] = {
  0b11100,
  0b11100,
  0b01000,
  0b01100,
  0b01000,
  0b01100,
  0b10010,
  0b10001
};

byte person2[8] = {
  0b01110,
  0b01110,
  0b00100,
  0b00110,
  0b00100,
  0b00100,
  0b01010,
  0b01010
};

byte boulder [8] = {
  0b00100,
  0b01110,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100
};

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int joyX = A1;                 
int joyY = A0;              
int joyButton = 0;        
int joyXvalue = 0;
int joyYvalue = 0;                 
boolean joyButtonValue = 0; 
 
int y = 1;
int x = 4;
int frame = 0;

int piezo = 1;
int greenLed = 8;
int yellowLed = 7;
int redLed = 6;

//(pins for shift register / seven segment display
int dataPin = 9; //SER (serial data bit in) (pin 14 on shift register)
int latchPin = 13; //RCLK (output register clock) (pin 12)
int clockPin = 10; //SRCLK (Output register clock) (pin 11)
//tutorial mixed up latch and clock!!
int score = 0;
byte numberConfigs[] = {B11111100, B01100000, B11011010, B11110010, B01100110,B10110110,B10111110,B11100000,B11111110,B11100110}; //0,1,..9


void setup() {
  //Serial.begin(9600);
  
  // initialize LCD and set up the number of columns and rows: 
  lcd.begin(16, 2);
  
  // create a new characters
  lcd.createChar(0, person);
  lcd.createChar(1, person2);
  
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  digitalWrite(greenLed, HIGH);
  
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  shiftOut(dataPin, clockPin, MSBFIRST, numberConfigs[score]); 
  digitalWrite(latchPin, LOW);
  digitalWrite(latchPin, HIGH);
    
    
  // Print a message to the lcd.
  /*lcd.print("I "); 
  lcd.write(byte(0)); // when calling lcd.write() '0' must be cast as a byte
  lcd.print(" Arduino! ");
  lcd.write(1);*/
}

int treatJoyValue(int data) {
  return (data = map(data, 0, 1024, 0, 100)) ;
}

void loop() {
  joyXvalue = treatJoyValue(analogRead(joyX)); 
  joyYvalue = treatJoyValue(analogRead(joyY));  
  joyButtonValue = digitalRead(joyButton);  
  
  /*Serial.print(joyXvalue);
  Serial.print(" ");
  Serial.print(joyYvalue);
  Serial.print(" ");
  Serial.println(joyButtonValue);*/
  
  if (joyYvalue > 75) {
    y = 0;
    tone(piezo, NOTE_A4, 20);
  } else if (joyYvalue < 25) {
    y =1;
    tone(piezo, NOTE_A4, 20);
  }
  
  if (joyXvalue > 75 && x<15) {
    x++;
    tone(piezo, NOTE_A4, 20);
  } else if (joyXvalue < 25 && x>0) {
    x--;
    tone(piezo, NOTE_A4, 20);
  }
  
  lcd.clear();
  lcd.setCursor(x, y);
  lcd.write(byte(frame % 2));
  delay(600);
  frame++;
}
 
 
 
