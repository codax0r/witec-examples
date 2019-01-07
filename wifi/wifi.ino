/*

 This example connects to an unencrypted Wifi network.
 Then it prints the  MAC address of the Wifi shield,
 the IP address obtained, and other network details.

 Circuit:
 * WiFi shield attached

 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe
 */
#include <SPI.h>
#include <WiFi.h>
#include <Wire.h>
#include "SSD1306Wire.h" 

char ssid[] = "";     //  your network SSID (name)
char pass[] = "";  // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status
SSD1306Wire  display(0x3c, 21, 22);

void disp(char* c) {
  
  display.clear();
  display.println(c);
  display.drawLogBuffer(0, 0);
  display.display();
  delay(2000);
}

void setup() {
  display.init();  
  display.setContrast(255);
  display.setLogBuffer(5, 30);
  
  display.clear();
  display.println("Initializing..");
  display.drawLogBuffer(0, 0);
  display.display();
  delay(5000);
  //Initialize serial and wait for port to open:
  //Serial.begin(9600);
//  while (!Serial) {
//    ; // wait for serial port to connect. Needed for native USB port only
//  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    disp("WiFi shield not present");
    // don't continue:
    while (true);
  }

  //String fv = WiFi.firmwareVersion();
  //if (fv != "1.1.0") {
  //  Serial.println("Please upgrade the firmware");
  //}

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    display.println("Attempting to connect to WPA SSID: ");
    display.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // you're connected now, so print out the data:
  display.println("You're connected to the network");
  printCurrentNet();
  printWifiData();

}

void loop() {
  // check the network connection once every 10 seconds:
  delay(10000);
  printCurrentNet();
}

void printWifiData() {
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  display.println("IP Address: ");
  display.println(ip);
  display.println(ip);

  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  display.print("MAC address: ");
  display.print(mac[5], HEX);
  display.print(":");
  display.print(mac[4], HEX);
  display.print(":");
  display.print(mac[3], HEX);
  display.print(":");
  display.print(mac[2], HEX);
  display.print(":");
  display.print(mac[1], HEX);
  display.print(":");
  display.println(mac[0], HEX);

}

void printCurrentNet() {
  // print the SSID of the network you're attached to:
  display.print("SSID: ");
  display.println(WiFi.SSID());

  // print the MAC address of the router you're attached to:
//  byte bssid[6];
//  WiFi.BSSID(bssid);
//  Serial.print("BSSID: ");
//  Serial.print(bssid[5], HEX);
//  Serial.print(":");
//  Serial.print(bssid[4], HEX);
//  Serial.print(":");
//  Serial.print(bssid[3], HEX);
//  Serial.print(":");
//  Serial.print(bssid[2], HEX);
//  Serial.print(":");
//  Serial.print(bssid[1], HEX);
//  Serial.print(":");
//  Serial.println(bssid[0], HEX);
//
//  // print the received signal strength:
//  long rssi = WiFi.RSSI();
//  Serial.print("signal strength (RSSI):");
//  Serial.println(rssi);
//
//  // print the encryption type:
//  byte encryption = WiFi.encryptionType();
//  Serial.print("Encryption Type:");
//  Serial.println(encryption, HEX);
//  Serial.println();
}
