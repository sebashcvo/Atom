#include <SoftwareSerial.h>

SoftwareSerial master(0,1);
float valx=96.27; //input de datos proveniente del sensor mpu
float valy=100.15;
float valz=-80.96;
void setup() {
Serial.begin(38400);
master.begin(38400);
}
void loop() {
  String letterx="X\n"; //String con funcion de Label
  String lettery="Y\n";
  String letterz="Z\n";
  String msgx=valx+letterx; //Valor Input con el label 
  String msgy=valy+lettery;
  String msgz=valz+letterz;
  Serial.print(msgx); //Print en el Serial
  Serial.print(msgy);
  Serial.print(msgz);
  delay(10);
}
