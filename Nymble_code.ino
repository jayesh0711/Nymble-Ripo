#include <EEPROM.h>
#include <SoftwareSerial.h>

#define  BAUD_RATE 2400
#define TEXT_SIZE 1000
#define TX_PIN 1
#define RX_PIN 0


SoftwareSerial uart(TX_PIN, RX_PIN);
void sendDataFromEEPROM();

void setup() 
{
  Serial.begin(BAUD_RATE);
  uart.begin(BAUD_RATE); 
}

void loop() {
  int address = 0;
  
  
  while (address < TEXT_SIZE) {

    if (uart.available()) 
    {
    
      EEPROM.write(address,uart.read());
      address++;
    }
    
  }

  
  sendDataFromEEPROM();
}

void sendDataFromEEPROM() {
  unsigned long startTime = millis(); 
  for (int i = 0; i < TEXT_SIZE; i++) {
    uart.write(EEPROM.read(i));
  }
  unsigned long endTime = millis(); 
  unsigned long totalTime = endTime - startTime;
  float transmissionSpeed = (TEXT_SIZE * 8.0) / (totalTime / 1000.0); // Calculate speed in bits/second
  Serial.println("Transmission Speed: " + String(transmissionSpeed) + " bits/second");
}
