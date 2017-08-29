
/* Arduino Code (C) for Team Blynx's Intel RPC device  */

//Global Variable declarations
  const int trig1Pin = 11;
  const int echo1Pin = 13;
  const int vibe1Pin = 9;

  const int trig2Pin = 0;
  const int echo2Pin = 4;
  const int vibe2Pin = 3;
  
  const int LO_V_OUT = 12;

  
  const int numSamples = 25;
  const float convRatio = 0.017015;   //proportionality constant for converting elapsed time
                                      //to centimeters
  int duration1;
  float distance1;
  int outVal1;

  
  int duration2;
  float distance2;
  int outVal2;

void setup() {
  Serial.begin(115200);
  pinMode(LO_V_OUT, OUTPUT);
  digitalWrite(LO_V_OUT, HIGH);
  
  pinMode(trig1Pin, OUTPUT);
  pinMode(echo1Pin, INPUT);
  
  pinMode(trig2Pin, OUTPUT);
  pinMode(echo2Pin, INPUT);
  
  Serial.println("START");
}



void loop() {
  
  //duration1 = smooth1(readSensor(trig1Pin,echo1Pin));    //smooth function evaluates average of several values
  //distance1 = duration1*convRatio;
  //outVal1 = map(duration1, 0, 12000, 255, 48);
  //outVal1 = outVal1 > 1 ? outVal1 : 1;

  //delay(100);

  duration2 = smooth2(readSensor(trig2Pin,echo2Pin));    //smooth function evaluates average of several values
  distance2 = duration2*convRatio;
  outVal2 = map(duration2, 0, 5000, 255, 48);
  outVal2 = outVal2 > 1 ? outVal2 : 1;
  
  printStatus();

  //analogWrite(vibe1Pin, outVal2);
  analogWrite(vibe2Pin, outVal2);

  //delay(50);
  //delayMicroseconds(10);
}



int readSensor(int trigPin, int echoPin){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(20);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(100);
  digitalWrite(trigPin, LOW);

  return pulseIn(echoPin, HIGH, 12000);

}




int smooth1 (int newRead) {
  static int index = 0;
  static int count;
  static int samples[numSamples] = {0};
  static int sum = 0;
  static float avg;

  samples[index] = newRead;
  count++;
  count = count < numSamples ? count + 1 : numSamples;
  sum += newRead;
  sum -= samples[++index %= numSamples];
  avg = sum/count;

  return avg;
}

int smooth2 (int newRead) {
  static int index = 0;
  static int count;
  static int samples[numSamples] = {0};
  static int sum = 0;
  static float avg;

  samples[index] = newRead;
  count++;
  count = count < numSamples ? count + 1 : numSamples;
  sum += newRead;
  sum -= samples[++index %= numSamples];
  avg = sum/count;

  return avg;
}

void printStatus(){
  /*
  Serial.println("SENSOR 1:");
  Serial.print("duration1 = ");
  Serial.print(duration1);
  Serial.println(" microseconds");
  
  Serial.print("outVal1 = ");
  Serial.println(outVal1);

  Serial.print(distance1);
  Serial.println(" cm");
  Serial. println ("#####################");
  */
  
  
  //Serial.println("\nSENSOR 2:");

  Serial.print("duration2 = ");
  Serial.print(duration2);
  Serial.println(" microseconds");
  
  Serial.print("outVal2 = ");
  Serial.println(outVal2);

  Serial.print(distance2);
  Serial.println(" cm");
  
  Serial. println ("#####################");
}


/*
         _
     .__(.)< ("Quack. Don't mind me, I'm just a duck swimming on the source code")
      \___)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

*/
