#include <WiFi.h>
#include <WiFiUDP.h>
#include "common.h"
#include "func_cpp.h"

void setup() {
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);

  memcpy(disp_data[1], thanks, sizeof(thanks));
  memcpy(disp_data[0], pika, sizeof(pika));

  gpio_put(oe, HIGH);

  // reset the connection
  WiFi.disconnect(true);
  delay(500);

  WiFi.mode(WIFI_STA);
  WiFi.config(myIP);

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
  }

  Udp.begin(5000);
}

void loop() {
  // udp data check
  int packetSize = Udp.parsePacket();
  if (packetSize){  
    memset(packetBuffer,0,sizeof(packetBuffer));
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    // message to specify display data panel to core1
    if (packetBuffer[0] == 'A'){
      if (init_disp == true){
        message_s = 1;
      } else {
        if (img_pointer == 0){
          if (plane == 0){
            memcpy(disp_data[1], thanks, sizeof(thanks));
            message_s = 1;

          } else{
            memcpy(disp_data[0], thanks, sizeof(thanks));
            message_s = 0;
            }
          img_pointer += 1;
        } else{
          if (img_pointer == 1){
            if (plane == 0){
              memcpy(disp_data[1], akafuji, sizeof(akafuji));
              message_s = 1;
            } else{
              memcpy(disp_data[0], akafuji, sizeof(akafuji));
              message_s = 0;
              }
          img_pointer += 1;
          } else{
            if (img_pointer == 2){
            if (plane == 0){
              memcpy(disp_data[1], pika, sizeof(pika));
              message_s = 1;
            } else{
            memcpy(disp_data[0], pika, sizeof(pika));
            message_s = 0;
            }
            img_pointer = 0;
            }
          }}
      }
    } else {
      if (packetBuffer[0] == 'C'){
        message_s = 9;
      }
    }
    rp2040.fifo.push(message_s);  // send message to core1
  }
  // board led indication
  //
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);

  }
}

void setup1(){
  // set the gpio pins direction
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);    
  pinMode(g1, OUTPUT);
  pinMode(g2, OUTPUT);    
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);    
  pinMode(clk, OUTPUT);    
  pinMode(lat, OUTPUT);
  pinMode(oe, OUTPUT);    
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);    
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);

  gpio_put(oe, HIGH);
  gpio_put(lat, LOW);
  gpio_put(clk, LOW);
}

void loop1(){
  if (init_disp == true){
    init_disp = false;
    delay(2000);
  }
  // message check from core0
  //
  while (rp2040.fifo.available()>0){
    // bool rp2040.fifo.pop_nb(uint32_t *dest)
    message = rp2040.fifo.pop();
  }
 
  if (message == 0 || message == 1){
      plane = message;
      refresh();
    } else {
      gpio_put(oe, HIGH);
  }
}
