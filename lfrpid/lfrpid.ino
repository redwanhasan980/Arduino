 float kp=50;
float ki=0;
float kd=25;
const int lspeed = 170;
const int rspeed = 200;
const int in1= 8;
const int in2= 9;
const int in3= 11;
const int in4= 12;
const int lsc= 3;
const int rsc= 5;
const int conspeed=250;
float P=0,I=0,D=0;
float error=0,prror=0,pI=0,pid=0,lms,rms;
int s1,s2,s3,s4,s5,s6,lasterror;
int maxsens[7];
int minsens[7];
unsigned long starttime;
unsigned long currenttime;

void setup() {
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(lsc,OUTPUT);
  pinMode(rsc,OUTPUT);

  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);
  Serial.begin(9600);

 //calabaration
for(int i=1;i<7;i++)
 maxsens[i]=0;
 for(int i=1;i<7;i++)
  minsens[i]=2000;
 starttime=millis();

 while((currenttime-starttime)<=8500)
 {   analogWrite(lsc,lspeed);
       analogWrite(rsc,rspeed);
      digitalWrite(in1,1);
  digitalWrite(in2,0);
  digitalWrite(in3,0);
  digitalWrite(in4,0);
  s1=analogRead(A0);
  if(s1> maxsens[1])
    maxsens[1]=s1;
   else if(s1<minsens[1])
    minsens[1]=s1;

 s2=analogRead(A1);
  if(s2> maxsens[2])
    maxsens[2]=s2;
 else if(s2<minsens[2])
    minsens[2]=s2;
 s3=analogRead(A2);
  if(s3> maxsens[3])
    maxsens[3]=s3;
     else if(s3<minsens[3])
      minsens[3]=s3;
 s4=analogRead(A3);
  if(s4> maxsens[4])
    maxsens[4]=s4;
     else if(s4<minsens[4])
    minsens[4]=s4;
 s5=analogRead(A4);
  if(s5> maxsens[5])
    maxsens[5]=s5;
     else if(s5<minsens[5])
    minsens[5]=s5;
 s6=analogRead(A5);
   if(s6> maxsens[6])
  maxsens[6]=s6;
     else if(s6<minsens[6])
    minsens[6]=s6;
    currenttime = millis(); 
 }
   
   
   
  for(int i=1;i<7;i++)
   maxsens[i]=(maxsens[i]+minsens[i])/2;

}

void read()
{
 s1=analogRead(A0);
 s2=analogRead(A1);
 s3=analogRead(A2);
 s4=analogRead(A3);
 s5=analogRead(A4);
 s6=analogRead(A5);

  

 if(s1>maxsens[1])s1=1;
  else s1=0;
  if(s2>maxsens[2])s2=1;
  else s2=0;
  if(s3>maxsens[3])s3=1;
  else s3=0;
  if(s4>maxsens[4])s4=1;
  else s4=0;
  if(s5>maxsens[5])s5=1;
  else s5=0;
  if(s6>maxsens[6])s6=1;
  else s6=0;

}
void calcerror()
{
  if(s1==1&&s2==0&&s3==0&&s4==0&&s5==0&&s6==0)
  error=5;
   else if(s1==1&&s2==1&&s3==0&&s4==0&&s5==0&&s6==0)
  error=4;
   else if(s1==0&&s2==1&&s3==0&&s4==0&&s5==0&&s6==0)
  error=3;
  else if(s1==0&&s2==1&&s3==1&&s4==0&&s5==0&&s6==0)
  error=2;
   else if(s1==0&&s2==0&&s3==1&&s4==0&&s5==0&&s6==0)
  error=1;
  else if(s1==0&&s2==0&&s3==1&&s4==1&&s5==0&&s6==0)
  error=0;
  else if(s1==0&&s2==0&&s3==0&&s4==1&&s5==0&&s6==0)
  error=-1;
  else if(s1==0&&s2==0&&s3==0&&s4==1&&s5==1&&s6==0)
  error=-2;
  else if(s1==0&&s2==0&&s3==0&&s4==0&&s5==1&&s6==0)
  error=-3;
  else if(s1==0&&s2==0&&s3==0&&s4==0&&s5==1&&s6==1)
  error=-4;
  else if(s1==0&&s2==0&&s3==0&&s4==0&&s5==0&&s6==1)
  error=-5;
  else if((s3==1&&s4==0&&s5==1)||(s4==1&&s5==0&&s6==1)||(s3==1&&s5==0&&s6==1)||(s3==1&&s4==0&&s6==1)||(s3==1&&s4==0&&s5==0&&s6==1)||(s2==1&&s3==0&&s4==1&&s5==1))
  error=201;
  else if((s1==1&&s2==0&&s3==1)||(s2==1&&s3==0&&s4==1)||(s1==1&&s3==0&&s4==1)||(s1==1&&s2==0&&s4==1)||(s1==1&&s2==0&&s3==0&&s4==1)||(s2==1&&s3==1&&s4==0&&s5==1))
  error=202;
   else if(s1==0&&s2==0&&s3==0&&s4==0&&s5==0&&s6==0)
  error=404;
  else if(s1==1&&s2==1&&s3==1&&s5==0&&s6==0)
  error=100;
  else if(s1==0&&s2==0&&s4==1&&s5==1&&s6==1)
  error=-101;
  

 
  

}
void calcpid()
{
  P=error;
  
  I+=error;
  D=error-prror;
  pid=kp*P+ki*I+kd*D;
  prror=error;


}
void forward()
{
  digitalWrite(in1,1);
  digitalWrite(in2,0);
  digitalWrite(in3,1);
  digitalWrite(in4,0);
 


}
void motor()
{
  
  
    lms=lspeed-pid;
    rms=rspeed+pid;
   
  
   if(lms>conspeed)
     lms=conspeed;
     if(lms<-conspeed)
     lms=-conspeed;
       if(rms>conspeed)
     rms=conspeed;
     if(rms<-conspeed)
     rms=-conspeed;

     analogWrite(lsc,lms);
       analogWrite(rsc,rms);
       forward();

}

