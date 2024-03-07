// ultra sonicsensor pins definetion
#define TRIG 11
#define ECHO 12

//IR sensors pins
#define IR_left A2
#define IR_right A1
#define IR_center A3

// Left side DC motors pins definetion
#define MotorAforword 3 
#define MotorAbackword 2
#define MotorA_PWM 5

// Right side DC motors pins definetion
#define MotorBforword 7
#define MotorBbackword 4
#define MotorB_PWM 6



// t refared to the time that ultrasonic sensor take to recive the 40K HZ wave.
// variable distance used to store the value of distance.
int distance=0 ,t=0;  

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
  
  // define IR senesors as input pins
  pinMode(IR_left,INPUT);
  pinMode(IR_right,INPUT);
  pinMode(IR_center,INPUT);

//define pins of ultrasonic sensor.
  pinMode(TRIG,OUTPUT);
  pinMode(ECHO,INPUT);  

}

void ultrasonic (){
  
  // first we give the TRIG pin pulse to let the ultrasonic sensor work
  // After this pulse the time (go and return)will be resived from ultrasonic sensor and stored 
  
  digitalWrite(TRIG,LOW);  
  delayMicroseconds(5);  // this delay to make the reading more stable 
  digitalWrite(TRIG,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG,LOW);
  t=pulseIn(ECHO,HIGH);
  
  // this time (t) is a time of double distance (go and return) so we divide it by 2 to get the time of the distance that we use.
  
  distance=t/(1/((340*0.0001)/2));
  Serial.println(distance);
  delay(20);
  //Distance = (Speed of Sound * (Time/2)) = t/(1/((350*0.0001)/2))
  // the speed of sound can be calculated due to the tempreture of the atmospher and many parameters 
  // it can be calculated by the following web site: https://www.omnicalculator.com/physics/speed-of-sound 
  // after calculate the speed of sound we multiply it 0.0001 to make the units of time the same.
}

void forward(){
  
  //fuction to let robot go forword.
  analogWrite(MotorA_PWM,110); //control the speed of Motors A side 
  analogWrite(MotorB_PWM,130); //control the speed of Motors B side
  // there is a diferance in PWM singnal for 2 motors because my two motors not identical.
  //let motor A side go forward.
  digitalWrite(MotorAforword,HIGH);
  digitalWrite(MotorAbackword,LOW);
  //let motor B side go forward.
  digitalWrite(MotorBforword,HIGH);
  digitalWrite(MotorBbackword,LOW);
  
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
  
  //fuction to let robot go rotate left.
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
  
  //fuction to let robot go rotat left.
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
  //calling for ultrasonic sensor to detict if there is an obistical in front of robot or not 
  ultrasonic();
  //check the values of IR sensors. these used for test cases
  Serial.println(digitalRead(IR_center));
  Serial.print(digitalRead(IR_left));
  Serial.print(digitalRead(IR_right));

  if (distance <=15) // in case of there is an object in front of the robot by 15CM or less than that, the robot will stop.
  {
    nomotion();  
  }
  else if (distance > 15){  //in case of this distace grater than 15 the line follower function starts to work.
      
    if ((digitalRead(IR_left) == 0)&&(digitalRead(IR_center) == 1)&&(digitalRead(IR_right) == 0))
    {
      // in this case there is black line under center IR sensor only so the robot go forward
     forward();
    }
    if ((digitalRead(IR_left) == 1)&&(digitalRead(IR_center) == 1)&&(digitalRead(IR_right) == 0))
    {
      // in this case there is black line under center and left IR sensor  so the robot rotate left to make robot centered above the black line
      rotatleft();
    }
    if ((digitalRead(IR_left) == 1)&&(digitalRead(IR_center) ==0)&&(digitalRead(IR_right) == 0)) 
    {
    // in this case there is black line under left IR sensor  so the robot rotate left to make robot centered above the black line
     rotatleft();
    }

    if ((digitalRead(IR_left) == 0)&&(digitalRead(IR_center) == 1)&&(digitalRead(IR_right) == 1))
    {
    // in this case there is black line under right and center IR sensor  so the robot rotate right to make robot centered above the black line
     rotatright();
    }
    if ((digitalRead(IR_left) == 0)&&(digitalRead(IR_center) == 0)&&(digitalRead(IR_right) == 1))
    {
      // in this case there is black line under right IR sensor  so the robot rotate right to make robot centered above the black line      
      rotatright();
    }
  
    if ((digitalRead(IR_left) == 1)&&(digitalRead(IR_center) == 1)&&(digitalRead(IR_right) == 1))
    { 
     nomotion();
    }  
  }
}











