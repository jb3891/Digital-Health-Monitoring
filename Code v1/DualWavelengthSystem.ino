#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 96 
#define SCREEN_HEIGHT 16

#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS 1000
PulseOximeter pox;
uint32_t tsLastReport = 0;
int O2;
int LEDpmin = 6;
int LEDpmax = 9;
bool s;
bool p;

void onBeatDetected() {
  switch (s) {
    case 0:
      digitalWrite(9,HIGH);
      digitalWrite(7,LOW);
      s = 1;
      break;
    case 1:
      digitalWrite(9,LOW);
      digitalWrite(7,HIGH);
      s = 0;
      break;
  }
}

void setup() {
  Serial.begin(9600);
  //attachInterrupt(digitalPinToInterrupt(4), pswitch, RISING);
  for (int i=LEDpmin; i<=LEDpmax; i++) {
    pinMode(i,OUTPUT);
  }
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH);
  Serial.print("Initialising Oximeter: ");
  if (!pox.begin()) {
    Serial.println("FAILED");
    digitalWrite(6,HIGH);
    digitalWrite(7,LOW);
    for(;;);
  }
  else {
    Serial.println("SUCCESS");
    digitalWrite(6,LOW);
    digitalWrite(7,HIGH);
  }
  pox.setOnBeatDetectedCallback(onBeatDetected);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.display();
}

void loop() {
  pox.update();
  
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    /*Serial.print("Heart rate:");
    int HR = pox.getHeartRate();
    Serial.print(HR);
    Serial.print("bpm / SpO2:");
    Serial.print(pox.getSpO2());
    Serial.println("%");
    display.clearDisplay();
    Serial.print("readings");*/
    Serial.println(p);
    readings();
    while (p==1) {
      halt();
    }       
    
    tsLastReport = millis();
    }
  delay(1);
}
