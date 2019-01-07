/*
 *  This sketch sends a message to a TCP server
 *
 */

#include <WiFi.h>
#include <WiFiMulti.h>
#include <WebServer.h>
#include <Wire.h>
#include "SSD1306Wire.h" 

WiFiMulti WiFiMulti;

char ssid[] = "";     //  your network SSID (name)
char pass[] = "";  // your network password
SSD1306Wire  display(0x3c, 21, 22);
WebServer server(80);

const int led = 13;

void handleRoot() {
  disp("client connected\n");
  server.send(200, "text/plain", "hello from esp8266!");
  //digitalWrite(led, 0);
}

void disp(char* c) {
  display.clear();
  display.print(c);
  display.drawLogBuffer(0, 0);
  display.display();
  delay(2000);
}

void setup() {
    display.init();  
    display.flipScreenVertically();
    display.setContrast(255);
    display.setLogBuffer(5, 30);
    disp("connecting...\n");
    disp("Network: \n");
    disp(ssid);
    disp("\n");   

    // We start by connecting to a WiFi network
    WiFiMulti.addAP(ssid, pass);

    disp("Waiting for WiFi...\n");

    while(WiFiMulti.run() != WL_CONNECTED) {
        disp(".");
        delay(500);
    }

    disp("WiFi connected\n");
    disp("IP addr: ");

    display.clear();
    display.print(WiFi.localIP());
    display.drawLogBuffer(0, 0);
    display.display();
    disp("\n");
    delay(50);
    server.on("/", handleRoot);
    server.begin();
    disp("started HTTP Server\n");
}


void loop() {
    server.handleClient();
}
