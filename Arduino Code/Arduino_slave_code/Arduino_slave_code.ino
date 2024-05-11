#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial slave(0,1);
Servo servo_1;
Servo servo_2;
int valx=0; //variable para almacenar angulo en X
int valy=0; //variable para almacenar angulo en Y
int valz=0; //variable para almacenar angulo en Z
String msg="";


void setup() {
Serial.begin(38400);
slave.begin(38400);
servo_1.attach(9);
servo_2.attach(10);
}
void loop() {
 
while(slave.available()>0){   //Condicion en donde solo se accede a Serial cuando hay dato disponible
  msg = Serial.readStringUntil('\n');   //El string dentro del Serial solo se lee hasta tener salto de linea
  delay(10);
  int axis=msg.length()-1;  //Se resta uno para poder acceder a la posicion del index del ultimo caracter
  String s_angulo = msg.substring(0,axis); //Se extrae los caracteres que tienen un numero en el String
  float angulo = s_angulo.toFloat();  //Se convierte el substring anterior a una variable tipo Float
  String completter=msg.substring(axis); //Guarda el lable de letra del string original 
  
  if(completter=="X"){  //Si el String es X, se guarda una variable para guardar angulo en X y se imprime en el Serial
    valx=angulo;
    String letterx="Angulo X: ";
    String msgx=letterx+valx;
    Serial.println(msgx);
    servo_1.write(valx);
  }else if(completter=="Y"){ //Si el String es Y, se guarda una variable para guardar angulo en Y y se imprime en el Serial
    valy=angulo;
    String lettery="Angulo Y: ";
    String msgy=lettery+valy;
    Serial.println(msgy);
    
  }else if(completter=="Z"){
    valz=angulo;
    String letterz="Angulo Z: ";
    String msgz=letterz+valz;
    Serial.println(msgz);
    servo_2.write(valz);
     //Si el String es z, se guarda una variable para guardar angulo en Z y se imprime en el Serial
  }
  
  
  }
  delay(100);
  }
