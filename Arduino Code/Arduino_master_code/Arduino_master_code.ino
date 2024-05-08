#include <SoftwareSerial.h>

SoftwareSerial master(0,1);

void setup() {
Serial.begin(38400);
master.begin(38400);
}
void loop() {
  String val= "X180";
  Serial.println(val);
  delay(100);
}
