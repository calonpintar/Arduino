
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <SPI.h>    

#include <OSCBundle.h>
#include <OSCBoards.h>

const int RELAY_PIN1 = 3;
const int RELAY_PIN2 = 4;

EthernetUDP Udp;
byte mac[] = {  
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //Arduino custom MAC Address

//the Arduino's IP
IPAddress ip(192,168,1, 201);

//port numbers
const unsigned int inPort = 9090;

void setup() {
  //setup ethernet part
  Ethernet.begin(mac,ip);
  Udp.begin(inPort);

  pinMode(RELAY_PIN1, OUTPUT);
  pinMode(RELAY_PIN2, OUTPUT);
  
  Serial.begin(9600);

}

void route1(OSCMessage &msg, int addrOffset ){
 if (msg.getFloat(0) == 1) {digitalWrite(RELAY_PIN1, LOW);} else {digitalWrite(RELAY_PIN1, HIGH);}
}
void route2(OSCMessage &msg, int addrOffset ){
 if (msg.getFloat(0) == 1) {digitalWrite(RELAY_PIN2, LOW);} else {digitalWrite(RELAY_PIN2, HIGH);}
}

void loop(){ 
    OSCBundle bundleIN;
   int size;
 
   if( (size = Udp.parsePacket())>0)
   {
     while(size--)
       bundleIN.fill(Udp.read());

      if(!bundleIN.hasError())
        bundleIN.route("/osc/setting1", route1);
        bundleIN.route("/osc/setting2", route2);
   }
}
