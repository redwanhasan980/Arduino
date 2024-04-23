
const int lspeed = 170;
const int rspeed = 200;
const int in1= 12;
const int in2= 13;
const int in3= 7;
const int in4= 8;
const int lsc= 3;
const int rsc= 5;
const int tring_l= 11;
const int echo_l= 10;
const int tring_r= 4;
const int echo_r= 9;
const int v5=2;
const int conspeed=250;
float P=0,I=0,D=0;
unsigned long starttime;
unsigned long currenttime;
long duration_l;
int distance_l;
long duration_r;
int distance_r;

void setup() {
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(lsc,OUTPUT);
  pinMode(rsc,OUTPUT);
  //sonar_right
    pinMode(tring_r, OUTPUT); 
    pinMode(echo_r, INPUT); 
  //sonar_l
    pinMode(tring_l, OUTPUT); 
    pinMode(echo_l, INPUT); 
   Serial.begin(9600);

}


void forward()
{
  digitalWrite(in1,1);
  digitalWrite(in2,0);
  digitalWrite(in3,1);
  digitalWrite(in4,0);
   analogWrite(lsc,130);
  analogWrite(rsc,150);
 
}
void left()
{
  digitalWrite(in1,0);
  digitalWrite(in2,1);
  digitalWrite(in3,1);
  digitalWrite(in4,0);
   analogWrite(lsc,80);
  analogWrite(rsc,80);
 
}

void right()
{
  digitalWrite(in1,1);
  digitalWrite(in2,0);
  digitalWrite(in3,0);
  digitalWrite(in4,1);
  analogWrite(lsc,80);
  analogWrite(rsc,80);
 
}
void stop()
{
  digitalWrite(in1,0);
  digitalWrite(in2,0);
  digitalWrite(in3,0);
  digitalWrite(in4,0);
 
}
void sonar_l()
{
  digitalWrite(tring_l, LOW);
  delayMicroseconds(2);
  digitalWrite(tring_l, HIGH);
  delayMicroseconds(10);
  digitalWrite(tring_l, LOW);
  duration_l = pulseIn(echo_l, HIGH);
  distance_l = duration_l * 0.034 / 2;
  Serial.print("Distance_l: ");
  Serial.println(distance_l);
}
void sonar_r()
{
  digitalWrite(tring_r, LOW);
  delayMicroseconds(2);
  digitalWrite(tring_r, HIGH);
  delayMicroseconds(10);
  digitalWrite(tring_r, LOW);
  duration_r = pulseIn(echo_r, HIGH);
  distance_r = duration_r * 0.034 / 2;
  Serial.print("Distance_r: ");
  Serial.println(distance_r);
}

void loop() {
  delay(100);
    digitalWrite(v5, HIGH);
    sonar_l();
    sonar_r();
    if(distance_l<=10)
    {
     right();
     delay(500);
    }
     
     else if(distance_r<=10)
      {
         left();
         delay(500);
    }
      else
       {
     forward();
     Serial.println("f");
    }
      

  
}