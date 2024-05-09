#include <SoftwareSerial.h>

SoftwareSerial slave(0,1);
String val="";
int valx=0;
String msg="";


void setup() {
Serial.begin(38400);
slave.begin(38400);
}
void loop() {
 
while(slave.available()>0){
  msg = Serial.readStringUntil('\n');
  int axis=msg.length()-1;
  String s_angulox = msg.substring(0,axis);
  int angulox = s_angulox.toInt();
  String completter=msg.substring(axis);
  if(completter=="X"){
    valx=angulox;
    Serial.println(valx);
  }
  
  }
  
  }
