#include <SoftwareSerial.h>

SoftwareSerial slave(0,1);
float valx=0; //variable para almacenar angulo en X
float valy=0; //variable para almacenar angulo en Y
float valz=0; //variable para almacenar angulo en Z
String msg="";


void setup() {
Serial.begin(38400);
slave.begin(38400);
}
void loop() {
 
while(slave.available()>0){   //Condicion en donde solo se accede a Serial cuando hay dato disponible
  msg = Serial.readStringUntil('\n');   //El string dentro del Serial solo se lee hasta tener salto de linea
  int axis=msg.length()-1;  //Se resta uno para poder acceder a la posicion del index del ultimo caracter
  String s_angulo = msg.substring(0,axis); //Se extrae los caracteres que tienen un numero en el String
  float angulo = s_angulo.toFloat();  //Se convierte el substring anterior a una variable tipo Float
  String completter=msg.substring(axis); //Guarda el lable de letra del string original 
  if(completter=="X"){  //Si el String es X, se guarda una variable para guardar angulo en X y se imprime en el Serial
    valx=angulo;
    Serial.println(valx);
  }
  if(completter=="Y"){ //Si el String es Y, se guarda una variable para guardar angulo en Y y se imprime en el Serial
    valy=angulo;
    Serial.println(valy);
  }
  if(completter=="Z"){
    valz=angulo;
    Serial.println(valz); //Si el String es z, se guarda una variable para guardar angulo en Z y se imprime en el Serial
  }
  
  }
  
  }
