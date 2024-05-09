#include <SoftwareSerial.h>

SoftwareSerial master(0,1);
int valx=-180.27;

void setup() {
Serial.begin(38400);
master.begin(38400);
}
void loop() {
  String letter="X\n";
  String msg=valx+letter;
  Serial.print(msg);
  delay(100);
}
