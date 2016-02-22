/*
  ver 1.0
  A program to control the linear actuator and print
  its displacement to the output channel.

  Known issues:
  1) The actuator can be heared stalling when non of the
     buttons are pressed which may reduce its lifespan.
  2) Readings update too fast which may reduce reliability
     of the measurments.
  3) Readings exceed the 100mm mark (will fix later). 
*/

byte black = 10;    //black wire
byte red = 6;       //red wire
byte blue = A1;     //blue wire
byte yellow = 12;   //high reference rail
bool button1 = 0;   //call extend function (pin 8)
bool button2 = 0;   //call pull function (pin 9)

void setup() {

  Serial.begin(9600);
  pinMode(black, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(blue, INPUT);
  pinMode(yellow, OUTPUT);

}

void loop() {

  button1 = digitalRead(8);
  button2 = digitalRead(9);

  if (button1) {
    extendArm();
  }

  if (button2) {
    pullArm();
  }

}



//--------------------- Functions ---------------------

// extends arm
void extendArm() {
  digitalWrite(yellow, HIGH);
  digitalWrite(black, HIGH);
  digitalWrite(red, LOW);
  Serial.println(analogRead(blue));
}

// pulls arm
void pullArm() {
  digitalWrite(yellow, HIGH);
  digitalWrite(black, LOW);
  digitalWrite(red, HIGH);
  Serial.println(analogRead(blue));
}

