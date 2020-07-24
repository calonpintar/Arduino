#include <Filters.h>
#include <ArduinoOSC.h>

// Ethernet stuff
const IPAddress ip(192, 168, 1, 201);
uint8_t mac[] = {0x01, 0x23, 0x45, 0x67, 0x88, 0xA1};

// for ArduinoOSC
OscEthernet osc;
const char* host = "192.168.1.10";
const int recv_port = 10000;
const int send_port = 9191;

int potPin1 = 0;   
int potPin2 = 4;   
int val1, val2 = 0; 
float filterFrequency = 3.0  ;     
FilterOnePole lowpassFilter1( LOWPASS, filterFrequency ); 
FilterOnePole lowpassFilter2( LOWPASS, filterFrequency ); 

void setup() {
  Serial.begin(9600);
  // Ethernet stuff
  Ethernet.begin(mac, ip);
}

void loop() {
  val1 = lowpassFilter1.input( analogRead( potPin1 ) );
  val2 = lowpassFilter2.input( analogRead( potPin2 ) ); 
  //Serial.println(val2);
  //Serial.println(val2);

  OscMessage msg(host, send_port, "/arduino/osc");
  msg.push(val1);
  msg.push(val2);
  osc.send(msg);
  osc.parse(); // should be called
  delay(1);                 
}
