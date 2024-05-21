
#include "Wire.h"
#include <MPU6050_light.h>

MPU6050 mpu(Wire);


unsigned long timer = 0;


void setup() {
Serial.begin(38400);

Wire.begin();
pinMode(9,OUTPUT); //Led Indicador
byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n");
}


void loop() {
  mpu.update();
  int valx1= mpu.getAngleX();
  String letterx="X1\n"; //String con funcion de Label
  String msgx=valx1+letterx; //Valor Input con el label 
  
   int valz= mpu.getAngleZ();
   String letterz="Z3\n"; //String con funcion de Label
  String msgz=valz+letterz; //Valor Input con el label 
  Serial.print(msgx);
  Serial.print(msgz);

  delay(100);
}
