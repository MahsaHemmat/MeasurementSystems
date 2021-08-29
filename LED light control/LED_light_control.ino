const int LED = 11; // set pin for led
const int LDR = A0; //set pin for photoresistor
//defining variables
float inputval=0; 
float outval =0; 
double Vout =0;
int Vs = 5 ;int Rref = 220;  //constant variables
double R=0; double illum ;
void setup() {
//Initialize pinModes
  pinMode(LED, OUTPUT);
  pinMode(LDR, INPUT);
  Serial.begin(9600);
}

void loop() {
    inputval = analogRead(LDR); //collecting data from input pin A0
    Vout = (inputval*Vs)/1023;  //maping the data from 0-1023 to 0-5 volts
    R = Rref*(1/(Vs/Vout-1));  //calculating R_photoresistor 
    illum =interpolation_lux(R); //obtaining the illumination attributed to the calculated R from the lookup table and interpolation
    Serial.print("R : ");
    Serial.print(R);
    Serial.print(",\t");
    Serial.print("Illumination: ");
    Serial.println(illum);
    outval = map(R, 10, 100000 , 0, 255); //maping R to 0-255
    int lightval = constrain(outval, 0,255);//the contain output values within 0-255 range
    analogWrite(LED, lightval);  //Hand the intensity to the LED
    delay (100);
}

//Defining interpolation function
double interpolation_lux(double x){
  double data[][2] = {{10,100000},{47,23000},{1400,7300},{2800,3700},{3800,1380},
 {15000,200},{17000,157},{30000,72},{75000,35},{1000000,0.1},{15000000,0.001}};
  double y1,x1,y0,x0,y,result;
  for(int i=0; i<10;i++){
      if (x>data[i][0] && x<data[i+1][0]){
        y0 = data[i][1];  //lower bound
        y1 = data[i + 1][1]; //upper bound
        x0 = data[i][0];
        x1 = data[i + 1][0];
        y = log10(y0)+((log10(y1)-log10(y0))*(log10(x)-log10(x0))/(log10(x1)-log10(x0)));
        result = pow(10,y);
      }
  }
    return result;
}
