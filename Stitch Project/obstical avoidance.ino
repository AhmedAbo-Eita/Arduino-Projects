//***************************************************************************************************************************//
//this code using for a obstacle avoidance robot that go forward and if it face any object it will avoid to crash it//
//the main components using in this robot(srevo motor-ultrasonic sensor-motor driver-dc Motors- car robot body with 4 wheels)//   
//***************************************************************************************************************************//

#include <Servo.h> // servo moter library 
#define servosignal 9
Servo myservo; // create servo object to control a servo

// Left side DC motors pins definetion
#define MotorAforword 3 
#define MotorAbackword 2
#define MotorA_PWM 5

// Right side DC motors pins definetion
#define MotorBforword 7
#define MotorBbackword 4
#define MotorB_PWM 6

// ultra sonicsensor pins definetion
#define TRIG 11
#define ECHO 12

int distance=0 ,t=0;  
// t refared to the time that ultrasonic sensor take to recive the 40K HZ wave.
// variable distance used to store the value of distance.



void setup() {
  Serial.begin(9600);
  //define servo pin 
   myservo.attach(servosignal);
   
  //define motors A pins as output .
  pinMode(MotorAforword,OUTPUT);
  pinMode(MotorAbackword,OUTPUT);
  pinMode(MotorA_PWM,OUTPUT);

  //define motors B pins as output. 
  pinMode(MotorBforword,OUTPUT);
  pinMode(MotorBbackword,OUTPUT);
  pinMode(MotorB_PWM,OUTPUT);

  //define pins of ultrasonic sensor.
  pinMode(TRIG,OUTPUT);
  pinMode(ECHO,INPUT);

  myservo.write(95);  
  
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
  delay(100);
  //Distance = (Speed of Sound * (Time/2)) = t/(1/((350*0.0001)/2))
  // the speed of sound can be calculated due to the tempreture of the atmospher and many parameters 
  // it can be calculated by the following web site: https://www.omnicalculator.com/physics/speed-of-sound 
  // after calculate the speed of sound we multiply it 0.0001 to make the units of time the same.
}

void forward(){
  
  //fuction to let robot go forward.
  analogWrite(MotorA_PWM,100); //control the speed of Motors A side 
  analogWrite(MotorB_PWM,120); //control the speed of Motors B side
  //let motor A side go forward.
  digitalWrite(MotorAforword,HIGH);
  digitalWrite(MotorAbackword,LOW);
  //let motor B side go forward.
  digitalWrite(MotorBforword,HIGH);
  digitalWrite(MotorBbackword,LOW);
  
}

void backward(){
  
  //fuction to let robot go backward.
  analogWrite(MotorA_PWM,100); //control the speed of Motors A side 
  analogWrite(MotorB_PWM,120); //control the speed of Motors B side
  //let motor A side go backward.
  digitalWrite(MotorAforword,LOW);
  digitalWrite(MotorAbackword,HIGH);
  //let motor B side go backward.
  digitalWrite(MotorBforword,LOW);
  digitalWrite(MotorBbackword,HIGH);
  delay(200);
  
}
void reverse(){
  
  //fuction to let robot go reverse its direction.
  analogWrite(MotorA_PWM,100); //control the speed of Motors A side 
  analogWrite(MotorB_PWM,120); //control the speed of Motors B side
  digitalWrite(MotorAforword,LOW);
  digitalWrite(MotorAbackword,HIGH);
  digitalWrite(MotorBforword,HIGH);
  digitalWrite(MotorBbackword,LOW);
  delay(700);

  
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
  delay(450);

  
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
  delay(450);
}

void loop() {

  //calling fo utra sonic sensor to get the distance in front of robot.
  ultrasonic();

  //conditions 
  if (distance >= 30 )
  {
    forward();         //in case of no object on front of robot go forward
  }
  else if (distance < 30)
  {
    
    // in case of there is an object in front of it 
    // rotate the ultrasonic sensor 45 degree to chech the side of robot if it clear or not 
    backward();
    nomotion();
    myservo.write(25);
    delay(300);
    ultrasonic();
    delay(300);

    //in case of no object in front of robot go forward
    if (distance >= 40)
    {
      myservo.write(95); // return ultasonic sensor to its initial pos 
      rotatright();       
      forward();
    }

    //in case of there is an  object in front of robot rotate ultra sonic sensor to another side to check if there is an object or not
    else if (distance < 40)
    {
      myservo.write(165);
      delay(300);
      ultrasonic();
      delay(300);
      

      //if there is no object rotate and go forward
      if (distance >=45 )
      {
        myservo.write(95); //reset ultra sonic sensor to its initial pose
        delay(300);
        rotatleft();
        forward();
      }
      
      //in case of there is an object in front of ultrasonic sensor the robot will go back 
      else
      {
        myservo.write(95); //reset ultra sonic sensor to its initial pose        
        delay(300);
        reverse();
      }
    }
  }
}