void sharpleft()
{  forward();
    delay(500);
    
   while(1)
   {read();
    calcerror();
    if(error==0||error==-1||error==1)
    break;
    digitalWrite(in1,0);
  digitalWrite(in2,1);
  digitalWrite(in3,1);
  digitalWrite(in4,0);
  analogWrite(lsc,200);
  analogWrite(rsc,200);
      
   }

}
void sharpright()
{
    forward();
    delay(500);
   while(1)
   {read();
    calcerror();
    if(error==0||error==-1||error==1)
    break;
    digitalWrite(in1,1);
  digitalWrite(in2,0);
  digitalWrite(in3,0);
  digitalWrite(in4,1);
  analogWrite(lsc,200);
  analogWrite(rsc,200);
    Serial.println(error);
      
   }

}
void ruturn()
{
    forward();
    delay(800);
   while(1)
   {read();
    calcerror();
    if(error==0||error==-1||error==1)
    break;
    digitalWrite(in1,1);
  digitalWrite(in2,0);
  digitalWrite(in3,0);
  digitalWrite(in4,1);
  analogWrite(lsc,200);
  analogWrite(rsc,200);
    Serial.println(error);
      
   }

}
void luturn()
{  forward();
    delay(800);
    
   while(1)
   {read();
    calcerror();
    if(error==0||error==-1||error==1)
    break;
    digitalWrite(in1,0);
  digitalWrite(in2,1);
  digitalWrite(in3,1);
  digitalWrite(in4,0);
  analogWrite(lsc,200);
  analogWrite(rsc,200);
      
   }

}
void uturn()
  {
   if(lasterror<0)
   {
    while(1)
   {read();
    calcerror();
    if(error==0||error==-1||error==1)
    break;
    digitalWrite(in1,1);
  digitalWrite(in2,0);
  digitalWrite(in3,0);
  digitalWrite(in4,1);
  analogWrite(lsc,150);
  analogWrite(rsc,150);
  Serial.print("tr ");
  Serial.println(lasterror);
   }
   
      
   }
   else
   {

    while(1)
   {read();
    calcerror();
    if(error==0||error==-1||error==1)
    break;
    digitalWrite(in1,0);
  digitalWrite(in2,1);
  digitalWrite(in3,1);
  digitalWrite(in4,0);
  analogWrite(lsc,150);
  analogWrite(rsc,150);
  
   Serial.print("lr ");
   Serial.println(lasterror);
   }
   
   }

  

}

void loop() {
  
 
  read();
   calcerror();
   if(error!=0&&error!=404)
   lasterror=error;
     if(error==201)
     {
       //right uturn
       ruturn();
     }
     else if(error==202)
     {
       //left uturn
       luturn();
     }
  
   else if(error==100)
    sharpleft();
 else if(error==-101)
     sharpright();
     else if(error==404)
     uturn();
    
    
 else
 {
  calcpid();
  motor();
 }
 


 Serial.print(error);
  Serial.print(" ");
   Serial.print(lasterror);
  Serial.print(" ");
  Serial.print(lms);
  Serial.print(" ");
  Serial.println(rms);



}