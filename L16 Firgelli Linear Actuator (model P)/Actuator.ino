/*
 * ver 1.1
 * A program to control the linear actuator and print
 * its displacement to the output channel.
 *
 * Changelog:
 * 1) Resolved stalling issues.
 * 2) Readings are now scaled down to 100mm.
 * 
 * Known issues:
 * 1) Readings update too fast which may reduce reliability
 *    of the measurments.
 * 2) Readings never reach the 100mm mark. Max reading
 *    is 98mm for some reason.
 * 
*/

byte black = 10;      //black wire
byte red = 6;         //red wire
byte blue = A1;       //analogRead wire
byte yellow = 12;     //high reference rail
bool button;          //button attached to (pin 9)
byte buttonState = 1; //state trigger 

// ------------------- Arduino Functions -------------------

void setup() {

  Serial.begin(9600);
  pinMode(black, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(blue, INPUT);
  pinMode(yellow, OUTPUT);

}

void loop() {
  button = digitalRead(9);
  if (button == false) {
    buttonState++;
    delay(500);
    if (buttonState > 1) {
      buttonState = 0;
    }
  }

  switch (buttonState) {
    case 1:
      extendArm();
      break;

    case 0:
      pullArm();
      break;
  }

}

//--------------------- Functions ---------------------

// extending state
void extendArm() {
  digitalWrite(yellow, HIGH);
  digitalWrite(black, HIGH);
  digitalWrite(red, LOW);

  // read displacement
  unsigned int displacement = analogRead(blue);
  displacement = map(displacement, 0, 1023, 0, 100);
  displacement = constrain(displacement, 0, 100);

  // print displacement
  Serial.print("Displacement= ");
  Serial.print(displacement);
  Serial.println("mm");

}

// retracting state
void pullArm() {
  digitalWrite(yellow, HIGH);
  digitalWrite(black, LOW);
  digitalWrite(red, HIGH);

  // read displacement
  unsigned int displacement = analogRead(blue);
  displacement = map(displacement, 0, 1023, 0, 100);
  displacement = constrain(displacement, 0, 100);

  // print displacement
  Serial.print("Displacement= ");
  Serial.print(displacement);
  Serial.println("mm");

}

