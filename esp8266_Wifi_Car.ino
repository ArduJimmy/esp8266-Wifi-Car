/*
 * Ardujimmy ESP8266 Wifi Car with App.Inventor.2
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

#define ENA   14          //GPIO14(D5)
#define ENB   12          //GPIO12(D6)
#define IN_1  15          //GPIO15(D8)
#define IN_2  13          //GPIO13(D7)
#define IN_3  2           //GPIO2(D4)
#define IN_4  0           //GPIO0(D3)

String command;
int speedCar = 800;
int speed_Coeff = 3;

const char* ssid = "Ardujimmy";
ESP8266WebServer server(80);

void setup() {
Serial.begin(115200);
pinMode(ENA, OUTPUT);
pinMode(ENB, OUTPUT);  
pinMode(IN_1, OUTPUT);
pinMode(IN_2, OUTPUT);                                                                                                                                                                                                                     
pinMode(IN_3, OUTPUT);
pinMode(IN_4, OUTPUT); 
  
//Let's connec to WiFi

  WiFi.mode(WIFI_AP); // Wifi APP (Access Point)
  WiFi.softAP(ssid);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: "); //Your IP Address should be: 192.168.1.1 / 192.168.1.2 / 192.168.4.1
  Serial.println(myIP);
 
 //Starting WEB-server 
   server.on ( "/", HTTP_handleRoot );
   server.onNotFound ( HTTP_handleRoot );
   server.begin();    
}

void goAhead(){ 
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
  }
void goBack(){ 
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }
void goRight(){ 
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
  }
void goLeft(){
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }

void goAheadRight(){
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar/speed_Coeff);
 
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
   }
void goAheadLeft(){
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar/speed_Coeff);
  }
void goBackRight(){ 
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar/speed_Coeff);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }
void goBackLeft(){ 
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar/speed_Coeff);
  }

void stopRobot(){  

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
 }
void loop() {
    server.handleClient();
      command = server.arg("State");
      if (command == "F") goAhead();
      else if (command == "B") goBack();
      else if (command == "L") goLeft();
      else if (command == "R") goRight();
      else if (command == "I") goAheadRight();
      else if (command == "G") goAheadLeft();
      else if (command == "J") goBackRight();
      else if (command == "H") goBackLeft();
      else if (command == "0") speedCar = 400;
      else if (command == "1") speedCar = 470;
      else if (command == "2") speedCar = 540;
      else if (command == "3") speedCar = 610;
      else if (command == "4") speedCar = 680;
      else if (command == "5") speedCar = 750;
      else if (command == "6") speedCar = 820;
      else if (command == "7") speedCar = 890;
      else if (command == "8") speedCar = 960;
      else if (command == "9") speedCar = 1023;
      else if (command == "S") stopRobot();
}

void HTTP_handleRoot(void) {
if( server.hasArg("State") ){
    Serial.println(server.arg("State"));
    }
    server.send ( 200, "text/html", "" );
    delay(1);
}
