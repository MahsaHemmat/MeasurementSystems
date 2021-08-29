const int encoder = 2; //set pin for encoder interruption
const int LED =13 ;   //set pin for LED
//defining variables
volatile int State=0;  //set variable for LED state
volatile int nc = 0; //counter variable 
volatile long t=0;   //set variable for  time at the moment
volatile long tp=0; //set variable for  saving 
volatile int dt=0;  //time difference between 2 interrupts in a row
volatile int N =0 ; //revs of the encoder
volatile int n = 8; //related to number of encoder rise and falls
volatile int Pos=0;   //position 0-360 degree
volatile double omega=0; //angular velocity
volatile int Position=0; //angular position
int debouncingtime =500;

void setup() {
//Initialize pinModes
  pinMode(LED, OUTPUT);
  pinMode(encoder, INPUT);
  attachInterrupt(digitalPinToInterrupt(encoder),count,CHANGE); //set the interrupt to encoder pin
  Serial.begin(9600);
  
}
void loop() {
  
}

void count(){
  if(millis()-tp>debouncingtime){
  nc++; //when encoder rises or falls
  t = millis();
  dt = t -tp; //time difference between 2 interrupts in a roe
  tp = t ;  //save millis of interrupt
  Pos = (nc*360/(n));  // calculating position 0-360
  Position = Pos+360*N;  //position
  omega = (0.785*1000)/(dt); //calculating velocity in [ rad/sec]
  Serial.print("Number of revs : ");
  Serial.print(N);
  Serial.print(",\t");
  Serial.print("angularPosition : ");
  Serial.print(Position);
  Serial.print(",\t");
  Serial.print("AngularVelocity : ");
  Serial.println(omega);
  if(nc == n){//calculating revs of the encoder
  nc=0;
  N++;
  }
  State = digitalRead(encoder);
  digitalWrite(LED,State); //LED toggling
  }
}
