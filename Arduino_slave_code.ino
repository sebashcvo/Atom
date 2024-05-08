#include <SoftwareSerial.h>

SoftwareSerial slave(0,1);
String val="";
String valx="";


void setup() {
Serial.begin(38400);
slave.begin(38400);
}
void loop() {
 
while(slave.available()>0){
  char c=slave.read();
  val +=c;
  
  delay(10);
}

Serial.println(val);
}
