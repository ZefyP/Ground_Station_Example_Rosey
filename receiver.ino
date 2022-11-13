/* 
  Check the new incoming messages, and print via serialin 115200 baud rate.
  by Zefy Pissaki from Project Sunride, Sheffield, UK
*/
//libraries:
#include "Arduino.h"
#include "heltec.h"

//Set frequency band here directly,e.g. 868E6,915E6
#define BAND    868E6 

unsigned int counter = 0; //number of messages received
int rssi = 0; //signal strength
String packSize = "--";  //message size
String packet;           //the text message
int packetSize = 0 ;

void setup() {
  //setup the radio
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  Heltec.display -> clear();

}

void loop() {
  // try to parse packet
  packet = ""; //clear the variable of the message by setting is empty
  int packetSize = LoRa.parsePacket();
  packSize = String(packetSize,DEC);

  if (packetSize) {
    // received a packet
    Serial.print("Received packet, ");
    // read packet while the radio is active
    while (LoRa.available()) {
      packet += (char) LoRa.read(); //save the received message in a variable
      //Serial.print((char)LoRa.read());
    }
    // print RSSI of packet
    Serial.print(packet + "' with signal strength RSSI (db) ");
    rssi = LoRa.packetRssi();
    
    Serial.println(rssi);
    displayReceive();
  }
}


void displayReceive()
{
    Heltec.display -> drawString(0, 0, "Size," + packSize+"rssi, " + String(rssi) + ",db");
    Heltec.display -> drawString(0, 10, packet);
    Heltec.display -> drawString(0, 20, "rssi, " + String(rssi) + ",db");
    Heltec.display -> display();
    delay(100);
    Heltec.display -> clear();
}