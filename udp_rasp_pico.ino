#include <WiFi.h>
#include <WiFiUDP.h>
#include <M5Stack.h>

const char ssid[] = "TP-LINK_8FBE";
const char pass[] = "17559294";

WiFiUDP wifiUdp; 
const char *pc_addr = "192.168.1.201";
const int pc_port = 5000;   // dest port
const int my_port = 5001;   // rcv port

const IPAddress IP(192, 168, 1, 200);
const IPAddress GATEWAY(192, 168, 1, 1);
const IPAddress NETMASK(255, 255, 255, 0);
const IPAddress DNS(192, 168, 1, 1);

void setup() {
  M5.begin();
  M5.Power.begin();
  M5.Lcd.setTextSize(2);

  WiFi.begin(ssid, pass);
  // set fixed IP
  if (!WiFi.config(IP, GATEWAY, NETMASK, DNS)) {
    Serial.println("Failed to configure!");
  }

  while( WiFi.status() != WL_CONNECTED) {
    delay(500); 
    M5.Lcd.print("."); 
  }  
  M5.Lcd.println("WiFi connected");
  M5.Lcd.print("IP address = ");
  M5.Lcd.println(WiFi.localIP());
  
  wifiUdp.begin(my_port);
}

void loop(){
  M5.update();

  if(M5.BtnA.wasReleased()){
    wifiUdp.beginPacket(pc_addr, pc_port);
    wifiUdp.write('A');
    wifiUdp.endPacket();
    M5.Lcd.print("a");
  } else if(M5.BtnB.wasReleased()){
    wifiUdp.beginPacket(pc_addr, pc_port);
    wifiUdp.write('B');
    wifiUdp.endPacket();
    M5.Lcd.print("b");
  } else if(M5.BtnC.wasReleased()){
    wifiUdp.beginPacket(pc_addr, pc_port);
    wifiUdp.write('C');
    wifiUdp.endPacket();
    M5.Lcd.print("c");
  }

  delay(100);

}