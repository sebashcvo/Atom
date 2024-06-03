#include <SoftwareSerial.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
#include <Arduino.h>

//Setup Angulos y SoftwareSerial
SoftwareSerial slave(10,11); //rx y tx

int valx1=0;
int valx2=0;
int valy2=0;//variable para almacenar angulo en X

String msg="";

//Setup PWM Driver para Servos
Adafruit_PWMServoDriver servos1 = Adafruit_PWMServoDriver(0x40);
unsigned int pos0=102; //ancho en pulso de cuentas para 0 grados, DEPENDE DEL MOTOR
unsigned int pos180=511; //ancho en pulso de cuentas para 180 grados
int tiempo = 100;
int prev_5 = 1000;

void setup() {
  //Setup Bluetooth
  Serial.begin(38400);
  slave.begin(38400);

  //Setup Servos
  servos1.begin();
  servos1.setPWMFreq(50);

}//end void setup

//Funcion para controlar SERVOS
void setServo(uint8_t n_servo, int angulo){
  int duty;
  if (n_servo==0){
    //Servo Izquierdo Eslabon 1 "X"
    int pos90 = pos180 / 2;
    angulo = constrain(angulo,0,90);
    duty = map(angulo,0,90,pos90,450);
    servos1.setPWM(n_servo, 0, duty);
  }//end if
  else if (n_servo==1){
    //Servo Derecho Eslabon 1 "X"
    int pos90 = pos180 / 2;
    angulo = constrain(angulo,0,90);
    duty = map(angulo,0,90,pos90,80);
    servos1.setPWM(n_servo, 0, duty);
  }//end else if
  else if (n_servo==3){
    //Servo Giro de Garra "Y"
    angulo = constrain(angulo,-90,90);
    duty = map(angulo,-90,90,pos0,pos180);
    servos1.setPWM(n_servo, 0, duty);
  }//end else if
  else if (n_servo==7){
    //Eslabon 2 "X"
    angulo = constrain(angulo,0,180);
    duty = map(angulo,0,180,pos0,pos180);
    servos1.setPWM(n_servo, 0, duty);
  }//end else if
  else if (n_servo==8){
    //Servo Abrir y Cerrar Garra
    angulo = constrain(angulo,0,1023);
    duty = map(angulo,0,1023,pos0,pos180);
    servos1.setPWM(n_servo, 0, duty);
  }//end else if
  else{
    angulo = constrain(angulo,-90,90); //CAMBIAR
    duty = map(angulo,-90,90,pos0,pos180); //CAMBIAR
    servos1.setPWM(n_servo, 0, duty);
  }//end else
}//end setServo

void loop() {
  
while(slave.available()>0){   //Condicion en donde solo se accede a Serial cuando hay dato disponible
  msg = slave.readStringUntil('\n');   //El string dentro del Serial solo se lee hasta tener salto de linea
  delay(10);
//  Serial.print("Message: ");
//  Serial.println(msg);

  String angulo_s = msg.substring(1);
  int angulo = angulo_s.toInt();
//  Serial.print("Angulo: ");
//  Serial.println(angulo);

  char eslabon = msg[0];
  
  if(eslabon=='2'){  //Controla el eslabon X2, el que esta conectado a la garra
    valx2=angulo*-1;
    String letterx="Angulo X2: ";
    String msgx2=letterx+valx2;
    Serial.println(msgx2);
    setServo(7,valx2);
    
  
  }else if(eslabon=='3'){  //Controla la rotacion de las BASE/STEPPER
    int valz3=angulo;
    String letterz="Angulo Z3: ";
    String msgz3=letterz+valz3;
    Serial.println(msgz3);
    setServo(4,valz3);
   
  }
  else if(eslabon=='1'){  //Controla el eslabon X1, el que esta conectado a la base
    int valx1=angulo*-1;
    String letterx1="Angulo X1: ";
    String msgx1=letterx1+valx1;
    Serial.println(msgx1);
    setServo(0,valx1);
    setServo(1,valx1);
   
  }
  else if(eslabon=='4'){  //Controla la el giro de la GARRA
    int valy=angulo*-1;
    String lettery="Angulo Y4: ";
    String msgy=lettery+valy;
    Serial.println(msgy);
    setServo(3,valy);
   
  }
  else if(eslabon=='5'){  //Controla el abrir y cerrar de la garra con el flexometro
    int valf=angulo;
    String letterf="Garra: ";
    String msgf=letterf+valf;
    int diff = abs(abs(prev_5) - abs(valf));
    if (diff < 300){
      Serial.println(msgf);
      setServo(8,valf); 
      prev_5 = valf;
    }
   
  }
  delay(10);
  }
}
