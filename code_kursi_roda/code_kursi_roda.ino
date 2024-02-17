/////asuuuuuuuuu
//////jancukkkkkkkk
#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"
VR myVR(11, 12);   // 2:RX 3:TX, you can choose your favourite pins.

//PIN ULTRASONIK
int echoPin_2 = 4;    // Echo
int echoPin_3 = 7;    // Echo
int echoPin_4 = 8;    // Echo
int echoPin_1 = 3;    // Echo
int trigPin = 2;    //Trigger
int cm_1, cm_2;
int pwm = 13;
// Motor A
int motor1Pin1 = 5;
int motor1Pin2 = 6; 
// Motor B
int motor2Pin1 = 9;
int motor2Pin2 = 10;
//variabel pwm
int FPWM[] = {255, 225, 200, 175, 150,125, 100, 75, 50, 25, 0};

uint8_t records[7]; // save record
uint8_t buf[64];
#define maju    (0)
#define mundur   (1)
#define belok_kiri   (2)
#define belok_kanan    (3)
#define stopp  (4)

void printSignature(uint8_t *buf, int len)
{
  int i;
  for (i = 0; i < len; i++) {
    if (buf[i] > 0x19 && buf[i] < 0x7F) {
      Serial.write(buf[i]);
    }
    else {
      Serial.print("[");
      Serial.print(buf[i], HEX);
      Serial.print("]");
    }
  }
}

/**
  @brief   Print signature, if the character is invisible,
           print hexible value instead.
  @param   buf  -->  VR module return value when voice is recognized.
             buf[0]  -->  Group mode(FF: None Group, 0x8n: User, 0x0n:System
             buf[1]  -->  number of record which is recognized.
             buf[2]  -->  Recognizer index(position) value of the recognized record.
             buf[3]  -->  Signature length
             buf[4]~buf[n] --> Signature
*/
void printVR(uint8_t *buf)
{
  //  Serial.println("VR Index\tGroup\tRecordNum\tSignature");

  //  Serial.print(buf[2], DEC);
  //  Serial.print("\t\t");

  if (buf[0] == 0xFF) {
    //    Serial.print("NONE");
  }
  else if (buf[0] & 0x80) {
    //    Serial.print("UG ");
    //    Serial.print(buf[0]&(~0x80), DEC);
  }
  else {
    //    Serial.print("SG ");
    //    Serial.print(buf[0], DEC);
  }
  //  Serial.print("\t");

  //  Serial.print(buf[1], DEC);
  //  Serial.print("\t\t");
  if (buf[3] > 0) {
    printSignature(buf + 4, buf[3]);
  }
  else {
    //    Serial.print("NONE");
  }
  //  Serial.println("\r\n");
}

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin_1, INPUT);
  pinMode(echoPin_2, INPUT);
  pinMode(echoPin_3, INPUT);
  pinMode(echoPin_4, INPUT);
  pinMode(pwm, OUTPUT);
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  /** initialize */
  myVR.begin(9600);

  Serial.begin(115200);
  Serial.println("Elechouse Voice Recognition V3 Module\r\nControl wheel chair");

  if (myVR.clear() == 0) {
    Serial.println("Recognizer cleared.");
  } else {
    Serial.println("Not find VoiceRecognitionModule.");
    Serial.println("Please check connection and restart Arduino.");
    while (1);
  }
  if (myVR.load((uint8_t)maju) >= 0) {
  }
  if (myVR.load((uint8_t)mundur) >= 0) {
  }
  if (myVR.load((uint8_t)belok_kiri) >= 0) {
  }
  if (myVR.load((uint8_t)belok_kanan) >= 0) {
  }
  if (myVR.load((uint8_t)stopp) >= 0) {
  }
}

void loop() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  voice();
  cm_1 = ultra(trigPin, echoPin_4, 4);
  cm_2 = ultra(trigPin, echoPin_1, 1);
  if (cm_1 or cm_2 < 50)
  {
//    digitalWrite(buzzer, HIGH);

  }


}
