

#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"
#include "user.h"
MAX30105 particleSensor;

#define LED 19

unsigned long delayStart = 0; // the time the delay started
bool delayRunning = false; // true if still waiting for delay to finish

const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred

float beatsPerMinute;
int beatAvg;

int user_bpm;
unsigned long check = millis();
unsigned long timer = 10000;
bool runTimer = false;

String user;

void getScan()
{

  long irValue = particleSensor.getIR();

  if (irValue < 50000) {
    //Serial.print(" No finger?");
    check = millis();
    return;
  }

  if (checkForBeat(irValue) == true)
  {
    //We sensed a beat!
    long delta = millis() - lastBeat;
    lastBeat = millis();

    beatsPerMinute = 60 / (delta / 1000.0);
    /*if (beatsPerMinute <= 50 || beatsPerMinute >= 140) {

      }*/
    if (beatsPerMinute < 255 && beatsPerMinute > 20)
    {

      rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
      rateSpot %= RATE_SIZE; //Wrap variable

      //Take average of readings
      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;

      if (beatAvg > 50 && beatAvg < 140) {
        runTimer = true;
      }
    }
    //delay(500);
  }

  Serial.println();
  Serial.print(", BPM=");
  Serial.print(beatsPerMinute);
  Serial.print(", Avg BPM=");
  Serial.print(beatAvg);
  Serial.println();

}

void(* resetFunc) (void) = 0; //declare reset function @ address 0

void pulseScan() { // the led task
  //unsigned long check = millis();
  if (runTimer) {
    if (millis() - check > timer) {
      //runTimer = false;
      updateUser(user, String(user_bpm));
      Serial.println(user_bpm);
      digitalWrite(LED, LOW);
      beatAvg = 0;
      runTimer = false;
      user_bpm = 0;
      Serial.println(user.length());
      user = "";
      //updateUser(
      delay(3000);
     // user = getRandomUser();
     // Serial.println("NEW USER" + user);
      return;
    } else {

    }
  }
  if(user.length() != 0){
      getScan();
  user_bpm = beatAvg;  
    }

  // check if delay has timed out after 10sec == 10000mS
  /* if (delayRunning && ((millis() - delayStart) >= 10000)) {
     delayRunning = false; // // prevent this code being run more then once
     user_bpm = beatAvg;
     Serial.println(user_bpm);
     Serial.println("Turned LED Off");
    } else {*/

  /* }*/
}

void pulseInit()
{

  /// make sure that if no lantern available dont run bpm
  ///maybe make a osc call to indicate that nothing is available and do a led anime
  pinMode(LED, OUTPUT);

  user = getRandomUser();
  Serial.println(user);
  Serial.println("Initializing...");

  // Initialize sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }
  Serial.println("Place your index finger on the sensor with steady pressure.");

  particleSensor.setup(); //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED
  digitalWrite(LED, HIGH);
  delayStart = millis();   // start delay
  delayRunning = true; // not finished yet
}
