#define USB_CFG_DEVICE_NAME     'B','T','C'
#define USB_CFG_DEVICE_NAME_LEN 3
#include <DigiUSB.h>

#define RESTART_TIME 10

byte in = 0;
static uint32_t detected = millis();

void setup() {
    DigiUSB.begin();
    pinMode(1, OUTPUT); //LED on Model B
}

void restartPC() {
  for(int i =0; i < 30; i++)
  {
    digitalWrite(1, !digitalRead(1));
    delay(100);
  }
}

void loop() { 
     DigiUSB.refresh();   
     if (DigiUSB.available() > 0) {
       in = 0;       
       in = DigiUSB.read();

        if(in == 'a'){
          detected = millis();
          digitalWrite(1, !digitalRead(1));
        }      
     }

     if(millis() - detected > RESTART_TIME * 1000)
     {
        restartPC();
        DigiUSB.println("Restart");
        detected = millis();
     }
 }


