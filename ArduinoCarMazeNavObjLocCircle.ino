const int LBack =4;
const int LFor =7;
const int RBack =8;
const int RFor =12;
const int RS =10;
const int LS =11;
int d;
int r;
int l;
int x;
int R;
int L;
int X;
float s;
float S;
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04
void findDist(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.println();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  Serial.println();
  return(distance);
  delay(1000);
}
void carControl(int s, int d, int x) {
  //s = 100;
  S = map(s, 0, 100, 0, 255);
  // x is from -100 to 100
  // at x = -23 the car is going straight
  //x = 0;
  //d = 1 for forward 0 for backward, 2 for stopped
  //d = 2;
  X = map(x, 0, 100, 0, s);
  if (x > 0) {
    if (d==0) {
        //R = s-X;
        r = s-X;
        R = map(r, 0, 100, 0, 255);
        //r = s*X;
        //R = 255-r;
        analogWrite(RS, R);
        digitalWrite(RFor, HIGH);
        digitalWrite(RBack, LOW);
        //Serial.println(R);
        digitalWrite(LFor, HIGH);
        digitalWrite(LBack, LOW);
        analogWrite(LS, S*0.95);
    }
    else if (d == 1){
        //R = S-X;
        r = s-X;
        R = map(r, 0, 100, 0, 255);
        //r = s*X;
        //R = 255-r;
        analogWrite(RS, R);
        digitalWrite(RBack, HIGH);
        digitalWrite(RFor, LOW);
        //Serial.println(R);
        digitalWrite(LBack, HIGH);
        digitalWrite(LFor, LOW);
        analogWrite(LS, S*0.95);
    }
    else if (d == 2){
        digitalWrite(LBack, LOW);
        digitalWrite(LFor, LOW);
        digitalWrite(RBack, LOW);
        digitalWrite(RFor, LOW);
    }
    
  }
  else if (x < 0){
    if (d==0){
        //L = S+X;
        l = s+X;
        L = map(l, 0, 100, 0, 255);
        //l = (-1*(s*X));
        //L = 255-l;
        analogWrite(LS, L*0.95);
        digitalWrite(LFor, HIGH);
        digitalWrite(LBack, LOW);
        //Serial.println(L);
        digitalWrite(RFor,HIGH);
        digitalWrite(RBack, LOW);
        analogWrite(RS, S);
    }
    else if (d == 1){
        //L = S+X;
        l = s+X;
        L = map(l, 0, 100, 0, 255);
        //l = (-1*(s*X));
        //L = 255-l;
        //Serial.println(L);
        analogWrite(LS, L*0.95);
        digitalWrite(LBack, HIGH);
        digitalWrite(LFor, LOW);
        //Serial.println(L);
        digitalWrite(RBack, HIGH);
        digitalWrite(RFor, LOW);
        analogWrite(RS, S);
    }
    else if (d == 2){
        digitalWrite(LBack, LOW);
        digitalWrite(LFor, LOW);
        digitalWrite(RBack, LOW);
        digitalWrite(RFor, LOW);
    }
  }
  else if (x == 0){
    if (d==0){
        analogWrite(LS, S*0.95);
        //analogWrite(LS, 196);
        digitalWrite(LFor, HIGH);
        digitalWrite(LBack, LOW);
        digitalWrite(RFor,HIGH);
        digitalWrite(RBack, LOW);
        //analogWrite(RS, 255);
        analogWrite(RS, S);

    }
    else if (d == 1){
        analogWrite(LS, S*0.95);
        //analogWrite(LS, 230);
        digitalWrite(LBack, HIGH);
        digitalWrite(LFor, LOW);
        digitalWrite(RBack, HIGH);
        digitalWrite(RFor, LOW);
        //analogWrite(RS, 255);
        analogWrite(RS, S);
        
    }
    else if (d == 2){
        digitalWrite(LBack, LOW);
        digitalWrite(LFor, LOW);
        digitalWrite(RBack, LOW);
        digitalWrite(RFor, LOW);
  }
  }
}
  
// defines variables


void setup() {
  // put your setup code here, to run once:
  pinMode(LFor, OUTPUT);
  pinMode(LBack, OUTPUT);
  pinMode(RFor, OUTPUT);
  pinMode(RBack, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600);
}

