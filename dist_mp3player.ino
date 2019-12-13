#include "DFRobotDFPlayerMini.h"
#include "SoftwareSerial.h"
const int pingPin = 6;
// SE settings.
const int folder = 1;
const int index = 2;
const int volume = 2;
//
unsigned long duration;
int cm;
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void setup()
{
  pinMode(pingPin, OUTPUT);
  Serial.begin(9600);
  mySoftwareSerial.begin(9600);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true);
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.volume(volume);
}

void loop()
{
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  duration = duration / 2;
  cm = int(duration / 29);

  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  if (cm <= 110 && cm >= 70) {
    myDFPlayer.playFolder(folder, index);
    delay(5000);
  }
  delay(100);
}
