#include <SoftwareSerial.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>



SoftwareSerial slave(10,11);

int valx1=0;
int valx2=0;
int valy2=0;//variable para almacenar angulo en X

String msg="";

Adafruit_PWMServoDriver servos1 = Adafruit_PWMServoDriver(0x40);
unsigned int pos0=102; //ancho en pulso de cuentas para 0 grados, DEPENDE DEL MOTOR
unsigned int pos180=511; //ancho en pulso de cuentas para 180 grados
int tiempo = 100;



void setup() {
Serial.begin(38400);
slave.begin(38400);
servos1.begin();
  servos1.setPWMFreq(50);
  
}

void setServo(uint8_t n_servo, int angulo){
  int duty;
  duty = map(angulo,-90,90,pos0,pos180);
  servos1.setPWM(n_servo, 0, duty);
}

void loop() {
  
 
while(slave.available()>0){   //Condicion en donde solo se accede a Serial cuando hay dato disponible
  msg = slave.readStringUntil('\n');   //El string dentro del Serial solo se lee hasta tener salto de linea
  delay(10);
  int axis=msg.length()-1;  //Se resta uno para poder acceder a la posicion del index del ultimo caracter
  String s_angulo = msg.substring(0,axis-1); //Se extrae los caracteres que tienen un numero en el String
  
  float angulo = s_angulo.toFloat();  //Se convierte el substring anterior a una variable tipo Float
  String completter=msg.substring(axis); //Guarda el lable de letra del string original 
  int eslabon=completter.toInt();
  if(eslabon==2){  //Si el String es X, se guarda una variable para guardar angulo en X y se imprime en el Serial
    valx2=angulo;
    String letterx="Angulo X2: ";
    String msgx2=letterx+valx2;
    Serial.println(msgx2);
    setServo(0,valx2);
    
  
  }else if(eslabon==3){  //Si el String es X, se guarda una variable para guardar angulo en X y se imprime en el Serial
    int valz3=angulo;
    String letterz="Angulo Z3: ";
    String msgz3=letterz+valz3;
    Serial.println(msgz3);
   
  }
  else if(eslabon==1){  //Si el String es X, se guarda una variable para guardar angulo en X y se imprime en el Serial
    int valx1=angulo;
    String letterx1="Angulo X1: ";
    String msgx1=letterx1+valx1;
    Serial.println(msgx1);
   
  }
  else if(eslabon==4){  //Si el String es X, se guarda una variable para guardar angulo en X y se imprime en el Serial
    int valy=angulo;
    String lettery="Angulo y: ";
    String msgy=lettery+valy;
    Serial.println(msgy);
   
  }
  delay(10);
  }
}
