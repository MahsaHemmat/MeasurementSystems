//set the pin number for buttons and LED
int startbtn =2;
int restartbtn =3;
int LED = 8;
long t3 = 0;    
volatile int j = 1;  //counter variable
volatile long a = 0 ; //time variable to show
volatile long c ;   //variable to save start time
volatile long b ;   //variable to save stop time
volatile long t1;
volatile long t2;
int debouncingt =200;
volatile long mic = 0 ;
volatile int mil = 0;
void setup() {
  //set pin modes
  pinMode(LED,OUTPUT);
  Serial.begin(9600);
  pinMode(startbtn,INPUT_PULLUP);
  pinMode(restartbtn,INPUT_PULLUP);
  //set interrupt on each button
  attachInterrupt(digitalPinToInterrupt(2),btnstart,FALLING);
  attachInterrupt(digitalPinToInterrupt(3),btnrestart,FALLING);
}

void loop() {
   //make LED blink every 1 sec
  if(millis()-t3 > 1000){
  digitalWrite(LED,HIGH);
  delay(300);
  digitalWrite(LED,LOW);
  delay(100);
  t3 = millis();
  }
}
void btnstart(){
  if(millis()-t1>debouncingt){//check debouncing time
  if(j%2==1){
  c = micros();
  Serial.print("STARTtime in microseconds\t" );
  Serial.print(a );
  Serial.print("\t" );
  Serial.print("STARTtime in miliseconds\t" );
  Serial.print(mil);
  Serial.print("." );
  Serial.println(mic );
  j++;
}
else{
  b = micros(); 
  a = ((b-c)/1000)+a;
  mic = a %1000 ; 
  mil = a / 1000;
  Serial.print("STOPtime in microseconds\t" );
  Serial.print(a );
  Serial.print("\t" );
  Serial.print("STOPtime in miliseconds \t");
  Serial.print(mil);
  Serial.print("." );
  Serial.println(mic );
  j++;
}
t1=millis();
  }
  } 
void btnrestart(){
  if(millis()-t2>debouncingt){
  Serial.println("StopWatch has been restarted:");
  a=0;
  mil = 0;
  mic =0;
  j=1;
  t2=millis();
  }
}
