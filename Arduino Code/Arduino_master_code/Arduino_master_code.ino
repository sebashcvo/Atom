#include <SoftwareSerial.h>

SoftwareSerial master(0,1);
float valx=96.27;
float valy=100.15;
float valz=-80.96;
void setup() {
Serial.begin(38400);
master.begin(38400);
}
void loop() {
  String letterx="X\n";
  String lettery="Y\n";
  String letterz="Z\n";
  String msgx=valx+letterx;
  String msgy=valy+lettery;
  String msgz=valz+letterz;
  Serial.print(msgx);
  Serial.print(msgy);
  Serial.print(msgz);
  delay(100);
}
