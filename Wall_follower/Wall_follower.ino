//Define variables for different uses
const int lspeed = 170;
const int rspeed = 200;
const int in1= 12;
const int in2= 13;
const int in3= 7;
const int in4= 8;
const int lsc= 3;
const int rsc= 5;
const int tring_f= 11;
const int echo_f= 10;
const int tring_r= 4;
const int echo_r= 9;
const int conspeed=250;
long duration_f;
int distance_f;
long duration_r;
int distance_r;
int range = 2;
int dis_wall = 7;
void setup() {
  //Setup pin mode
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(lsc,OUTPUT);
  pinMode(rsc,OUTPUT);
  //sonar_right
    pinMode(tring_r, OUTPUT); 
    pinMode(echo_r, INPUT); 
  //sonar_front
    pinMode(tring_f, OUTPUT); 
    pinMode(echo_f, INPUT); 
   Serial.begin(9600);

}

//Function to drive the bot forward
void forward()
{
  digitalWrite(in1,1);
  digitalWrite(in2,0);
  digitalWrite(in3,1);
  digitalWrite(in4,0);
   analogWrite(lsc,130);
  analogWrite(rsc,150);
 
}
//Function to turn the bot left
void left()
{
  digitalWrite(in1,0);
  digitalWrite(in2,0);
  digitalWrite(in3,1);
  digitalWrite(in4,0);
   analogWrite(lsc,80);
  analogWrite(rsc,80);
 
}
//Function to turn the bot right
void right()
{
  digitalWrite(in1,1);
  digitalWrite(in2,0);
  digitalWrite(in3,0);
  digitalWrite(in4,0);
  analogWrite(lsc,80);
  analogWrite(rsc,80);
 
}
//Function to turn the bot 90 degree left
void sharp_left()
{
  digitalWrite(in1,0);
  digitalWrite(in2,0);
  digitalWrite(in3,1);
  digitalWrite(in4,0);
   analogWrite(lsc,150);
  analogWrite(rsc,150);
  delay(500);
}
//Function to stop the bot
void stop()
{
  digitalWrite(in1,0);
  digitalWrite(in2,0);
  digitalWrite(in3,0);
  digitalWrite(in4,0);
 
}
//Take input of Forward sonar
void sonar_f()
{ 
  digitalWrite(tring_f, LOW);
  delayMicroseconds(2);
  //making sound wave pulse
  digitalWrite(tring_f, HIGH);
  delayMicroseconds(10);
  digitalWrite(tring_f, LOW);
  //taking input of time duration that take the pulse to come back to sonar
  duration_f = pulseIn(echo_f, HIGH);
  //converting time duration to distance 
  distance_f = duration_f * 0.034 / 2;
  //printing forward distance
  Serial.print("Distance_forward: ");
  Serial.println(distance_f);
}
//Take input of right sonar
void sonar_r()
{
  digitalWrite(tring_r, LOW);
  delayMicroseconds(2);
   //making sound wave pulse
  digitalWrite(tring_r, HIGH);
  delayMicroseconds(10);
  digitalWrite(tring_r, LOW);
  //taking input of time duration that take the pulse to come back to sonar
  duration_r = pulseIn(echo_r, HIGH);
   //converting time duration to distance (unit cm)
  distance_r = duration_r * 0.034 / 2;
  Serial.print("Distance_r: ");
  Serial.println(distance_r);
}
//ROBOT LOOP
void loop() {
  delay(100);
  //taking input of distance of wall forward and right
    sonar_f();
    sonar_r();
    //control logic
    if(distance_f>5)
    {
       if(distance_r<=dis_wall+range&&distance_r>=dis_wall-range)
       forward();
       else if(distance_r>dis_wall+range)
        right();
        else if(distance_r<dis_wall-range)
        left();
    }
    else
    {
          sharp_left();
    }
    
  
}