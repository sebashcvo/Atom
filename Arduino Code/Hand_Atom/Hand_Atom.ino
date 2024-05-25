 #include <SoftwareSerial.h>
#include "Wire.h"
#include <MPU6050_light.h>

MPU6050 mpu(Wire);


unsigned long timer = 0;
 
SoftwareSerial hand(10,11);//rx y tx


void setup() {
Serial.begin(38400);
hand.begin(38400);
Wire.begin();
pinMode(9,INPUT);

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
  //Datos provenientes del Arduino Arm (Eslabon 1)
  while(hand.available()>0){   //Condicion en donde solo se accede a Serial cuando hay dato disponible
  String msg = hand.readStringUntil('\n');   //El string dentro del Serial solo se lee hasta tener salto de linea
  Serial.println(msg);
  }

  //Angulo X Eslabon 2
  mpu.update();
  int valx2= mpu.getAngleX();
  String letterx2="2"; //String con funcion de Label
  String space="\n";
  String msgx2=letterx2+valx2+space; //Valor Input con el label 
  Serial.print(msgx2);

  int valy4= mpu.getAngleY();
  String lettery4="4"; //String con funcion de Label
  String msgy4=lettery4+valy4+space; //Valor Input con el label 
  Serial.print(msgy4);

  int flex= analogRead(9);
  String letterf="5";
  String msgf=letterf+flex+space; //Valor Input con el label 
  
  delay(100);
}
  
