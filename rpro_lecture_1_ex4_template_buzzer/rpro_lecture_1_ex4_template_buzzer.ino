#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4Buzzer buzzer;

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  delay(1000);
  victory();
  delay(4000);
}

void victory(){
    buzzer.playNote(NOTE_E(4), 350, 15);
    delay(400);
    buzzer.playNote(NOTE_E(4), 200, 15);
    delay(200);
    buzzer.playNote(NOTE_G(4), 400, 15);
    delay(400);
    buzzer.playNote(NOTE_E(4), 200, 15);
    delay(200);
    buzzer.playNote(NOTE_G(4), 400, 15);
    delay(400);
}
