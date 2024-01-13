//jb3891
void readings() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);    
  display.setTextSize(1);    
  display.setCursor(0,0);
  Serial.println("A");
  //pox.update();
    
  while ((pox.getHeartRate()<60) || (pox.getSpO2()<90)) {
    display.setCursor(0,0);
    display.print("Place finger    over the light");
    digitalWrite(6,LOW);
    digitalWrite(8,LOW);
    digitalWrite(7,LOW);
    display.display();
    pox.update();
  }
    digitalWrite(8,HIGH);
    display.clearDisplay();
    int HR = pox.getHeartRate();
    display.printf("%8s", "BPM:");
    display.printf("%4d", HR);
    display.println();

    if (pox.getSpO2()>100) {
      O2 = 100;
    }
    else {
      O2 = pox.getSpO2();
    }
    display.printf("%8s", "SpO2:");
    display.printf("%4d", O2);
    display.println("%");
        
  display.display();
}
//jb3891
void halt() {
  display.clearDisplay();
    display.drawRect(7, 0, 4, 16, SSD1306_WHITE);
    display.drawRect(15, 0, 4, 16, SSD1306_WHITE);
    display.setCursor(0,0);

    int HR = pox.getHeartRate();
    display.printf("%10s", "BPM:");
    display.printf("%4d", HR);
    display.println();

    if (pox.getSpO2()>100) {
      O2 = 100;
    }
    else {
      O2 = pox.getSpO2();
    }
    display.printf("%10s", "SpO2:");
    display.printf("%4d", O2);
    display.println("%");
        
  display.display();
}
void pswitch() {
  switch (p) {
    case 0:
      p = 1;
      break;
    case 1:
      p = 0;
      break;
  }
}
//jb3891
