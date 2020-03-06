#include "NewPing.h"

#define TRIGGER_PIN 10
#define ECHO_PIN 13
#define MAX_DISTANCE 400

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

float duration, distance;

int iterations = 5;
int passes = 0;
int x = 0;
int m = 0;
void setup() {

 Serial.begin(9600);
 Serial.println("hello");


}

void loop() {
  m = 0;
  x = 0;
  
  while (x != 1) {
 //räkna ut distansen
    duration = sonar.ping_median(iterations);

    distance = (duration / 2) * 0.0343;

    distance = roundf(distance*100);
    distance = distance/100;

   //Serial.print("Distance = ");
   //Serial.print(distance);
   //Serial.println(" cm");
   
//Om distansen är mindre än 10cm innebär det att tåget passerar framför sensorn. +1 till hur många gånger tåget har passerat
   if (distance < 10){
      Serial.println("Train passing");
      x = 1;
      passes = passes + 1;
    Serial.print("The train has passed ");
    Serial.print(passes);
    Serial.println(" times");
  }
 }
  
  while (x != 2) {
  
    duration = sonar.ping_median(iterations);

    distance = (duration / 2) * 0.0343;

    distance = roundf(distance*100);
    distance = distance/100;

    Serial.print(".");
//Om distansen är över 10cm innebär det att tåget inte längre befinner sig framför sensorn, detta innebär att vi bör igen leta efter när tåget befinner sig framför sensorn, kör föregående loop
   m = m + 1;
   if (m > 150) {
    Serial.println("FUCKING PASS ALREADY");
    m = 0;
   }
   if (distance > 10){
      Serial.println(" ");
      Serial.println("Train has passed");
      Serial.println(" ");
      x = 2;
  
   }
   delay(50);

  }

  delay(500);
     
}

  