//                                                                 
void loop() {
  //carControl(s, d, x);
  //speed:
  //s = 100;
  // turn angle:
  //x = 0;
  //direction
  //d = 1 for forward, 0 for backward, 2 for stopped
  //d = 2;
  /*
  //Maze Code
  delay(5000);
  while(1==1) {
  findDist();
  if (distance>=15) {
  carControl(100, 1, 0);
  delay(500);
  carControl(0, 2, 0);
  delay(200);
  }
  else if (distance<15) {
     carControl(100, 0, 0);
     delay(500);
     carControl(100, 1,-100);
     delay(700);
     carControl(100, 0, 0);
     delay(200);
     findDist();
     delay(100);
     if (distance>40){
      carControl(100, 1, 0);
      delay(500);
     }
     else {
      carControl(100, 1, 100);
      delay(350);
      carControl(100, 0, 0);
      delay(200);
      findDist();
      delay(100);
      if (distance>40){
        carControl(100, 1, 0);
        delay(500);
      }
      else {
        carControl(100, 1, 100);
        delay(350);
        carControl(100, 0, 0);
        delay(200);
        findDist();
        delay(100);
          if (distance>40){
             carControl(100, 1, 0);
               delay(500);
      }
          else {
             carControl(100, 1, 100);
             delay(350);
             carControl(100, 0, 0);
             delay(200);
             findDist();
             delay(100);
             if (distance>40){
               carControl(100, 1, 0);
               delay(500);
      }
             else {
               carControl(100, 1, 100);
               delay(350);
               carControl(100, 0, 0);
               delay(200);
               findDist();
               delay(100);
               if (distance>40){
               carControl(100, 1, 0);
               delay(500);
               }
               else {
                   carControl(100, 1, 100);
                   delay(350);
                   carControl(100, 0, 0);
                   delay(200);
                   findDist();
                   delay(100);
               if (distance>40){
                   carControl(100, 1, 0);
                   delay(500);
               }
                   else {
                       carControl(100, 1, 100);
                       delay(350);
                       carControl(100, 0, 0);
                       delay(200);
                       findDist();
                       delay(100);
                   if (distance>40){
                       carControl(100, 1, 0);
                       delay(500);
                   }
                       else {
                           carControl(100, 1, 100);
                           delay(350);
                           carControl(100, 0, 0);
                           delay(200);
                           findDist();
                           delay(100);
                       if (distance>40){
                           carControl(100, 1, 0);
                           delay(500);
                       }
                           else {
                               carControl(100, 1, 100);
                               delay(350);
                               carControl(100, 0, 0);
                               delay(200);
                               findDist();
                               delay(100);
                           if (distance>40){
                               carControl(100, 1, 0);
                               delay(500);
     }
     }
     }
  }
     }
  }
  }
}
     }
  }
  }
}
*/

//Find Object Code
delay(5000);
  while(1==1) {
  findDist();
/*
  if (distance<=30){
    carControl(100, 1, 0);
    delay(100);
    carControl(100, 1, -100);
    delay(630);
    carControl(100, 2, 0);
    delay(500);
    carControl(100, 1, 40);
    delay(7100);
    carControl(100, 2, 0);
    delay(500);
    carControl(100, 1, -100);
    delay(640);
    carControl(100, 2, 0);
    delay(200);
    carControl(100, 1, 0);
    delay(800);
  }
  */
  if (distance<=350) {
  carControl(100, 1, 0);
  delay(1000);
  carControl(0, 2, 0);
  delay(200);
  }
  else if (distance>350) {
     carControl(100, 0, 0);
     delay(500);
     carControl(100, 1,-100);
     delay(700);
     carControl(100, 0, 0);
     delay(200);
     findDist();
     delay(100);
     if (distance<350){
      carControl(100, 1, 0);
      delay(500);
     }
     else {
      carControl(100, 1, 100);
      delay(350);
      carControl(100, 0, 0);
      delay(200);
      findDist();
      delay(100);
      if (distance<350){
        carControl(100, 1, 0);
        delay(500);
      }
      else {
        carControl(100, 1, 100);
        delay(350);
        carControl(100, 0, 0);
        delay(200);
        findDist();
        delay(100);
          if (distance<350){
             carControl(100, 1, 0);
               delay(500);
      }
          else {
             carControl(100, 1, 100);
             delay(350);
             carControl(100, 0, 0);
             delay(200);
             findDist();
             delay(100);
             if (distance<350){
               carControl(100, 1, 0);
               delay(500);
      }
             else {
               carControl(100, 1, 100);
               delay(350);
               carControl(100, 0, 0);
               delay(200);
               findDist();
               delay(100);
               if (distance<350){
               carControl(100, 1, 0);
               delay(500);
               }
               else {
                   carControl(100, 1, 100);
                   delay(350);
                   carControl(100, 0, 0);
                   delay(200);
                   findDist();
                   delay(100);
               if (distance<350){
                   carControl(100, 1, 0);
                   delay(500);
               }
                   else {
                       carControl(100, 1, 100);
                       delay(350);
                       carControl(100, 0, 0);
                       delay(200);
                       findDist();
                       delay(100);
                   if (distance<350){
                       carControl(100, 1, 0);
                       delay(500);
                   }
                       else {
                           carControl(100, 1, 100);
                           delay(350);
                           carControl(100, 0, 0);
                           delay(200);
                           findDist();
                           delay(100);
                       if (distance<350){
                           carControl(100, 1, 0);
                           delay(500);
                       }
                           else {
                               carControl(100, 1, 100);
                               delay(350);
                               carControl(100, 0, 0);
                               delay(200);
                               findDist();
                               delay(100);
                           if (distance<350){
                               carControl(100, 1, 0);
                               delay(500);
     }
     }
     }
  }
     }
  }
  }
}
     }
  }
  }
  
  /*
//circle code
delay(5000);
carControl(100, 1, 0);
delay(100);
carControl(100, 1, -100);
delay(630);
carControl(100, 2, 0);
delay(500);
carControl(100, 1, 40);
delay(7100);
carControl(100, 2, 0);
delay(500);
carControl(100, 1, -100);
delay(640);
carControl(100, 2, 0);
*/
exit(0);
}
