#include <SoftwareSerial.h>
#include "Wire.h"
#include <MPU6050_light.h>

MPU6050 mpu(Wire);


unsigned long timer = 0;
 

SoftwareSerial master(0,1);
 //input de datos proveniente del sensor mpu
int valy=0;


void setup() {
Serial.begin(38400);
master.begin(38400);
Wire.begin();


byte status = mpu.begin();
   Serial.print(F("MPU6050 status: "));
   Serial.println(status);
   while (status != 0) { } // stop everything if could not connect to MPU6050
 Serial.println(F("Calculating offsets, do not move MPU6050"));
   delay(1000);
   mpu.calcOffsets(); // gyro and accelero
   Serial.println("Done!\n");
 }

void loop() {
  mpu.update();
  int valx= mpu.getAngleX();
  int valz= mpu.getAngleZ();
 
  String letterx="X\n"; //String con funcion de Label
  String lettery="Y\n";
  String letterz="Z\n";
  String msgx=valx+letterx; //Valor Input con el label 
  String msgy=valy+lettery;
  String msgz=valz+letterz;
  Serial.print(msgx);
  Serial.print(msgz);//Print en el Serial
  delay(100);
}
