/*
   RadioLib SX127x Receive Example

   This example listens for LoRa transmissions from multiple SX1276 Lora modules.
   To successfully receive data, the following settings have to be the same
   on both transmitter and receiver:
    - carrier frequency
    - bandwidth
    - spreading factor
    - coding rate
    - sync word
    - preamble length
*/

// include the library
#include <RadioLib.h>
#include <Arduino.h>

// Create Modules for the number of student radios you expect

// SX1278 has the following connections:
// NSS pin:   10
// DIO0 pin:  2
// RESET pin: 9
// DIO1 pin:  3
SX1278 radio = new Module(10, 2, 9, 3);


// SET YOUR SYNC WORD
uint8_t my_password = 'A'; // if you're transmitting, change this to your letter of preference from A to P  
int state;
String str;

void setup() {
    Serial.begin(115200);

    // initialize the radio chip SX1276 with default settings
    Serial.print(F("[SX1278] Initialising ... "));
    state = radio.begin();
}

void loop() {

    // Sweep every millisecond for 15 places (password = ('A','P'))
//    my_password = char((millis()%15)+ 65); // 65 is the Decimal value of char A from ASCII table 
    my_password = 65;
    
    Serial.println(char(my_password));
    if (radio.setSyncWord(my_password) != RADIOLIB_ERR_NONE) { 
        //if something went wrong
        Serial.println(F("Unable to set sync word!"));
        while (true);
    }


    // Returns error code. Wrap this to a function later: 
    if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("Initialisation success!"));
    } else {
    Serial.print(F("failed, state code "));
    Serial.println(state);
    while (true);
    }

    Serial.print(F("[SX1276] Waiting for incoming transmission ... "));

    // you can receive data as an Arduino String
    int state = radio.receive(str);
  
  
    if (state == RADIOLIB_ERR_NONE) {
      // packet was successfully received
      Serial.println(F("success!"));
  
      // print the data of the packet
      Serial.print(F("[SX1278] Data:\t\t\t"));
      Serial.println(str);
  
      // print the RSSI (Received Signal Strength Indicator)
      // of the last received packet
      Serial.print(F("[SX1278] RSSI:\t\t\t"));
      Serial.print(radio.getRSSI());
      Serial.println(F(" dBm"));
  
      // print the SNR (Signal-to-Noise Ratio)
      // of the last received packet
      Serial.print(F("[SX1278] SNR:\t\t\t"));
      Serial.print(radio.getSNR());
      Serial.println(F(" dB"));
  
      // print frequency error
      // of the last received packet
      Serial.print(F("[SX1278] Frequency error:\t"));
      Serial.print(radio.getFrequencyError());
      Serial.println(F(" Hz"));
  
      } else if (state == RADIOLIB_ERR_RX_TIMEOUT) {
      // timeout occurred while waiting for a packet
      Serial.println(F("timeout!"));
  
      } else if (state == RADIOLIB_ERR_CRC_MISMATCH) {
      // packet was received, but is malformed
      Serial.println(F("CRC error!"));

    } else {
      // some other error occurred
      Serial.print(F("failed, code "));
      Serial.println(state);
      Serial.println(my_password);

    }//end of error checks
}
