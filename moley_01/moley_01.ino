#define PIN_LED PD3
#define PID_BUZ PD2

long random_sleep;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(PID_BUZ, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {

  while(1) {
    random_sleep = random(1,6);
    digitalWrite(PID_BUZ, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(PID_BUZ, LOW);    // turn the LED off by making the voltage LOW
    delay(random_sleep * 1000);    // wait for a second
  }
}
