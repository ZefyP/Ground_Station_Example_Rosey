/*
  This is a simple example show the Heltec.LoRa recived data in OLED.

  The onboard OLED display is SSD1306 driver and I2C interface. In order to make the
  OLED correctly operation, you should output a high-low-high(1-0-1) signal by soft-
  ware to OLED's reset pin, the low-level signal at least 5ms.

  OLED pins to ESP32 GPIOs via this connecthin:
  OLED_SDA -- GPIO4
  OLED_SCL -- GPIO15
  OLED_RST -- GPIO16

*/
#include "heltec.h" 

#define BAND    868E6  //you can set band here directly,e.g. 868E6,915E6
String rssi = "RSSI --";
String packSize = "--";
String packet ;

void OLED_display_LoRaData(){
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0 , 15 , "Received "+ packSize + " bytes");
  Heltec.display->drawStringMaxWidth(0 , 26 , 128, packet);
  Heltec.display->drawString(0, 0, rssi+ " db");  
  Heltec.display->display();
}

void cbk(int packetSize) {
  packet ="";
  packSize = String(packetSize,DEC);
  for (int i = 0; i < packetSize; i++) { packet += (char) LoRa.read(); }
  rssi = "RSSI " + String(LoRa.packetRssi(), DEC) ;
  OLED_display_LoRaData();
  Serial.println(packet);
}

void setup() { 
  //init serial communication 
  Serial.begin(115200);

  //init radio
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
 
  Heltec.display->init(); 
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->clear();
  
  Heltec.display->drawString(0, 0, "Heltec.LoRa Initial success!");
  Heltec.display->drawString(0, 10, "Wait for incoming data...");
  Heltec.display->display();
  delay(1000);
  //LoRa.onReceive(cbk);
  LoRa.receive();
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) { cbk(packetSize);  }
  delay(10);
}








//
//
////-----------------------
//// include the library
//#include <RadioLib.h>
//
//// SX1278 has the following connections:
//// NSS pin:   10
//// DIO0 pin:  2
//// RESET pin: 9
//// DIO1 pin:  3
//SX1276 radio = new Module(18, 26, 14);
//// or using RadioShield
//// https://github.com/jgromes/RadioShield
////SX1278 radio = RadioShield.ModuleA;
//
//void setup() {
//  Serial.begin(115200);
//
//  // initialize SX1278 with default settings
//  Serial.print(F("[SX1276] Initialising ... "));
//  int state = radio.begin();
//  if (state == RADIOLIB_ERR_NONE) {
//    Serial.println(F("success!"));
//  } else {
//    Serial.print(F("failed, code "));
//    Serial.println(state);
//    while (true);
//  }
//}
//
//void loop() {
//  Serial.print(F("[SX1276] Waiting for incoming transmission ... "));
//
//  // you can receive data as an Arduino String
//  // NOTE: receive() is a blocking method!
//  //       See example ReceiveInterrupt for details
//  //       on non-blocking reception method.
//  String str;
//  int state = radio.receive(str);
//
//  // you can also receive data as byte array
//  /*
//    byte byteArr[8];
//    int state = radio.receive(byteArr, 8);
//  */
//
//  if (state == RADIOLIB_ERR_NONE) {
//    // packet was successfully received
//    Serial.println(F("success!"));
//
//    // print the data of the packet
//    Serial.print(F("[SX1276] Data:\t\t\t"));
//    Serial.println(str);
//
//    // print the RSSI (Received Signal Strength Indicator)
//    // of the last received packet
//    Serial.print(F("[SX1276] RSSI:\t\t\t"));
//    Serial.print(radio.getRSSI());
//    Serial.println(F(" dBm"));
//
//    // print the SNR (Signal-to-Noise Ratio)
//    // of the last received packet
//    Serial.print(F("[SX1276] SNR:\t\t\t"));
//    Serial.print(radio.getSNR());
//    Serial.println(F(" dB"));
//
//    // print frequency error
//    // of the last received packet
//    Serial.print(F("[SX1276] Frequency error:\t"));
//    Serial.print(radio.getFrequencyError());
//    Serial.println(F(" Hz"));
//
//  } else if (state == RADIOLIB_ERR_RX_TIMEOUT) {
//    // timeout occurred while waiting for a packet
//    Serial.println(state+ "----");
//    Serial.println(F("timeout!"));
//
//  } else if (state == RADIOLIB_ERR_CRC_MISMATCH) {
//    // packet was received, but is malformed
//    Serial.println(F("CRC error!"));
//
//  } else {
//    // some other error occurred
//    Serial.print(F("failed, code "));
//    Serial.println(state);
//
//  }
//
//  delay(100);
//}
