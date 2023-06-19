#include <Servo.h>

//CONFIGURAÇÕES BASICAS
#define pinServo 8

#define pinSensorDir A1
#define pinSensorEsq A0

#define noite false
#define dia true

#define posServoNoite 90

#define valorNoite 100

Servo servo;

bool estadoDia = noite;
int anguloServo = posServoNoite;

void setup(){
	pinMode(pinSensorDir, INPUT);
	pinMode(pinSensorEsq, INPUT);
  
 	servo.attach(pinServo);
  
  	Serial.begin(9600);
}

void loop(){
  
  //altera o estado do dia de acordo com o retorno da função
  // verificarNoite(); 
  estadoDia = !verificarNoite();
  
  //condição para fazer a movimentação do servo
  if(estadoDia){
  	servo.write(constrain(anguloServo, 0, 180));
    
    anguloServo += comparaValorLDR();
    
  }else{
  	servo.write(posServoNoite);
  }
  
  Serial.println(comparaValorLDR());
  
  delay(20);
}


//COMPARA O VALOR QUE OS DOIS LDRs ESTÃO GERANDO
//FAZ COM QUE A POSIÇÃO DO SERVO MOTOR MUDE 
// 1 GIRA PARA DIREITA
// -1 GIRA PARA ESQUERDA
// 0 POSIÇÃO INICIAL (COMO SE ESTIVESSE "CENTRALIZADO")
int comparaValorLDR(){
  int valorDireita = analogRead(pinSensorDir);
  int valorEsquerda = analogRead(pinSensorEsq);
    
  if(valorDireita > valorEsquerda){
    return 1;
  }else if(valorDireita < valorEsquerda){
  	return -1;
  } else{
  	return 0;
  }
}

//VERIFICA A LUMINOSIDADE TOTAL DO AMBIENTE
//SE O VALOR FOR MENOR QUE 100 SIGNIFICA QUE ESTÁ DE NOITE
bool verificarNoite(){
 
  int valorDireita = analogRead(pinSensorDir);
  int valorEsquerda = analogRead(pinSensorEsq);
  
  return(valorDireita < valorNoite && valorDireita < valorNoite);
 

}
