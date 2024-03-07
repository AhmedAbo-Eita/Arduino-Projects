//***************************************************************************************************************************//
//this code using to move the car robot using mobile application//
//the main components using in this robot(blutooth module-motor driver-dc Motors- car robot body with 4 wheels-power supply)//   
//***************************************************************************************************************************//

// Left side DC motors pins definetion
#define MotorAforword 3 
#define MotorAbackword 2
#define MotorA_PWM 5

// Right side DC motors pins definetion
#define MotorBforword 7
#define MotorBbackword 4
#define MotorB_PWM 6


//variable to store the recived input0
char state = '0' ;

void setup() {

  Serial.begin(9600);

  //define motors A pins as output .
  pinMode(MotorAforword,OUTPUT);
  pinMode(MotorAbackword,OUTPUT);
  pinMode(MotorA_PWM,OUTPUT);

  //define motors B pins as output. 
  pinMode(MotorBforword,OUTPUT);
  pinMode(MotorBbackword,OUTPUT);
  pinMode(MotorB_PWM,OUTPUT);
}
void forward(){
  
  //fuction to let robot go forword.
  analogWrite(MotorA_PWM,140); //control the speed of Motors A side 
  analogWrite(MotorB_PWM,160); //control the speed of Motors B side
  //let motor A side go forward.
  digitalWrite(MotorAforword,HIGH);
  digitalWrite(MotorAbackword,LOW);
  //let motor B side go forward.
  digitalWrite(MotorBforword,HIGH);
  digitalWrite(MotorBbackword,LOW);
  
}

void backward(){
  
  //fuction to let robot go backward.
  analogWrite(MotorA_PWM,140); //control the speed of Motors A side 
  analogWrite(MotorB_PWM,160); //control the speed of Motors B side
  digitalWrite(MotorAforword,LOW);
  digitalWrite(MotorAbackword,HIGH);
  digitalWrite(MotorBforword,LOW);
  digitalWrite(MotorBbackword,HIGH);
  
  
}

void nomotion(){

  //fuction to let robor stop.
  //let motor A side stop.
  digitalWrite(MotorAforword,LOW);
  digitalWrite(MotorAbackword,LOW);
  //let motor B side stop.
  digitalWrite(MotorBforword,LOW);
  digitalWrite(MotorBbackword,LOW);
  
}

void rotatleft(){
  
  //fuction to let robot go backward.
  analogWrite(MotorA_PWM,100); //control the speed of Motors A side 
  analogWrite(MotorB_PWM,100); //control the speed of Motors B side
  //let motor A side go forward.
  digitalWrite(MotorAforword,LOW);
  digitalWrite(MotorAbackword,HIGH);
  //let motor B side go backward.
  digitalWrite(MotorBforword,HIGH);
  digitalWrite(MotorBbackword,LOW);
  
  
}

void rotatright(){
  
  //fuction to let robot go backward.
  analogWrite(MotorA_PWM,100); //control the speed of Motors A side 
  analogWrite(MotorB_PWM,100); //control the speed of Motors B side
  //let motor A side go backward.
  digitalWrite(MotorAforword,HIGH);
  digitalWrite(MotorAbackword,LOW);
  //let motor B side go forward.
  digitalWrite(MotorBforword,LOW);
  digitalWrite(MotorBbackword,HIGH);
  
  
}
void loop() {
 //  condition to call the needed function when the user push certain button0
  if(Serial.available()){
      state = Serial.read();
  }  
  
  if(state == 'f') // when the app send 'f' the robot go forward
  {
    forward();
  }
  
  else if(state == 'b') // when the app send 'b' the robot go backward
  {
    backward();
  }

  else if(state == 'r') // when the app send 'r' the robot rotate right
  {
    rotatright();
  }  
  
  else if(state == 'l') // when the app send 'l' the robot rotate right
  {
    rotatleft();
  }  
  else {
  nomotion(); // if there is no input the robot stop 
  }
}
